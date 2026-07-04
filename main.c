#include <stdio.h>

#include "io.h"
int main(void) {
    Header header;
    ADCsample * samples = readBinData("adc_sensor_log.bin",&header);
    return 0;
}
