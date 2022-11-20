/**********************************************************************************************************************
*
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*  \file      : app.c
*
*  \category  : Application Module
*
*  \date      : 12 Oct. 2022
*
*  \brief     : Implementation file for payment application module.
*
*********************************************************************************************************************/

/* ================================================================================================================= */
/* ================                                    INCLUDES                                     ================ */
/* ================================================================================================================= */

#include "app.h"

/* ================================================================================================================= */
/* ================                              GLOBAL DATA PROTOTYPES                             ================ */
/* ================================================================================================================= */

ST_cardData_t userCard;
ST_terminalData_t mainTerminal;

/* ================================================================================================================= */
/* ================                               Payment Application                               ================ */
/* ================================================================================================================= */

int main(void)
{
    sint32 userChoice = -1;
    uint32 transNumber = 0;
    printf("1-> Sale Process\n");
    printf("2-> Get transaction\n");
    printf("0-> Exit\n");
    do
    {
        printf("\nProcess: ");
        scanf("%d%*c", &userChoice);

        switch (userChoice)
        {
        case 1:
            appStart();
            break;
        case 2:
            printf("Sequence Number: ");
            scanf("%d%*c", &transNumber);
            getTransaction(transNumber, transactionDatabase);
            break;
        }

    } while (userChoice != 0);

    return E_OK;
}

void appStart(void)
{
    /* <-----------------------------[ Read and Validate format for User's Card Data ]-----------------------------> */

    /* Check Card Holder's Name length */
    if (getCardHolderName(&userCard) != CARD_OK)
    {
        printf("Error: Wrong Name.\n");
        return ;
    }

    /* Check Expiry date format */
    if (getCardExpiryDate(&userCard) != CARD_OK)
    {
        printf("Error: Wrong expiry date.\n");
        return ;
    }

    /* Check Card Primary Account Number length */
    if (getCardPAN(&userCard) != CARD_OK)
    {
        printf("Error: Wrong Primary Account Number.\n");
        return ;
    }

    /* <-----------------------------[ Read and Validate Card Data from Terminal Side ]----------------------------> */

    /* Get Transaction date using PC/Terminal clock */
    getTransactionDate(&mainTerminal);

    /* Check whether card primary account number follow luhn's Algorithm */
    if (isValidCardPAN(&userCard) != TERMINAL_OK)
    {
        printf("Error: Invalid Card.\n");
        return ;
    }

    /* Check whether card is expired */
    if (isCardExpired(userCard, mainTerminal) != TERMINAL_OK)
    {
        printf("Error: Card is Expired.\n");
        return ;
    }

    /* Get user Transaction amount */
    if (getTransactionAmount(&mainTerminal) != TERMINAL_OK)
    {
        printf("Error: Invalid Amount.\n");
        return ;
    }

    /* Set Terminal's Maximum Transaction Amount */
    if (setMaxAmount(&mainTerminal) != TERMINAL_OK)
    {
        printf("Error: Invalid Terminal Maxmimum Amount.\n");
        return ;
    }

    /* Check whether transaction amount is below maximum terminal amount ($5,000) */
    if (isBelowMaxAmount(&mainTerminal) != TERMINAL_OK)
    {
        printf("Error: Transaction amount exceeded maximum terminal amount.\n");
        return ;
    }

    /* <------------------------------[ Read and Validate Card Data from Server Side ]-----------------------------> */

    /* Read and validate data and complete transaction if all data are valid */
    if (recieveTransactionData(&tmpTransactionData) != TRANS_APPROVED)
    {
        saveTransaction(&tmpTransactionData);
        return ;
    }

    /* Save transaction into transaction database */
    saveTransaction(&tmpTransactionData);
}

/* ================================================================================================================= */
/* ================                               END OF FILE: app.c                                ================ */
/* ================================================================================================================= */
