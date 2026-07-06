//
// Created by poper on 6/30/2026.
//

#ifndef ADC_H
#define ADC_H
#include "io.h"

typedef struct {
    float voltage;
}VoltageSamples;

VoltageSamples * ConvertAdcRawToVoltages(ADCsample *  samples , Header  header);

#endif //ADC_H
