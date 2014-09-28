namespace ActionEditorUI
{
    partial class ColorOptionDelta
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
            this.label3 = new System.Windows.Forms.Label();
            this.b = new System.Windows.Forms.NumericUpDown();
            this.labelName = new System.Windows.Forms.Label();
            this.g = new System.Windows.Forms.NumericUpDown();
            this.r = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.alpha)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.b)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.g)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.r)).BeginInit();
            this.SuspendLayout();
            // 
            // alpha
            // 
            this.alpha.Location = new System.Drawing.Point(310, 8);
            this.alpha.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.alpha.Name = "alpha";
            this.alpha.Size = new System.Drawing.Size(41, 21);
            this.alpha.TabIndex = 32;
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label.Location = new System.Drawing.Point(285, 11);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(22, 15);
            this.label.TabIndex = 31;
            this.label.Text = "透";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(163, 11);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(22, 15);
            this.label3.TabIndex = 36;
            this.label3.Text = "绿";
            // 
            // b
            // 
            this.b.Location = new System.Drawing.Point(244, 7);
            this.b.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.b.Name = "b";
            this.b.Size = new System.Drawing.Size(40, 21);
            this.b.TabIndex = 39;
            // 
            // labelName
            // 
            this.labelName.AutoSize = true;
            this.labelName.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.labelName.Location = new System.Drawing.Point(-1, 11);
            this.labelName.Name = "labelName";
            this.labelName.Size = new System.Drawing.Size(67, 15);
            this.labelName.TabIndex = 35;
            this.labelName.Text = "背景颜色";
            // 
            // g
            // 
            this.g.Location = new System.Drawing.Point(185, 7);
            this.g.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.g.Name = "g";
            this.g.Size = new System.Drawing.Size(40, 21);
            this.g.TabIndex = 37;
            // 
            // r
            // 
            this.r.Location = new System.Drawing.Point(125, 7);
            this.r.Maximum = new decimal(new int[] {
            255,
            0,
            0,
            0});
            this.r.Name = "r";
            this.r.Size = new System.Drawing.Size(40, 21);
            this.r.TabIndex = 34;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(105, 11);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(22, 15);
            this.label1.TabIndex = 33;
            this.label1.Text = "红";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(223, 10);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(22, 15);
            this.label4.TabIndex = 38;
            this.label4.Text = "蓝";
            // 
            // ColorOptionDelta
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.b);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.g);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.labelName);
            this.Controls.Add(this.r);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.alpha);
            this.Controls.Add(this.label);
            this.Name = "ColorOptionDelta";
            this.Size = new System.Drawing.Size(362, 35);
            ((System.ComponentModel.ISupportInitialize)(this.alpha)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.b)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.g)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.r)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown alpha;
        private System.Windows.Forms.Label label;
        private System.Windows.Forms.NumericUpDown r;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelName;
        private System.Windows.Forms.NumericUpDown g;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.NumericUpDown b;
        private System.Windows.Forms.Label label4;
    }
}
