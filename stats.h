//
// Created by poper on 6/30/2026.
//

#ifndef STATS_H
#define STATS_H
#include "adc.h"
#include "io.h"

//mean , min , max , stdDev for each channel ( VOLTAGES )
typedef struct {
    float min ;
    float max ;
    float mean_voltage;
    float stdDev;
}StatisticsChannel;

void getStatistics(ADCsample * samples , Header header , VoltageSamples * vsamples , StatisticsChannel stat[4]);

#endif //STATS_H
