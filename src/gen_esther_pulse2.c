/* Red Pitaya C API example Generating signal pulse on an external trigger 
 * This application generates a specific signal */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rp.h"
#include "build_pulse.h"

#define MAX_FREQ 125000000
#define MAX_BUFF_SIZE 16384

int main(int argc, char **argv){
        /* Print error, if rp_Init() function failed */
        if(rp_Init() != RP_OK){
                fprintf(stderr, "Rp api init failed!\n");
        }

	int buff_size = MAX_BUFF_SIZE;
	float *x = (float *)malloc(buff_size * sizeof(float));
	// one pulse of width= 980 * 8ns = 7.4 us
	//1 us = 10 mm @10km/s
	// lead ~= 1.6 us
	build_pulse(buff_size, 100, 300, 300, 8000, x);
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
	rp_GenArbWaveform(RP_CH_1, x, buff_size); 
//        rp_GenFreq(RP_CH_1, 1000000);
        rp_GenFreq(RP_CH_1, MAX_FREQ/buff_size); // whole buffer corresponds to ~0.13 ms
        rp_GenAmp(RP_CH_1, 1.0);

	float *x2 = (float *)malloc(buff_size * sizeof(float));
	// one pulse of width= 980 * 8ns = 7.4 us
	build_pulse(buff_size, 4750, 300, 300, 2000, x2);
        rp_GenWaveform(RP_CH_2, RP_WAVEFORM_ARBITRARY);
	rp_GenArbWaveform(RP_CH_2, x2, buff_size); 
        rp_GenFreq(RP_CH_2, MAX_FREQ/buff_size); // whole buffer corresponds to ~0.13 ms
        rp_GenAmp(RP_CH_2, 1.0);

        rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
        rp_GenBurstCount(RP_CH_1, 1);
        rp_GenBurstRepetitions(RP_CH_1, 1);
        rp_GenBurstPeriod(RP_CH_1, 200);

        rp_GenMode(RP_CH_2, RP_GEN_MODE_BURST);
        rp_GenBurstCount(RP_CH_2, 1);
        rp_GenBurstRepetitions(RP_CH_2, 1);
        rp_GenBurstPeriod(RP_CH_2, 500);
        
        rp_GenOutEnableSync(true);
        sleep(0.2);
        rp_GenTrigger(3); // Gen trigger on both channels
        rp_Release();
	free(x);
	free(x2);
}



