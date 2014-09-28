namespace ActionEditorUI
{
    partial class GlobalConfForm
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
            this.rb_ipad = new System.Windows.Forms.RadioButton();
            this.rb_iphone4 = new System.Windows.Forms.RadioButton();
            this.rb_iphone5 = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.window_scale = new System.Windows.Forms.NumericUpDown();
            this.btnOK = new System.Windows.Forms.Button();
            this.rb_3gs = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.window_scale)).BeginInit();
            this.SuspendLayout();
            // 
            // rb_ipad
            // 
            this.rb_ipad.AutoSize = true;
            this.rb_ipad.Location = new System.Drawing.Point(32, 29);
            this.rb_ipad.Name = "rb_ipad";
            this.rb_ipad.Size = new System.Drawing.Size(131, 16);
            this.rb_ipad.TabIndex = 0;
            this.rb_ipad.TabStop = true;
            this.rb_ipad.Text = "iapd -- 768 * 1024";
            this.rb_ipad.UseVisualStyleBackColor = true;
            // 
            // rb_iphone4
            // 
            this.rb_iphone4.AutoSize = true;
            this.rb_iphone4.Location = new System.Drawing.Point(32, 51);
            this.rb_iphone4.Name = "rb_iphone4";
            this.rb_iphone4.Size = new System.Drawing.Size(137, 16);
            this.rb_iphone4.TabIndex = 1;
            this.rb_iphone4.TabStop = true;
            this.rb_iphone4.Text = "ipone4 -- 640 * 960";
            this.rb_iphone4.UseVisualStyleBackColor = true;
            // 
            // rb_iphone5
            // 
            this.rb_iphone5.AutoSize = true;
            this.rb_iphone5.Location = new System.Drawing.Point(32, 73);
            this.rb_iphone5.Name = "rb_iphone5";
            this.rb_iphone5.Size = new System.Drawing.Size(143, 16);
            this.rb_iphone5.TabIndex = 2;
            this.rb_iphone5.TabStop = true;
            this.rb_iphone5.Text = "ipone5 -- 640 * 1136";
            this.rb_iphone5.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "窗口分辨率";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 124);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "窗口缩放";
            // 
            // window_scale
            // 
            this.window_scale.DecimalPlaces = 1;
            this.window_scale.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.window_scale.Location = new System.Drawing.Point(81, 120);
            this.window_scale.Maximum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.window_scale.Minimum = new decimal(new int[] {
            4,
            0,
            0,
            65536});
            this.window_scale.Name = "window_scale";
            this.window_scale.Size = new System.Drawing.Size(47, 21);
            this.window_scale.TabIndex = 5;
            this.window_scale.Value = new decimal(new int[] {
            10,
            0,
            0,
            65536});
            // 
            // btnOK
            // 
            this.btnOK.Location = new System.Drawing.Point(421, 152);
            this.btnOK.Name = "btnOK";
            this.btnOK.Size = new System.Drawing.Size(75, 23);
            this.btnOK.TabIndex = 6;
            this.btnOK.Text = "确定";
            this.btnOK.UseVisualStyleBackColor = true;
            this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
            // 
            // rb_3gs
            // 
            this.rb_3gs.Location = new System.Drawing.Point(33, 96);
            this.rb_3gs.Name = "rb_3gs";
            this.rb_3gs.Size = new System.Drawing.Size(143, 16);
            this.rb_3gs.TabIndex = 7;
            this.rb_3gs.TabStop = true;
            this.rb_3gs.Text = "ipone3GS-- 320 * 480";
            this.rb_3gs.UseVisualStyleBackColor = true;
            // 
            // GlobalConfForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(530, 187);
            this.Controls.Add(this.rb_3gs);
            this.Controls.Add(this.btnOK);
            this.Controls.Add(this.window_scale);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.rb_iphone5);
            this.Controls.Add(this.rb_iphone4);
            this.Controls.Add(this.rb_ipad);
            this.Name = "GlobalConfForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "GlobalConfForm";
            ((System.ComponentModel.ISupportInitialize)(this.window_scale)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.RadioButton rb_ipad;
        private System.Windows.Forms.RadioButton rb_iphone4;
        private System.Windows.Forms.RadioButton rb_iphone5;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown window_scale;
        private System.Windows.Forms.Button btnOK;
        private System.Windows.Forms.RadioButton rb_3gs;
    }
}