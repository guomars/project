using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class AETypeForm : Form
    {
        List<RadioButton> rbs = new List<RadioButton>();
        EAeDataType selected = EAeDataType.Cocos;

        public AETypeForm()
        {
            InitializeComponent();

            rbs.Add(radioButton1);
            rbs.Add(radioButton2);
            rbs.Add(radioButton3);

            foreach (RadioButton rb in rbs)
            {
                rb.CheckedChanged += onCheckedChanged;
            }
        }

        internal void setType(EAeDataType e)
        {
            foreach (RadioButton rb in rbs)
            {
                if (!rb.Text.Contains(Enum.GetName(typeof(EAeDataType), e))) continue;

                rb.Checked = true;
                selected = e;
                return;
            }
        }

        internal EAeDataType getType()
        {
            return selected;
        }

        private void onCheckedChanged(object sender, EventArgs e)
        {
            foreach (object o in Enum.GetValues(typeof(EAeDataType)))
            {
                EAeDataType eType = (EAeDataType)o;
                if (((RadioButton)sender).Text.Contains(Enum.GetName(typeof(EAeDataType), eType)))
                {
                    selected = eType;
                    break;
                }
            }
        }

        private void btnOk_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
