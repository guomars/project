namespace ActionEditorUI
{
    partial class RegionMoveForm
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
            this.regionPanel = new System.Windows.Forms.Panel();
            this.btnAddParam = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.tbTestBackGround = new System.Windows.Forms.TextBox();
            this.btnOpen = new System.Windows.Forms.Button();
            this.btnSimulate = new System.Windows.Forms.Button();
            this.btnNew = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // regionPanel
            // 
            this.regionPanel.BackColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.regionPanel.Location = new System.Drawing.Point(12, 12);
            this.regionPanel.Name = "regionPanel";
            this.regionPanel.Size = new System.Drawing.Size(384, 512);
            this.regionPanel.TabIndex = 0;
            // 
            // btnAddParam
            // 
            this.btnAddParam.Font = new System.Drawing.Font("宋体", 11F);
            this.btnAddParam.Location = new System.Drawing.Point(521, 58);
            this.btnAddParam.Name = "btnAddParam";
            this.btnAddParam.Size = new System.Drawing.Size(131, 30);
            this.btnAddParam.TabIndex = 1;
            this.btnAddParam.Text = "添加震动区域";
            this.btnAddParam.UseVisualStyleBackColor = true;
            this.btnAddParam.Click += new System.EventHandler(this.btnAddParam_Click);
            // 
            // btnSave
            // 
            this.btnSave.Font = new System.Drawing.Font("宋体", 12F);
            this.btnSave.Location = new System.Drawing.Point(618, 455);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(80, 69);
            this.btnSave.TabIndex = 2;
            this.btnSave.Text = "保存";
            this.btnSave.UseVisualStyleBackColor = true;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 11F);
            this.label1.Location = new System.Drawing.Point(420, 21);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(75, 15);
            this.label1.TabIndex = 3;
            this.label1.Text = "测试底图:";
            // 
            // tbTestBackGround
            // 
            this.tbTestBackGround.Location = new System.Drawing.Point(505, 15);
            this.tbTestBackGround.Name = "tbTestBackGround";
            this.tbTestBackGround.Size = new System.Drawing.Size(260, 21);
            this.tbTestBackGround.TabIndex = 4;
            this.tbTestBackGround.TextChanged += new System.EventHandler(this.tbTestBackGround_TextChanged);
            // 
            // btnOpen
            // 
            this.btnOpen.Font = new System.Drawing.Font("宋体", 12F);
            this.btnOpen.Location = new System.Drawing.Point(521, 455);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(82, 69);
            this.btnOpen.TabIndex = 5;
            this.btnOpen.Text = "打开";
            this.btnOpen.UseVisualStyleBackColor = true;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // btnSimulate
            // 
            this.btnSimulate.Font = new System.Drawing.Font("宋体", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btnSimulate.Location = new System.Drawing.Point(717, 455);
            this.btnSimulate.Name = "btnSimulate";
            this.btnSimulate.Size = new System.Drawing.Size(79, 69);
            this.btnSimulate.TabIndex = 6;
            this.btnSimulate.Text = "模拟";
            this.btnSimulate.UseVisualStyleBackColor = true;
            this.btnSimulate.Click += new System.EventHandler(this.btnSimulate_Click);
            // 
            // btnNew
            // 
            this.btnNew.Font = new System.Drawing.Font("宋体", 12F);
            this.btnNew.Location = new System.Drawing.Point(423, 455);
            this.btnNew.Name = "btnNew";
            this.btnNew.Size = new System.Drawing.Size(82, 69);
            this.btnNew.TabIndex = 7;
            this.btnNew.Text = "新建";
            this.btnNew.UseVisualStyleBackColor = true;
            this.btnNew.Click += new System.EventHandler(this.btnNew_Click);
            // 
            // RegionMoveForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(808, 539);
            this.Controls.Add(this.btnNew);
            this.Controls.Add(this.btnSimulate);
            this.Controls.Add(this.btnOpen);
            this.Controls.Add(this.tbTestBackGround);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnAddParam);
            this.Controls.Add(this.regionPanel);
            this.DoubleBuffered = true;
            this.Name = "RegionMoveForm";
            this.Text = "区域震动编辑";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel regionPanel;
        private System.Windows.Forms.Button btnAddParam;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tbTestBackGround;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.Button btnSimulate;
        private System.Windows.Forms.Button btnNew;
    }
}