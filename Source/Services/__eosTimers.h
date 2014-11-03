#ifndef __EOS_TIMERS_H__
#define	__EOS_TIMERS_H__


#ifndef __EOS_H
#include "eos.h"
#endif


// Comandes
//
#define CMD_NOP                   0    // NOP
#define CMD_PAUSE                 1    // Posa un temporitzador en pausa
#define CMD_CONTINUE              2    // Reanuda un temporitzador
#define CMD_RESET                 3    // Reseteja un temporitzador
#define CMD_REMOVE                4    // Elimina un temporitzador

// Estats del servei
//
#define SS_INITIALIZING           0    // Inicialitzant
#define SS_RUNNING                1    // Executant

// Indicadors del temporitzador
//
#define TF_PAUSED            0x0001    // Temporitzador en pausa
#define TF_TYPE              0x0006    // Tipus de temporitzador
#define TF_TYPE_CYCLIC       0x0002    // -Ciclic
#define TF_TYPE_AUTODESTROY  0x0003    // -Destruccio automatica


struct __MESSAGE {                     // Missatge
    unsigned command;                  // -Identificador de la comanda
    struct __TIMER *timer;             // -Temporitzador
};

struct __TIMER {                       // Dades internes del temporitzador
    struct __TIMER_SERVICE *service;   // -Servei asociat
    unsigned flags;                    // -Indicadors
    unsigned timeout;                  // -Temps en ms
    unsigned counter;                  // -Contador de temps en ms
    eosCallback callback;              // -Funcio callback
    void *context;                     // -Parametre de la funcio callback
    struct __TIMER *nextTimer;         // -Seguent temporitzadorde la llista
};

struct __TIMER_SERVICE {               // Dades internes del servei
    unsigned state;                    // -Estat
    unsigned triggered;                // -Indica event del temporitzador
    eosHandle hQueue;                  // -Cua de missatges
    eosHandle hAttach;                 // -Handler del servei TICK
    struct __TIMER *firstTimer;        // -Primer temporitzador de la llista
};


typedef struct __MESSAGE Message;
typedef struct __TIMER eosTimer;
typedef struct __TIMER_SERVICE eosTimerService;


#include "Services/eosTimers.h"


#endif

