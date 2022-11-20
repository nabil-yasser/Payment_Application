/**********************************************************************************************************************
*
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*  \file      : terminal.c
*
*  \category  : Terminal Module
*
*  \date      : 12 Oct. 2022
*
*  \brief     : Implementation file for TErminal module functions
*
*********************************************************************************************************************/

/* ================================================================================================================= */
/* ================                                    INCLUDES                                     ================ */
/* ================================================================================================================= */

#include "terminal.h"

/* ================================================================================================================= */
/* ================                                GLOBAL FUNCTIONS                                 ================ */
/* ================================================================================================================= */

/*************************************************************************************
*  \Syntax          : EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
*  \Description     : This function will ask for the cardholder's name and store it into card data
*  \Parameters      : termData -> Pointer to Terminal data
*  \Return value:   : EN_terminalError_t
************************************************************************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    strftime(termData->transactionDate, sizeof(termData->transactionDate), "%d/%m/%y", tm);
    return TERMINAL_OK;
}

/*************************************************************************************
*  \Syntax          : EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
*  \Description     : This function compares the card expiry date with the transaction date.
*  \Parameters      : cardData -> Card data structure
                      termData -> Terminal data structure
*  \Return value:   : EN_terminalError_t
************************************************************************************/
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    uint16 transactionMonth = 0, transactionYear = 0;
    uint16 expiryMonth = 0, expiryYear = 0;
    uint8 tmpDate[3];

    /* Getting Transaction Month from string */
    strncpy(tmpDate, (termData.transactionDate + 3), 2);
    tmpDate[2] = '\0';
    transactionMonth = atoi(tmpDate);

    /* Getting Transaction Year from string */
    strncpy(tmpDate, (termData.transactionDate + 6), 2);
    tmpDate[2] = '\0';
    transactionYear = atoi(tmpDate);

    /* Getting Expiry Month from string */
    strncpy(tmpDate, cardData.cardExpirationDate, 2);
    tmpDate[2] = '\0';
    expiryMonth = atoi(tmpDate);

    /* Getting Expiry Year from string */
    strncpy(tmpDate, (cardData.cardExpirationDate + 3), 2);
    tmpDate[2] = '\0';
    expiryYear = atoi(tmpDate);

    /* Check if card is expired */
    if (expiryYear < transactionYear)
    {
        return TERMINAL_EXPIRED_CARD;
    }
    else if (expiryYear == transactionYear)
    {
        if (expiryMonth < transactionMonth)
        {
            return TERMINAL_EXPIRED_CARD;
        }
    }

    return TERMINAL_OK;
}

/*************************************************************************************
*  \Syntax          : EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
*  \Description     : This function checks if the PAN is a Luhn number or not.
*  \Parameters      : cardData -> Pointer to card data
*  \Return value:   : EN_terminalError_t
************************************************************************************/
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData)
{
    uint64 tmpCardPAN = atoll(cardData->primaryAccountNumber);
    uint8 sum = 0, checkSum = 0, digitCounter = 0, digitDouble = 0;

    /* Applying Luhn Algorithm to check if it's Valid card */
    while (tmpCardPAN != 0)
    {
        uint8 lastDigit = tmpCardPAN % 10;

        if (digitCounter % 2 != 0)
        {
            digitDouble = lastDigit * 2;
            sum += (digitDouble % 100 < 10) ? digitDouble : (digitDouble % 10 + digitDouble / 10);
        }
        else
        {
            checkSum += lastDigit;
        }
        tmpCardPAN /= 10;
        digitCounter++;
    }
    
    checkSum = (checkSum + sum) % 10;

    /* Return if it's valid or not */
    if (checkSum != 0)
    {
        return TERMINAL_INVALID_CARD;
    }

    return TERMINAL_OK;
}

/*************************************************************************************
*  \Syntax          : EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
*  \Description     : This function asks for the transaction amount and saves it into terminal data.
*  \Parameters      : termData -> Pointer to terminal data
*  \Return value:   : EN_terminalError_t
************************************************************************************/
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    float tmpTransAmount = 0;
    printf("Transaction Amount: ");
    scanf("%f", &tmpTransAmount);

    /* Check if Transaction amount is zero or negative*/
    if (tmpTransAmount <= 0)
    {
        return TERMINAL_INVALID_AMOUNT;
    }

    termData->transAmount = tmpTransAmount;
    return TERMINAL_OK;
}

/*************************************************************************************
*  \Syntax          : EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
*  \Description     : This function compares the transaction amount with the terminal max amount.
*  \Parameters      : termData -> Pointer to terminal data
*  \Return value:   : EN_terminalError_t
************************************************************************************/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount > termData->maxTransAmount)
    {
        return TERMINAL_EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}

/*************************************************************************************
*  \Syntax          : EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
*  \Description     : This function sets the maximum allowed amount into terminal data.
*  \Parameters      : termData -> Pointer to terminal data
*  \Return value:   : EN_terminalError_t
************************************************************************************/
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    if (TERMINAL_MAX_AMOUNT <= 0)
    {
        return TERMINAL_INVALID_MAX_AMOUNT;
    }

    termData->maxTransAmount = TERMINAL_MAX_AMOUNT;
    return TERMINAL_OK;
}

/* ================================================================================================================= */
/* ================                              END OF FILE: terminal.c                            ================ */
/* ================================================================================================================= */
