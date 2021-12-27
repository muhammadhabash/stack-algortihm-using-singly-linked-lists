/**************************************************************/
/*                 Author    : Muhammad Ali Habash            */
/*                 Version   : 1.0                            */
/*                 Date      : 12/26/2021                     */
/*                 Last Edit : N/A                            */
/**************************************************************/

#ifndef __STACK_ALGORITHM_H__
#define __STACK_ALGORITHM_H__

/**************************************************************/
/*                                                            */
/*                    Files Inclusions                        */
/*                                                            */
/**************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "STD_types.h"

/**************************************************************/
/*                                                            */
/*                    End Of Section                          */
/*                                                            */
/**************************************************************/


/**************************************************************/
/*                                                            */
/*                    Structs Definitions                     */
/*                                                            */
/**************************************************************/

typedef struct gstrNode_t
{
	uint8_t u8_Data;
	struct  gstrNode_t* pstr_next;
}gstrNode_t;

/**************************************************************/
/*                                                            */
/*                    End Of Section                          */
/*                                                            */
/**************************************************************/


/**************************************************************/
/*                                                            */
/*                    Functions Protoypes                     */
/*                                                            */
/**************************************************************/

uint8_t check_input_is_digit (uint8_t* u8_line);               // This function is used to check whether input consists only of digits or not
uint16_t extract_numbers (uint8_t* u8_line);                   // This function converts a number from string format to integer format
uint16_t select_stack_size ();                                 // This function selects the size of the stack
void push (uint8_t u8_data);                                   // This function pushes data to the stack by means of a linked list
uint8_t pull ();                                               // This function pulls data from the stack by means of a linked list
void printStack();                                             // This function prints the current stack
uint8_t* balancedParentheses(uint8_t* expression);              // This function checks whether the expression passed to it is balanced or not, this is achieved by popping each opening and closing pair, if the stack is empty then the expression is balanced. otherwise, not balanced.

/**************************************************************/
/*                                                            */
/*                    End Of Section                          */
/*                                                            */
/**************************************************************/


#endif