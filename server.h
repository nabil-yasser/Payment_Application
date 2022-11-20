/**********************************************************************************************************************
*
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*  \file      : server.h
*
*  \category  : Server Module
*
*  \date      : 12 Oct. 2022
*
*  \brief     : Header file for server module
*
*********************************************************************************************************************/

#ifndef SERVER_H
#define SERVER_H

/* ================================================================================================================= */
/* ================                                     INCLUDES                                    ================ */
/* ================================================================================================================= */

#include <stdio.h>
#include <string.h>
#include "Std_Types.h"
#include "terminal.h"

/* ================================================================================================================= */
/* ================                              GLOBAL DATA PROTOTYPES                             ================ */
/* ================================================================================================================= */

extern ST_cardData_t userCard;
extern ST_terminalData_t mainTerminal;

/* ================================================================================================================= */
/* ================                         GLOBAL DATA TYPES AND STRUCTURES                        ================ */
/* ================================================================================================================= */

typedef enum EN_transState_t
{
    TRANS_APPROVED, 
    TRANS_DECLINED_INSUFFECIENT_FUND,
    TRANS_DECLINED_STOLEN_CARD,
    TRANS_INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef enum EN_serverError_t
{
    SERVER_OK,
    SERVER_SAVING_FAILED,
    SERVER_TRANSACTION_NOT_FOUND,
    SERVER_ACCOUNT_NOT_FOUND,
    SERVER_LOW_BALANCE
}EN_serverError_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32 transactionSequenceNumber;
}ST_transaction_t;

typedef struct ST_accountsDB_t
{
    float balance;
    uint8 primaryAccountNumber[20];
}ST_accountsDB_t;

/* ================================================================================================================= */
/* ================                            GLOBAL FUNCTION PROTOTYPES                           ================ */
/* ================================================================================================================= */

EN_transState_t recieveTransactionData(ST_transaction_t *transData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32 transactionSequenceNumber, ST_transaction_t *transData);

#endif /* SERVER_H */

/* ================================================================================================================= */
/* ================                              END OF FILE: server.h                              ================ */
/* ================================================================================================================= */
