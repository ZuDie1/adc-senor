//
// Created by poper on 6/30/2026.
//

#ifndef IO_H
#define IO_H

#include <stdint.h>
typedef struct { //24 byte 192
    uint32_t magic;
    uint16_t version;
    uint16_t channel_count;
    uint32_t sampleCount;
    uint32_t sample_rate_hz;
    uint8_t reserved[8];
}Header;

typedef struct __attribute__((__packed__)) { //16 byte --128 padding
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
    uint8_t reserved[2];
}ADCsample;

ADCsample * readBinData(char * filename , Header * h);
void printHeaderFile(Header * header);
void PrintSamples(ADCsample * samples , Header * h);

#endif //IO_H
