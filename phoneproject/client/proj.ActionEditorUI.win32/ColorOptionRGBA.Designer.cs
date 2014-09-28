namespace ActionEditorUI
{
    partial class ColorOptionRGBA
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
            this.alpha = new System.Windows.Forms.NumericUpDown();
            this.label = new System.Windows.Forms.Label();
            this.rgb = new ActionEditorUI.ColorOptionRGB();
            ((System.ComponentModel.ISupportInitialize)(this.alpha)).BeginInit();
            this.SuspendLayout();
            // 
            // alpha
            // 
            this.alpha.Location = new System.Drawing.Point(317, 6);
            this.alpha.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.alpha.Name = "alpha";
            this.alpha.Size = new System.Drawing.Size(41, 21);
            this.alpha.TabIndex = 30;
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label.Location = new System.Drawing.Point(256, 10);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(52, 15);
            this.label.TabIndex = 29;
            this.label.Text = "透明度";
            // 
            // rgb
            // 
            this.rgb.Location = new System.Drawing.Point(3, -2);
            this.rgb.Name = "rgb";
            this.rgb.Size = new System.Drawing.Size(265, 37);
            this.rgb.TabIndex = 31;
            // 
            // ColorOptionRGBA
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.alpha);
            this.Controls.Add(this.label);
            this.Controls.Add(this.rgb);
            this.Name = "ColorOptionRGBA";
            this.Size = new System.Drawing.Size(363, 32);
            ((System.ComponentModel.ISupportInitialize)(this.alpha)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown alpha;
        private System.Windows.Forms.Label label;
        private ColorOptionRGB rgb;
    }
}
