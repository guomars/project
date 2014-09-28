namespace ActionEditorUI
{
    partial class RegionParamForm
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
            this.tbMoveCenter = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.tbRadius = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.tbCenter = new System.Windows.Forms.TextBox();
            this.btnOK = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.tbAmplitude = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.tbPeriod = new System.Windows.Forms.TextBox();
            this.rbSin = new System.Windows.Forms.RadioButton();
            this.label6 = new System.Windows.Forms.Label();
            this.tbDir = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // tbMoveCenter
            // 
            this.tbMoveCenter.Font = new System.Drawing.Font("宋体", 9F);
            this.tbMoveCenter.Location = new System.Drawing.Point(122, 78);
            this.tbMoveCenter.Name = "tbMoveCenter";
            this.tbMoveCenter.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tbMoveCenter.Size = new System.Drawing.Size(136, 21);
            this.tbMoveCenter.TabIndex = 12;
            this.tbMoveCenter.Text = "(128,128)";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(29, 87);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 11;
            this.label4.Text = "摇摆中心点";
            // 
            // tbRadius
            // 
            this.tbRadius.Font = new System.Drawing.Font("宋体", 9F);
            this.tbRadius.Location = new System.Drawing.Point(122, 47);
            this.tbRadius.Name = "tbRadius";
            this.tbRadius.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tbRadius.Size = new System.Drawing.Size(136, 21);
            this.tbRadius.TabIndex = 10;
            this.tbRadius.Text = "(128,128)";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(29, 56);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 9;
            this.label3.Text = "椭圆直径";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(29, 26);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 8;
            this.label2.Text = "椭圆中心点";
            // 
            // tbCenter
            // 
            this.tbCenter.Font = new System.Drawing.Font("宋体", 9F);
            this.tbCenter.Location = new System.Drawing.Point(122, 17);
            this.tbCenter.Name = "tbCenter";
            this.tbCenter.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tbCenter.Size = new System.Drawing.Size(136, 21);
            this.tbCenter.TabIndex = 7;
            this.tbCenter.Text = "(128,128)";
            // 
            // btnOK
            // 
            this.btnOK.Font = new System.Drawing.Font("宋体", 13F);
            this.btnOK.Location = new System.Drawing.Point(345, 105);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 60);
            this.btnOK.TabIndex = 13;
            this.btnOK.Text = "确认";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(31, 153);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(29, 12);
            this.label9.TabIndex = 14;
            this.label9.Text = "振幅";
            // 
            // tbAmplitude
            // 
            this.tbAmplitude.Font = new System.Drawing.Font("宋体", 9F);
            this.tbAmplitude.Location = new System.Drawing.Point(85, 145);
            this.tbAmplitude.Name = "tbAmplitude";
            this.tbAmplitude.Size = new System.Drawing.Size(33, 21);
            this.tbAmplitude.TabIndex = 15;
            this.tbAmplitude.Text = "28";
            this.tbAmplitude.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(29, 181);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(41, 12);
            this.label10.TabIndex = 16;
            this.label10.Text = "周期秒";
            // 
            // tbPeriod
            // 
            this.tbPeriod.Font = new System.Drawing.Font("宋体", 9F);
            this.tbPeriod.Location = new System.Drawing.Point(85, 172);
            this.tbPeriod.Name = "tbPeriod";
            this.tbPeriod.Size = new System.Drawing.Size(33, 21);
            this.tbPeriod.TabIndex = 17;
            this.tbPeriod.Text = "2";
            this.tbPeriod.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // rbSin
            // 
            this.rbSin.AutoSize = true;
            this.rbSin.Location = new System.Drawing.Point(29, 213);
            this.rbSin.Name = "rbSin";
            this.rbSin.Size = new System.Drawing.Size(71, 16);
            this.rbSin.TabIndex = 18;
            this.rbSin.TabStop = true;
            this.rbSin.Text = "赛因震动";
            this.rbSin.UseVisualStyleBackColor = true;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(29, 117);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(125, 12);
            this.label6.TabIndex = 19;
            this.label6.Text = "震动方向, -1表示随机";
            // 
            // tbDir
            // 
            this.tbDir.Font = new System.Drawing.Font("宋体", 9F);
            this.tbDir.Location = new System.Drawing.Point(184, 108);
            this.tbDir.Name = "tbDir";
            this.tbDir.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tbDir.Size = new System.Drawing.Size(74, 21);
            this.tbDir.TabIndex = 20;
            this.tbDir.Text = "(0,0)";
            // 
            // RegionParamForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(432, 260);
            this.Controls.Add(this.tbDir);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.rbSin);
            this.Controls.Add(this.tbPeriod);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.tbAmplitude);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.tbMoveCenter);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.tbRadius);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tbCenter);
            this.Location = new System.Drawing.Point(400, 600);
            this.Name = "RegionParamForm";
            this.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "摇动参数";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbMoveCenter;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tbRadius;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox tbCenter;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox tbAmplitude;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox tbPeriod;
        private System.Windows.Forms.RadioButton rbSin;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tbDir;
    }
}