using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class ParticleOption : UserControl
    {
        public float cur = 0;
        public ParticleOptionData _data;
        public ParticleOptionData data
        {
            set
            {
                this._data = value;
                init();
            }
            get
            {
                return this._data;
            }
        }

        public ParticleOption()
        {
            InitializeComponent();
        }

        public float getValue()
        {
            return cur;
        }

        public void setValue(float value)
        {
            cur = value;

            init(cur);
        }

        private void init(float cur)
        {
            this.cur = cur;

            this.trackBar.Minimum = 0;
            this.trackBar.Maximum = 10000;
            this.trackBar.Value = (int)(_data.startPercent * this.trackBar.Maximum);
            this.trackBar.TickStyle = TickStyle.None;

            this.numericUpDown.Minimum = (decimal)_data.min;
            this.numericUpDown.Maximum = (decimal)_data.max;
            this.numericUpDown.Increment = _data.isInt ? (decimal)1.0 : (decimal)((_data.max - _data.min) / 100);
            this.numericUpDown.Value = (decimal)cur;
        }

        public void init()
        {
            this.labelName.Text = _data.strName;
            this.cur = _data.startPercent * (_data.max - _data.min) + _data.min;

            init(cur);
        }

        private void labelName_Click(object sender, EventArgs e)
        {

        }

        private void btnHelp_Click(object sender, EventArgs e)
        {
            MessageBox.Show(_data.strHelp);
        }

        private void trackBar_Scroll(object sender, EventArgs e)
        {
            float percent = (float)this.trackBar.Value / this.trackBar.Maximum;
            this.numericUpDown.Value = (decimal)(percent * (_data.max - _data.min) + _data.min);
            if (_data.isInt) this.numericUpDown.Value = Math.Floor(this.numericUpDown.Value);

            this.cur = (float)this.numericUpDown.Value;
            ParticleDesign.setDirty();
        }

        private void numericUpDown_ValueChanged(object sender, EventArgs e)
        {
            this.cur = (float)this.numericUpDown.Value;

            this.trackBar.Value = (int)(this.trackBar.Maximum * (this.cur - this._data.min) / (this._data.max - this._data.min));
            ParticleDesign.setDirty();
        }
    }

    public struct ParticleOptionData
    {
        public ParticleOptionData(String strName, float min, float max, bool isInt, String strHelp, float startPercent = 0.0f)
        {
            this.strName = strName;
            this.min = min;
            this.max = max;
            this.isInt = isInt;
            this.strHelp = strHelp;
            this.startPercent = startPercent;
        }

        internal String strName;
        internal float min;
        internal float max;
        internal bool isInt;
        internal String strHelp;
        internal float startPercent;
    }
}
