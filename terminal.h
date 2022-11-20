/**********************************************************************************************************************
*
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*  \file      : terminal.h
*
*  \category  : Terminal Module
*
*  \date      : 12 Oct. 2022
*
*  \brief     : Header file for terminal module
*
*********************************************************************************************************************/

#ifndef TERMINAL_H
#define TERMINAL_H

/* ================================================================================================================= */
/* ================                                     INCLUDES                                    ================ */
/* ================================================================================================================= */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "Std_Types.h"
#include "card.h"

/* ================================================================================================================= */
/* ================                              GLOBAL CONSTANT MACROS                             ================ */
/* ================================================================================================================= */

#define TERMINAL_MAX_AMOUNT 5000

/* ================================================================================================================= */
/* ================                         GLOBAL DATA TYPES AND STRUCTURES                        ================ */
/* ================================================================================================================= */

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8 transactionDate[9];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, 
    TERMINAL_WRONG_DATE,
    TERMINAL_EXPIRED_CARD,
    TERMINAL_INVALID_CARD,
    TERMINAL_INVALID_AMOUNT,
    TERMINAL_EXCEED_MAX_AMOUNT,
    TERMINAL_INVALID_MAX_AMOUNT
}EN_terminalError_t;

/* ================================================================================================================= */
/* ================                            GLOBAL FUNCTION PROTOTYPES                           ================ */
/* ================================================================================================================= */

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

#endif /* TERMINAL_H */

/* ================================================================================================================= */
/* ================                             END OF FILE: terminal.h                             ================ */
/* ================================================================================================================= */
