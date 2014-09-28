using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class CondTypeForm : Form
    {
        List<RadioButton> rbs = new List<RadioButton>();
        ECondType selected = ECondType.GREAT;

        public CondTypeForm()
        {
            InitializeComponent();

            rbs.Add(radioButton1);
            rbs.Add(radioButton2);
            rbs.Add(radioButton3);
            rbs.Add(radioButton4);
            rbs.Add(radioButton5);

            foreach (RadioButton rb in rbs)
            {
                rb.CheckedChanged += onCheckedChanged;
            }
        }

        internal void setType(ECondType e)
        {
            foreach (RadioButton rb in rbs)
            {
                if (!rb.Text.Contains(" " + Enum.GetName(typeof(ECondType), e) + " ")) continue;

                rb.Checked = true;
                selected = e;
                return;
            }
        }

        internal ECondType getType()
        {
            return selected;
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void onCheckedChanged(object sender, EventArgs e)
        {
            foreach (object o in Enum.GetValues(typeof(ECondType)))
            {
                ECondType eType = (ECondType)o;
                if (((RadioButton)sender).Text.Contains(" " + Enum.GetName(typeof(ECondType), eType) + " "))
                {
                    selected = eType;
                    break;
                }
            }
        }
    }
}
