/**********************************************************************************************************************
*
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*  \file      : app.h
*
*  \category  : Application Module
*
*  \date      : 12 Oct. 2022
*
*  \brief     : Header file for Payment Application module
*
*********************************************************************************************************************/

#ifndef APP_H
#define APP_H

/* ================================================================================================================= */
/* ================                                     INCLUDES                                    ================ */
/* ================================================================================================================= */

#include <stdio.h>
#include "Std_Types.h"
#include "card.h"
#include "terminal.h"
#include "server.h"

/* ================================================================================================================= */
/* ================                              GLOBAL DATA PROTOTYPES                             ================ */
/* ================================================================================================================= */

extern ST_transaction_t transactionDatabase[255];
extern ST_accountsDB_t accountsDatabase[255];
extern ST_transaction_t tmpTransactionData;

/* ================================================================================================================= */
/* ================                            GLOBAL FUNCTION PROTOTYPES                           ================ */
/* ================================================================================================================= */

void appStart(void);

#endif /* APP_H */

/* ================================================================================================================= */
/* ================                               END OF FILE: app.h                                ================ */
/* ================================================================================================================= */
