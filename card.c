/**********************************************************************************************************************
*
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*  \file      : card.c
*
*  \category  : Card Module
*
*  \date      : 12 Oct. 2022
*
*  \brief     : Implementation file for card module functions
*
*********************************************************************************************************************/

/* ================================================================================================================= */
/* ================                                    INCLUDES                                     ================ */
/* ================================================================================================================= */

#include "card.h"

/* ================================================================================================================= */
/* ================                                GLOBAL FUNCTIONS                                 ================ */
/* ================================================================================================================= */

/*************************************************************************************
*  \Syntax          : EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
*  \Description     : This function will ask for the cardholder's name and store it into card data
*  \Parameters      : cardData -> Pointer to user card
*  \Return value:   : EN_cardError_t
************************************************************************************/
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    uint8 tmp[50];
    uint8 tmpLength = 0;

    /* Get and store card holder's name into tmp variable */
    printf("Please Enter Card Holder Name: ");
    scanf("%[^\n]%*c", tmp);
    tmpLength = (uint8)strlen(tmp);

    /* Check and Validate the card holder's name */
    if (tmpLength < 20 || tmpLength > 24)
    {
        return CARD_WRONG_NAME;
    }

    strcpy(cardData->cardHolderName, tmp);
    return CARD_OK;
}

/*************************************************************************************
*  \Syntax          : EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
*  \Description     : This function will ask for the card expiry date and store it in card data.
*  \Parameters      : cardData -> Pointer to user card
*  \Return value:   : EN_cardError_t
************************************************************************************/
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    uint8 tmp[10];
    uint8 tmpLength = 0;

    /* Get and store card expiry date into tmp variable */
    printf("Expiry date (mm/yy): ");
    scanf("%[^\n]%*c", tmp);
    tmpLength = (uint8)strlen(tmp);

    /* Check and Validate card expiry date */
    if (tmpLength != 5 || tmp[2] != '/')
    {
        return CARD_WRONG_EXP_DATE;
    }

    strcpy(cardData->cardExpirationDate, tmp);
    return CARD_OK;
}

/*************************************************************************************
*  \Syntax          : EN_cardError_t getCardPAN(ST_cardData_t *cardData);
*  \Description     : This function will ask for the card's Primary Account Number and store it in card data.
*  \Parameters      : cardData -> Pointer to user card
*  \Return value:   : EN_cardError_t
************************************************************************************/
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    uint8 tmp[30];
    uint8 tmpLength = 0;

    /* Get and store card expiry date into tmp variable */
    printf("Card Number: ");
    scanf("%[^\n]%*c", tmp);
    tmpLength = (uint8)strlen(tmp);

    /* Check and Validate APN range */
    if (tmpLength < 16 || tmpLength > 19)
    {
        return CARD_WRONG_PAN;
    }

    /* Check and Validate that PAN only alphanumeric */
    for (uint8 i = 0; i < tmpLength; i++)
    {
        if (!isalnum(tmp[i]))
        {
            return CARD_WRONG_PAN;
        }
    }

    strcpy(cardData->primaryAccountNumber, tmp);
    return CARD_OK;
}

/* ================================================================================================================= */
/* ================                               END OF FILE: card.c                               ================ */
/* ================================================================================================================= */
