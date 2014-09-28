namespace ActionEditorUI
{
    partial class TimeSpanForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnAnimRun = new System.Windows.Forms.Button();
            this.btnAnimPause = new System.Windows.Forms.Button();
            this.btnAnimNext = new System.Windows.Forms.Button();
            this.btnAnimStop = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.stepUpDown = new System.Windows.Forms.NumericUpDown();
            this.btnAnimReset = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.stepUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // btnAnimRun
            // 
            this.btnAnimRun.Image = global::ActionEditorUI.Properties.Resources.icon_anim_run;
            this.btnAnimRun.Location = new System.Drawing.Point(21, 12);
            this.btnAnimRun.Name = "btnAnimRun";
            this.btnAnimRun.Size = new System.Drawing.Size(38, 38);
            this.btnAnimRun.TabIndex = 0;
            this.btnAnimRun.UseVisualStyleBackColor = true;
            this.btnAnimRun.Click += new System.EventHandler(this.button1_Click);
            // 
            // btnAnimPause
            // 
            this.btnAnimPause.Image = global::ActionEditorUI.Properties.Resources.icon_anim_pause;
            this.btnAnimPause.Location = new System.Drawing.Point(76, 12);
            this.btnAnimPause.Name = "btnAnimPause";
            this.btnAnimPause.Size = new System.Drawing.Size(38, 38);
            this.btnAnimPause.TabIndex = 1;
            this.btnAnimPause.UseVisualStyleBackColor = true;
            // 
            // btnAnimNext
            // 
            this.btnAnimNext.Image = global::ActionEditorUI.Properties.Resources.icon_anim_next_frame;
            this.btnAnimNext.Location = new System.Drawing.Point(130, 12);
            this.btnAnimNext.Name = "btnAnimNext";
            this.btnAnimNext.Size = new System.Drawing.Size(38, 38);
            this.btnAnimNext.TabIndex = 2;
            this.btnAnimNext.UseVisualStyleBackColor = true;
            // 
            // btnAnimStop
            // 
            this.btnAnimStop.Image = global::ActionEditorUI.Properties.Resources.icon_anim_stop;
            this.btnAnimStop.Location = new System.Drawing.Point(184, 12);
            this.btnAnimStop.Name = "btnAnimStop";
            this.btnAnimStop.Size = new System.Drawing.Size(38, 38);
            this.btnAnimStop.TabIndex = 3;
            this.btnAnimStop.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 11F);
            this.label1.Location = new System.Drawing.Point(265, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 15);
            this.label1.TabIndex = 5;
            this.label1.Text = "步长（秒）";
            // 
            // stepUpDown
            // 
            this.stepUpDown.DecimalPlaces = 2;
            this.stepUpDown.Increment = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.stepUpDown.Location = new System.Drawing.Point(361, 22);
            this.stepUpDown.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.stepUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            131072});
            this.stepUpDown.Name = "stepUpDown";
            this.stepUpDown.Size = new System.Drawing.Size(64, 21);
            this.stepUpDown.TabIndex = 6;
            this.stepUpDown.Value = new decimal(new int[] {
            2,
            0,
            0,
            131072});
            // 
            // btnAnimReset
            // 
            this.btnAnimReset.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnAnimReset.Location = new System.Drawing.Point(477, 12);
            this.btnAnimReset.Name = "btnAnimReset";
            this.btnAnimReset.Size = new System.Drawing.Size(82, 38);
            this.btnAnimReset.TabIndex = 7;
            this.btnAnimReset.Text = "重置初始";
            this.btnAnimReset.UseVisualStyleBackColor = true;
            // 
            // TimeSpanForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1008, 762);
            this.Controls.Add(this.btnAnimReset);
            this.Controls.Add(this.stepUpDown);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnAnimStop);
            this.Controls.Add(this.btnAnimNext);
            this.Controls.Add(this.btnAnimPause);
            this.Controls.Add(this.btnAnimRun);
            this.Name = "TimeSpanForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "时间轴编辑";
            ((System.ComponentModel.ISupportInitialize)(this.stepUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnAnimRun;
        private System.Windows.Forms.Button btnAnimPause;
        private System.Windows.Forms.Button btnAnimNext;
        private System.Windows.Forms.Button btnAnimStop;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown stepUpDown;
        private System.Windows.Forms.Button btnAnimReset;




    }
}