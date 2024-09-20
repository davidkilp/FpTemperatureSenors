#pragma once

#ifdef FPTEMPSENSORDLL_EXPORTS		// <LIBNAME>_EXPORT
#define TEMPSENSOR_API __declspec(dllexport)
#else
#define TEMPSENSOR_API __declspec(dllimport)
#endif

enum class TempSensor 
{
	TOP = 0x49,
	CPU	= 0x48
};

/**
* Face Pod Temperature Sensor 
*/
class FpTempSensor {
private:
	unsigned int i2cSpeed = 400;
	const char *bus = "user";

public:
	FpTempSensor();
	double getTemperature(TempSensor sensor);
};

// Helper methods for constructor and exported methods
extern "C" TEMPSENSOR_API FpTempSensor* FpTemp_Instantiate();

extern "C" TEMPSENSOR_API double FpTS_getTemperature(FpTempSensor* p, TempSensor sensor);
