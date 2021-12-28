/**************************************************************/
/*                 Author    : Muhammad Ali Habash            */
/*                 Version   : 1.0                            */
/*                 Date      : 12/26/2021                     */
/*                 Last Edit : N/A                            */
/**************************************************************/


/**************************************************************/
/*                                                            */
/*                    Files Inclusions                        */
/*                                                            */
/**************************************************************/

#include "STACK_algorithm.h"

/**************************************************************/
/*                                                            */
/*                    End Of Section                          */
/*                                                            */
/**************************************************************/


/**************************************************************/
/*                                                            */
/*                    Macros                                  */
/*                                                            */
/**************************************************************/

#define TRUE  1
#define FALSE 0

/**************************************************************/
/*                                                            */
/*                    End Of Section                          */
/*                                                            */
/**************************************************************/


/**************************************************************/
/*                                                            */
/*                    Global Variables                        */
/*                                                            */
/**************************************************************/

int8_t          gs8_Top = -1;                                  // This is the top of the stack
gstrNode_t*  gpstr_Head = NULL;                                // This is the head of the linked list
uint16_t gu16_StackSize = 0;                                   // This is the size of the stack before changing it to a desired size

/**************************************************************/
/*                                                            */
/*                    End Of Section                          */
/*                                                            */
/**************************************************************/


/**************************************************************/
/*                                                            */
/*                    Functions Definitions                   */
/*                                                            */
/**************************************************************/

/******************************************************************************************/
/* Refer to the STACK_algorithm.h file to read the explanation of each function if needed */
/******************************************************************************************/

uint8_t check_input_is_digit (uint8_t* u8_Line)  
{
	uint32_t u32_LiteralIndex;
	
	for(u32_LiteralIndex = 0 ; u32_LiteralIndex < strlen(u8_Line)-1 ; u32_LiteralIndex++)
	{
		if ( !( ( *(u8_Line+u32_LiteralIndex) >='0')	&& ( *(u8_Line+u32_LiteralIndex) <= '9' ) ) )
		{
			return 0;
		}
	}
	
    return 1;
}

uint16_t extract_numbers (uint8_t* u8_Line)
{
	uint8_t u8_Index, u8_Number, u8_Weight;
	uint16_t u16_Sum = 0;
	u8_Weight        = strlen(u8_Line) - 2;
	for(u8_Index = 0 ; u8_Index < strlen(u8_Line) - 1 ; u8_Index++)
	{
	    u8_Number = ( (u8_Line[u8_Index] - 48 ) );
	    u16_Sum += ( u8_Number * pow(10, u8_Weight) ); 
		u8_Weight --;
    }
	return u16_Sum;
}

uint16_t select_stack_size ()
{
	uint8_t  u8_Line[256];
	uint8_t  u8_IsDigit;
	uint8_t  u8_NoChoice = TRUE;
	uint16_t u16_StackSize;
	
	while (u8_NoChoice)
	{
		printf("Choose stack size: ");
		fflush(stdin);
		fgets(u8_Line, sizeof(u8_Line), stdin);
		u8_IsDigit = check_input_is_digit(u8_Line);
		
		if(u8_IsDigit)
		{
			u8_NoChoice = FALSE;
			u16_StackSize = extract_numbers(u8_Line);
		}
		else 
			printf("\nWrong choice\n");
	}
	return u16_StackSize;
}

void push (uint8_t u8_data)
{
	gstrNode_t* pstr_Temp  = malloc(sizeof(gstrNode_t));
	pstr_Temp -> u8_Data   = u8_data;
	pstr_Temp -> pstr_next = NULL;
	
	if (gs8_Top < gu16_StackSize)
	{
		gs8_Top++;
	}
	if (gs8_Top == 0)
	{
		gpstr_Head = pstr_Temp;
	}
	else if (gs8_Top < gu16_StackSize)
	{
		gstrNode_t* pstr_Ptr = gpstr_Head;
		while (pstr_Ptr -> pstr_next != NULL)
		{
			pstr_Ptr = pstr_Ptr -> pstr_next;
		}
		pstr_Ptr -> pstr_next = pstr_Temp;
	}
	else 
	{
		printf("\nStack overflow\n");
	}
}

uint8_t pull ()
{
	gstrNode_t* pstr_Ptr;
	uint8_t pop_data;
	if (gs8_Top == 0)
	{
		pop_data = gpstr_Head -> u8_Data;
		free(gpstr_Head);
		gpstr_Head = NULL;
	}
	else if (gs8_Top > 0)
	{
		gstrNode_t* pstr_Ptr = gpstr_Head;
		while ( ( (pstr_Ptr -> pstr_next) -> pstr_next ) != NULL )
		{
			pstr_Ptr = pstr_Ptr -> pstr_next;
		}
		pop_data = (pstr_Ptr -> pstr_next)-> u8_Data;
		free(pstr_Ptr -> pstr_next);
		pstr_Ptr -> pstr_next = NULL;
	}
	else 
	{
		printf("\nEmpty Stack\n");
	}
	if (gs8_Top >= 0)
	{
		gs8_Top--;
	}		
	return pop_data;
}

void printStack()
{
	gstrNode_t* pstr_Ptr = gpstr_Head;
	while (pstr_Ptr != NULL)
	{
		printf("%c\n",pstr_Ptr->u8_Data);
		pstr_Ptr = pstr_Ptr -> pstr_next;
	}
}

uint8_t* balancedParentheses(uint8_t* expression)
{
	uint8_t u8_Index;
	for (u8_Index = 0 ; u8_Index < strlen(expression) - 1 ; u8_Index++)
	{
		if( ( expression[u8_Index] == '{' ) || ( expression[u8_Index] == '(' ) || ( expression[u8_Index] == '[' ) )
		{
			push(expression[u8_Index]);
		}
		else if( ( expression[u8_Index] == '}' ) ||  ( expression[u8_Index] == ')' ) || ( expression[u8_Index] == ']') )
		{
			push(expression[u8_Index]);
			if (gpstr_Head != NULL)
			{
			gstrNode_t* pstr_Ptr = gpstr_Head;
			if((pstr_Ptr -> pstr_next) != NULL)
			{
		        while((pstr_Ptr->pstr_next)->pstr_next != NULL)
		        {
			        pstr_Ptr = pstr_Ptr->pstr_next;
		        }
			    if((((pstr_Ptr->u8_Data) == '{') && (((pstr_Ptr->pstr_next)->u8_Data) == '}')) || (((pstr_Ptr->u8_Data) == '[') && (((pstr_Ptr->pstr_next)->u8_Data) == ']')) || (((pstr_Ptr->u8_Data) == '(') && ((pstr_Ptr->pstr_next)->u8_Data == ')')))
		        {
			        pull();
					pull();
		        }
			}
			}
		}
	}
	if(gpstr_Head == NULL)
	{
		return "\nBalanced\n";
	}
	else 
	{
		return "\nNot balanced\n";
	}
}

/**************************************************************/
/*                                                            */
/*                    End Of Section                          */
/*                                                            */
/**************************************************************/

uint8_t main()
{	
	uint8_t u8_Line[256];
	uint8_t au8_Result[20];
	gu16_StackSize  = select_stack_size();
	printf("\nEnter a string: ");
	fgets(u8_Line,sizeof(u8_Line),stdin);
	strcpy(au8_Result, balancedParentheses(u8_Line));
	printf("%s",au8_Result);
	return 0;
}
