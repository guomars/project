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
using System.Drawing.Drawing2D;

namespace ActionEditorUI
{
    public partial class RegionMoveForm : Form
    {
        private const float scaleFactor = 0.5f;

        private Process simulatedProcess;

        private OpenFileDialog openRYFileDialog = new OpenFileDialog();
        private SaveFileDialog saveRYFileDialog = new SaveFileDialog();
        private RegionParamForm paramDialog = new RegionParamForm();

        internal RegionMoveData ryData = new RegionMoveData();
        internal List<Button> paramButtons = new List<Button>();
        internal List<Button> delButtons = new List<Button>();

        internal Keys curKeyDown = Keys.None;
        internal DateTime lastKeyDT = DateTime.Now;
        internal bool isInMouseDrag = false;
        internal Point mouseLastMoved = new Point();
        internal int curMouseSelect_regionIndex = -1;
        internal bool curMouseSelect_isCenter = false;

        private bool isDirty = false;

        public void SetData(RegionMoveData _ryData)
        {
            if (_ryData != null) { 
                this.ryData = _ryData;
            }

            UpdateStatus(false);
        }

        public RegionMoveForm()
        {
            InitializeComponent();

            openRYFileDialog.Filter = "区域震动编辑器文件(*.ry)|*.ry";
            openRYFileDialog.RestoreDirectory = false;
            saveRYFileDialog.Filter = "区域震动编辑器文件(*.ry)|*.ry";
            saveRYFileDialog.RestoreDirectory = false;

            Panel oldPanel = this.regionPanel;
            this.regionPanel = new AEPanel();
            this.regionPanel.BackColor = oldPanel.BackColor;
            this.regionPanel.Location = oldPanel.Location;
            this.regionPanel.Name = oldPanel.Name;
            this.regionPanel.Size = oldPanel.Size;
            this.regionPanel.TabIndex = 0;

            this.Controls.Remove(oldPanel);
            this.Controls.Add(this.regionPanel);

            paramDialog.ParamChanged += OnParamChanged;
            regionPanel.Paint += OnPaint;
            regionPanel.MouseDown += OnMouseDown;
            regionPanel.MouseUp += OnMouseUp;
            regionPanel.MouseMove += OnMouseMove;

            regionPanel.KeyUp += OnKeyUp;
            regionPanel.KeyDown += OnKeyDown;

            Timer aTimer = new Timer();
            aTimer.Interval = 10;
            aTimer.Enabled = true;
            aTimer.Tick += OnTimer;
            aTimer.Start();

            this.DoubleBuffered = true;
            this.SetStyle(ControlStyles.OptimizedDoubleBuffer | ControlStyles.AllPaintingInWmPaint, true);
        }

        private void UpdateStatus(bool _isDirty)
        {
            this.isDirty = _isDirty;
            StringBuilder sb = new StringBuilder();
            sb.Append("区域震动编辑器");
            if (ryData.fileName != "")
            {
                sb.Append(" -- ").Append(ryData.fileName);
            }
            if (isDirty)
            {
                sb.Append(" *");
            }
            this.Text = sb.ToString();
            if (this.isDirty)
            {
                regionPanel.Invalidate();
            }
            this.tbTestBackGround.Text = ryData.testBackGround;

            UpdateButtons();

            Refresh();
        }

        private float distance(float x1, float x2, float y1, float y2)
        {
            return (float)Math.Sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        }

        private bool isInEllipse(float x, float y, CCPoint center, CCPoint radius)
        {
            return (x - center.x) * (x - center.x) / (radius.x * radius.x) + (y - center.y) * (y - center.y) / (radius.y * radius.y) < 1;
        }

        private void OnMouseDown(Object sender, MouseEventArgs e)
        {
            regionPanel.Select();

            isInMouseDrag = true;
            mouseLastMoved = e.Location;
            curMouseSelect_regionIndex = -1;
            Point mp = new Point((int)(e.Location.X / scaleFactor), (int)(ryData.originalSize.y - e.Location.Y / scaleFactor));
            for (int i = 0; i < ryData.regionParams.Count; ++i)
            {
                if (distance(ryData.regionParams[i].moveCenter.x, mp.X, ryData.regionParams[i].moveCenter.y, mp.Y) < 10)
                {
                    curMouseSelect_isCenter = true;
                    curMouseSelect_regionIndex = i;
                    break;
                }

                if (isInEllipse(mp.X, mp.Y, ryData.regionParams[i].center, ryData.regionParams[i].radius))
                {
                    curMouseSelect_isCenter = false;
                    curMouseSelect_regionIndex = i;
                    break;
                }
            }

            Refresh();
        }

        private void OnMouseMove(Object sender, MouseEventArgs e)
        {
            if (!isInMouseDrag) return;

            int deltaX = (int)((e.Location.X - mouseLastMoved.X) / scaleFactor);
            int deltaY = -(int)((e.Location.Y - mouseLastMoved.Y) / scaleFactor);
            if (deltaX == 0 && deltaY == 0) return;
            mouseLastMoved = e.Location;

            if (curMouseSelect_regionIndex >= 0 && curMouseSelect_regionIndex < ryData.regionParams.Count)
            {
                RegionParam rp = ryData.regionParams[curMouseSelect_regionIndex];
                if (curMouseSelect_isCenter)
                {
                    rp.moveCenter.x += deltaX;
                    rp.moveCenter.y += deltaY;
                }
                else
                {
                    rp.moveCenter.x += deltaX;
                    rp.moveCenter.y += deltaY;
                    rp.center.x += deltaX;
                    rp.center.y += deltaY;
                }
            }
            else
            {
                curMouseSelect_regionIndex = -1;
            }

            UpdateStatus(true);
            Refresh();
        }

        private void OnMouseUp(Object sender, MouseEventArgs e)
        {
            isInMouseDrag = false;
        }

        private void OnTimer(object sender, EventArgs e)
        {
            lastKeyDT = DateTime.Now;
            if (curMouseSelect_regionIndex < 0 || curMouseSelect_regionIndex >= ryData.regionParams.Count)
            {
                curMouseSelect_regionIndex = -1;
                return;
            }
            if (this.curKeyDown == Keys.None) return;

            DateTime curDT = DateTime.Now;
            int delta = Math.Max((int)curDT.Subtract(lastKeyDT).TotalMilliseconds / 10, 1);
            Console.WriteLine("delta: " + delta);
            RegionParam rp = ryData.regionParams[curMouseSelect_regionIndex];
            if (this.curKeyDown == Keys.W)
            {
                rp.radius.y += delta;
            }
            else if (this.curKeyDown == Keys.A)
            {
                rp.radius.x -= delta;
            }
            else if (this.curKeyDown == Keys.S)
            {
                rp.radius.y -= delta;
            }
            else if (this.curKeyDown == Keys.D)
            {
                rp.radius.x += delta;
            }
            else if (this.curKeyDown == Keys.D1)
            {
                rp.dir = (rp.dir + delta * 15) % 360;
            }
            else if (this.curKeyDown == Keys.D2)
            {
                rp.dir = Math.Max((rp.dir - delta * 15), 0) % 360;
            }
            else if (this.curKeyDown == Keys.D3)
            {
                rp.amplitude += delta * 2;
            }
            else if (this.curKeyDown == Keys.D4)
            {
                rp.amplitude = Math.Max(0, rp.amplitude - delta * 2);
            }

            UpdateStatus(true);
            Refresh();

            lastKeyDT = curDT;
        }

        private void OnKeyUp(Object sender, KeyEventArgs e)
        {
            this.curKeyDown = Keys.None;
            lastKeyDT = DateTime.Now;
        }

        private void OnKeyDown(Object sender, KeyEventArgs e)
        {
            this.curKeyDown = e.KeyCode;
            lastKeyDT = DateTime.Now;
        }

        private void OnPaint(Object sender, PaintEventArgs e)
        {
            BufferedGraphicsContext currentContext = BufferedGraphicsManager.Current;
            BufferedGraphics myBuffer = currentContext.Allocate(e.Graphics, e.ClipRectangle);
            Graphics g = myBuffer.Graphics;
            g.SmoothingMode = SmoothingMode.HighQuality;
            g.PixelOffsetMode = PixelOffsetMode.HighSpeed;

            if (ryData.testBackGround != "")
            {
                String path = ActionParamTemplate.FindResPath(ryData.testBackGround);
                if (path != null)
                {
                    Image image = Image.FromFile(path);
                    g.DrawImage(image, new Rectangle(0, 0, (int)(image.Width * scaleFactor), (int)(image.Height * scaleFactor)), 0, 0, image.Width, image.Height, GraphicsUnit.Pixel);
                }

                for (int i = 0; i < ryData.regionParams.Count; ++i) {
                    RegionParam param = ryData.regionParams[i];

                    Color color = curMouseSelect_regionIndex == i && !curMouseSelect_isCenter ? Color.Red : Color.Black;
                    g.DrawEllipse(new Pen(color, 2), 
                        (int)((param.center.x - param.radius.x) * scaleFactor),
                        (int)((ryData.originalSize.y - param.center.y - param.radius.y) * scaleFactor),
                        (int)(param.radius.x * 2 * scaleFactor),
                        (int)(param.radius.y * 2 * scaleFactor));
                    color = curMouseSelect_regionIndex == i ? Color.Red : Color.Black;
                    g.DrawEllipse(new Pen(color, 2), 
                        ((param.moveCenter.x - 2) * scaleFactor), 
                        ((ryData.originalSize.y - param.moveCenter.y - 2) * scaleFactor), 
                        4, 
                        4);

                    if (param.dir >= 0) {
                        float lineX = param.amplitude * (float)Math.Cos(param.dir / 180 * Math.PI);
                        float lineY = param.amplitude * (float)Math.Sin(param.dir / 180 * Math.PI);

                        g.DrawLine(new Pen(color, 2),
                            new Point((int)(param.moveCenter.x * scaleFactor), (int)((ryData.originalSize.y - param.moveCenter.y) * scaleFactor)),
                            new Point((int)((param.moveCenter.x + lineX) * scaleFactor), (int)((ryData.originalSize.y - param.moveCenter.y - lineY) * scaleFactor)));
                    }
                }
            }

            myBuffer.Render();
            myBuffer.Dispose();//释放资源
        }

        private void UpdateButtons()
        {
            foreach (Button btn in paramButtons) {
                this.Controls.Remove(btn);
            }
            paramButtons.Clear();
            foreach (Button btn in delButtons) {
                this.Controls.Remove(btn);
            }
            delButtons.Clear();

            for (int i = 0; i < ryData.regionParams.Count; ++i)
            {
                RegionParam param = ryData.regionParams[i];
                {
                    Button btnParam = new Button();
                    btnParam.RightToLeft = RightToLeft.No;
                    btnParam.Size = new System.Drawing.Size(330, 30);
                    btnParam.Location = new Point(420, 100 + 40 * paramButtons.Count);
                    btnParam.Text = "" + (i+1) + ". c=" + param.center + ",r=" + param.radius + ",mc=" + param.moveCenter + ",dir=" + param.dir;
                    paramButtons.Add(btnParam);
                    this.Controls.Add(btnParam);

                    btnParam.Click += onClickBtnParam;
                }

                {
                    Button btnDel = new Button();
                    btnDel.RightToLeft = RightToLeft.No;
                    btnDel.Size = new System.Drawing.Size(40, 30);
                    btnDel.Location = new Point(760, 100 + 40 * delButtons.Count);
                    btnDel.Text = "删除";
                    delButtons.Add(btnDel);
                    this.Controls.Add(btnDel);

                    btnDel.Click += onClickBtnDel;
                }
            }
        }

        private void OnParamChanged(object sender, EventArgs e)
        {
            RegionParam param = (RegionParam)sender;
            if (!ryData.regionParams.Contains(param))
            {
                ryData.regionParams.Add(param);
            }
            UpdateStatus(true);
        }

        private void OpenRegionParamDialog(RegionParam param)
        {

            if (param != null)
            {
                paramDialog.Init(param);
            }
            else
            {
                paramDialog.Init(new RegionParam());
            }
            paramDialog.ShowDialog(this);
        }

        private void btnAddParam_Click(object sender, EventArgs e)
        {
            OpenRegionParamDialog(null);
        }

        private void onClickBtnParam(object sender, EventArgs e)
        {
            Button btnParam = (Button)sender;
            if (btnParam == null || !paramButtons.Contains(btnParam)) return;
            int index = paramButtons.IndexOf(btnParam);

            OpenRegionParamDialog(ryData.regionParams[index]);
        }

        private void onClickBtnDel(object sender, EventArgs e)
        {
            int index = delButtons.IndexOf((Button)sender);
            if (index >= 0 && index < ryData.regionParams.Count)
            {
                ryData.regionParams.RemoveAt(index);
            }
            UpdateStatus(true);
        }

        private void btnSimulate_Click(object sender, EventArgs e)
        {
            if (ryData.fileName == "") return;
            if (isDirty)
            {
                ryData.WriteToFile(ryData.fileName);
                UpdateStatus(false);
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

            System.Diagnostics.ProcessStartInfo Info = new System.Diagnostics.ProcessStartInfo();
            Info.FileName = Application.StartupPath + "\\ActionEditor.win32.exe";
            Info.WorkingDirectory = Application.StartupPath;
            int width = 768;
            int height = 1024;
            float scale = 0.8f;
            Info.Arguments = " " + width + " " + height + " " + scale + " " + ryData.fileName + " ";
            simulatedProcess = System.Diagnostics.Process.Start(Info);
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            save();
        }

        private void save()
        {
            ryData.testBackGround.Replace('\\', '/');
            if (ryData.fileName == "")
            {
                if (saveRYFileDialog.ShowDialog() == DialogResult.OK)
                {
                    ryData.WriteToFile(saveRYFileDialog.FileName);

                    UpdateStatus(false);
                }
            }
            else
            {
                ryData.WriteToFile(ryData.fileName);

                UpdateStatus(false);
            }
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (isDirty)
            {
                if (DialogResult.OK == MessageBox.Show("是否保存当前编辑?", "是否保存", MessageBoxButtons.YesNo))
                {
                    save();
                }
            }
            if (openRYFileDialog.ShowDialog() == DialogResult.OK)
            {
                SetData(new RegionMoveData(openRYFileDialog.FileName));
                UpdateStatus(false);
            }
        }

        private void tbTestBackGround_TextChanged(object sender, EventArgs e)
        {
            ryData.testBackGround = tbTestBackGround.Text.Replace('\\', '/');
            UpdateStatus(true);
        }

        private void btnNew_Click(object sender, EventArgs e)
        {
            if (isDirty)
            {
                if (DialogResult.OK == MessageBox.Show("是否保存当前编辑?", "是否保存", MessageBoxButtons.YesNo))
                {
                    save();
                }
            }
            if (saveRYFileDialog.ShowDialog() == DialogResult.OK)
            {
                SetData(new RegionMoveData());
                ryData.WriteToFile(saveRYFileDialog.FileName);
                UpdateStatus(false);
            }
        }
    }

    public class RegionMoveData
    {
        internal String testBackGround = "";
        internal CCPoint originalSize = new CCPoint(768, 1024);
        internal List<RegionParam> regionParams = new List<RegionParam>();
        internal String fileName = "";

        public String toXmlStr()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
            sb.Append("<ry testBackGround=\"").Append(testBackGround).Append("\" originalSize=\"").Append(originalSize.ToString()).Append("\">\n");
            foreach (RegionParam xxx in regionParams)
            {
                sb.Append("\t").Append(xxx.ToXmlStr()).Append("\n");
            }
            sb.Append("</ry>");
            return sb.ToString();
        }

        public RegionMoveData() { }

        public RegionMoveData(String fileName)
        {
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load(fileName);

            XmlNodeList nodeList = xmlDoc.SelectNodes("ry");
            if (nodeList.Count == 0) throw new Exception("load RY, not find <aeditor>, fileName=" + fileName);

            this.fileName = fileName;
            Init((XmlElement)(nodeList.Item(0)));
        }

        public void Init(XmlElement e)
        {
            testBackGround = e.GetAttribute("testBackGround");
            if (e.HasAttribute("originalSize"))
            {
                originalSize = new CCPoint(e.GetAttribute("originalSize"));
            }
            foreach (XmlNode eNode in e.SelectNodes("RegionParam"))
            {
                regionParams.Add(new RegionParam((XmlElement)eNode));
            }
        }

        public void WriteToFile(String fileName)
        {
            StreamWriter sw = new StreamWriter(new FileStream(fileName, FileMode.Create), new UTF8Encoding(false));
            try
            {
                sw.Write(toXmlStr());
            }
            finally
            {
                sw.Close();
            }
            this.fileName = fileName;
        }
    }

    public class AEPanel : Panel
    {
        public AEPanel()
        {
            SetStyle(ControlStyles.UserPaint |
                       ControlStyles.AllPaintingInWmPaint |
                       ControlStyles.OptimizedDoubleBuffer |
                       ControlStyles.ResizeRedraw |
                       ControlStyles.SupportsTransparentBackColor, true);
        }
    }
}
