//
// Created by poper on 6/30/2026.
//

#include "io.h"

#include <stdio.h>
#include <stdlib.h>

ADCsample * readBinData(char * filename , Header * h)
{
   FILE * binaryFile ;
   binaryFile=fopen(filename,"rb");
   //validate file ,

   if (binaryFile== NULL) {
      printf("there was a problem with the file name : %s    try again with different name \n",filename);
      return NULL;
   }
   fread(h,sizeof(Header),1,binaryFile);
   printHeaderFile(h);

   if (h->magic != 0xADC1BEEF) {
      //end the program
      printf("Magic number from header file is invalid \n");
      fclose(binaryFile);
      return NULL;
   }

   if(h->sampleCount <=0) {
      printf("There is no records in the file \n");
      fclose(binaryFile);
      return NULL;
   }

   //read the records
   ADCsample * samples = malloc(h->sampleCount * sizeof(ADCsample) );

   fread(samples,sizeof(ADCsample) , h->sampleCount ,binaryFile);

   PrintSamples(samples,h);

   fclose(binaryFile);
   return samples;
}

void printHeaderFile(Header * header) {
   printf("Header info : \n");
   printf("Magic number is :0x%X\n Version is %u  \n Channel count is : %u  \n Sample count is : %u \n Sample rate is : %u \n ",
   header->magic , header->version , header->channel_count , header->sampleCount ,header->sample_rate_hz);
}

void PrintSamples(ADCsample * samples,Header *h) {
   printf("Rec   TimeStamp        Channel     Raw    Temp    Status     Seq \n");
   for (uint32_t i=0;i<h->sampleCount;i++) {
      printf("%u     %f            %u         %u     %u       0x%X        %u   \n" ,
         i , samples[i].timestamp , samples[i].channel_id , samples[i].raw_value , samples[i].temperature,
         samples[i].status_flags , samples[i].sequence_number);
   }
}
