// FpTemperatureSenors.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <vector>
#include <format>
#include <chrono>
#include <Windows.h>
#include "MSCI2C.h"

void showUsage(void)
{
    std::cout << "Usage: " << std::endl;
    std::cout << "\t-h  This help" << std::endl;
    std::cout << "\t-f filename - where to send timestampped output > " << std::endl;
}


class InputParser {
public:
    InputParser(int& argc, char** argv) {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    /// @author iain
    const std::string& getCmdOption(const std::string& option) const {
        std::vector<std::string>::const_iterator itr;
        itr = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }
    /// @author iain
    bool cmdOptionExists(const std::string& option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option)
            != this->tokens.end();
    }
private:
    std::vector <std::string> tokens;
};

std::string get_file_timestamp()
{
    const auto now = std::chrono::system_clock::now();
    const auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream output_stream;

    struct tm time_info;
    const auto errno_value = localtime_s(&time_info, &in_time_t);
    if (errno_value != 0)
    {
        throw std::runtime_error("localtime_s() failed: " + std::to_string(errno_value));
    }

    output_stream << std::put_time(&time_info, "%Y-%m-%d.%H:%M:%S");
    return output_stream.str();
}

int main(int argc, char *argv[])
{
    bool saveOutput = false;
    std::ofstream outFile;

    std::cout << "Temperature Sensors on I2C bus 0!\n";
    
    InputParser input(argc, argv);
    if (input.cmdOptionExists("-h")) {
        showUsage();
        return 0;
    }

    if (input.cmdOptionExists("-f")) {

        const std::string& filename = input.getCmdOption("-f");
        if (!filename.empty()) {
            outFile = std::ofstream(filename, std::ios_base::app);
            saveOutput = true;
        }
    }

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
        if (saveOutput) {
            //std::string formattedString = std::format(" Temperature near CPU (sensor 0x{:02X}) is {:f} degrees C", i2cAddr, temp);
            std::string formattedString = std::format(", {:f}, ", temp);
            outFile << get_file_timestamp() << formattedString;
        }
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
        if (saveOutput) {
            //std::string formattedString = std::format(" Temperature near CPU (sensor 0x{:02X}) is {:f} degrees C", i2cAddr, temp);
            std::string formattedString = std::format("{:f}", temp);
            outFile << formattedString << std::endl;
        }
        printf("----------------------------------------------------\n");

        Sleep(2000);
    }

    return 0;
}
