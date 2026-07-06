#include <stdio.h>

#include "adc.h"
#include "io.h"
int main(void) {
    Header header;
    ADCsample * samples = readBinData("adc_sensor_log.bin",&header);
    VoltageSamples * vsamples=ConvertAdcRawToVoltages(samples,header);
    for(uint32_t i =0 ; i < header.sampleCount ; i ++) {
        printf("Rec : %u           Voltage :  %f \n" , i , vsamples[i].voltage);
    }
    return 0;
}
