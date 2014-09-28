using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;

namespace ActionEditorUI
{
    public partial class PropForm : Form
    {
        public List<Prop> props = new List<Prop>();

        public PropForm()
        {
            InitializeComponent();
        }

        public void addProp(EPropType ePropType, String initText, String note, bool isFileName = false)
        {
            if (ePropType == EPropType.ePropType_Str && note == "内置粒子类型")
            {
                ePropType = EPropType.ePropType_GL_SysParticle;
            }
            else if (ePropType == EPropType.ePropType_Str && note == "条件类型")
            {
                ePropType = EPropType.ePropType_Condition;
            }
            else if (ePropType == EPropType.ePropType_Str && note == "Shader名称")
            {
                ePropType = EPropType.ePropType_ShaderType;
            }
            else if (ePropType == EPropType.ePropType_Str && note.Contains("Shader参数名"))
            {
                ePropType = EPropType.ePropType_ShaderParamType;
            }
            props.Add(new Prop(ePropType, note, initText, this, isFileName));
            Size = new Size(Size.Width, 100 + 30 * props.Count);
            btnOk.Location = new Point(btnOk.Location.X, Size.Height - 80);

            foreach (Prop prop in props) {
                prop.tb.KeyUp += onKeyUp;
            }
        }

        public void clearProps()
        {
            foreach (Prop prop in props) {
                this.Controls.Remove(prop.label);
                this.Controls.Remove(prop.tb);
                this.Controls.Remove(prop.btnSet);
            }
        }

        void onKeyUp(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                btnOk_Click(sender, new EventArgs());
            }
        }

        void check()
        {
            foreach (Prop prop in props)
            {
                prop.check();
            }
        }

        virtual protected void btnOk_Click(object sender, EventArgs e)
        {
            check();
        }
    }

    public enum EPropType
    {
        ePropType_Int,
        ePropType_Float,
        ePropType_Point,
        ePropType_Bezier,
        ePropType_Str,
        ePropType_Strs,
        ePropType_Condition,
        ePropType_GL_BlendFactor,
        ePropType_GL_SysParticle,
        ePropType_OffsetType,
        ePropType_ShaderType,
        ePropType_ShaderParamType,
    }

    public class Prop
    {
        public Prop(EPropType ePropType, String note, String initText, PropForm propForm, bool isFileName)
        {
            this.propForm = propForm;
            this.ePropType = ePropType;
            this.isFileName = isFileName;

            String prefix = "";
            switch (ePropType)
            {
                case EPropType.ePropType_Int: prefix = "[int]"; break;
                case EPropType.ePropType_Float: prefix = "[float]"; break;
                case EPropType.ePropType_Point: prefix = "[point]"; break;
                case EPropType.ePropType_Bezier: prefix = "[bezier]"; break;
                case EPropType.ePropType_Str: prefix = "[string]"; break;
                case EPropType.ePropType_Strs: prefix = "[strings]"; break;
                case EPropType.ePropType_GL_BlendFactor: prefix = "[GLBlendFactor]"; break;
                case EPropType.ePropType_GL_SysParticle: prefix = "[SysParticle]"; break;
                case EPropType.ePropType_ShaderType: prefix = "[Shader]"; break;
                case EPropType.ePropType_ShaderParamType: prefix = "[ShaderParam]"; break;
                case EPropType.ePropType_Condition: prefix = "[Condition]"; break;
                case EPropType.ePropType_OffsetType: prefix = "[Offset]"; break;
            }

            this.tb.Text = initText;
            this.defaultForeColor = this.tb.ForeColor;

            int i = propForm.props.Count;

            this.label.Text = prefix + note;
            this.label.TabIndex = 3;
            this.label.Size = new System.Drawing.Size(300, 22);
            this.label.Location = new System.Drawing.Point(12, 24 + 25 * i);
            propForm.Controls.Add(label);

            this.tb.Location = new System.Drawing.Point(360, 20 + 25 * i);
            this.tb.Size = new System.Drawing.Size(300, 22);
            this.tb.TabIndex = 1;
            this.tb.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.onKeyPressed);
            propForm.Controls.Add(tb);

            this.btnSet.Location = new System.Drawing.Point(315, 20 + 25 * i);
            this.btnSet.Size = new System.Drawing.Size(45, 22);
            this.btnSet.TabIndex = 2;
            this.btnSet.Text = "设置";
            this.btnSet.UseVisualStyleBackColor = true;
            propForm.Controls.Add(btnSet);

            switch (ePropType)
            {
                case EPropType.ePropType_Int:
                case EPropType.ePropType_Float:
                case EPropType.ePropType_Str:
                    this.btnSet.Visible = false;
                    break;
                case EPropType.ePropType_GL_BlendFactor:
                case EPropType.ePropType_GL_SysParticle:
                case EPropType.ePropType_Condition:
                case EPropType.ePropType_OffsetType:
                case EPropType.ePropType_ShaderType:
                case EPropType.ePropType_ShaderParamType:
                    this.btnSet.Visible = true;
                    this.tb.Enabled = false;
                    break;
                default:
                    //ePropType_Point,
                    //ePropType_Bezier,
                    //ePropType_Strs,
                    //ePropType_PNG_File,
                    //ePropType_PNG_Files,
                    this.btnSet.Visible = false; // TODO 先都禁止掉
                    break;
            }

            this.btnSet.Click += onBtnSet_Click;
        }

        public void onBtnSet_Click(object sender, EventArgs e)
        {
            if (ePropType == EPropType.ePropType_GL_BlendFactor)
            {
                GLBlendFactorForm form = new GLBlendFactorForm();
                form.setGlBendFactor((EBlendFactor)Enum.Parse(typeof(EBlendFactor), tb.Text));
                form.ShowDialog();
                this.tb.Text = Enum.GetName(typeof(EBlendFactor), form.getGlBendFactor());
            }
            else if (ePropType == EPropType.ePropType_GL_SysParticle)
            {
                ParticleTypeForm form = new ParticleTypeForm();
                form.setType((ESysParticleType)Enum.Parse(typeof(ESysParticleType), tb.Text));
                form.ShowDialog();
                this.tb.Text = Enum.GetName(typeof(ESysParticleType), form.getType());
            }
            else if (ePropType == EPropType.ePropType_Condition)
            {
                CondTypeForm form = new CondTypeForm();
                form.setType((ECondType)Enum.Parse(typeof(ECondType), tb.Text));
                form.ShowDialog();
                this.tb.Text = Enum.GetName(typeof(ECondType), form.getType());
            }
            else if (ePropType == EPropType.ePropType_OffsetType)
            {
                OffsetTypeForm form = new OffsetTypeForm();
                form.setType((EOffsetType)Enum.Parse(typeof(EOffsetType), tb.Text));
                form.ShowDialog();
                this.tb.Text = Enum.GetName(typeof(EOffsetType), form.getType());
            }
            else if (ePropType == EPropType.ePropType_ShaderType)
            {
                __curContextMenuValue = "";
                ContextMenu contextMenu = new ContextMenu();
                contextMenu.MenuItems.Add("默认 - ShaderPositionTextureColor");
                contextMenu.MenuItems.Add("模糊 - ShaderBlur");
                contextMenu.MenuItems.Add("灰度图 - ShaderGrey");
                contextMenu.MenuItems.Add("马赛克 - ShaderMosaic");
                contextMenu.MenuItems.Add("调色(亮度，对比度，饱和度) - ShaderCompose");
                contextMenu.MenuItems.Add("Bloom - ShaderBloom");
                contextMenu.Show(this.tb, new Point(0, 0));
                for (int i = 0; i < contextMenu.MenuItems.Count; i++ )
                {
                    contextMenu.MenuItems[i].Click += onContextMenuClick;
                }
            }
            else if (ePropType == EPropType.ePropType_ShaderParamType)
            {
                String shaderName = "";
                foreach (Prop prop in propForm.props) {
                    if (prop.ePropType == EPropType.ePropType_ShaderType) {
                        shaderName = prop.tb.Text;
                        break;
                    }
                }

                if (shaderName == "") return;

                ContextMenu contextMenu = new ContextMenu();
                contextMenu.MenuItems.Add("(空)");
                switch (shaderName)
                {
                    case "ShaderBlur":
                        contextMenu.MenuItems.Add("模糊程度 - ShaderParam_Blur");
                        break;
                    case "ShaderGrey":  // 目前没有参数
                        contextMenu.MenuItems.Add("灰度程度 - ShaderParam_Grey");
                        break;
                    case "ShaderMosaic":  // 目前没有参数
                        contextMenu.MenuItems.Add("马赛克程度 - ShaderParam_Mosaic");
                        break;
                    case "ShaderCompose":  // 目前没有参数
                        contextMenu.MenuItems.Add("调色（亮度）  - ShaderParam_Compose_brightness");
                        contextMenu.MenuItems.Add("调色（对比度） - ShaderParam_Compose_contrast");
                        contextMenu.MenuItems.Add("调色（饱和度） - ShaderParam_Compose_saturation");
                        break;
                    case "ShaderBloom":
                        contextMenu.MenuItems.Add("bloom（offset）  - ShaderParam_Bloom_offset");
                        contextMenu.MenuItems.Add("bloom（scale）  - ShaderParam_Bloom_scale");
                        break;
                }

                contextMenu.Show(this.tb, new Point(0, 0));
                for (int i = 0; i < contextMenu.MenuItems.Count; i++)
                {
                    contextMenu.MenuItems[i].Click += onContextMenuClick;
                }
            }
        }

        public void check()
        {
            try { 
                switch (ePropType) {
                    case EPropType.ePropType_Int:
                    {
                        int.Parse(tb.Text);
                        break;
                    }
                    case EPropType.ePropType_Float:
                    {
                        float.Parse(tb.Text);
                        break;
                    }
                    case EPropType.ePropType_Point:
                    {
                        new CCPoint(tb.Text);
                        break;
                    }
                    case EPropType.ePropType_Bezier:
                    {
                        new Bezier(tb.Text);
                        break;
                    }
                    case EPropType.ePropType_Str:
                    {
                        if (isFileName && tb.Text != "" && ActionParamTemplate.FindResPath(tb.Text) == null)
                        {
                            throw new Exception();
                        }
                        break;
                    }
                    case EPropType.ePropType_Strs:
                    {
                        if (isFileName)
                        {
                            foreach (string str in Regex.Split(tb.Text, ","))
                            {
                                if (str == "") continue;
                                if (ActionParamTemplate.FindResPath(str) == null)
                                {
                                    throw new Exception();
                                }
                            }
                        }
                        break;
                    }
                }
                tb.ForeColor = defaultForeColor;
            } catch (Exception) {
                tb.ForeColor = Color.Red;
                throw new Exception("错误的参数：" + tb.Text);
            }
        }

        public EPropType ePropType;
        public Label label = new Label();
        public Button btnSet = new Button();
        public TextBox tb = new TextBox();
        public bool isFileName;
        private Color defaultForeColor;
        private PropForm propForm;

        public String __curContextMenuValue = "";

        internal void onContextMenuClick(object sender, EventArgs e)
        {
            MenuItem item = sender as MenuItem;
            __curContextMenuValue = item != null ? item.Text : "";

            String ret = "";
            if (__curContextMenuValue != "" && __curContextMenuValue.IndexOf(" - ") >= 0)
            {
                ret = __curContextMenuValue.Substring(__curContextMenuValue.IndexOf(" - ") + " - ".Length);
            }
            else {
                ret = "";
                __curContextMenuValue = "";
            }

            if (ret == tb.Text) return; // no Change

            tb.Text = ret;

            if (ePropType == EPropType.ePropType_ShaderParamType)
            { // ePropType_ShaderType 类型
                int index = propForm.props.IndexOf(this);
                // 下面三个应该是参数，恢复成默认
                propForm.props[index + 1].tb.Text = "";
                propForm.props[index + 2].tb.Text = "1";
                propForm.props[index + 3].tb.Text = "1";
            }
        }

        private void onKeyPressed(object sender, KeyPressEventArgs e)
        {

        }
    }
}
