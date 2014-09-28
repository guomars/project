using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class ColorOptionRGBA : UserControl
    {
        public ColorOptionRGBA()
        {
            InitializeComponent();
        }

        public void setName(String str)
        {
            this.rgb.setName(str);
        }

        public byte getR()
        {
            return this.rgb.getR();
        }

        public byte getG()
        {
            return this.rgb.getG();
        }

        public byte getB()
        {
            return this.rgb.getB();
        }

        public byte getA()
        {
            return (byte)alpha.Value;
        }

        public void setR(byte v)
        {
            this.rgb.setR(v);
        }

        public void setG(byte v)
        {
            this.rgb.setG(v);
        }

        public void setB(byte v)
        {
            this.rgb.setB(v);
        }

        public void setA(byte v)
        {
            this.alpha.Value = v;
            ParticleDesign.setDirty();
        }
    }
}
