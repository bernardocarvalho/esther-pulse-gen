/* Red Pitaya C API example Generating signal pulses on both channels 
 * This application generates a specific signal 
https://redpitaya.readthedocs.io/en/latest/appsFeatures/examples/genRF-exm2.html

https://redpitaya.readthedocs.io/en/latest/appsFeatures/remoteControl/remoteControl.html#list-of-supported-scpi-commands

 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rp.h"

#define MAX_FREQ 125000000
#define MAX_BUFF_SIZE 16384

int main(int argc, char **argv){

	/* Burst count */


	/* Print error, if rp_Init() function failed */
	if(rp_Init() != RP_OK){
		fprintf(stderr, "Rp api init failed!\n");
	}

	rp_GenSynchronise(); // The generator is reset on both channels.

	int buff_size = MAX_BUFF_SIZE;
	float *x = (float *) malloc(buff_size * sizeof(float));
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
	rp_GenMode(RP_CH_1, RP_GEN_MODE_BURST);
	rp_GenBurstCount(RP_CH_1, 1);
	rp_GenBurstRepetitions(RP_CH_1, 65536);  // set to 65536 for INF pulses
	rp_GenBurstPeriod(RP_CH_1, 5000);

	rp_GenOutEnable(RP_CH_1);

	rp_GenWaveform(RP_CH_2, RP_WAVEFORM_ARBITRARY);
	rp_GenFreq(RP_CH_2, MAX_FREQ/buff_size); // whole buffer corresponds to ~0.13 ms
	rp_GenAmp(RP_CH_2, 1.0);
	rp_GenArbWaveform(RP_CH_2, x, buff_size); 

	rp_GenMode(RP_CH_2, RP_GEN_MODE_BURST);
	rp_GenBurstCount(RP_CH_2, 1);
	rp_GenBurstRepetitions(RP_CH_2, 65536);  // set to 65536 for INF pulses
	rp_GenBurstPeriod(RP_CH_2, 5000);

	rp_GenOutEnable(RP_CH_2);

	rp_GenOutEnableSync(true);
	//rp_GenTriggerOnly(RP_CH_1);
	//rp_GenTriggerOnly(RP_CH_2);
	// sleep(0.2);

	rp_GenTrigger(3); // Gen trigger on both channels

	//sleep(10.0);
	/* Release rp resources */
	rp_Release();
	free(x);

	return 0;
}
// vim: syntax=c ts=4 sw=4 sts=4 sr noet

