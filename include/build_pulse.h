/* Red Pitaya C API example Generating signal pulse on an external trigger 
 * This application generates a specific signal */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void build_pulse( unsigned int size, unsigned int start,unsigned int lead, unsigned int trail, unsigned int width, float * y);
