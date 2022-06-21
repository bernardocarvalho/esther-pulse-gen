/* Red Pitaya C API example Generating signal pulse on an external trigger 
 * This application generates a specific signal */

//#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>

#include "build_pulse.h"

/* Filter coefficient value: A < 1 */
#define A_VALUE                ((float)(0.01))

//void IIR_Filter_First_Order(float x_input) {
//	static float y_history = 0.0;
//}
// Width must be larger than Lead
void build_pulse( unsigned int size, unsigned int start,unsigned int lead, unsigned int trail, unsigned int width, float * y){
	// one pulse of width= 980 * 8ns = 7.4 us
	float y_history = 0.0;
	for (int i = 0; i < size; i++){
		if (i> start && i< start + lead){ 
			y[i] = 1.0 * (i - start)/lead;
		}
		else if (i> start + lead  && i < start + width) 
			y[i] = 1.;
		else if (i> start + width && i < start + width + trail){
			y[i] = 1.0 *(1.0 - ((float)(i - start - width))/trail);
//	printf("i: %d; y: %f, ", i, y[i]);
		}
		else
			y[i] = 0;
	} 
	for (int i = 0; i < size; i++){
		y_history += A_VALUE * (y[i] - y_history); 
		y[i] = y_history;
	}
}
