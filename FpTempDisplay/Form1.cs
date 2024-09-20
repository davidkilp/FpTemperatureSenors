using System;
using System.ComponentModel;
using static FpTempDisplay.TempSensors;

namespace FpTempDisplay
{
    public partial class Form1 : Form
    {
        IntPtr pSensors = 0;
        bool doUpdate = false;

        public Form1()
        {
            InitializeComponent();
            initTempSensors();
            button1.Enabled = true;
            button2.Enabled = false;
            label1.Text = "init";
        }

        private void initTempSensors()
        {
            pSensors = TempSensors.FpTemp_Instantiate();
            updateTemperatures();
        }

        private void updateTemperatures()
        {
            //Random random = new Random();
            //double tempTop = random.NextDouble();
            double tempTop = TempSensors.FpTS_getTemperature(pSensors, TEMP_SENSOR.TOP);
            labelTTop.Text = tempTop.ToString();

            //tempTop = random.NextDouble();
            tempTop = TempSensors.FpTS_getTemperature(pSensors, TEMP_SENSOR.CPU);
            labelTCPU.Text = tempTop.ToString();
        }

        // Start background task
        private async void button1_Click(object sender, EventArgs e)
        {
            label1.Text = "running";   
            button1.Enabled = false;
            button2.Enabled = true;
            doUpdate = true;

            // start asynchronous operation
            await Task.Run(() =>
            {
                TimeConsumingOperation();
            });
        }

        // Cancel background task
        private void button2_Click(object sender, EventArgs e)
        {
            label1.Text = "cancel";
            button1.Enabled = true;
            button2.Enabled = false;
            doUpdate = false;
        }

        private void InvokeUI(Action a)
        {
            this.BeginInvoke(new MethodInvoker(a));
        }

        // time consuming operation
        private void TimeConsumingOperation()
        {

            while (doUpdate)
            {
                InvokeUI(() =>
                {
                    updateTemperatures();

                });
                System.Threading.Thread.Sleep(2000);
            }
        }

    }
}
