/**********************************************************************/
/* Freeware Demo SW from the www.dsp-weimich.com                      */
/* Version 1.1                                                        */
/* IIRfirstOrderFixedPoint.c                                          */
/* IIR Filter First Order                                             */
/* H(z) = A/(1-(1-A)z^-1)                                             */         
/* y(n) = y(n-1)+A(x(n)-y(n-1))                                       */
/* A = Ts/(Ts+tau)                                                    */
/*                                                                    */
/* Update History                                                     */
/* 22.03.2021 Version 1.1                                             */
/* - compilation error bugfix                                         */
/* - insert the test in main()                                        */
/*                                                                    */
/**********************************************************************/

#include "IIRfirstOrderFloat.h"

/* Filter coefficient value: A < 1 */
#define A_VALUE                ((float)(0.24))
/* Round */
#define ROUND_VALUE            ((float)(0.5))
/* Round Macro */
#define ROUND_MACRO(value)     ((sint16)(value>=0?(value+ROUND_VALUE):(value-ROUND_VALUE)))

/* Filter history */
float y_history = 0.0;

/*
 IIR Filter First Order
 Input
 sint16 x_input - filter input x(n)
 Return
 sint16 - filter output y(n)
*/
sint16 IIR_Filter_First_Order(sint16 x_input)
{
	sint16 y_round;
	y_history = y_history + A_VALUE*(((float)x_input - y_history));
	y_round = ROUND_MACRO(y_history);
	return y_round;
}

/* Only Test */
int main()
{
	/* Check Round Macro */
	float  flt_value;
	sint16 int_value;
	
	flt_value = 12.6;
	int_value = ROUND_MACRO(flt_value);
	
	flt_value = 12.1;
	int_value = ROUND_MACRO(flt_value);

	flt_value = -12.6;
	int_value = ROUND_MACRO(flt_value);
	
	flt_value = -12.1;
	int_value = ROUND_MACRO(flt_value);
	
	/* IIR Filter */
	#define JUMP_STEP    (32767u)
	#define BUFFER_SIZE  (100u)
	uint16 index;
    sint16 y_buffer_output[BUFFER_SIZE];
	for(index=0;index<BUFFER_SIZE;index++)
	{
		y_buffer_output[index]=IIR_Filter_First_Order(JUMP_STEP);
	}		

    return 0;
}
