# ADC Sensor Data Processor

Simple C program for reading and analysing ADC sensor data from a binary file.

## Files

- main.c
- io.c / io.h
- adc.c / adc.h
- stats.c / stats.h
- report.h
- CMakeLists.txt

## Build with CLion

1. Open the project folder in CLion.
2. Let CMake load the project.
3. Build the project.
4. Run the program.

## Build with GCC

Compile:

```bash
gcc main.c io.c adc.c stats.c -o adc_program -lm
```

Run:

```bash
./adc_program
```

## Input File

Place the file below in the project folder:

```
adc_sensor_log.bin
```

## Output

The program creates:

```
result.txt
```
