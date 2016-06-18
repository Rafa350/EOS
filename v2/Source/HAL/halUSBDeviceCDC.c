#include "HAL/halUSBDevice.h"
#include "usb/usb_device_cdc.h"
#include "stdint.h"
#include "stdbool.h"


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
    /* Device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE deviceHandle;

    /* Application's current state*/
    APP_STATES state;

    /* Set Line Coding Data */
    USB_CDC_LINE_CODING setLineCodingData;

    /* Device configured state */
    bool isConfigured;

    /* Get Line Coding Data */
    USB_CDC_LINE_CODING getLineCodingData;

    /* Control Line State */
    USB_CDC_CONTROL_LINE_STATE controlLineStateData;

    /* Read transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE readTransferHandle;

    /* Write transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE writeTransferHandle;

    /* True if a character was read */
    bool isReadComplete;

    /* True if a character was written*/
    bool isWriteComplete;

    /* Flag determines SOF event occurrence */
    bool sofEventHasOccurred;

    /* Break data */
    uint16_t breakData;

    /* Application CDC read buffer */
    uint8_t * readBuffer;
} APP_DATA;


static uint8_t APP_MAKE_BUFFER_DMA_READY readBuffer[APP_READ_BUFFER_SIZE];
static APP_DATA appData;


/// ----------------------------------------------------------------------
/// \brief Procesa els events del dispositiu CDC.
/// \param index: El index del dispositiu.
/// \param event: El event a procesar.
/// \param pData: Parametres del event.
/// \param userData: Dades de l'aplicacio.
///
static USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler(
    USB_DEVICE_CDC_INDEX index,
    USB_DEVICE_CDC_EVENT event,
    void *pData,
    uintptr_t userData) {
    
    APP_DATA *appData = (APP_DATA*) userData;
    USB_CDC_CONTROL_LINE_STATE *controlLineStateData;

    switch (event) {
        
        case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

            // This means the host wants to know the current line
            // coding. This is a control transfer request. Use the
            // USB_DEVICE_ControlSend() function to send the data to
            // host.  
            //
            USB_DEVICE_ControlSend(appData->deviceHandle,
                &appData->getLineCodingData, sizeof(USB_CDC_LINE_CODING));
            break;

        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

            // This means the host wants to set the line coding.
            // This is a control transfer request. Use the
            // USB_DEVICE_ControlReceive() function to receive the
            // data from the host 
            //
            USB_DEVICE_ControlReceive(appData->deviceHandle,
                &appData->setLineCodingData, sizeof(USB_CDC_LINE_CODING));
            break;

        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:

            // This means the host is setting the control line state.
            // Read the control line state. We will accept this request
            // for now. 
            //
            controlLineStateData = (USB_CDC_CONTROL_LINE_STATE*) pData;
            appData->controlLineStateData.dtr = controlLineStateData->dtr;
            appData->controlLineStateData.carrier = controlLineStateData->carrier;
            USB_DEVICE_ControlStatus(appData->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case USB_DEVICE_CDC_EVENT_SEND_BREAK:

            // This means that the host is requesting that a break of the
            // specified duration be sent. Read the break duration 
            //
            appData->breakData = ((USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK*) pData)->breakDuration;
            break;

        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:

            // This means that the host has sent some data
            //
            appData->isReadComplete = true;
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

            // The data stage of the last control transfer is
            // complete. For now we accept all the data 
            //
            USB_DEVICE_ControlStatus(appData->deviceHandle, USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

            // This means the GET LINE CODING function data is valid. We dont
            // do much with this data in this demo. 
            //
            break;

        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:

            // This means that the data write got completed. We can schedule
            // the next read. 
            //
            appData->isWriteComplete = true;
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}


static void APP_USBDeviceEventHandler( 
    USB_DEVICE_EVENT event, 
    void *eventData, 
    uintptr_t context) {
    
    USB_DEVICE_EVENT_DATA_CONFIGURED *configuredEventData;

    switch (event) {
        
        case USB_DEVICE_EVENT_SOF:
            
            /* This event is used for switch debounce. This flag is reset
             * by the switch process routine. 
             */
            appData.sofEventHasOccurred = true;
            break;

        case USB_DEVICE_EVENT_RESET:
            
            /* Update LED to show reset state 
             */
            appData.isConfigured = false;
            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Check the configuratio. We only support configuration 1 
             */
            configuredEventData = (USB_DEVICE_EVENT_DATA_CONFIGURED*) eventData;
            if (configuredEventData->configurationValue == 1) {
                
                /* Register the CDC Device application event handler here.
                 * Note how the appData object pointer is passed as the
                 * user data 
                 */
                USB_DEVICE_CDC_EventHandlerSet(USB_DEVICE_CDC_INDEX_0, APP_USBDeviceCDCEventHandler, (uintptr_t)&appData);

                /* Mark that the device is now configured 
                 */
                appData.isConfigured = true;
            }
            break;

        case USB_DEVICE_EVENT_POWER_DETECTED:
            
            /* VBUS was detected. We can attach the device 
             */
            USB_DEVICE_Attach(appData.deviceHandle);
            break;

        case USB_DEVICE_EVENT_POWER_REMOVED:
            
            /* VBUS is not available any more. Detach the device. 
             */
            USB_DEVICE_Detach(appData.deviceHandle);
            break;

        case USB_DEVICE_EVENT_SUSPENDED:
            break;

        case USB_DEVICE_EVENT_RESUMED:
            break;
            
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
        appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.isReadComplete = true;
        appData.isWriteComplete = true;
        retVal = true;
    }
    else {
        retVal = false;
    }

    return retVal;
}


void halUSBDeviceCDCSetup(void) {
    
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    
    /* Device Layer Handle  */
    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;

    /* Device configured status */
    appData.isConfigured = false;

    /* Initial get line coding state */
    appData.getLineCodingData.dwDTERate = 9600;
    appData.getLineCodingData.bParityType = 0;
    appData.getLineCodingData.bParityType = 0;
    appData.getLineCodingData.bDataBits = 8;

    /* Read Transfer Handle */
    appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Write Transfer Handle */
    appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Intialize the read complete flag */
    appData.isReadComplete = true;

    /*Initialize the write complete flag*/
    appData.isWriteComplete = true;

    /* Reset other flags */
    appData.sofEventHasOccurred = false;

    /* Set up the read buffer */
    appData.readBuffer = &readBuffer[0];     
}


void halUSBDeviceCDCTask(void) {
    
    // Update the application state machine based
    // on the current state 
    //
    switch (appData.state) {
        
        case APP_STATE_INIT:

            // Open the device layer
            //
            appData.deviceHandle = USB_DEVICE_Open(USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE);
            if (appData.deviceHandle != USB_DEVICE_HANDLE_INVALID) {
                
                // Register a callback with device layer to get 
                // event notification (for end point 0) 
                //
                USB_DEVICE_EventHandlerSet(appData.deviceHandle, APP_USBDeviceEventHandler, 0);
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
            if (appData.isReadComplete == true) {
                appData.isReadComplete = false;
                appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

                USB_DEVICE_CDC_Read (USB_DEVICE_CDC_INDEX_0,
                    &appData.readTransferHandle, appData.readBuffer,
                    APP_READ_BUFFER_SIZE);
                
                if (appData.readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID) {
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
            if (appData.isReadComplete) {
                appData.state = APP_STATE_SCHEDULE_WRITE;
            }

            break;


        case APP_STATE_SCHEDULE_WRITE:

            if (APP_StateReset()) {
                break;
            }

            // Setup the write
            //
            appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
            appData.isWriteComplete = false;
            appData.state = APP_STATE_WAIT_FOR_WRITE_COMPLETE;

            // echo the received character + 1
            //
            appData.readBuffer[0] = appData.readBuffer[0] + 1;
            USB_DEVICE_CDC_Write(USB_DEVICE_CDC_INDEX_0,
                &appData.writeTransferHandle,
                appData.readBuffer, 1,
                USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            break;

        case APP_STATE_WAIT_FOR_WRITE_COMPLETE:

            if (APP_StateReset()) {
                break;
            }

            // Check if a character was sent. The isWriteComplete
            // flag gets updated in the CDC event handler 
            //
            if (appData.isWriteComplete == true) {
                appData.state = APP_STATE_SCHEDULE_READ;
            }
            break;

        case APP_STATE_ERROR:
            break;
            
        default:
            break;
    }
}
