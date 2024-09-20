#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include <iostream>
#include <iomanip>
#include <format>
#include <Windows.h>

#include "FpTempSensor.h"
#include "MSCI2C.h"

FpTempSensor::FpTempSensor()
{
	// Initialize the sensor for continuous operation mode, etc.
    bool ret;
    unsigned int i2cAddr = 0x48;
    unsigned int offset = 0x01;
    unsigned int nbrBytes = 2;
    UCHAR ioBuf[10];
    unsigned int bytesWritten;
    unsigned int bytesRead;
    unsigned short deviceID;

    // check TOP sensor is present
    i2cAddr = (unsigned int)TempSensor::TOP;
    offset = 0x0F;
    ret = read1(bus, i2cAddr, i2cSpeed, offset, nbrBytes, ioBuf, &bytesRead);
    if (ret)
        printf("We read %u bytes from i2c=0x%02X and returned 0x%02X%02X\n", bytesRead, i2cAddr, ioBuf[0], ioBuf[1]);
    else
        printf("Read failed\n");
    deviceID = (ioBuf[0] << 8) + ioBuf[1];
    if (deviceID == 0x7500)
        printf("TMP1075 Sensor at 0x%02X found\n", i2cAddr);

    // check CPU sensor is present
    i2cAddr = (unsigned int)TempSensor::CPU;
    offset = 0x0F;
    ret = read1(bus, i2cAddr, i2cSpeed, offset, nbrBytes, ioBuf, &bytesRead);
    if (ret)
        printf("We read %u bytes from i2c=0x%02X and returned 0x%02X%02X\n", bytesRead, i2cAddr, ioBuf[0], ioBuf[1]);
    else
        printf("Read failed\n");
    deviceID = (ioBuf[0] << 8) + ioBuf[1];
    if (deviceID == 0x7500)
        printf("TMP1075 Sensor at 0x%02X found\n", i2cAddr);


    i2cAddr = (unsigned int)TempSensor::TOP;  // 0x48;
    offset = 0x01;
    ioBuf[0] = 0x78;
    ioBuf[1] = 0xFF;
    ret = write1(bus, i2cAddr, i2cSpeed, offset, ioBuf, 2, &bytesWritten);
    if (ret)
        printf("Configured sensor at 0x%02X for continuous conversion\n", i2cAddr);
    else
        printf("Write failed\n");
    ret = read1(bus, i2cAddr, i2cSpeed, offset, 2, ioBuf, &bytesRead);
    if (ret)
        printf("We read %u bytes from i2c=0x%02X and returned 0x%02X%02X\n", bytesRead, i2cAddr, ioBuf[0], ioBuf[1]);

    i2cAddr = (unsigned int)TempSensor::CPU;  // 0x49;
    offset = 0x01;
    ioBuf[0] = 0x78;
    ioBuf[1] = 0xFF;
    ret = write1(bus, i2cAddr, i2cSpeed, offset, ioBuf, 2, &bytesWritten);
    if (ret)
        printf("Configured sensor at 0x%02X for continuous conversion\n", i2cAddr);
    else
        printf("Write failed\n");
    ret = read1(bus, i2cAddr, i2cSpeed, offset, 2, ioBuf, &bytesRead);
    if (ret)
        printf("We read %u bytes from i2c=0x%02X and returned 0x%02X%02X\n", bytesRead, i2cAddr, ioBuf[0], ioBuf[1]);

}

double FpTempSensor::getTemperature(TempSensor sensor)
{
    bool ret;
    unsigned int i2cAddr = 0x48;
    unsigned int offset = 0x00;
    unsigned int nbrBytes = 2;
    UCHAR ioBuf[10];
    unsigned int bytesRead;
    signed short rawtemp;
    double temp = 0.0;
    
    // read the specified Sensor over I2C interface
    i2cAddr = (unsigned int) sensor;
    offset = 0x00;
    memset(ioBuf, 0, sizeof(ioBuf));
    ret = read1(bus, i2cAddr, i2cSpeed, offset, nbrBytes, ioBuf, &bytesRead);
    if (ret)
        printf("We read %u bytes and returned 0x%02X%02X\n", bytesRead, ioBuf[0], ioBuf[1]);
    else
        printf("Read failed\n");

    rawtemp = ((ioBuf[0] << 8) + (ioBuf[1])) >> 4;
    printf("Raw temp is %d (0x%0X)\n", rawtemp, rawtemp);
    temp = rawtemp * 0.0625;
    printf("Temperature on sensor 0x%02X is %f degrees C\n", i2cAddr, temp);

    return temp;
}

// Helper methods for constructor and exported methods
extern "C" TEMPSENSOR_API FpTempSensor* FpTemp_Instantiate()
{
    return new FpTempSensor();
}

extern "C" TEMPSENSOR_API double FpTS_getTemperature(FpTempSensor* p, TempSensor sensor)
{
    return p->getTemperature(sensor);
}
