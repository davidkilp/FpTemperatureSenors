// FpTemperatureSenors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include "MSCI2C.h"

int main()
{
    std::cout << "Temperature Sensors on I2C bus 0!\n";

    // get information about the available I2C busses:
    unsigned int nbrI2CControllers;
    const unsigned int I2CControllerNameArrLen = 10;	// number of I2C Controller friendly names
    const unsigned int I2CControllerNameLen = 40;		// max. length of an I2C Controller friendly name
    char* pI2CBusses = ListI2cControllers(&nbrI2CControllers);

    printf("Found %u I2C controllers\n", nbrI2CControllers);
    for (unsigned int i = 0; i < nbrI2CControllers; i++)
    {
        char* name = pI2CBusses + i * 40;
        printf("I2C controller %u is named: %s\n", i, name);
        //std::cout << "I2C Controller " << i << " is named: " << pI2CBusses[i].c_str() << std::endl;
    }

    // read from device to confirm presence
    bool ret;
    unsigned int i2cAddr = 0x48;
    unsigned int i2cSpeed = 400;
    unsigned int offset = 0x0F;
    unsigned int nbrBytes = 2;
    UCHAR ioBuf[10];
    unsigned int bytesRead;
    unsigned int bytesWritten;
    const char bus[] = "user";
    unsigned short deviceID;
    signed short rawtemp;
    double temp;

    // Do sensor at 0x48
    ret = read1(bus, i2cAddr, i2cSpeed, offset, nbrBytes, ioBuf, &bytesRead);
    if (ret)
        printf("We read %u bytes and returned 0x%02X%02X\n", bytesRead, ioBuf[0], ioBuf[1]);
    else
        printf("Read failed\n");
    deviceID = (ioBuf[0] << 8) + ioBuf[1];
    if (deviceID == 0x7500)
        printf("TMP1075 Sensor at 0x%02X found\n", i2cAddr);

    // Do sensor at 0x49
    i2cAddr = 0x49;
    ret = read1(bus, i2cAddr, i2cSpeed, offset, nbrBytes, ioBuf, &bytesRead);
    if (ret)
        printf("We read %u bytes and returned 0x%02X%02X\n", bytesRead, ioBuf[0], ioBuf[1]);
    else
        printf("Read failed\n");
    deviceID = (ioBuf[0] << 8) + ioBuf[1];
    if (deviceID == 0x7500)
        printf("TMP1075 Sensor at 0x%02X found\n", i2cAddr);

    // Configure Sensor at 0x48
    i2cAddr = 0x48;
    offset = 0x01;
    ioBuf[0] = 0x78;
    ioBuf[1] = 0xFF;
    ret = write1(bus, i2cAddr, i2cSpeed, offset, ioBuf, 2, &bytesWritten);
    if (ret)
        printf("Configured sensor at 0x%02X for continuous conversion\n", i2cAddr);
    else
        printf("Write failed\n");

    // Configure Sensor at 0x49
    i2cAddr = 0x49;
    offset = 0x01;
    ioBuf[0] = 0x78;
    ioBuf[1] = 0xFF;
    ret = write1(bus, i2cAddr, i2cSpeed, offset, ioBuf, 2, &bytesWritten);
    if (ret)
        printf("Configured sensor at 0x%02X for continuous conversion\n", i2cAddr);
    else
        printf("Write failed\n");

    printf("----------------------------------------------------\n");

    while (1)
    {
        // Now let's read the Temperature in reg 0x00 for 0x48
        i2cAddr = 0x48;
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
        printf("----------------------------------------------------\n");

        // Now let's read the Temperature in reg 0x00 for 0x49
        i2cAddr = 0x49;
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
        printf("----------------------------------------------------\n");

        Sleep(2000);
    }

    return 0;
}
