using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.Collections;

namespace ActionEditorUI
{
    public partial class ParticleDesign : Form
    {
        public delegate bool WNDENUMPROC(IntPtr hwnd, uint lParam);

        [DllImport("user32.dll")]
        private static extern int SendMessage(IntPtr hWnd, int Msg, int wParam, int lParam);

        [DllImport("user32.dll", EntryPoint = "EnumWindows", SetLastError = true)]
        public static extern bool EnumWindows(WNDENUMPROC lpEnumFunc, uint lParam);

        [DllImport("user32.dll", EntryPoint = "GetParent", SetLastError = true)]
        public static extern IntPtr GetParent(IntPtr hWnd);

        [DllImport("user32.dll", EntryPoint = "GetWindowThreadProcessId")]
        public static extern uint GetWindowThreadProcessId(IntPtr hWnd, ref uint lpdwProcessId);

        [DllImport("user32.dll", EntryPoint = "IsWindow")]
        public static extern bool IsWindow(IntPtr hWnd);

        [DllImport("kernel32.dll", EntryPoint = "SetLastError")]
        public static extern void SetLastError(uint dwErrCode);

        private static Hashtable processWnd = new Hashtable();

        public static IntPtr GetCurrentWindowHandle(uint uiPid)
        {
            IntPtr ptrWnd = IntPtr.Zero;
            object objWnd = processWnd[uiPid];

            if (objWnd != null)
            {
                ptrWnd = (IntPtr)objWnd;
                if (ptrWnd != IntPtr.Zero && IsWindow(ptrWnd))  // 从缓存中获取句柄
                {
                    return ptrWnd;
                }
                else
                {
                    ptrWnd = IntPtr.Zero;
                }
            }

            bool bResult = EnumWindows(new WNDENUMPROC(EnumWindowsProc), uiPid);
            // 枚举窗口返回 false 并且没有错误号时表明获取成功
            if (!bResult && Marshal.GetLastWin32Error() == 0)
            {
                objWnd = processWnd[uiPid];
                if (objWnd != null)
                {
                    ptrWnd = (IntPtr)objWnd;
                }
            }

            return ptrWnd;
        }

        private static bool EnumWindowsProc(IntPtr hwnd, uint lParam)
        {
            uint uiPid = 0;

            if (GetParent(hwnd) == IntPtr.Zero)
            {
                GetWindowThreadProcessId(hwnd, ref uiPid);
                if (uiPid == lParam)    // 找到进程对应的主窗口句柄
                {
                    processWnd[uiPid] = hwnd;   // 把句柄缓存起来
                    SetLastError(0);    // 设置无错误
                    return false;   // 返回 false 以终止枚举窗口
                }
            }

            return true;
        }


        public static ParticleDesign instance;

        public static void setDirty()
        {
            if (instance != null) instance.updateTitle(true);
        }

        private Process simulatedProcess;

        internal String plistFilePath = "";
        internal String textureFileName = "";   // texture file in the same dir of plistFileName
        internal String editorVersion = "1.0";

        private OpenFileDialog openPlistFileDialog = new OpenFileDialog();
        private SaveFileDialog savePlistFileDialog = new SaveFileDialog();
        private OpenFileDialog openPngFileDialog = new OpenFileDialog();

        private System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();

        public void setTextureFileName(String fileName)
        {
            this.textureFileName = fileName;
        }

        public ParticleDesign()
        {
            InitializeComponent();

            timer.Interval = 100;
            timer.Tick += timer_Tick;
            timer.Start();

            instance = this;

            openPlistFileDialog.Filter = "粒子Plist文件(*.plist)|*.plist";
            savePlistFileDialog.Filter = "粒子Plist文件(*.plist)|*.plist";
            openPngFileDialog.Filter = "纹理文件(*.png)|*.png";

            // 粒子设置
            maxParticles.data = new ParticleOptionData("最大粒子数", 0, 2000, true, "同时存在的最多粒子数量");
            lifeSpan.data = new ParticleOptionData("生命期(秒)", 0, 10, false, "单个粒子最大存在时间（秒）");
            lifeSpanVar.data = new ParticleOptionData("生命期变化(秒)", 0, 10, false, "单个粒子最大存在时间随机部分（秒）");
            startSize.data = new ParticleOptionData("初始大小", 0, 512, true, "粒子出生时大小，单位像素");
            startSizeVar.data = new ParticleOptionData("初始大小变化", 0, 512, true, "粒子出生时大小随机部分，单位像素");
            finishSize.data = new ParticleOptionData("结束大小", 0, 512, true, "粒子结束时大小，单位像素");
            finishSizeVar.data = new ParticleOptionData("结束大小变化", 0, 512, true, "粒子结束时大小变量，单位像素");
            emitAngle.data = new ParticleOptionData("发射角度", 0, 360, false, "粒子发射的角度");
            emitAngleVar.data = new ParticleOptionData("发射角度变化", 0, 360, true, "粒子发射的角度变量");
            rotationStart.data = new ParticleOptionData("旋转起始角度", -3600, 3600, true, "粒子自身旋转起始角度", 0.5f);
            rotationStartVar.data = new ParticleOptionData("旋转起始角度变化", -3600, 3600, true, "粒子自身旋转起始角度变量部分", 0.5f);
            rotationEnd.data = new ParticleOptionData("旋转终止角度", -3600, 3600, true, "粒子自身旋转终止角度", 0.5f);
            rotationEndVar.data = new ParticleOptionData("旋转终止角度变化", -3600, 3600, true, "旋转终止角度变量", 0.5f);

            bgColorOption.setColor(0, 0, 0);

            startColor.setName("起始颜色");
            startColorVar.setName("起始颜色变化");
            endColor.setName("结束颜色");
            endColorVar.setName("结束颜色变化");

            emDuration.data = new ParticleOptionData("生命期秒(-1:无限)", -1, 10, false, "发射器生命期，指的是粒子的总生命期", 0f);
            emPosX.data = new ParticleOptionData("X坐标位置", -1024, 1024, false, "发射器的X坐标", 0.5f);
            emPosXVar.data = new ParticleOptionData("X坐标变化", -1024, 1024, false, "发射器的X坐标变化", 0.5f);
            emPosY.data = new ParticleOptionData("Y坐标位置", -1024, 1024, false, "发射器的Y坐标", 0.5f);
            emPosYVar.data = new ParticleOptionData("Y坐标变化", -1024, 1024, false, "发射器的Y坐标变化", 0.5f);

            emGravitySpeed.data = new ParticleOptionData("速度", 0, 1024, false, "粒子发射出去的速度，[重力模式]", 0.0f);
            emGravitySpeedVar.data = new ParticleOptionData("速度变化值", 0, 1024, false, "粒子发射出去的速度变化值，[重力模式]", 0.0f);
            emGravityX.data = new ParticleOptionData("重力X分量", -3000, 3000, false, "重力在X轴上的分量，[重力模式]", 0.5f);
            emGravityY.data = new ParticleOptionData("重力Y分量", -3000, 3000, false, "重力在Y轴上的分量，[重力模式]", 0.5f);
            emGravityRadialAccel.data = new ParticleOptionData("径向加速度", -1024, 1024, false, "等我研究下的 ...[重力模式]", 0.5f);
            emGravityRadialAccelVar.data = new ParticleOptionData("径向加速度变化值", -1024, 1024, false, "等我研究下的 ...[重力模式]", 0.5f);
            emGravityTangentAccel.data = new ParticleOptionData("切线加速度", -1024, 1024, false, "等我研究下的 ...[重力模式]", 0.5f);
            emGravityTangentAccelVar.data = new ParticleOptionData("切线加速度变化值", -1024, 1024, false, "等我研究下的 ...[重力模式]", 0.5f);

            emRadialMaxRadius.data = new ParticleOptionData("最大半径", 0, 1024, false, "粒子出生位置的最大半径[径向模式]", 0.0f);
            emRadialMaxRadiusVar.data = new ParticleOptionData("最大半径变化", 0, 1024, false, "粒子出生位置的最大半径变化[径向模式]", 0.0f);
            emRadialMinRadius.data = new ParticleOptionData("最小半径", 0, 1024, false, "粒子出生位置的最小半径[径向模式]", 0.0f);
            emRadialDegPerSecond.data = new ParticleOptionData("角速度", 0, 360, false, "角速度，0~360[径向模式]", 0.0f);
            emRadialDegPerSecondVar.data = new ParticleOptionData("角速度变化", 0, 360, false, "角速度，0~360[径向模式]", 0.0f);

            radioEmitterGravity.Select();

            updateTitle(false);
        }

        void timer_Tick(object sender, EventArgs e)
        {
            if (simulatedProcess != null)
            { // 5000 设置窗口位置
                SendMessage(GetCurrentWindowHandle((uint)simulatedProcess.Id), 5000, this.DesktopLocation.X + Width + 20, this.DesktopLocation.Y);
            }
        }

        private void domainUpDown1_SelectedItemChanged(object sender, EventArgs e)
        {

        }

        private void maxParticles_Load(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void btnBlendSrc_Click(object sender, EventArgs e)
        {
            EBlendFactor eBlendFactor = (EBlendFactor)Enum.Parse(typeof(EBlendFactor), btnBlendSrc.Text);
            GLBlendFactorForm form = new GLBlendFactorForm();
            form.setGlBendFactor(eBlendFactor);
            form.ShowDialog();
            if (form.DialogResult == DialogResult.OK)
            {
                btnBlendSrc.Text = form.getGlBendFactor().ToString();
                if (btnBlendSrc.Text == Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_SRC_ALPHA)
                    && btnBlendDst.Text == Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_ONE_MINUS_SRC_ALPHA))
                {
                    btnBlendNormal.Font = new Font(btnBlendNormal.Font, FontStyle.Bold);
                    btnBlendToAdd.Font = new Font(btnBlendToAdd.Font, FontStyle.Regular);
                }
                else if (btnBlendSrc.Text == Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_SRC_ALPHA)
                    && btnBlendDst.Text == Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_ONE))
                {
                    btnBlendToAdd.Font = new Font(btnBlendToAdd.Font, FontStyle.Bold);
                    btnBlendNormal.Font = new Font(btnBlendNormal.Font, FontStyle.Regular);
                }
                else
                {
                    btnBlendToAdd.Font = new Font(btnBlendToAdd.Font, FontStyle.Regular);
                    btnBlendNormal.Font = new Font(btnBlendNormal.Font, FontStyle.Regular);
                }
                updateTitle(true);
            }
        }

        private void btnBlendDst_Click(object sender, EventArgs e)
        {
            EBlendFactor eBlendFactor = (EBlendFactor)Enum.Parse(typeof(EBlendFactor), btnBlendDst.Text);
            GLBlendFactorForm form = new GLBlendFactorForm();
            form.setGlBendFactor(eBlendFactor);
            form.ShowDialog();
            if (form.DialogResult == DialogResult.OK)
            {
                btnBlendDst.Text = form.getGlBendFactor().ToString();
                if (btnBlendSrc.Text == Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_SRC_ALPHA) 
                    && btnBlendDst.Text == Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_ONE_MINUS_SRC_ALPHA))
                {
                    btnBlendNormal.Font = new Font(btnBlendNormal.Font, FontStyle.Bold);
                    btnBlendToAdd.Font = new Font(btnBlendToAdd.Font, FontStyle.Regular);
                }
                else if (btnBlendSrc.Text == Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_SRC_ALPHA)
                    && btnBlendDst.Text == Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_ONE))
                {
                    btnBlendToAdd.Font = new Font(btnBlendToAdd.Font, FontStyle.Bold);
                    btnBlendNormal.Font = new Font(btnBlendNormal.Font, FontStyle.Regular);
                }
                else
                {
                    btnBlendToAdd.Font = new Font(btnBlendToAdd.Font, FontStyle.Regular);
                    btnBlendNormal.Font = new Font(btnBlendNormal.Font, FontStyle.Regular);
                }
                updateTitle(true);
            }
        }

        private void btnBlendNormal_Click(object sender, EventArgs e)
        {
            btnBlendSrc.Text = Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_SRC_ALPHA);
            btnBlendDst.Text = Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_ONE_MINUS_SRC_ALPHA);
            btnBlendNormal.Font = new Font(btnBlendNormal.Font, FontStyle.Bold);
            btnBlendToAdd.Font = new Font(btnBlendToAdd.Font, FontStyle.Regular);
            updateTitle(true);
        }

        private void btnBlendToAdd_Click(object sender, EventArgs e)
        {
            btnBlendSrc.Text = Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_SRC_ALPHA);
            btnBlendDst.Text = Enum.GetName(typeof(EBlendFactor), EBlendFactor.GL_ONE);
            btnBlendToAdd.Font = new Font(btnBlendToAdd.Font, FontStyle.Bold);
            btnBlendNormal.Font = new Font(btnBlendNormal.Font, FontStyle.Regular);
            updateTitle(true);
        }

        private void radioEmitterGravity_CheckedChanged(object sender, EventArgs e)
        {
            emGravitySpeed.Visible = true;
            emGravitySpeedVar.Visible = true;
            emGravityX.Visible = true;
            emGravityY.Visible = true;
            emGravityRadialAccel.Visible = true;
            emGravityRadialAccelVar.Visible = true;
            emGravityTangentAccel.Visible = true;
            emGravityTangentAccelVar.Visible = true;

            emRadialDegPerSecond.Visible = false;
            emRadialDegPerSecondVar.Visible = false;
            emRadialMaxRadius.Visible = false;
            emRadialMaxRadiusVar.Visible = false;
            emRadialMinRadius.Visible = false;
        }

        private void radioEmitterRadial_CheckedChanged(object sender, EventArgs e)
        {
            emGravitySpeed.Visible = false;
            emGravitySpeedVar.Visible = false;
            emGravityX.Visible = false;
            emGravityY.Visible = false;
            emGravityRadialAccel.Visible = false;
            emGravityRadialAccelVar.Visible = false;
            emGravityTangentAccel.Visible = false;
            emGravityTangentAccelVar.Visible = false;

            emRadialMaxRadius.Visible = true;
            emRadialMaxRadiusVar.Visible = true;
            emRadialMinRadius.Visible = true;
            emRadialDegPerSecond.Visible = true;
            emRadialDegPerSecondVar.Visible = true;
        }

        private void btnTexture_Click(object sender, EventArgs e)
        {
            if (plistFilePath == "")
            {
                MessageBox.Show("当前没有选择粒子文件");
                return;
            }
            if (DialogResult.OK == openPngFileDialog.ShowDialog())
            {
                if (Path.GetDirectoryName(plistFilePath) != Path.GetDirectoryName(openPlistFileDialog.FileName))
                {
                    MessageBox.Show("粒子文件纹理，必须在粒子文件所在目录下");
                    return;
                }
                setTextureFileName(Path.GetFileName(openPngFileDialog.FileName));

                String dir = Path.GetDirectoryName(plistFilePath);
                String textureFilePath = dir + Path.DirectorySeparatorChar + textureFileName;
                Image image = Image.FromFile(textureFilePath);
                if (image != null) { 
                    image = image.GetThumbnailImage(btnTexture.Size.Width, btnTexture.Size.Height, new Image.GetThumbnailImageAbort(isTrue), IntPtr.Zero);
                    btnTexture.Image = image;
                }
                updateTitle(true);
            }
        }

        private static void AppendKV(StringBuilder sb, int ntab, String k, String v, String type) {
            if (type == "real" && v == "0") v = "0.0";
            String strNTab = new String('\t', ntab);
            sb.Append(strNTab).Append("<key>").Append(k).Append("</key>\n");
            sb.Append(strNTab).Append("<" + type + ">").Append(v).Append("</" + type + ">\n");
        }

        private void readFromXml(XmlDocument doc)
        {
            XmlElement eDict = ((XmlElement)doc.SelectNodes("plist")[0].SelectNodes("dict")[0]);
            List<XmlElement> eChilds = new List<XmlElement>();
            for (XmlNode node = eDict.FirstChild; node != null; node = node.NextSibling )
            {
                if (!(node is XmlElement)) continue;

                eChilds.Add((XmlElement)node);
            }   

            for (int i = 0; i < eChilds.Count; ++i )
            {
                XmlElement e = eChilds[i];
                if (e.ChildNodes[0].Value == "angle")
                {
                    emitAngle.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "angleVariance")
                {
                    emitAngleVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "blendFuncDestination")
                {
                    btnBlendDst.Text = Enum.GetName(typeof(EBlendFactor), GLBlendFactorForm.transGlBlendFactor(int.Parse(eChilds[++i].ChildNodes[0].Value)));
                }
                else if (e.ChildNodes[0].Value == "blendFuncSource")
                {
                    btnBlendSrc.Text = Enum.GetName(typeof(EBlendFactor), GLBlendFactorForm.transGlBlendFactor(int.Parse(eChilds[++i].ChildNodes[0].Value)));
                }
                else if (e.ChildNodes[0].Value == "duration")
                {
                    emDuration.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "emitterType")
                {
                    // ??? emitterType TODO confirm 1.0 and 0.0
                    if (float.Parse(eChilds[++i].ChildNodes[0].Value) == 0)
                    {
                        radioEmitterGravity.Checked = true;
                    }
                    else
                    {
                        radioEmitterRadial.Checked = true;
                    }
                }
                else if (e.ChildNodes[0].Value == "finishColorAlpha")
                {
                    endColor.setA((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "finishColorBlue")
                {
                    endColor.setB((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "finishColorGreen")
                {
                    endColor.setG((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "finishColorRed")
                {
                    endColor.setR((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "finishColorVarianceAlpha")
                {
                    endColorVar.setA((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "finishColorVarianceBlue")
                {
                    endColorVar.setB((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "finishColorVarianceGreen")
                {
                    endColorVar.setG((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "finishColorVarianceRed")
                {
                    endColorVar.setR((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "finishParticleSize")
                {
                    finishSize.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "finishParticleSizeVariance")
                {
                    finishSizeVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "gravityx")
                {
                    emGravityX.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "gravityy")
                {
                    emGravityY.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "maxParticles")
                {
                    maxParticles.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "maxRadius")
                {
                    emRadialMaxRadius.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "maxRadiusVariance")
                {
                    emRadialMaxRadiusVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "minRadius")
                {
                    emRadialMinRadius.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "particleLifespan")
                {
                    lifeSpan.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "particleLifespanVariance")
                {
                    lifeSpanVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "radialAccelVariance")
                {
                    emGravityRadialAccelVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "radialAcceleration")
                {
                    emGravityRadialAccel.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "rotatePerSecond")
                {
                    emRadialDegPerSecond.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "rotatePerSecondVariance")
                {
                    emRadialDegPerSecondVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "rotationEnd")
                {
                    rotationEnd.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "rotationEndVariance")
                {
                    rotationEndVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "rotationStart")
                {
                    rotationStart.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "rotationStartVariance")
                {
                    rotationStartVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "sourcePositionVariancex")
                {
                    emPosXVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "sourcePositionVariancey")
                {
                    emPosYVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "sourcePositionx")
                {
                    emPosX.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "sourcePositiony")
                {
                    emPosY.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "speed")
                {
                    emGravitySpeed.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "speedVariance")
                {
                    emGravitySpeedVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "startColorAlpha")
                {
                    startColor.setA((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "startColorBlue")
                {
                    startColor.setB((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "startColorGreen")
                {
                    startColor.setG((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "startColorRed")
                {
                    startColor.setR((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "startColorVarianceAlpha")
                {
                    startColorVar.setA((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "startColorVarianceBlue")
                {
                    startColorVar.setB((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "startColorVarianceGreen")
                {
                    startColorVar.setG((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "startColorVarianceRed")
                {
                    startColorVar.setR((byte)Math.Round((float.Parse(eChilds[++i].ChildNodes[0].Value) * 255)));
                }
                else if (e.ChildNodes[0].Value == "startParticleSize")
                {
                    startSize.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "startParticleSizeVariance")
                {
                    startSizeVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "tangentialAccelVariance")
                {
                    emGravityTangentAccelVar.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "tangentialAcceleration")
                {
                    emGravityTangentAccel.setValue(float.Parse(eChilds[++i].ChildNodes[0].Value));
                }
                else if (e.ChildNodes[0].Value == "textureFileName")
                {
                    setTextureFileName(eChilds[++i].ChildNodes[0].Value);
                }
            }
        }

        private String toXml()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
            sb.Append("<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n");
            sb.Append("<plist version=\"1.0\">\n");
            sb.Append("<dict>\n");
            // angle
            AppendKV(sb, 1, "angle", emitAngle.getValue().ToString(), "real");
            // angleVariance
            AppendKV(sb, 1, "angleVariance", emitAngleVar.getValue().ToString(), "real");
            // ??? blendFuncDestination
            AppendKV(sb, 1, "blendFuncDestination", GLBlendFactorForm.transGlBlendFactor((EBlendFactor)Enum.Parse(typeof(EBlendFactor), btnBlendDst.Text)).ToString(), "integer");
            // ??? blendFuncSource
            AppendKV(sb, 1, "blendFuncSource", GLBlendFactorForm.transGlBlendFactor((EBlendFactor)Enum.Parse(typeof(EBlendFactor), btnBlendSrc.Text)).ToString(), "integer");
            // duration
            AppendKV(sb, 1, "duration", emDuration.getValue().ToString(), "real");
            // ??? emitterType TODO confirm 1.0 and 0.0
            AppendKV(sb, 1, "emitterType", (radioEmitterGravity.Checked ? 0.0f : 1.0f).ToString(), "real");
            // finishColorAlpha
            AppendKV(sb, 1, "finishColorAlpha", ((float)(endColor.getA() / 255.0f)).ToString(), "real");
            // finishColorBlue
            AppendKV(sb, 1, "finishColorBlue", ((float)(endColor.getB() / 255.0f)).ToString(), "real");
            // finishColorGreen
            AppendKV(sb, 1, "finishColorGreen", ((float)(endColor.getG() / 255.0f)).ToString(), "real");
            // finishColorRed
            AppendKV(sb, 1, "finishColorRed", ((float)(endColor.getR() / 255.0f)).ToString(), "real");
            // finishColorVarianceAlpha
            AppendKV(sb, 1, "finishColorVarianceAlpha", ((float)(endColorVar.getA() / 255.0f)).ToString(), "real");
            // finishColorVarianceBlue
            AppendKV(sb, 1, "finishColorVarianceBlue", ((float)(endColorVar.getB() / 255.0f)).ToString(), "real");
            // finishColorVarianceGreen
            AppendKV(sb, 1, "finishColorVarianceGreen", ((float)(endColorVar.getG() / 255.0f)).ToString(), "real");
            // finishColorVarianceRed
            AppendKV(sb, 1, "finishColorVarianceRed", ((float)(endColorVar.getR() / 255.0f)).ToString(), "real");
            // finishParticleSize
            AppendKV(sb, 1, "finishParticleSize", finishSize.getValue().ToString(), "real");
            // finishParticleSizeVariance
            AppendKV(sb, 1, "finishParticleSizeVariance", finishSizeVar.getValue().ToString(), "real");
            // gravityx
            AppendKV(sb, 1, "gravityx", emGravityX.getValue().ToString(), "real");
            // gravityy
            AppendKV(sb, 1, "gravityy", emGravityY.getValue().ToString(), "real");
            // maxParticles
            AppendKV(sb, 1, "maxParticles", maxParticles.getValue().ToString(), "real");
            // maxRadius
            AppendKV(sb, 1, "maxRadius", emRadialMaxRadius.getValue().ToString(), "real");
            // maxRadiusVariance
            AppendKV(sb, 1, "maxRadiusVariance", emRadialMaxRadiusVar.getValue().ToString(), "real");
            // minRadius
            AppendKV(sb, 1, "minRadius", emRadialMinRadius.getValue().ToString(), "real");
            // particleLifespan
            AppendKV(sb, 1, "particleLifespan", lifeSpan.getValue().ToString(), "real");
            // particleLifespanVariance
            AppendKV(sb, 1, "particleLifespanVariance", lifeSpanVar.getValue().ToString(), "real");
            // radialAccelVariance
            AppendKV(sb, 1, "radialAccelVariance", emGravityRadialAccelVar.getValue().ToString(), "real");
            // radialAcceleration
            AppendKV(sb, 1, "radialAcceleration", emGravityRadialAccel.getValue().ToString(), "real");
            // rotatePerSecond
            AppendKV(sb, 1, "rotatePerSecond", emRadialDegPerSecond.getValue().ToString(), "real");
            // rotatePerSecondVariance
            AppendKV(sb, 1, "rotatePerSecondVariance", emRadialDegPerSecondVar.getValue().ToString(), "real");
            // rotationEnd
            AppendKV(sb, 1, "rotationEnd", rotationEnd.getValue().ToString(), "real");
            // rotationEndVariance
            AppendKV(sb, 1, "rotationEndVariance", rotationEndVar.getValue().ToString(), "real");
            // rotationStart
            AppendKV(sb, 1, "rotationStart", rotationStart.getValue().ToString(), "real");
            // rotationStartVariance
            AppendKV(sb, 1, "rotationStartVariance", rotationStartVar.getValue().ToString(), "real");
            // sourcePositionVariancex
            AppendKV(sb, 1, "sourcePositionVariancex", emPosXVar.getValue().ToString(), "real");
            // sourcePositionVariancey
            AppendKV(sb, 1, "sourcePositionVariancey", emPosYVar.getValue().ToString(), "real");
            // sourcePositionx
            AppendKV(sb, 1, "sourcePositionx", emPosX.getValue().ToString(), "real");
            // sourcePositiony
            AppendKV(sb, 1, "sourcePositiony", emPosY.getValue().ToString(), "real");
            // speed
            AppendKV(sb, 1, "speed", emGravitySpeed.getValue().ToString(), "real");
            // speedVariance
            AppendKV(sb, 1, "speedVariance", emGravitySpeedVar.getValue().ToString(), "real");
            // startColorAlpha
            AppendKV(sb, 1, "startColorAlpha", ((float)(startColor.getA() / 255.0f)).ToString(), "real");
            // startColorBlue
            AppendKV(sb, 1, "startColorBlue", ((float)(startColor.getB() / 255.0f)).ToString(), "real");
            // startColorGreen
            AppendKV(sb, 1, "startColorGreen", ((float)(startColor.getG() / 255.0f)).ToString(), "real");
            // startColorRed
            AppendKV(sb, 1, "startColorRed", ((float)(startColor.getR() / 255.0f)).ToString(), "real");
            // startColorVarianceAlpha
            AppendKV(sb, 1, "startColorVarianceAlpha", ((float)(startColorVar.getA() / 255.0f)).ToString(), "real");
            // startColorVarianceBlue
            AppendKV(sb, 1, "startColorVarianceBlue", ((float)(startColorVar.getB() / 255.0f)).ToString(), "real");
            // startColorVarianceGreen
            AppendKV(sb, 1, "startColorVarianceGreen", ((float)(startColorVar.getG() / 255.0f)).ToString(), "real");
            // startColorVarianceRed
            AppendKV(sb, 1, "startColorVarianceRed", ((float)(startColorVar.getR() / 255.0f)).ToString(), "real");
            // startParticleSize
            AppendKV(sb, 1, "startParticleSize", startSize.getValue().ToString(), "real");
            // startParticleSizeVariance
            AppendKV(sb, 1, "startParticleSizeVariance", startSizeVar.getValue().ToString(), "real");
            // tangentialAccelVariance
            AppendKV(sb, 1, "tangentialAccelVariance", emGravityTangentAccelVar.getValue().ToString(), "real");
            // tangentialAcceleration
            AppendKV(sb, 1, "tangentialAcceleration", emGravityTangentAccel.getValue().ToString(), "real");
            // textureFileName
            AppendKV(sb, 1, "textureFileName", textureFileName, "string");

            sb.Append("</dict>\n");
            sb.Append("</plist>\n");

            return sb.ToString();
        }

        private void btnSaveTo_Click(object sender, EventArgs e)
        {
            saveTo();          
        }

        private void save()
        {
            if (plistFilePath != "") { 
                StreamWriter sw = new StreamWriter(new FileStream(plistFilePath, FileMode.Create), new UTF8Encoding(false));
                try
                {
                    sw.Write(toXml());
                }
                finally
                {
                    sw.Close();
                }
                updateTitle(false);
                if (simulatedProcess != null) {
                    SendMessage(GetCurrentWindowHandle((uint)simulatedProcess.Id), 5001, 0, 0);
                }
            }
        }

        private void saveTo()
        {
            if (DialogResult.OK == savePlistFileDialog.ShowDialog())
            {
                String newFilePath = savePlistFileDialog.FileName;
                StreamWriter sw = new StreamWriter(new FileStream(newFilePath, FileMode.Create), new UTF8Encoding(false));
                try
                {
                    sw.Write(toXml());
                }
                finally
                {
                    sw.Close();
                }
                plistFilePath = newFilePath;
                updateTitle(false);
            }
        }

        private bool isDirty()
        {
            return this.Text.Contains("*");
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (DialogResult.OK != openPlistFileDialog.ShowDialog()) return;
            if (this.Text.Contains("*"))
            { // Dirty
                if (plistFilePath != "")
                {
                    if (DialogResult.OK == MessageBox.Show("是否保存对 " + plistFilePath + " 的修改?"))
                    {
                        save();
                    }
                }
                else
                {
                    if (DialogResult.OK == MessageBox.Show("是否保存当前修改?"))
                    {
                        saveTo();
                    }
                }
            }

            String oldFilePath = plistFilePath;
            try
            {
                readPlistFile(openPlistFileDialog.FileName);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
                if (oldFilePath != "")
                {
                    readPlistFile(oldFilePath);
                }
            }

            String dir = Path.GetDirectoryName(plistFilePath);
            String textureFilePath = dir + Path.DirectorySeparatorChar + textureFileName;
            Image image = Image.FromFile(textureFilePath);
            if (image != null) { 
                image = image.GetThumbnailImage(btnTexture.Size.Width, btnTexture.Size.Height, new Image.GetThumbnailImageAbort(isTrue), IntPtr.Zero);
                btnTexture.Image = image;
            }

            updateTitle(false);
        }

        private bool isTrue()
        {
            return true;
        }

        private void readPlistFile(String filePath)
        {
            XmlDocument doc = new XmlDocument();
            // 断网的时候，很影响效率
            String toDel = "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">";
            StreamReader fs = new StreamReader(new FileStream(filePath, FileMode.Open));
            String strData = fs.ReadToEnd();
            strData = strData.Replace(toDel, "");
            fs.Close();
            doc.LoadXml(strData);
            readFromXml(doc);

            plistFilePath = filePath;
        }

        private void updateTitle(bool isDirty)
        {
            this.Text = "粒子编辑器" + editorVersion + " -- " + (plistFilePath == "" ? "NewFile" : plistFilePath) + (isDirty ? " *" : "");
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            save();
        }

        private void btnRun_Click(object sender, EventArgs e)
        {
            if (plistFilePath == "")
            {
                MessageBox.Show("plist文件不存在！！！！");
                return;
            }
            if (textureFileName == "")
            {
                MessageBox.Show("纹理没有设置");
                return;
            }

            if (isDirty())
            {
                if (plistFilePath == "")
                {
                    saveTo();
                }
                else
                {
                    save();
                }
            }

            if (simulatedProcess != null)
            {
                try
                {
                    simulatedProcess.Kill();
                }
                catch (Exception ex)
                {
                    Console.Error.WriteLine(ex);
                }
                simulatedProcess = null;
            }

            String path = Path.GetFullPath(plistFilePath);
            String commonPath = Path.GetFullPath("./common");
            path = path.Replace(commonPath, "");
            path = path.Replace("\\", "/");
            System.Diagnostics.ProcessStartInfo Info = new System.Diagnostics.ProcessStartInfo();
            Info.FileName = Application.StartupPath + "\\PListViewer.exe ";
            Info.WorkingDirectory = Application.StartupPath;
            Info.Arguments = path;
            simulatedProcess = System.Diagnostics.Process.Start(Info);
            Thread.Sleep(1000);
            Console.WriteLine(simulatedProcess.MainWindowHandle);
        }
    }
}
