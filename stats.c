//
// Created by poper on 6/30/2026.
//

#include "stats.h"
#include "math.h"
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


}

void getStdDev(ADCsample * samples , Header header , VoltageSamples * vsamples , StatisticsChannel stat[4]) {
    //std dev :
    int voltage_count_per_channel [4] ={0};

    //1- we get the variance : current voltage
    float total_diff_squares[4];
    for ( uint32_t i=0 ; i < header.sampleCount ; i++) {
        uint8_t current_channel = (samples+i)->channel_id; //0 ,1 , 2 ,3
        //variance :
        float volt_difference = vsamples[i].voltage - stat[current_channel].mean_voltage;
        float diff_squares = volt_difference * volt_difference;
        total_diff_squares[current_channel] = total_diff_squares[current_channel]+diff_squares;
        voltage_count_per_channel[current_channel]++;
    }
    //std
       float var_ch0=total_diff_squares[0]/voltage_count_per_channel[0];
       float var_ch1=total_diff_squares[1]/voltage_count_per_channel[1];
       float var_ch2=total_diff_squares[2]/voltage_count_per_channel[2];
       float var_ch3=total_diff_squares[3]/voltage_count_per_channel[3];

    stat[0].stdDev=sqrt(var_ch0);
    stat[1].stdDev=sqrt(var_ch1);
    stat[2].stdDev=sqrt(var_ch2);
    stat[3].stdDev=sqrt(var_ch3);


}
void getFaultsData(ADCsample * samples , Header header , VoltageSamples * vsamples , FaultSamples fautls[4]) {
    for(uint32_t i=0 ; i< 4; i++) {
        fautls[i].over_voltage=0;
        fautls[i].under_voltage=0;
        fautls[i].sensor_flag=0;
    }
    for ( uint32_t i=0 ; i < header.sampleCount ; i++) {
        uint8_t current_channel = (samples+i)->channel_id;

        if ( (samples+1)->status_flags & 0x01 ) {
            fautls[current_channel].sensor_flag++;
        }

        if((vsamples+i)->voltage > 3.0f) {
            fautls[current_channel].over_voltage++;
        }

        if((vsamples+i)->voltage < 0.3f) {
            fautls[current_channel].under_voltage ++;

        }
    }
}
void getSequenceIntegrity(ADCsample * samples , Header header  , SequenceIntegrity * sequence) {
    sequence->missing_seq=0;
    sequence->out_of_order_seq=0;
    for ( uint32_t i=1 ; i < header.sampleCount ; i++) {
        uint32_t expected_seq= (samples+i-1)->sequence_number+1;

        uint32_t current_seq= (samples+i)->sequence_number;

        if ( current_seq > expected_seq) {
            sequence->missing_seq++;
        }
        if(current_seq < expected_seq) {
            sequence->out_of_order_seq++;
        }
    }
}