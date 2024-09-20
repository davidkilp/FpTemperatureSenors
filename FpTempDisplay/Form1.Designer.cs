namespace FpTempDisplay
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            labelTop = new Label();
            labelCPU = new Label();
            button1 = new Button();
            labelTTop = new Label();
            labelTCPU = new Label();
            button2 = new Button();
            label1 = new Label();
            SuspendLayout();
            // 
            // labelTop
            // 
            labelTop.AutoSize = true;
            labelTop.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            labelTop.Location = new Point(108, 76);
            labelTop.Name = "labelTop";
            labelTop.Size = new Size(207, 30);
            labelTop.TabIndex = 0;
            labelTop.Text = "Temperature Top (°C)";
            // 
            // labelCPU
            // 
            labelCPU.AutoSize = true;
            labelCPU.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            labelCPU.Location = new Point(368, 76);
            labelCPU.Name = "labelCPU";
            labelCPU.Size = new Size(213, 30);
            labelCPU.TabIndex = 1;
            labelCPU.Text = "Temperature CPU (°C)";
            // 
            // button1
            // 
            button1.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button1.Location = new Point(108, 192);
            button1.Name = "button1";
            button1.Size = new Size(145, 66);
            button1.TabIndex = 4;
            button1.Text = "Start";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // labelTTop
            // 
            labelTTop.AutoSize = true;
            labelTTop.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            labelTTop.Location = new Point(108, 117);
            labelTTop.Name = "labelTTop";
            labelTTop.Size = new Size(51, 30);
            labelTTop.TabIndex = 5;
            labelTTop.Text = "N/A";
            // 
            // labelTCPU
            // 
            labelTCPU.AutoSize = true;
            labelTCPU.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            labelTCPU.Location = new Point(368, 117);
            labelTCPU.Name = "labelTCPU";
            labelTCPU.Size = new Size(51, 30);
            labelTCPU.TabIndex = 6;
            labelTCPU.Text = "N/A";
            // 
            // button2
            // 
            button2.Font = new Font("Segoe UI", 15.75F, FontStyle.Regular, GraphicsUnit.Point, 0);
            button2.Location = new Point(368, 192);
            button2.Name = "button2";
            button2.Size = new Size(145, 66);
            button2.TabIndex = 7;
            button2.Text = "Cancel";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(148, 313);
            label1.Name = "label1";
            label1.Size = new Size(38, 15);
            label1.TabIndex = 8;
            label1.Text = "label1";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(695, 436);
            Controls.Add(label1);
            Controls.Add(button2);
            Controls.Add(labelTCPU);
            Controls.Add(labelTTop);
            Controls.Add(button1);
            Controls.Add(labelCPU);
            Controls.Add(labelTop);
            Name = "Form1";
            Text = "Form1";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label labelTop;
        private Label labelCPU;
        private Button button1;
        private Label labelTTop;
        private Label labelTCPU;
        private Button button2;
        private Label label1;
    }
}
