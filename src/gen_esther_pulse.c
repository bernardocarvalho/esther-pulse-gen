/* Red Pitaya C API example Generating signal pulse on an external trigger 
 * This application generates a specific signal */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rp.h"
#include "build_pulse.h"


#define MAX_FREQ 125000000
int main(int argc, char **argv){

        /* Burst count */


        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
                fprintf(stderr, "Rp api init failed!\n");
        }

	unsigned int buff_size = 16384;
	float *x = (float *)malloc(buff_size * sizeof(float));
	// one pulse of width= 980 * 8ns = 7.4 us
	build_pulse(buff_size, 10, 1000, 1000, 4000, x);
	rp_GenArbWaveform(RP_CH_1, x, buff_size); 
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
//        rp_GenFreq(RP_CH_1, 1000000);
        rp_GenFreq(RP_CH_1, MAX_FREQ/buff_size); // whole buffer corresponds to ~0.13 ms
        rp_GenAmp(RP_CH_1, 1.0);

        rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
        rp_GenBurstCount(RP_CH_1, 1);
        rp_GenBurstRepetitions(RP_CH_1, 2);
//Set P total time of one burst in in micro seconds. This includes the signal and delay.
        rp_GenBurstPeriod(RP_CH_1, 500);
        rp_GenTrigger(1);
        sleep(1);
        rp_GenOutEnable(RP_CH_1);
        rp_Release();
	free(x);
}



