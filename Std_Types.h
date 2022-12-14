/**********************************************************************************************************************
*
*  FILE DESCRIPTION
*  -------------------------------------------------------------------------------------------------------------------
*  \file      : Std_Types.h
*
*  \category  : Common
*
*  \date      : 22 Sep. 2022
*
*  \brief     : Provision of Standard Types
*
*  \details   :
*
*********************************************************************************************************************/

#ifndef STD_TYPES_H
#define STD_TYPES_H

/* ================================================================================================================= */
/* ================                              GLOBAL CONSTANT MACROS                             ================ */
/* ================================================================================================================= */

#define ENABLE      1u
#define DISABLE     0u

#define E_OK        0u
#define E_NOT_OK    1u

/* ================================================================================================================= */
/* ================                         GLOBAL DATA TYPES AND STRUCTURES                        ================ */
/* ================================================================================================================= */

typedef unsigned char uint8;        // 0 .. 255
typedef unsigned short uint16;      // 0 .. 65,535
typedef unsigned int uint32;        // 0 .. 4,294,967,295
typedef unsigned long long uint64;  // 0 .. 18,446,744,073,709,551,615

typedef char sint8;                 // -128 .. +127
typedef short sint16;               // -32,768 .. +32,767
typedef int sint32;                 // -2,147,483,648 .. +2,147,483,647
typedef long long sint64;           // -9,223,372,036,854,775,808 .. 9,223,372,036,854,775,807

typedef float float32;
typedef double float64;

#endif /* STD_TYPES_H */

/* ================================================================================================================= */
/* ================                             END OF FILE: Std_Types.h                            ================ */
/* ================================================================================================================= */
