using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class GLBlendFactorForm : Form
    {
        List<RadioButton> rbs = new List<RadioButton>();
        EBlendFactor selected = EBlendFactor.GL_ONE;

        public GLBlendFactorForm()
        {
            InitializeComponent();

            rbs.Add(radioButton1);
            rbs.Add(radioButton2);
            rbs.Add(radioButton3);
            rbs.Add(radioButton4);
            rbs.Add(radioButton5);
            rbs.Add(radioButton6);
            rbs.Add(radioButton7);
            rbs.Add(radioButton8);
            rbs.Add(radioButton9);
            rbs.Add(radioButton10);
            rbs.Add(radioButton11);

            foreach (RadioButton rb in rbs)
            {
                rb.CheckedChanged += onCheckedChanged;
            }
        }

        internal void setGlBendFactor(EBlendFactor e)
        {
            foreach (RadioButton rb in rbs) {
                if (rb.Text != Enum.GetName(typeof(EBlendFactor), e)) continue;

                rb.Checked = true;
                selected = e;
                return;
            }
        }

        internal static int transGlBlendFactor(EBlendFactor e) {
            switch (e) {
                case EBlendFactor.GL_ZERO: return 0x0;
                case EBlendFactor.GL_ONE: return 0x1;
                case EBlendFactor.GL_SRC_COLOR: return 0x0300;
                case EBlendFactor.GL_ONE_MINUS_SRC_COLOR: return 0x0301;
                case EBlendFactor.GL_SRC_ALPHA: return 0x0302;
                case EBlendFactor.GL_ONE_MINUS_SRC_ALPHA: return 0x0303;
                case EBlendFactor.GL_DST_ALPHA: return 0x0304;
                case EBlendFactor.GL_ONE_MINUS_DST_ALPHA: return 0x0305;
                case EBlendFactor.GL_DST_COLOR: return 0x0306;
                case EBlendFactor.GL_ONE_MINUS_DST_COLOR: return 0x0307;
                case EBlendFactor.GL_SRC_ALPHA_SATURATE: return 0x0308;
                default: throw new Exception("" + e);
            }         
        }

        internal static EBlendFactor transGlBlendFactor(int i)
        {
            foreach (EBlendFactor e in Enum.GetValues(typeof(EBlendFactor)))
            {
                if (i == transGlBlendFactor(e)) return e;
            }
            throw new Exception("" + i);
        }

        internal EBlendFactor getGlBendFactor()
        {
            return selected;
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void onCheckedChanged(object sender, EventArgs e)
        {
            selected = (EBlendFactor)Enum.Parse(typeof(EBlendFactor), ((RadioButton)sender).Text);
        }
    }
}
