#include "HAL/halUSBDeviceCDC.h"
#include "usb/usb_device_cdc.h"
#include "stdint.h"
#include "stdbool.h"


#define COM1 USB_DEVICE_CDC_INDEX_0
#define COM2 USB_DEVICE_CDC_INDEX_1

#define APP_READ_BUFFER_SIZE 1024


typedef enum {
    /* Application's state machine's initial state. */
    APP_STATE_INIT = 0,

    /* Application waits for device configuration*/
    APP_STATE_WAIT_FOR_CONFIGURATION,

    /* The application checks if a switch was pressed */
    APP_STATE_CHECK_SWITCH_PRESSED,

    /* Wait for a character receive */
    APP_STATE_SCHEDULE_READ,

    /* A character is received from host */
    APP_STATE_WAIT_FOR_READ_COMPLETE,

    /* Wait for the TX to get completed */
    APP_STATE_SCHEDULE_WRITE,

    /* Wait for the write to complete */
    APP_STATE_WAIT_FOR_WRITE_COMPLETE,

    /* Application Error state*/
    APP_STATE_ERROR

} APP_STATES;


typedef struct {
    USB_DEVICE_CDC_INDEX cdcInstance;  // Index del port CDC
    USB_CDC_LINE_CODING setLineCodingData;
    USB_CDC_LINE_CODING getLineCodingData;
    USB_CDC_CONTROL_LINE_STATE controlLineStateData;       // Estat de les linias de control
    USB_DEVICE_CDC_TRANSFER_HANDLE readTransferHandle;     // Handler de lectura
    USB_DEVICE_CDC_TRANSFER_HANDLE writeTransferHandle;    // Handler d'escriptura
    bool isReadComplete;               // Indica si s'ha completat una lectura
    bool isWriteComplete;              // Indica si s'ha competat una escriptura
    uint16_t breakData;                // Dades break
    uint8_t *readBuffer;               // Buffer de lectura
    uint8_t *writeBuffer;              // Buffer d'escriptura
} PortData;

typedef struct {
    USB_DEVICE_HANDLE deviceHandle;    // Handler del dispositiu
    APP_STATES state;                  // Estat actual
    bool isConfigured;                 // Indica si esta configurat
    PortData port[1];                  // Dades del port
} Data;


static uint8_t /*APP_MAKE_BUFFER_DMA_READY*/ readBuffer[APP_READ_BUFFER_SIZE];
static uint8_t /*APP_MAKE_BUFFER_DMA_READY*/ writeBuffer[APP_READ_BUFFER_SIZE];
static Data appData;
static USBDeviceCallback callback;
static void *param;


/// ----------------------------------------------------------------------
/// \brief Procesa els events del dispositiu CDC.
/// \param index: El index del dispositiu.
/// \param event: El event a procesar.
/// \param pData: Parametres del event.
/// \param userData: Dades de l'aplicacio.
///
static USB_DEVICE_CDC_EVENT_RESPONSE deviceCDCEventHandler(
    USB_DEVICE_CDC_INDEX index,
    USB_DEVICE_CDC_EVENT event,
    void *pData,
    uintptr_t userData) {
    
    Data *appData = (Data*) userData;
    PortData *portData = &appData->port[index];

    switch (event) {
        
        // This means the host wants to know the current line
        // coding. This is a control transfer request
        //
        case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:
            USB_DEVICE_ControlSend(
                appData->deviceHandle,
                &portData->getLineCodingData, 
                sizeof(USB_CDC_LINE_CODING));
            break;

        // This means the host wants to set the line coding
        // This is a control transfer request. 
        //
        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:
            USB_DEVICE_ControlReceive(
                appData->deviceHandle,
                &portData->setLineCodingData, 
                sizeof(USB_CDC_LINE_CODING));
            break;

        // This means the host is setting the control line state.
        //
        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE: {

            // Read the control line state. We will accept this request
            // for now. 
            //
            USB_CDC_CONTROL_LINE_STATE *controlLineStateData = (USB_CDC_CONTROL_LINE_STATE*) pData;
            portData->controlLineStateData.dtr = controlLineStateData->dtr;
            portData->controlLineStateData.carrier = controlLineStateData->carrier;
            USB_DEVICE_ControlStatus(
                appData->deviceHandle, 
                USB_DEVICE_CONTROL_STATUS_OK);
            break;
        }

        // This means that the host is requesting that a break of the
        // specified duration be sent
        //
        case USB_DEVICE_CDC_EVENT_SEND_BREAK:

            // Read the break duration 
            //
            portData->breakData = ((USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK*) pData)->breakDuration;
            break;

        // This means that the host has sent some data
        //
        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:
            portData->isReadComplete = true;
            break;
            
        // This means that the data write got completed
        //
        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:
            portData->isWriteComplete = true;
            break;
            
        // The data stage of the last control transfer is complete
        // 
        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:
            USB_DEVICE_ControlStatus(
                appData->deviceHandle, 
                USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}


/// ----------------------------------------------------------------------
/// \brief Procesa els events del dispositiu USB.
/// \param event: El event a procesar.
/// \param eventData: Parametres del event
/// \param context: Dades d'usuari.
///
static void deviceEventHandler( 
    USB_DEVICE_EVENT event, 
    void *eventData, 
    uintptr_t context) {
    
    Data *appData = (Data*) context;

    switch (event) {
        
        case USB_DEVICE_EVENT_RESET:
            appData->isConfigured = false;
            break;

        case USB_DEVICE_EVENT_CONFIGURED: {
            USB_DEVICE_EVENT_DATA_CONFIGURED *configuredEventData = (USB_DEVICE_EVENT_DATA_CONFIGURED*) eventData;
            if (configuredEventData->configurationValue == 1) {
                
                // Register the CDC Device application event handler here.
                // Note how the appData object pointer is passed as the
                // user data 
                //
                USB_DEVICE_CDC_EventHandlerSet(
                    COM1, 
                    deviceCDCEventHandler, 
                    (uintptr_t) appData);
                
                appData->isConfigured = true;
            }
            break;
        }

        case USB_DEVICE_EVENT_POWER_DETECTED:
            
            // VBUS was detected. We can attach the device 
            ///
            USB_DEVICE_Attach(appData->deviceHandle);
            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:
            
            // VBUS is not available any more. Detach the device. 
            //
            USB_DEVICE_Detach(appData->deviceHandle);
            break;

        case USB_DEVICE_EVENT_SOF:
        case USB_DEVICE_EVENT_SUSPENDED:
        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ERROR:
            break;
    }
}


static bool APP_StateReset(void) {
    
    /* This function returns true if the device
     * was reset  */

    bool retVal;

    if (appData.isConfigured == false) {
        appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
        appData.port[COM1].readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.port[COM1].writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.port[COM1].isReadComplete = true;
        appData.port[COM1].isWriteComplete = true;
        retVal = true;
    }
    else {
        retVal = false;
    }

    return retVal;
}


/// ----------------------------------------------------------------------
/// \brief Inicialitza un dispositiu CDC.
/// \param info: Parametres de configuracio.
///
void halUSBDeviceCDCInitialize(
    const USBDeviceCDCInitializeInfo *info) {
    
    callback = info->callback;
    param = info->param;
    
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    /* Device Layer Handle  */
    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;

    /* Device configured status */
    appData.isConfigured = false;

    /* Initial get line coding state */
    appData.port[COM1].getLineCodingData.dwDTERate = 9600;
    appData.port[COM1].getLineCodingData.bParityType = 0;
    appData.port[COM1].getLineCodingData.bParityType = 0;
    appData.port[COM1].getLineCodingData.bDataBits = 8;

    /* Read Transfer Handle */
    appData.port[COM1].readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Write Transfer Handle */
    appData.port[COM1].writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Intialize the read complete flag */
    appData.port[COM1].isReadComplete = true;

    /* Set up the read buffer */
    appData.port[COM1].readBuffer = &readBuffer[0];     
    appData.port[COM1].writeBuffer = &writeBuffer[0];     
}


/// ----------------------------------------------------------------------
/// \brief Tasca de control del dispositiu CDC.
///
void halUSBDeviceCDCTask() {
    
    // Update the application state machine based
    // on the current state 
    //
    switch (appData.state) {
        
        case APP_STATE_INIT:

            // Open the device layer
            //
            appData.deviceHandle = USB_DEVICE_Open(
                USB_DEVICE_INDEX_0, 
                DRV_IO_INTENT_READWRITE);
            if (appData.deviceHandle != USB_DEVICE_HANDLE_INVALID) {
                
                // Register a callback with device layer to get 
                // event notification (for end point 0) 
                //
                USB_DEVICE_EventHandlerSet(
                    appData.deviceHandle, 
                    deviceEventHandler, 
                    (uintptr_t) &appData);
                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            break;

        case APP_STATE_WAIT_FOR_CONFIGURATION:

            // Check if the device was configured 
            //
            if (appData.isConfigured) 
                appData.state = APP_STATE_SCHEDULE_READ;
            break;

        case APP_STATE_SCHEDULE_READ:

            if(APP_StateReset()) {
                break;
            }

            // If a read is complete, then schedule a read
            // else wait for the current read to complete 
            //
            appData.state = APP_STATE_WAIT_FOR_READ_COMPLETE;
            if (appData.port[COM1].isReadComplete == true) {
                appData.port[COM1].isReadComplete = false;
                appData.port[COM1].readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

                USB_DEVICE_CDC_Read(
                    USB_DEVICE_CDC_INDEX_0,
                    &appData.port[COM1].readTransferHandle, 
                    appData.port[COM1].readBuffer,
                    APP_READ_BUFFER_SIZE);
                
                if (appData.port[COM1].readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID) {
                    appData.state = APP_STATE_ERROR;
                    break;
                }
            }
            break;

        case APP_STATE_WAIT_FOR_READ_COMPLETE:
        case APP_STATE_CHECK_SWITCH_PRESSED:

            if (APP_StateReset()) {
                break;
            }

            // Check if a character was received or a switch was pressed.
            // The isReadComplete flag gets updated in the CDC event handler. 
            //
            if (appData.port[COM1].isReadComplete) {
                appData.state = APP_STATE_SCHEDULE_WRITE;
            }

            break;


        case APP_STATE_SCHEDULE_WRITE:

            if (APP_StateReset()) {
                break;
            }

            // Setup the write
            //
            appData.port[COM1].writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
            appData.port[COM1].isWriteComplete = false;
            appData.state = APP_STATE_WAIT_FOR_WRITE_COMPLETE;

            // echo the received character + 1
            //
            appData.port[COM1].readBuffer[0] = appData.port[COM1].readBuffer[0] + 1;
            USB_DEVICE_CDC_Write(
                USB_DEVICE_CDC_INDEX_0,
                &appData.port[COM1].writeTransferHandle,
                appData.port[COM1].readBuffer, 
                1,
                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            break;

        case APP_STATE_WAIT_FOR_WRITE_COMPLETE:

            if (APP_StateReset()) {
                break;
            }

            // Check if a character was sent. The isWriteComplete
            // flag gets updated in the CDC event handler 
            //
            if (appData.port[COM1].isWriteComplete == true) {
                appData.state = APP_STATE_SCHEDULE_READ;
            }
            break;

        case APP_STATE_ERROR:
            break;
            
        default:
            break;
    }
}
