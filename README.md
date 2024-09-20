# FpLtg - HID Gate on-board Temperature Sensors

## Summary
Provides access to the two on-board Temperature Sensors which are located
near the camera at the top and in the middle close to the CPU module.

Solution includes separate builds for :

 * C++ DLL that hides all the low level details: FpTempSensorDll.dll
 * A Cpp command line demo program that uses the DLL: CppTemClient.exe
 * A .NET Forms GUI demo application using the DLL through interop services: FpTempDisplay.exe
 
The primary output is the FpTempSensorDll.dll which can be included in users program to control the lighting strips.

## Requirements
* Visual Studio 2022
* .NET 8 Runtime must be installed on hosted system. See: [.NET 8 Runtime Installer:](https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-desktop-8.0.2-windows-x64-installer)
* MSCI2C64.dll from Avnet Embedded. This provides an PICMG Embedded Application Programming Interface (EAPI) to the I2C interface on 
	the underlying COM-Express module via A copy is included here but the original can be obtained from [[Avnet MSC EAPI NG Win10 Win11 x64](https://embedded.avnet.com/software-tools/#msc_eapi_ng])


## API

The FpTempSensorDll.dll provides the following API for user programs:

```
extern "C" TEMPSENSOR_API FpTempSensor* FpTemp_Instantiate();

extern "C" TEMPSENSOR_API double FpTS_getTemperature(FpTempSensor* p, TempSensor sensor);
```


## Usage

Find the .NET GUI application, FpTempDisplay.exe, and launch it. 

![screenshot](https://github.com/davidkilp/FpLtg/blob/master/FpTempDisplay_screenshot.jpg)

Click the Start button will intitiate a update of the temperature sensors every 2-seconds.

