namespace ActionEditorUI
{
    partial class ParticleOption
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.labelName = new System.Windows.Forms.Label();
            this.trackBar = new System.Windows.Forms.TrackBar();
            this.numericUpDown = new System.Windows.Forms.NumericUpDown();
            this.btnHelp = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown)).BeginInit();
            this.SuspendLayout();
            // 
            // labelName
            // 
            this.labelName.AutoSize = true;
            this.labelName.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.labelName.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelName.Location = new System.Drawing.Point(27, 8);
            this.labelName.Name = "labelName";
            this.labelName.Size = new System.Drawing.Size(67, 15);
            this.labelName.TabIndex = 5;
            this.labelName.Text = "粒子数量";
            this.labelName.Click += new System.EventHandler(this.labelName_Click);
            // 
            // trackBar
            // 
            this.trackBar.Location = new System.Drawing.Point(153, 1);
            this.trackBar.Name = "trackBar";
            this.trackBar.Size = new System.Drawing.Size(105, 45);
            this.trackBar.TabIndex = 4;
            this.trackBar.Scroll += new System.EventHandler(this.trackBar_Scroll);
            // 
            // numericUpDown
            // 
            this.numericUpDown.DecimalPlaces = 12;
            this.numericUpDown.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDown.Location = new System.Drawing.Point(264, 5);
            this.numericUpDown.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDown.Name = "numericUpDown";
            this.numericUpDown.Size = new System.Drawing.Size(55, 21);
            this.numericUpDown.TabIndex = 3;
            this.numericUpDown.Value = new decimal(new int[] {
            105,
            0,
            0,
            131072});
            this.numericUpDown.ValueChanged += new System.EventHandler(this.numericUpDown_ValueChanged);
            // 
            // btnHelp
            // 
            this.btnHelp.Location = new System.Drawing.Point(1, 5);
            this.btnHelp.Name = "btnHelp";
            this.btnHelp.Size = new System.Drawing.Size(28, 20);
            this.btnHelp.TabIndex = 6;
            this.btnHelp.Text = "详";
            this.btnHelp.UseVisualStyleBackColor = true;
            this.btnHelp.Click += new System.EventHandler(this.btnHelp_Click);
            // 
            // ParticleOption
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnHelp);
            this.Controls.Add(this.labelName);
            this.Controls.Add(this.trackBar);
            this.Controls.Add(this.numericUpDown);
            this.Name = "ParticleOption";
            this.Size = new System.Drawing.Size(320, 31);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label labelName;
        private System.Windows.Forms.TrackBar trackBar;
        private System.Windows.Forms.NumericUpDown numericUpDown;
        private System.Windows.Forms.Button btnHelp;
    }
}
