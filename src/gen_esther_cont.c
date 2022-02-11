/* Red Pitaya C API example Generating signal pulse on an external trigger 
 * This application generates a specific signal */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rp.h"

#define MAX_FREQ 125000000
int main(int argc, char **argv){

        /* Burst count */


        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
                fprintf(stderr, "Rp api init failed!\n");
        }

	int buff_size = 16384;
	float *x = (float *)malloc(buff_size * sizeof(float));
	// one pulse of width= 980 * 8ns = 7.4 us
	for (int i = 0; i < buff_size; ++i){
		if (i> 20 && i<1000) 
			x[i] = 1.;
		else if (i> 4096 && i<5000) 
			x[i] = 1.;
		else
			x[i] = 0;
	} 
	rp_GenArbWaveform(RP_CH_1, x, buff_size); 
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
//        rp_GenFreq(RP_CH_1, 1000000);
        //rp_GenFreq(RP_CH_1, 5000); // period 200 us
        rp_GenFreq(RP_CH_1, 2500); // period 400 us
        rp_GenAmp(RP_CH_1, 0.5);

        //rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
//        rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
//        rp_GenBurstCount(RP_CH_1, 3);
//        rp_GenBurstRepetitions(RP_CH_1, 2);
//        rp_GenBurstPeriod(RP_CH_1, 20);
//        rp_GenTrigger(1);
//        sleep(1);
        rp_GenOutEnable(RP_CH_1);
        rp_Release();
}

