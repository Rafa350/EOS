#ifndef _APP_H
#define _APP_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"


typedef enum {
    /* Application's state machine's initial state. */
    APP_STATE_INIT=0,

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

    /* True is switch was pressed */
    bool isSwitchPressed;

    /* True if the switch press needs to be ignored*/
    bool ignoreSwitchPress;

    /* Flag determines SOF event occurrence */
    bool sofEventHasOccurred;

    /* Break data */
    uint16_t breakData;

    /* Switch debounce timer */
    unsigned int switchDebounceTimer;

    unsigned int debounceCount;

    /* Application CDC read buffer */
    uint8_t * readBuffer;
} APP_DATA;


void APP_Initialize (void);
void APP_Tasks (void);


#endif 

