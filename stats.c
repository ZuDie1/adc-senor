//
// Created by poper on 6/30/2026.
//

#include "stats.h"

void getStatistics(ADCsample * samples , Header header , VoltageSamples * vsamples , StatisticsChannel stat[4]) {

    for(uint32_t i=0 ; i< 4; i++) {
        stat[i].max=0;
        stat[i].min=10;
    }

    float sum_voltages[4]={0};
    int voltage_count_per_channel [4] ={0};

    for ( uint32_t i=0 ; i < header.sampleCount ; i++) { //0 - 3999

        uint8_t current_channel = (samples+i)->channel_id; //0 ,1 , 2 ,3

        float current_voltage= (vsamples+i)->voltage;

        voltage_count_per_channel[current_channel] = voltage_count_per_channel[current_channel]+1;
        sum_voltages[current_channel]=sum_voltages[current_channel] + current_voltage;

        //get the min , get the max
        if(current_voltage > stat[current_channel].max) {
            stat[current_channel].max=current_voltage;
        }

        if(current_voltage < stat[current_channel].min) {
            stat[current_channel].min=current_voltage;
        }

    }
    //mean
    stat[0].mean_voltage=sum_voltages[0]/voltage_count_per_channel[0];
    stat[1].mean_voltage=sum_voltages[1]/voltage_count_per_channel[1];
    stat[2].mean_voltage=sum_voltages[2]/voltage_count_per_channel[2];
    stat[3].mean_voltage=sum_voltages[3]/voltage_count_per_channel[3];

    getStdDev(samples,header,vsamples,stat,voltage_count_per_channel);

}

void getStdDev(ADCsample * samples , Header header , VoltageSamples * vsamples , StatisticsChannel stat[4],int voltage_count_per_channel[4]) {
    //std dev :
    //1- we get the variance : current voltage
    float total_diff_squares[4];
    for ( uint32_t i=0 ; i < header.sampleCount ; i++) {
        uint8_t current_channel = (samples+i)->channel_id; //0 ,1 , 2 ,3
        //variance :
        float volt_difference = vsamples[i].voltage - stat[current_channel].mean_voltage;
        float diff_squares = volt_difference * volt_difference;
        total_diff_squares[current_channel] = total_diff_squares[current_channel]+diff_squares;
    }
    //std
    stat[0].stdDev=total_diff_squares[0]/voltage_count_per_channel[0];
    stat[1].stdDev=total_diff_squares[1]/voltage_count_per_channel[1];
    stat[2].stdDev=total_diff_squares[2]/voltage_count_per_channel[2];
    stat[3].stdDev=total_diff_squares[3]/voltage_count_per_channel[3];
}
