using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.Xml;

namespace ActionEditorUI
{
    public partial class RegionParamForm : Form
    {
        internal RegionParam param = new RegionParam();
        internal event EventHandler ParamChanged;

        public void Init(RegionParam _param)
        {
            this.param = _param;

            this.tbCenter.Text = param.center.ToString();
            this.tbRadius.Text = param.radius.ToString();
            this.tbMoveCenter.Text = param.moveCenter.ToString();
            this.tbDir.Text = param.dir.ToString();
            this.tbAmplitude.Text = "" + param.amplitude;
            this.tbPeriod.Text = "" + param.period;
            this.rbSin.Checked = (param.eType == ERegionMoveType.Sin);

            this.tbCenter.KeyUp += onKeyUp;
            this.tbRadius.KeyUp += onKeyUp;
            this.tbMoveCenter.KeyUp += onKeyUp;
            this.tbDir.KeyUp += onKeyUp;
            this.tbAmplitude.KeyUp += onKeyUp;
            this.tbPeriod.KeyUp += onKeyUp;
        }

        public RegionParamForm()
        {
            InitializeComponent();

            this.KeyUp += onKeyUp;
        }

        private void onKeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                btnOK_Click(sender, null);
            }
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            try
            {
                this.param.center = new CCPoint(tbCenter.Text);
                this.param.radius = new CCPoint(tbRadius.Text);
                if (this.param.radius.x == 0)
                {
                    this.param.radius.x = 10;
                }
                if (this.param.radius.y == 0)
                {
                    this.param.radius.y = 10;
                }
                this.tbRadius.Text = this.param.radius.ToString();
                this.param.moveCenter = new CCPoint(tbMoveCenter.Text);
                this.param.dir = float.Parse(tbDir.Text);
                this.param.amplitude = float.Parse(tbAmplitude.Text);
                this.param.period = float.Parse(tbPeriod.Text);
                if (this.rbSin.Enabled)
                {
                    param.eType = ERegionMoveType.Sin;
                }
                ParamChanged(param, null);
            }
            catch (Exception)
            {
                MessageBox.Show("参数不合法！！！");
                return;
            }
        }
    }

    public enum ERegionMoveType
    {
        Sin,
    }

    public class RegionParam
    {
        public static String EnumToString(ERegionMoveType e)
        {
            switch (e) {
                case ERegionMoveType.Sin: return "sin";
                default: throw new Exception("[ToString]   Unkowned ERegionMoveType: " + e);
            }
        }

        public static ERegionMoveType StringToEnum(String str)
        {
            switch (str)
            {
                case "sin": return ERegionMoveType.Sin;
                default: throw new Exception("[FromString]  Unkowned Str: " + str);
            }
        }

        internal CCPoint center = new CCPoint(128, 128);
        internal CCPoint radius = new CCPoint(128, 128);
        internal CCPoint moveCenter = new CCPoint(128, 128);
        internal float dir = -1;
        internal float amplitude = 24f;
        internal float period = 2.2f;
        internal ERegionMoveType eType = ERegionMoveType.Sin;

        internal RegionParam() { }

        internal RegionParam(XmlElement e)
        {
            Parse(e);
        }

        void Parse(XmlElement e)
        {
            if (e.HasAttribute("center")) center = new CCPoint(e.GetAttribute("center"));
            if (e.HasAttribute("radius")) radius = new CCPoint(e.GetAttribute("radius"));
            if (e.HasAttribute("moveCenter")) moveCenter = new CCPoint(e.GetAttribute("moveCenter"));
            if (e.HasAttribute("dir")) dir = float.Parse(e.GetAttribute("dir"));
            if (e.HasAttribute("amplitude")) amplitude = float.Parse(e.GetAttribute("amplitude"));
            if (e.HasAttribute("period")) period = float.Parse(e.GetAttribute("period"));
            if (e.HasAttribute("type")) eType = StringToEnum(e.GetAttribute("type"));
        }

        public String ToXmlStr()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("<RegionParam ");
            sb.Append("center=\"").Append(center.ToString()).Append("\" ");
            sb.Append("radius=\"").Append(radius.ToString()).Append("\" ");
            sb.Append("moveCenter=\"").Append(moveCenter.ToString()).Append("\" ");
            sb.Append("dir=\"").Append(dir).Append("\" ");
            sb.Append("amplitude=\"").Append(amplitude).Append("\" ");
            sb.Append("period=\"").Append(period).Append("\" ");
            sb.Append("type=\"").Append(EnumToString(eType));
            sb.Append("\"/>");
            return sb.ToString();
        }
    }
}
