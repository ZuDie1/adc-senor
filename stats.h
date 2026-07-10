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

typedef struct {
    int over_voltage; // >3
    int under_voltage;// <0.3
    int sensor_flag;// 0x01
}FaultSamples;
void getStatistics(ADCsample * samples , Header header , VoltageSamples * vsamples , StatisticsChannel stat[4]);
void getStdDev(ADCsample * samples , Header header , VoltageSamples * vsamples , StatisticsChannel stat[4] , int voltage_count_per_channel[4]);
void getFaultsData(ADCsample * samples , Header header , VoltageSamples * vsamples , FaultSamples fautls[4]);
#endif //STATS_H
