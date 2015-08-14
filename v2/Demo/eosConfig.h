#ifndef __EOS_CONFIG_H
#define __EOS_CONFIG_H


#include "HardwareProfile.h"


// Opcions de configuracio del 'Kernel'
//
#define eosOPTION_Main
#define eosOPTION_Harmony


// Opcions de configuracio del servei 'Tick'
//
#define eosTickServiceConfig_UseTMR4                  // Temporitzador a utilitzar


// Opcions de configuracio pel servei 'Timers'
//
#define eosOPTIONS_TIMERS_MAX_INSTANCES          1    // Numero maxim d'instancies del servei
#define eosOPTIONS_TIMERS_MAX_TIMERS             20   // Numero maxim de temporitzadors


// Opcions de configuracio pel servei 'Inputs'
//


// Opcions de configuracio pel servei 'Outputs'
//
#define eosOPTIONS_OUTPUTS_MAX_INSTANCES         1    // Numero maxim d'instancies del servei
#define eosOPTIONS_OUTPUTS_MAX_OUTPUTS          32    // Numero maxim de sortides


// Opcions de configuracio pel servei 'I2CMaster'
//
#define eosOPTIONS_I2CMASTER_MAX_INSTANCES       4    // Numero maxim d'instancies del servei
#define eosOPTIONS_I2CMASTER_MAX_TRANSACTIONS    100  // Numero maxim de transaccions en cua
#define eosOPTIONS_I2CMASTER_END_TRANSACTION_DELAY 15 // Retard final de la transaccio


// Opcions de configuracio pel servei 'Forms'
//
#define eosOPTIONS_FORMS_MAX_INSTANCES           1    // Numero maxim d'instancies del servei
#define eosOPTIONS_FORMS_MAX_QUEUE_SIZE         50    // Numero maxim de missatges en la cua


#endif