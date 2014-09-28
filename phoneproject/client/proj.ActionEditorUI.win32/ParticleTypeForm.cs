using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class ParticleTypeForm : Form
    {
        List<RadioButton> rbs = new List<RadioButton>();
        ESysParticleType selected = ESysParticleType.CCParticleFire;

        public ParticleTypeForm()
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

        private void onCheckedChanged(object sender, EventArgs e)
        {
            foreach (object o in Enum.GetValues(typeof(ESysParticleType)))
            {
                ESysParticleType eType = (ESysParticleType)o;
                if (((RadioButton)sender).Text.Contains(Enum.GetName(typeof(ESysParticleType), eType) + " "))
                {
                    selected = eType;
                    break;
                }
            }
        }

        internal void setType(ESysParticleType e)
        {
            foreach (RadioButton rb in rbs)
            {
                if (!rb.Text.Contains(Enum.GetName(typeof(ESysParticleType), e))) continue;

                rb.Checked = true;
                selected = e;
                return;
            }
        }

        internal ESysParticleType getType()
        {
            return selected;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }


}
