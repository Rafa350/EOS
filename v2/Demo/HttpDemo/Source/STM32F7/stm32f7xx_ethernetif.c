#include "eos.h"
#include "OSAL/osalSemaphore.h"
#include "OSAL/osalTask.h"

#include "stm32f7xx_hal.h"
#include "lwip/opt.h"
#include "lwip/timeouts.h"
#include "lwip/tcpip.h"
#include "netif/ethernet.h"
#include "netif/etharp.h"
#include <string.h>


/* Stack size of the interface thread */
#define INTERFACE_THREAD_STACK_SIZE            (350)

/* Define those to better describe your network interface. */
#define IFNAME0 's'
#define IFNAME1 't'

/*
  @Note: The DMARxDscrTab and DMATxDscrTab must be declared in a device non cacheable memory region
         In this example they are declared in the first 256 Byte of SRAM2 memory, so this
         memory region is configured by MPU as a device memory.

         In this example the ETH buffers are located in the SRAM2 with MPU configured as normal 
         not cacheable memory.   
         
         Please refer to MPU_Config() in main.c file.
 */
#if defined ( __CC_ARM   )
ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB] __attribute__((at(0x2004C000)));/* Ethernet Rx DMA Descriptors */

ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB] __attribute__((at(0x2004C080)));/* Ethernet Tx DMA Descriptors */

uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE] __attribute__((at(0x2004C100))); /* Ethernet Receive Buffers */

uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE] __attribute__((at(0x2004D8D0))); /* Ethernet Transmit Buffers */

#elif defined ( __ICCARM__ ) /*!< IAR Compiler */
  #pragma data_alignment=4 

#pragma location=0x2004C000
__no_init ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB];/* Ethernet Rx DMA Descriptors */

#pragma location=0x2004C080
__no_init ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB];/* Ethernet Tx DMA Descriptors */

#pragma location=0x2004C100
__no_init uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE]; /* Ethernet Receive Buffers */

#pragma location=0x2004D8D0
__no_init uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE]; /* Ethernet Transmit Buffers */

#elif defined ( __GNUC__ ) /*!< GNU Compiler */

ETH_DMADescTypeDef  DMARxDscrTab[ETH_RXBUFNB] __attribute__((section(".RxDecripSection")));/* Ethernet Rx DMA Descriptors */

ETH_DMADescTypeDef  DMATxDscrTab[ETH_TXBUFNB] __attribute__((section(".TxDescripSection")));/* Ethernet Tx DMA Descriptors */

uint8_t Rx_Buff[ETH_RXBUFNB][ETH_RX_BUF_SIZE] __attribute__((section(".RxarraySection"))); /* Ethernet Receive Buffers */

uint8_t Tx_Buff[ETH_TXBUFNB][ETH_TX_BUF_SIZE] __attribute__((section(".TxarraySection"))); /* Ethernet Transmit Buffers */

#endif


static HSemaphore hSemaphore = NULL;    // Notifica la recepcio de paquets.
static HTask hTask = NULL;              // Fil del process de recepcio de paquets
static ETH_HandleTypeDef EthHandle;     // Handle del modul HAL ETH


static void ethernetif_input_task(void* param);


/// ----------------------------------------------------------------------
/// \brief    Inicialitza el modul ETH
/// \param    heth: Handler.
///
void HAL_ETH_MspInit(
	ETH_HandleTypeDef* heth) {

	GPIO_InitTypeDef GPIO_InitStructure;

  	// Enable GPIOs clocks
	//
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();

	/* Ethernet pins configuration ************************************************/
	/*
        RMII_REF_CLK ----------------------> PA1
        RMII_MDIO -------------------------> PA2
        RMII_MDC --------------------------> PC1
        RMII_MII_CRS_DV -------------------> PA7
        RMII_MII_RXD0 ---------------------> PC4
        RMII_MII_RXD1 ---------------------> PC5
        RMII_MII_RXER ---------------------> PG2
        RMII_MII_TX_EN --------------------> PG11
        RMII_MII_TXD0 ---------------------> PG13
        RMII_MII_TXD1 ---------------------> PG14
	 */

	// Configure PA1, PA2 and PA7
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Alternate = GPIO_AF11_ETH;
	GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	// Configure PC1, PC4 and PC5
	//
	GPIO_InitStructure.Pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

	// Configure PG2, PG11, PG13 and PG14
	//
	GPIO_InitStructure.Pin =  GPIO_PIN_2 | GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_14;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStructure);
  
	// Enable the Ethernet global Interrupt
	//
	HAL_NVIC_SetPriority(ETH_IRQn, 0x7, 0);
	HAL_NVIC_EnableIRQ(ETH_IRQn);
  
	// Enable ETHERNET clock
	//
	__HAL_RCC_ETH_CLK_ENABLE();
}


/// ----------------------------------------------------------------------
/// \brief    Notifica el final d'una transferencio.
/// \param    heth: Handler.
///
void HAL_ETH_RxCpltCallback(
	ETH_HandleTypeDef* heth) {

	osalSemaphoreReleaseISR(hSemaphore);
}


/// ----------------------------------------------------------------------
/// \brief    Handler de la interrupcio ETH
///
void ETH_IRQHandler(void) {

	HAL_ETH_IRQHandler(&EthHandle);
}


/// ----------------------------------------------------------------------
/// \brief    Inicialitzacio
/// \param    netif: El interficie a inicialitzar.
///
static void low_level_init(
	struct netif *netif) {

	uint8_t macaddress[6]= { MAC_ADDR0, MAC_ADDR1, MAC_ADDR2, MAC_ADDR3, MAC_ADDR4, MAC_ADDR5 };
  
	EthHandle.Instance = ETH;
	EthHandle.Init.MACAddr = macaddress;
	EthHandle.Init.AutoNegotiation = ETH_AUTONEGOTIATION_ENABLE;
	EthHandle.Init.Speed = ETH_SPEED_100M;
	EthHandle.Init.DuplexMode = ETH_MODE_FULLDUPLEX;
	EthHandle.Init.MediaInterface = ETH_MEDIA_INTERFACE_RMII;
	EthHandle.Init.RxMode = ETH_RXINTERRUPT_MODE;
	EthHandle.Init.ChecksumMode = ETH_CHECKSUM_BY_HARDWARE;
	EthHandle.Init.PhyAddress = LAN8742A_PHY_ADDRESS;
  
	// Configure ethernet peripheral (GPIOs, clocks, MAC, DMA)
	//
	if (HAL_ETH_Init(&EthHandle) == HAL_OK) {

		// Set netif link flag
		//
		netif->flags |= NETIF_FLAG_LINK_UP;
	}
  
	// Initialize Tx Descriptors list: Chain Mode
	//
	HAL_ETH_DMATxDescListInit(&EthHandle, DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
     
	// Initialize Rx Descriptors list: Chain Mode
	//
	HAL_ETH_DMARxDescListInit(&EthHandle, DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);
  
	// set netif MAC hardware address length
	//
	netif->hwaddr_len = ETHARP_HWADDR_LEN;

	// set netif MAC hardware address
	//
	netif->hwaddr[0] =  MAC_ADDR0;
	netif->hwaddr[1] =  MAC_ADDR1;
	netif->hwaddr[2] =  MAC_ADDR2;
	netif->hwaddr[3] =  MAC_ADDR3;
	netif->hwaddr[4] =  MAC_ADDR4;
	netif->hwaddr[5] =  MAC_ADDR5;

	// Set netif maximum transfer unit
	//
	netif->mtu = 1500;

	// Accept broadcast address and ARP traffic
	//
	netif->flags |= NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP;

	// Create a binary semaphore used for informing ethernetif of frame reception
	//
	hSemaphore = osalSemaphoreCreate(0);

	// Create the task that handles the ETH_MAC
	//
	static char* threadName = "EthIF";
	TaskInitializeInfo taskInfo;
	taskInfo.name = threadName;
	taskInfo.function = ethernetif_input_task;
	taskInfo.params = netif;
	taskInfo.stackSize = INTERFACE_THREAD_STACK_SIZE;
	taskInfo.options = OSAL_TASK_PRIORITY_REALTIME;
	hTask = osalTaskCreate(&taskInfo);

	// Enable MAC and DMA transmission and reception
	//
	HAL_ETH_Start(&EthHandle);
}


/// ----------------------------------------------------------------------
/// \brief    This function should do the actual transmission of the packet. The packet is
///           contained in the pbuf that is passed to the function. This pbuf
///           might be chained.
///
/// \param    netif: the lwip network interface structure for this ethernetif
/// \param    p: the MAC packet to send (e.g. IP packet including MAC addresses and type)
/// \return   ERR_OK if the packet could be sent
///           an err_t value if the packet couldn't be sent
///
/// \note     Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
///           strange results. You might consider waiting for space in the DMA queue
///           to become available since the stack doesn't retry to send a packet
///           dropped because of memory failure (except for the TCP timers).
///
static err_t low_level_output(
	struct netif* netif,
	struct pbuf* p) {

	err_t errval;
	struct pbuf* q;
	uint8_t* buffer = (uint8_t*)(EthHandle.TxDesc->Buffer1Addr);
	__IO ETH_DMADescTypeDef *DmaTxDesc;
	uint32_t framelength = 0;
	uint32_t bufferoffset = 0;
	uint32_t byteslefttocopy = 0;
	uint32_t payloadoffset = 0;

	DmaTxDesc = EthHandle.TxDesc;
	bufferoffset = 0;
  
	// copy frame from pbufs to driver buffers
	//
	for (q = p; q != NULL; q = q->next) {

		// Is this buffer available? If not, goto error
		//
		if ((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET) {
			errval = ERR_USE;
			goto error;
		}
    
		// Get bytes in current lwIP buffer
		//
		byteslefttocopy = q->len;
		payloadoffset = 0;
    
		// Check if the length of data to copy is bigger than Tx buffer size
		//
		while ((byteslefttocopy + bufferoffset) > ETH_TX_BUF_SIZE ) {

			// Copy data to Tx buffer
			//
			memcpy((uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload + payloadoffset), (ETH_TX_BUF_SIZE - bufferoffset));
      
			// Point to next descriptor
			//
			DmaTxDesc = (ETH_DMADescTypeDef*)(DmaTxDesc->Buffer2NextDescAddr);
      
			// Check if the buffer is available
			//
			if ((DmaTxDesc->Status & ETH_DMATXDESC_OWN) != (uint32_t)RESET) {
				errval = ERR_USE;
				goto error;
			}
      
			buffer = (uint8_t *)(DmaTxDesc->Buffer1Addr);
      
			byteslefttocopy = byteslefttocopy - (ETH_TX_BUF_SIZE - bufferoffset);
			payloadoffset = payloadoffset + (ETH_TX_BUF_SIZE - bufferoffset);
			framelength = framelength + (ETH_TX_BUF_SIZE - bufferoffset);
			bufferoffset = 0;
		}
    
		// Copy the remaining bytes
		//
		memcpy( (uint8_t*)((uint8_t*)buffer + bufferoffset), (uint8_t*)((uint8_t*)q->payload + payloadoffset), byteslefttocopy );
		bufferoffset = bufferoffset + byteslefttocopy;
		framelength = framelength + byteslefttocopy;
	}
 
	// Prepare transmit descriptors to give to DMA
	//
	HAL_ETH_TransmitFrame(&EthHandle, framelength);
  
	errval = ERR_OK;
  
	error:
    // When Transmit Underflow flag is set, clear it and issue a Transmit Poll Demand to resume transmission
	//
	if ((EthHandle.Instance->DMASR & ETH_DMASR_TUS) != (uint32_t)RESET) {

		// Clear TUS ETHERNET DMA flag
		//
		EthHandle.Instance->DMASR = ETH_DMASR_TUS;

		// Resume DMA transmission
		//
		EthHandle.Instance->DMATPDR = 0;
	}
  
	return errval;
}

/**
  * @brief Should allocate a pbuf and transfer the bytes of the incoming
  * packet from the interface into the pbuf.
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return a pbuf filled with the received packet (including MAC header)
  *         NULL on memory error
  */
static struct pbuf* low_level_input(
	struct netif *netif) {

	struct pbuf *p = NULL, *q = NULL;
	uint16_t len = 0;
	uint8_t *buffer;
	__IO ETH_DMADescTypeDef *dmarxdesc;
	uint32_t bufferoffset = 0;
	uint32_t payloadoffset = 0;
	uint32_t byteslefttocopy = 0;
	uint32_t i=0;

	// get received frame
	//
	if (HAL_ETH_GetReceivedFrame_IT(&EthHandle) != HAL_OK)
		return NULL;
  
	/* Obtain the size of the packet and put it into the "len" variable. */
	len = EthHandle.RxFrameInfos.length;
	buffer = (uint8_t *)EthHandle.RxFrameInfos.buffer;
  
	if (len > 0) {
		/* We allocate a pbuf chain of pbufs from the Lwip buffer pool */
		p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
	}
  
	if (p != NULL) {
		dmarxdesc = EthHandle.RxFrameInfos.FSRxDesc;
		bufferoffset = 0;
    
		for(q = p; q != NULL; q = q->next) {
			byteslefttocopy = q->len;
			payloadoffset = 0;
      
			/* Check if the length of bytes to copy in current pbuf is bigger than Rx buffer size */
			while( (byteslefttocopy + bufferoffset) > ETH_RX_BUF_SIZE ) {

				/* Copy data to pbuf */
				memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset), (uint8_t*)((uint8_t*)buffer + bufferoffset), (ETH_RX_BUF_SIZE - bufferoffset));
        
				/* Point to next descriptor */
				dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
				buffer = (uint8_t *)(dmarxdesc->Buffer1Addr);
        
				byteslefttocopy = byteslefttocopy - (ETH_RX_BUF_SIZE - bufferoffset);
				payloadoffset = payloadoffset + (ETH_RX_BUF_SIZE - bufferoffset);
				bufferoffset = 0;
			}
      
			/* Copy remaining data in pbuf */
			memcpy( (uint8_t*)((uint8_t*)q->payload + payloadoffset), (uint8_t*)((uint8_t*)buffer + bufferoffset), byteslefttocopy);
			bufferoffset = bufferoffset + byteslefttocopy;
		}
	}

	/* Release descriptors to DMA */
	/* Point to first descriptor */
	dmarxdesc = EthHandle.RxFrameInfos.FSRxDesc;

	/* Set Own bit in Rx descriptors: gives the buffers back to DMA */
	for (i=0; i< EthHandle.RxFrameInfos.SegCount; i++) {
		dmarxdesc->Status |= ETH_DMARXDESC_OWN;
		dmarxdesc = (ETH_DMADescTypeDef *)(dmarxdesc->Buffer2NextDescAddr);
	}
    
	/* Clear Segment_Count */
	EthHandle.RxFrameInfos.SegCount =0;

	/* When Rx Buffer unavailable flag is set: clear it and resume reception */
	if ((EthHandle.Instance->DMASR & ETH_DMASR_RBUS) != (uint32_t)RESET) {
    
		/* Clear RBUS ETHERNET DMA flag */
		EthHandle.Instance->DMASR = ETH_DMASR_RBUS;
		/* Resume DMA reception */
		EthHandle.Instance->DMARPDR = 0;
	}
  
	return p;
}

/**
  * @brief This function is the ethernetif_input task, it is processed when a packet 
  * is ready to be read from the interface. It uses the function low_level_input() 
  * that should handle the actual reception of bytes from the network
  * interface. Then the type of the received packet is determined and
  * the appropriate input function is called.
  *
  * @param netif the lwip network interface structure for this ethernetif
  */
static void ethernetif_input_task(
	void* param) {

	struct pbuf *p;

	struct netif *netif = (struct netif *) param;
  
	while (1) {
        if (osalSemaphoreWait(hSemaphore, (unsigned) -1)) {
			do {
				LOCK_TCPIP_CORE();

				p = low_level_input(netif);
				if (p != NULL) {
					if (netif->input( p, netif) != ERR_OK )	 {
						pbuf_free(p);
					}
				}

				UNLOCK_TCPIP_CORE();

			} while(p != NULL);
		}
	}
}


/**
  * @brief Should be called at the beginning of the program to set up the
  * network interface. It calls the function low_level_init() to do the
  * actual setup of the hardware.
  *
  * This function should be passed as a parameter to netif_add().
  *
  * @param netif the lwip network interface structure for this ethernetif
  * @return ERR_OK if the loopif is initialized
  *         ERR_MEM if private data couldn't be allocated
  *         any other err_t on error
  */
err_t ethernetif_init(
	struct netif *netif) {

	LWIP_ASSERT("netif != NULL", (netif != NULL));

#if LWIP_NETIF_HOSTNAME
	/* Initialize interface hostname */
	netif->hostname = "lwip";
#endif // LWIP_NETIF_HOSTNAME

	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;

	/* We directly use etharp_output() here to save a function call.
	 * You can instead declare your own function an call etharp_output()
	 * from it if you have to do some checks before sending (e.g. if link
	 * is available...)
	 */
	netif->output = etharp_output;
	netif->linkoutput = low_level_output;

	// initialize the hardware
	//
	low_level_init(netif);

	return ERR_OK;
}

/**
  * @brief  Returns the current time in milliseconds
  *         when LWIP_TIMERS == 1 and NO_SYS == 1
  * @param  None
  * @retval Time
  */
u32_t sys_now(void) {

	return HAL_GetTick();
}
