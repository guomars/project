using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class ActionListForm : Form
    {
        public void setItems(List<String> strs)
        {
            actionListBox.Items.Clear();
            foreach (String str in strs) {
                actionListBox.Items.Add(str);
            }
        }

        public String getSelected()
        {
            return actionListBox.SelectedItem == null ? null : actionListBox.SelectedItem.ToString();
        }

        public ActionListForm()
        {
            InitializeComponent();
        }

        private void btnConfirm_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
