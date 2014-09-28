using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class ColorOptionRGB : UserControl
    {
        internal byte R;
        internal byte G;
        internal byte B;
        ColorDialog colorDialog = new ColorDialog();

        public ColorOptionRGB()
        {
            InitializeComponent();

            colorDialog.FullOpen = true;
            this.btnShow.BackColor = Color.White;
        }

        private void btnColor_Click(object sender, EventArgs e)
        {
            onSelectColor();
        }

        private void onSelectColor()
        {
            if (DialogResult.OK == colorDialog.ShowDialog())
            {
                setColor(colorDialog.Color.R, colorDialog.Color.G, colorDialog.Color.B);
            }
        }

        private void btnShow_Click(object sender, EventArgs e)
        {
            onSelectColor();
        }

        public void setName(String str)
        {
            this.label.Text = str;
        }

        public void setColor(byte R, byte G, byte B)
        {
            this.R = R;
            this.G = G;
            this.B = B;

            this.btnShow.BackColor = Color.FromArgb(R, G, B);
            this.btnColor.Text = "{r=" + R + ",g=" + G + ",b=" + B + "}";
            ParticleDesign.setDirty();
        }

        public void setR(byte v)
        {
            setColor(v, G, B);
        }

        public void setG(byte v)
        {
            setColor(R, v, B);
        }

        public void setB(byte v)
        {
            setColor(R, G, v);
        }

        public byte getR()
        {
            return R;
        }

        public byte getG()
        {
            return G;
        }

        public byte getB()
        {
            return B;
        }
    }
}
