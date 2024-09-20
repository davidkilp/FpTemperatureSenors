// CppTempClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

#include "FpTempSensor.h"

int main()
{
    double temperature;
    std::cout << "Temperature Sensors Test!\n";

    //initialize sensors
    FpTempSensor* pSensor = FpTemp_Instantiate();

    while (1) {
        temperature = FpTS_getTemperature(pSensor, TempSensor::TOP);
        printf("Top (0x%02X) temperature: %f degrees C\n", TempSensor::TOP, temperature);

        temperature = FpTS_getTemperature(pSensor, TempSensor::CPU);
        printf("CPU (0x%02X) temperature: %f degrees C\n", TempSensor::CPU, temperature);
        Sleep(1000);
    }
    
    return 0;
}
