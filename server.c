/**********************************************************************************************************************
*
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*  \file      : server.c
*
*  \category  : Server Module
*
*  \date      : 13 Oct. 2022
*
*  \brief     : Implementation file for server module.
*
*********************************************************************************************************************/

/* ================================================================================================================= */
/* ================                                    INCLUDES                                     ================ */
/* ================================================================================================================= */

#include "server.h"

/* ================================================================================================================= */
/* ================                              GLOBAL DATA PROTOTYPES                             ================ */
/* ================================================================================================================= */

ST_transaction_t tmpTransactionData = {{ "", "", "" },{ 0, 0, "" }, SERVER_ACCOUNT_NOT_FOUND, 0 };

/* Server Users' Bank Accounts Database */
ST_accountsDB_t accountsDatabase[255] =
{
    { 5000, "5610591081018250" },
    { 4500, "6011111111111117" },
    { 300, "5555555555554444" },
    { 1700, "5105105105105100" },
    { 6780, "4111111111111111" },
    { 21, "4012888888881881" },
    { 2248, "6011000990139424" },
};

/* Server Users' Bank Transactions Database */
ST_transaction_t transactionDatabase[255] =
{
    { { "", "", "" }, { 0, 0, "" }, SERVER_ACCOUNT_NOT_FOUND, 0 },
    { { "", "", "" }, { 0, 0, "" }, SERVER_ACCOUNT_NOT_FOUND, 0 },
    { { "", "", "" }, { 0, 0, "" }, SERVER_ACCOUNT_NOT_FOUND, 0 },
    { { "", "", "" }, { 0, 0, "" }, SERVER_ACCOUNT_NOT_FOUND, 0 },
    { { "", "", "" }, { 0, 0, "" }, SERVER_ACCOUNT_NOT_FOUND, 0 },
    { { "", "", "" }, { 0, 0, "" }, SERVER_ACCOUNT_NOT_FOUND, 0 },
    { { "", "", "" }, { 0, 0, "" }, SERVER_ACCOUNT_NOT_FOUND, 0 }
};

/* ================================================================================================================= */
/* ================                                GLOBAL FUNCTIONS                                 ================ */
/* ================================================================================================================= */

/*************************************************************************************
*  \Syntax          : EN_transState_t recieveTransactionData(ST_transaction_t *transData)
*  \Description     : This function will take all transaction data and validate its data.
*  \Parameters      : transData -> Pointer to transaction data
*  \Return value:   : EN_serverError_t
************************************************************************************/
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    /* Read transaction data and copy it into temporary variable to check */
    strcpy(transData->cardHolderData.cardExpirationDate, userCard.cardExpirationDate);
    strcpy(transData->cardHolderData.cardHolderName, userCard.cardHolderName);
    strcpy(transData->cardHolderData.primaryAccountNumber, userCard.primaryAccountNumber);

    strcpy(transData->terminalData.transactionDate, mainTerminal.transactionDate);
    transData->terminalData.maxTransAmount = mainTerminal.maxTransAmount;
    transData->terminalData.transAmount = mainTerminal.transAmount;

    sint16 index = -1;
    for (uint8 i = 0; i < 255; i++)
    {
        if (strcmp(transData->cardHolderData.primaryAccountNumber, (accountsDatabase + i)->primaryAccountNumber) == 0)
        {
            index = i;
            break;
        }
    }

    /* Check if card was found */
    if (index == -1)
    {
        printf("Error: Transaction declined, Stolen Card!\nPlease give it back to the nearest Bank.\n");
        transData->transState = TRANS_DECLINED_STOLEN_CARD;
        return TRANS_DECLINED_STOLEN_CARD;
    }

    /* Check if fund is suffecient */
    if (transData->terminalData.transAmount > accountsDatabase[index].balance)
    {
        printf("Error: Insuffecient fund.\n");
        transData->transState = TRANS_DECLINED_INSUFFECIENT_FUND;
        return TRANS_DECLINED_INSUFFECIENT_FUND;
    }

    uint8 userConfirm = 0;
    printf("Your Balance: $%.2f\n\n", accountsDatabase[index].balance);

    printf("Please Confirm transaction [y/n]: ");
    do
    {
        scanf("%c", &userConfirm);
    } while (userConfirm != 'y' && userConfirm != 'n');

    if (userConfirm == 'n')
    {
        printf("Error: Transaction Cancelled!\n");
        transData->transState = TRANS_INTERNAL_SERVER_ERROR;
        return TRANS_INTERNAL_SERVER_ERROR;
    }

    accountsDatabase[index].balance -= transData->terminalData.transAmount;

    printf("Transaction done!\n");
    printf("Your Balance: $%.2f\n", accountsDatabase[index].balance);
    printf("Thanks for using our application!\n\n");
    transData->transState = TRANS_APPROVED;
    return TRANS_APPROVED;
}

/*************************************************************************************
*  \Syntax          : EN_serverError_t saveTransaction(ST_transaction_t *transData)
*  \Description     : This function will take all transaction data into the transactions database.
*  \Parameters      : transData -> Pointer to transaction data
*  \Return value:   : EN_serverError_t
************************************************************************************/
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    static uint16 saveCounter = 1;
    transData->transactionSequenceNumber = saveCounter;
    memcpy(&transactionDatabase[saveCounter - 1], transData, sizeof(ST_transaction_t));
    saveCounter++;
    return SERVER_OK;
}

/*************************************************************************************
*  \Syntax          : EN_serverError_t saveTransaction(ST_transaction_t *transData)
*  \Description     : This function will take all transaction data into the transactions database.
*  \Parameters      : transData -> Pointer to transaction data
*  \Return value:   : EN_serverError_t
************************************************************************************/
EN_serverError_t getTransaction(uint32 transactionSequenceNumber, ST_transaction_t *transData)
{
    sint32 index = -1;
    if ((transactionSequenceNumber - 1) > 255 || transactionSequenceNumber < 1)
    {
        printf("Error: Transaction not found!\n");
        return SERVER_TRANSACTION_NOT_FOUND;
    }

    for (uint32 i = 0; i <= 255; i++)
    {
        if (transactionSequenceNumber == transData[i].transactionSequenceNumber)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Error: Transaction not found!\n");
        return SERVER_TRANSACTION_NOT_FOUND;
    }

    printf("Card Holder Name: %s\n", transData[index].cardHolderData.cardHolderName);
    printf("Card PAN: %s\n", transData[index].cardHolderData.primaryAccountNumber);
    printf("Card Expiry date: %s\n\n", transData[index].cardHolderData.cardExpirationDate);

    printf("Transaction amount: %.2f\n", transData[index].terminalData.transAmount);
    printf("Transaction date: %s\n", transData[index].terminalData.transactionDate);

    switch (transData[index].transState)
    {
    case 0:
        printf("Transaction state: Approved\n");
        break;
    case 1:
        printf("Transaction state: Insufficient fund\n");
        break;
    case 2:
        printf("Transaction state: Stolen Card\n");
        break;
    case 3:
        printf("Transaction state: Internal server error\n");
        break;
    }

    return SERVER_OK;
}

/* ================================================================================================================= */
/* ================                               END OF FILE: app.c                                ================ */
/* ================================================================================================================= */
