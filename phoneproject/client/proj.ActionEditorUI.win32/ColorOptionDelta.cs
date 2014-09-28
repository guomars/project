using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class ColorOptionDelta : UserControl
    {
        public ColorOptionDelta()
        {
            InitializeComponent();
        }

        public void setName(String name)
        {
            labelName.Text = name;
        }

        public byte getR() { return (byte)r.Value; }
        public byte getG() { return (byte)g.Value; }
        public byte getB() { return (byte)b.Value; }
        public byte getA() { return (byte)alpha.Value; }

        public void setR(byte _r) { r.Value = _r; ParticleDesign.setDirty(); }
        public void setG(byte _g) { g.Value = _g; ParticleDesign.setDirty(); }
        public void setB(byte _b) { b.Value = _b; ParticleDesign.setDirty(); }
        public void setA(byte _a) { alpha.Value = _a; ParticleDesign.setDirty(); }
    }
}
