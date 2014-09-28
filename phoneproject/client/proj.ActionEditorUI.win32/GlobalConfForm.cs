using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace ActionEditorUI
{
    public partial class GlobalConfForm : Form
    {
        public GlobalConfForm()
        {
            InitializeComponent();
            updateDataToUI();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;

            setBack();
        }

        private void setBack() {
            if (rb_3gs.Checked)
            {
                GlobalConf.instance.eWindowResolution = EWindowResolution.E_480_320;
            }
            else if (rb_ipad.Checked)
            {
                GlobalConf.instance.eWindowResolution = EWindowResolution.E_1024_768;
            }
            else if (rb_iphone4.Checked)
            {
                GlobalConf.instance.eWindowResolution = EWindowResolution.E_960_640;
            }
            else if (rb_iphone5.Checked)
            {
                GlobalConf.instance.eWindowResolution = EWindowResolution.E_1136_640;
            }

            GlobalConf.instance.windowScale = (float)window_scale.Value;
        }

        private void updateDataToUI()
        {
            switch (GlobalConf.instance.eWindowResolution)
            {
                case EWindowResolution.E_320_480:
                    rb_3gs.Checked = true;
                    break;
                case EWindowResolution.E_480_320:
                    rb_3gs.Checked = true;
                    break;
                case EWindowResolution.E_640_1136:
                    rb_iphone5.Checked = true;
                    break;
                case EWindowResolution.E_1136_640:
                    rb_iphone5.Checked = true;
                    break;
                case EWindowResolution.E_640_960:
                    rb_iphone4.Checked = true;
                    break;
                case EWindowResolution.E_960_640:
                    rb_iphone4.Checked = true;
                    break;
                case EWindowResolution.E_768_1024:
                    rb_ipad.Checked = true;
                    break;
                case EWindowResolution.E_1024_768:
                    rb_ipad.Checked = true;
                    break;
            }
            window_scale.Value = (decimal)GlobalConf.instance.windowScale;
        }
    }



    public enum EWindowResolution
    {
        E_768_1024,
        E_640_960,
        E_640_1136,
        E_320_480,
        E_480_320,
        E_960_640,
        E_1136_640,
        E_1024_768,
    }

    public class GlobalConf {
        public EWindowResolution eWindowResolution = EWindowResolution.E_1136_640;
        public float windowScale = 0.8f;

        public static GlobalConf instance = new GlobalConf();

        public void getWindowResolution(ref int width, ref int height, ref float scale) {
            switch (eWindowResolution)
            {
                case EWindowResolution.E_768_1024: width = 768; height = 1024; break;
                case EWindowResolution.E_640_960: width = 640; height = 960; break;
                case EWindowResolution.E_640_1136: width = 640; height = 1136; break;
                case EWindowResolution.E_320_480: width = 320; height = 480; break;
                case EWindowResolution.E_480_320: width = 480; height = 320; break;
                case EWindowResolution.E_960_640: width = 960; height = 640; break;
                case EWindowResolution.E_1136_640: width = 1136; height = 640; break;
                case EWindowResolution.E_1024_768: width = 1024; height = 768; break;
            }

            scale = windowScale;
        }

        private GlobalConf() { }
    }


}
