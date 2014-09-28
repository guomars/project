using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace ActionEditorUI
{
    public partial class TimeSpanForm : Form
    {
        public static TimeSpanForm instance = null; 

        const int WM_SYSCOMMAND = 0x112;
        const int WM_SIZE = 0x0005;
        const int SC_CLOSE = 0xF060;
        const int SC_MINIMIZE = 0xF020;
        const int SC_MAXIMIZE = 0xF030;
        const int SC_RESTORE = 61728;

        const int spanPanelOffsetX = 5;
        const int spanPanelOffsetY1 = 50;
        const int spanPanelOffsetY2 = 10;

        SpanPanel spanPanel;

        internal void updateActionBox(AEData aeData)
        {
            spanPanel.updateActionBox(aeData);
        }

        public TimeSpanForm()
        {
            InitializeComponent();

            this.Size = new System.Drawing.Size(1024, 800);

            spanPanel = new SpanPanel(this.Size.Width - spanPanelOffsetX * 2, this.Size.Height - spanPanelOffsetY1 - spanPanelOffsetY2);
            this.Controls.Add(spanPanel);
            spanPanel.Location = new Point(spanPanelOffsetX, spanPanelOffsetY1);

            this.ResizeEnd += TimeSpanForm_ResizeEnd;
            this.MaximumSizeChanged += TimeSpanForm_MaximumSizeChanged;
            this.MouseWheel += TimeSpanForm_MouseWheel;

            this.FormClosed += TimeSpanForm_FormClosed;

            instance = this;

            spanPanel.updateActionBox(MainFrame.instance.curEditAEData);
        }

        void TimeSpanForm_FormClosed(object sender, FormClosedEventArgs e)
        {
            instance = null;
        }

        private void __resize()
        {
            spanPanel.resize(this.Size.Width - spanPanelOffsetX * 2, this.Size.Height - -spanPanelOffsetY1 - spanPanelOffsetY2);
        }

        protected override void WndProc(ref Message m)
        {
            base.WndProc(ref m);

            switch (m.Msg)
            {
                case WM_SYSCOMMAND:
                    if (m.WParam.ToInt32() == SC_MAXIMIZE || m.WParam.ToInt32() == SC_RESTORE)
                    {
                        __resize();                
                        return;
                    }
                    break;
                case WM_SIZE:
                    __resize();       
                    return;
            }
        }

        void TimeSpanForm_MaximumSizeChanged(object sender, EventArgs e)
        {
            __resize();
        }

        void TimeSpanForm_MouseWheel(object sender, MouseEventArgs e)
        {
            spanPanel.SpanPanel_MouseWheel(sender, e);
        }

        void TimeSpanForm_ResizeEnd(object sender, EventArgs e)
        {
            __resize();
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }
    }

    public class ActionBoxIndex
    {
        internal float passed;
        internal int spanHeight;
        internal float duration;

        internal ActionBoxIndex(float _passed, int _spanHeight, float _duration)
        {
            this.passed = _passed;
            this.spanHeight = _spanHeight;
            this.duration = _duration;
        }

        public override int GetHashCode()
        {
            return (int)(passed + spanHeight * 100 + duration * 10);
        }
        public override bool Equals(object obj)
        {
            if (!(obj is ActionBoxIndex)) return false;

            ActionBoxIndex oth = (ActionBoxIndex)obj;
            return oth.passed == passed && oth.spanHeight == this.spanHeight && oth.duration == duration;
        }
    }

    public class SpriteBox
    {
        internal AESprite aeSprite;
        internal int curHeight = 0;

        internal SpriteBox(AESprite _aeSprite, int curHeight)
        {
            this.aeSprite = _aeSprite;
            this.curHeight = curHeight;

            foreach (ActionTemplate actionTemplate in _aeSprite.actions)
            {
                addAction(actionTemplate);
            }
        }

        internal void addAction(ActionTemplate actionTemplate)
        {
            if (actionTemplate.subActionList.Count >= 1)
            { // 找到最子的动作
                foreach (ActionTemplate xxx in actionTemplate.subActionList)
                {
                    addAction(xxx);
                }
            }
            else
            { // 最子的动作
                ActionBoxIndex index = new ActionBoxIndex(actionTemplate.__passed, actionTemplate.__spanStart + curHeight, actionTemplate.__duration);
                if (!actionBoxs.ContainsKey(index))
                {
                    ActionsBox xxx = new ActionsBox(index);
                    actionBoxs[index] = xxx;
                }
                actionBoxs[index].actions.Add(actionTemplate);
            }
        }

        public void draw(SpanPanel spanPanel, Graphics g)
        {
            float width = SpanPanel.spriteWidth - 15;
            float startX = 10;
            float startY = spanPanel.getSpriteY(curHeight);
            PointF[] points = new PointF[] {
                new PointF(startX, startY),
                new PointF(startX + width, startY),
                new PointF(startX + width, startY + SpanPanel.spriteHeight),
                new PointF(startX, startY + SpanPanel.spriteHeight),
            };
            g.FillPolygon(new SolidBrush(Color.White), points);
            g.DrawPolygon(new Pen(Color.Black), points);

            StringFormat format = new StringFormat();
            format.Alignment = StringAlignment.Far;
            format.FormatFlags = StringFormatFlags.DirectionRightToLeft
                | StringFormatFlags.NoClip | StringFormatFlags.NoWrap;
            RectangleF layoutRectangle = new RectangleF();
            layoutRectangle.Location = new PointF(startX, startY + 4);
            layoutRectangle.Width = width;
            layoutRectangle.Height = SpanPanel.spriteHeight;
            g.DrawString(aeSprite.name, new Font("宋体", 11), new SolidBrush(Color.Black), layoutRectangle, format);

            foreach (ActionsBox actionsBox in actionBoxs.Values) {
                actionsBox.draw(spanPanel, g);
            }
        }

        Dictionary<ActionBoxIndex, ActionsBox> actionBoxs = new Dictionary<ActionBoxIndex, ActionsBox>();
    }

    public class ActionsBox
    {
        internal ActionBoxIndex index;
        internal List<ActionTemplate> actions = new List<ActionTemplate>();

        internal ActionsBox(ActionBoxIndex _index)
        {
            this.index = _index;
        }

        internal void draw(SpanPanel spanPanel, Graphics g)
        {
            float width = spanPanel.secondInPixel * index.duration;

            if (index.duration == 0)
            {
                if (index.passed < spanPanel.curBeginSecond) return;

                float startX = spanPanel.getPixelOfSecond(index.passed);
                float startY = spanPanel.getSpriteY(index.spanHeight);
                PointF[] points = new PointF[] {
                    new PointF(startX - 4, startY - 6),
                    new PointF(startX + 4, startY - 6),
                    new PointF(startX, startY),
                };
                g.FillPolygon(new SolidBrush(Color.Red), points);
                g.DrawPolygon(new Pen(Color.Black), points);
                g.DrawLine(new Pen(Color.Black), new PointF(startX, startY), new PointF(startX, startY + SpanPanel.spriteHeight / 2));
            }
            else 
            {
                if (index.passed + index.duration < spanPanel.curBeginSecond) return;

                float startX = spanPanel.getPixelOfSecond(index.passed > spanPanel.curBeginSecond ? index.passed : spanPanel.curBeginSecond);
                width = width + (spanPanel.getPixelOfSecond(index.passed) - startX);
                if (actions[0].name == "CCDelayTime")
                { // 延迟只画线
                    float startY = spanPanel.getSpriteY(index.spanHeight) + SpanPanel.spriteHeight / 2;
                    PointF[] points = new PointF[] {
                        new PointF(startX, startY - 2),
                        new PointF(startX + width, startY - 2),
                        new PointF(startX + width, startY + 2),
                        new PointF(startX, startY + 2),
                    };
                    g.FillPolygon(new SolidBrush(Color.BurlyWood), points);
                    g.DrawPolygon(new Pen(Color.Black), points);
                }
                else {
                    // 画盒子
                    float startY = spanPanel.getSpriteY(index.spanHeight);
                    PointF[] points = new PointF[] {
                        new PointF(startX, startY + 2),
                        new PointF(startX + width, startY + 2),
                        new PointF(startX + width, startY + SpanPanel.spriteHeight - 2),
                        new PointF(startX, startY + SpanPanel.spriteHeight - 2),
                    };
                    g.FillPolygon(new SolidBrush(Color.White), points);
                    g.DrawPolygon(new Pen(Color.Black), points);

                    // 画文字
                    StringFormat format = new StringFormat();
                    format.Alignment = StringAlignment.Far;
                    format.FormatFlags = StringFormatFlags.DirectionRightToLeft | StringFormatFlags.NoWrap | StringFormatFlags.DisplayFormatControl;
                    RectangleF layoutRectangle = new RectangleF();
                    layoutRectangle.Location = new PointF(startX, startY + 2 + 4);
                    layoutRectangle.Width = width;
                    layoutRectangle.Height = SpanPanel.spriteHeight;
                    g.DrawString(actions[0].note.Substring(actions[0].note.IndexOf("]") + 1) + "\u200E", new Font("宋体", 10), new SolidBrush(Color.Black), layoutRectangle, format);
                }
            }
        }

        public void isInside(PointF xy, SpanPanel spanPanel, Graphics g)
        {

        }
    }

    public class SpanPanel : Panel
    {
        List<SpriteBox> spriteBoxs = new List<SpriteBox>();

        bool isDebug = false;
        Color backGroundColor = Color.FromArgb(240, 240, 240);
        float __scale = 1.0f;                         // 1 to 10
        int __secondInPixel = 30;                        // 秒对应的像素值
        internal float curBeginSecond = 0.0f;            // 当前开始秒数
        internal float curSecond = 0.0f;                 // 当前刻度秒数
        int width = 1000;                        // 总宽
        int height = 800;                        // 总高

        public const int up = 30;                               // 上边 
        public const int left = 10;                           // 左边
        public const int spriteWidth = 160;                    // 精灵宽度
        public const int spriteHeight = 26;                    // 精灵高度
        public const int spriteHeightGap = 6;                  // 精灵高度缝隙

        // mouse
        Point lastDragPoint = new Point(-1, -1);
        Point curDragPoint = new Point(-1, -1);
        bool isInDrag = false;
        bool isDragCurSecond = false;           // 当前是否在拖拽当前刻度

        internal void updateActionBox(AEData aeData)
        {
            if (aeData == null) return;

            spriteBoxs.Clear();

            int curHeight = 0;
            foreach (AESprite aeSprite in aeData.aeSprites) {
                spriteBoxs.Add(new SpriteBox(aeSprite, curHeight));

                curHeight += aeSprite.__spanHeight;
            }
            this.Invalidate();
        }

        internal float spriteStartY
        {
            get { return up + 50; }
        }

        internal float getSpriteY(int spanHeight) {
            return spriteStartY + (SpanPanel.spriteHeight + SpanPanel.spriteHeightGap) * spanHeight + SpanPanel.spriteHeightGap;
        }

        internal float getPixelOfSecond(float second)
        {
            return startPixelOfTimeSpan + (second - curBeginSecond) * secondInPixel;
        }

        internal float secondInPixel
        {
            get { return __secondInPixel * __scale; }
        }

        internal float secondOfWidth
        {
            get { return (width - startPixelOfTimeSpan) / secondInPixel; }
        }

        internal float startPixelOfTimeSpan
        {
            get { return left + spriteWidth; }
        }

        internal float curSecondInPixel
        {
            get { return getPixelOfSecond(curSecond); }
        }

        internal SpanPanel(int _width, int _height)
        {
            this.width = _width;
            this.height = _height;

            this.Paint += SpanPanel_Paint;
            this.Size = new Size(width, height);

            this.MouseMove += SpanPanel_MouseMove;
            this.MouseWheel += SpanPanel_MouseWheel;
            this.MouseDown += SpanPanel_MouseDown;
            this.MouseUp += SpanPanel_MouseUp;

            SetStyle(ControlStyles.UserPaint |
               ControlStyles.AllPaintingInWmPaint |
               ControlStyles.OptimizedDoubleBuffer |
               ControlStyles.ResizeRedraw |
               ControlStyles.SupportsTransparentBackColor, true);
        }

        internal void resize(int _width, int _height)
        {
            this.width = _width;
            this.height = _height;
            this.Size = new Size(width, height);

            updateActionBox(MainFrame.instance.curEditAEData);
            this.Invalidate();
        }

        void SpanPanel_MouseDown(object sender, MouseEventArgs e)
        {
            lastDragPoint = e.Location;
            curDragPoint = e.Location;
            isInDrag = true;
            if (Math.Abs(curSecondInPixel - e.Location.X) < 5.0f)
            {
                isDragCurSecond = true;
            }
            this.Invalidate();
        }

        void SpanPanel_MouseMove(object sender, MouseEventArgs e)
        {
            lastDragPoint = curDragPoint;
            curDragPoint = e.Location;

            if (isInDrag) { 
                if (isDragCurSecond)
                {
                    curSecond += (curDragPoint.X - lastDragPoint.X) / secondInPixel;
                    if (curSecond < curBeginSecond) curSecond = curBeginSecond;
                    if (curSecond > secondOfWidth + curBeginSecond - 50 / secondInPixel) curSecond = secondOfWidth + curBeginSecond - 50 / secondInPixel;
                }
                else
                {
                    curBeginSecond -= (curDragPoint.X - lastDragPoint.X) / secondInPixel;
                    if (curBeginSecond < 0) curBeginSecond = 0;

                    updateActionBox(MainFrame.instance.curEditAEData);
                }
            }
            this.Invalidate();
        }

        void SpanPanel_MouseUp(object sender, MouseEventArgs e)
        {
            lastDragPoint = new Point(-1, -1);
            curDragPoint = new Point(-1, -1);
            isInDrag = false;
            isDragCurSecond = false;
        }

        internal void SpanPanel_MouseWheel(object sender, MouseEventArgs e)
        {
            if (e.Delta > 0)
            {
                __scale *= 1.2f;
                if (__scale > 20) __scale = 20;
            }
            else
            {
                __scale /= 1.2f;
                if (__scale <= 0.3f) __scale = 0.3f;
            }

            updateActionBox(MainFrame.instance.curEditAEData);
            this.Invalidate();
        }

        void SpanPanel_Paint(object sender, PaintEventArgs e)
        {
            BufferedGraphicsContext currentContext = BufferedGraphicsManager.Current;
            BufferedGraphics myBuffer = currentContext.Allocate(e.Graphics, e.ClipRectangle);
            Graphics g = myBuffer.Graphics;
            g.Clear(backGroundColor);
            g.SmoothingMode = SmoothingMode.HighQuality;
            g.PixelOffsetMode = PixelOffsetMode.HighSpeed;

            float start_i = (float)Math.Ceiling((double)(curBeginSecond * 10));       // 0.1 秒刻度
            float spanOffset = (start_i - curBeginSecond * 10) * secondInPixel / 10;
            int notDrawNumberCount = -1;
            for (float i = start_i; i < 1000; ++i)
            {
                float offset_i = i - start_i;
                if (startPixelOfTimeSpan + spanOffset + offset_i * secondInPixel / 10 > width) break;

                if (i % 10 == 0) {
                    g.DrawLine(new Pen(Color.Black, 1),
                        new PointF(startPixelOfTimeSpan + spanOffset + offset_i * secondInPixel / 10, up),
                        new PointF(startPixelOfTimeSpan + spanOffset + offset_i * secondInPixel / 10, up + 18));
                    ++notDrawNumberCount;
                    if (secondInPixel > 20.0f || notDrawNumberCount == 5)
                    {
                        notDrawNumberCount = 0;
                    }

                    if (notDrawNumberCount == 0)
                    {
                        g.DrawString("" + (int)(i / 10), new Font("宋体", 11), new SolidBrush(Color.Black),
                            startPixelOfTimeSpan + offset_i * secondInPixel / 10 - 5, up + 20);
                    }
                }
                else
                {
                    g.DrawLine(new Pen(Color.Black, 1),
                        new PointF(startPixelOfTimeSpan + spanOffset + offset_i * secondInPixel / 10, up),
                        new PointF(startPixelOfTimeSpan + spanOffset + offset_i * secondInPixel / 10, up + 10));
                }
            }
            g.DrawLine(new Pen(Color.Black, 1), new Point((int)startPixelOfTimeSpan - 13, up), new Point(width - 1, up));
            g.DrawLine(new Pen(Color.Black, 1), new Point((int)startPixelOfTimeSpan - 13, up), new Point((int)startPixelOfTimeSpan - 13, height - 1));

            // 画精灵
            foreach (SpriteBox spriteBox in spriteBoxs) {
                spriteBox.draw(this, g);
            }

            // 画刻度
            if (curSecond >= curBeginSecond)
            {
                String strCurSecond = "" + (int)(curSecond) + "." + (int)(curSecond * 100) % 100 + "秒";
                g.DrawString("" + strCurSecond, new Font("宋体", 11), new SolidBrush(Color.Green), curSecondInPixel - 7, up - 25);
                Point[] points = new Point[] { new Point((int)(curSecondInPixel) - 7, up - 8), 
                    new Point((int)(curSecondInPixel) + 7, up - 8),
                    new Point((int)(curSecondInPixel), up),
                };
                g.DrawPolygon(new Pen(Color.Green, isDragCurSecond ? 2 : 1), points);
                // 当前刻度
                for (int i = 0; i < height; i += 10)
                {
                    g.DrawLine(new Pen(Color.Green, isDragCurSecond ? 2 : 1),
                        new Point((int)(curSecondInPixel), up + i),
                        new Point((int)(curSecondInPixel), up + i + 2));

                    g.DrawLine(new Pen(Color.Green, isDragCurSecond ? 2 : 1),
                        new Point((int)(curSecondInPixel), up + i + 4),
                        new Point((int)(curSecondInPixel), up + i + 8));
                }
            }

            if (isDebug)
            {
                g.DrawLine(new Pen(Color.Red, 1), new Point(0, 0), new Point(width - 1, 0));
                g.DrawLine(new Pen(Color.Red, 1), new Point(0, 0), new Point(0, height - 1));
                g.DrawLine(new Pen(Color.Red, 1), new Point(width - 1, 0), new Point(width - 1, height - 1));
                g.DrawLine(new Pen(Color.Red, 1), new Point(0, height - 1), new Point(width - 1, height - 1));
            }

            myBuffer.Render();
            myBuffer.Dispose();//释放资源
        }


    }
}
