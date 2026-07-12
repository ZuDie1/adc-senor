#include <stdio.h>

#include "adc.h"
#include "io.h"
#include "report.h"
#include "stats.h"
#include <stdlib.h>
int main(void) {
    Header header;
    ADCsample * samples = readBinData("adc_sensor_log.bin",&header);
    VoltageSamples * vsamples=ConvertAdcRawToVoltages(samples,header);
    if( samples == NULL || vsamples ==NULL) {
        printf("Error reading adc_sensor_log.bin");
        return -1;
    }
    for(uint32_t i =0 ; i < header.sampleCount ; i ++) {
        printf("Rec : %u           Voltage :  %f \n" , i , vsamples[i].voltage);
    }
    StatisticsChannel statistics_channel[4];

    getStatistics(samples,header,vsamples,statistics_channel);
    getStdDev(samples,header,vsamples,statistics_channel);

    printf("Min of channel 0 is %f \n Max of channel 0 is %f \n",statistics_channel[0].min , statistics_channel[0].max);
    printf("Avg of channel 0 is %f \n Std dev of channel 0 is %f \n",statistics_channel[0].mean_voltage , statistics_channel[0].stdDev);

    FaultSamples fault_samples[4];

    getFaultsData(samples,header,vsamples,fault_samples);

    printf("Channel 0 faults : \n OverVoltages count : %d \n UnderVoltages count : %d \n Sensor fault count : %d \n",
        fault_samples[0].over_voltage , fault_samples[0].under_voltage ,fault_samples[0].sensor_flag);

    SequenceIntegrity  SequenceIntegrity;
    getSequenceIntegrity (samples,header,&SequenceIntegrity);
    printf("Out of order seq : %d \n",SequenceIntegrity.out_of_order_seq);
    printf("Missing seq : %d \n",SequenceIntegrity.missing_seq);

   GenerateResult_File("result.text",statistics_channel,fault_samples,SequenceIntegrity);

    free(samples);
    free(vsamples);
    return 0;
}
