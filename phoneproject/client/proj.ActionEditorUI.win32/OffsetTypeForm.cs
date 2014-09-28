using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class OffsetTypeForm : Form
    {
        List<RadioButton> rbs = new List<RadioButton>();
        EOffsetType selected = EOffsetType.Screen_Position;

        public OffsetTypeForm()
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

            foreach (RadioButton rb in rbs)
            {
                rb.CheckedChanged += onCheckedChanged;
            }
        }

        internal void setType(EOffsetType e)
        {
            foreach (RadioButton rb in rbs)
            {
                if (!rb.Text.Contains(" " + Enum.GetName(typeof(EOffsetType), e) + " ")) continue;

                rb.Checked = true;
                selected = e;
                return;
            }
        }

        internal EOffsetType getType()
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
            foreach (object o in Enum.GetValues(typeof(EOffsetType)))
            {
                EOffsetType eType = (EOffsetType)o;
                if (((RadioButton)sender).Text.Contains("-- " + Enum.GetName(typeof(EOffsetType), eType)))
                {
                    selected = eType;
                    break;
                }
            }
        }
    }
}
