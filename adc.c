//
// Created by poper on 6/30/2026.
//

#include "adc.h"
#include <stdio.h>
#include <stdlib.h>
VoltageSamples * ConvertAdcRawToVoltages(ADCsample *  samples , Header  header) {
 VoltageSamples * voltage_samples;


 voltage_samples = malloc(header.sampleCount * sizeof(VoltageSamples) );

 if(voltage_samples == NULL) {
  printf("Error allocating Voltage samples in the memory \n");
  return NULL;
 }
 for (uint32_t i =0 ; i < header.sampleCount ; i++) {
  (voltage_samples+i)->voltage = (samples+i)->raw_value / 4095.0f * 3.3f;
 }

 return voltage_samples;

}