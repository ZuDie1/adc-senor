#include <stdio.h>

#include "adc.h"
#include "io.h"
#include "stats.h"

int main(void) {
    Header header;
    ADCsample * samples = readBinData("adc_sensor_log.bin",&header);
    VoltageSamples * vsamples=ConvertAdcRawToVoltages(samples,header);
    for(uint32_t i =0 ; i < header.sampleCount ; i ++) {
        printf("Rec : %u           Voltage :  %f \n" , i , vsamples[i].voltage);
    }
    StatisticsChannel statistics_channel[4];

    getStatistics(samples,header,vsamples,statistics_channel);
    printf("Min of channel 0 is %f \n Max of channel 0 is %f \n",statistics_channel[0].min , statistics_channel[0].max);


    return 0;
}
