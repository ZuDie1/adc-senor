cmake_minimum_required(VERSION 3.28)
project(adc_sensor C)

set(CMAKE_C_STANDARD 99)

add_executable(adc_sensor main.c
        io.c
        io.h
        adc.c
        adc.h
        stats.c
        stats.h
        report.h)
