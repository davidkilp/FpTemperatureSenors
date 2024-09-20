using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using static FpTempDisplay.TempSensors;

namespace FpTempDisplay
{
    internal class TempSensors
    {
        public enum TEMP_SENSOR
        {
            TOP = 0x49,
            CPU = 0x48
        };

        #region dllImports
        // FpTempSensors c++ DLL here - needs a project reference to this dll in C# project also
        private const string _dllImportPath = @"FpTempSensorDll.dll";

        // External C++ Functions 
        [DllImport(_dllImportPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr FpTemp_Instantiate();

        [DllImport(_dllImportPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern double FpTS_getTemperature(IntPtr p, TEMP_SENSOR sensor);
        #endregion

    }
}
