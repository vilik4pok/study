using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using FastColoredTextBoxNS;

namespace TextEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            menuStrip1.Renderer = new MenuLightRenderer();
            statusStrip1.Renderer = new MenuLightRenderer();
        }

        private void OpenFile()
        {
            using (OpenFileDialog openFileDialog = new OpenFileDialog())
            {
                openFileDialog.Filter = "txt files (*.txt)|*.txt|c files (*.c)|*.c|cs files (*.cs)|*.cs|h files (*.h)|*.h|cpp files (*.cpp)|*.cpp|All files (*.*)|*.*";
                openFileDialog.FilterIndex = 0;
                if (openFileDialog.ShowDialog() == DialogResult.OK)
                {
                    for (int i = 0; i < customTabControl1.TabCount; i++)
                    {
                        var tab = customTabControl1.TabPages[i] as CustomTabPage;
                        if (openFileDialog.FileName == tab.filePath)
                        {
                            customTabControl1.SelectedIndex = i;
                            return;
                        }

                    }
                    var tabpage = new CustomTabPage(statusStrip1, new ExFastColoredTextBox(), openFileDialog);
                    customTabControl1.Controls.Add(tabpage);
                    customTabControl1.SelectedIndex = customTabControl1.TabCount - 1;
                }
            }
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (customTabControl1.TabCount > 0)
            {
                var tab = customTabControl1.SelectedTab as CustomTabPage;
                var encoding = tab.encoding;
                toolStripStatusLabel1.Text = encoding.EncodingName;
                var tbox = tab.textBox as FastColoredTextBox;
                toolStripStatusLabel2.Text = $"Lines {tbox.LinesCount} Length {tbox.Text.Length}";
                tab.statusStrip.Items[1].Text = $"Line: {tbox.Selection.Start.iLine + 1} Col: {tbox.Selection.Start.iChar + 1} Length: {tbox.Selection.Length}";
                tbox.Select();
                tbox.Focus();
            }
            else
                toolStripStatusLabel1.Text = Encoding.Default.EncodingName;
        }

        private void toolStripMenuItem7_Click(object sender, EventArgs e)
        {
            var item = sender as ToolStripMenuItem;
            var tab = customTabControl1.SelectedTab as CustomTabPage;
            var encodings = new Encoding[] { Encoding.Unicode, Encoding.UTF8, Encoding.BigEndianUnicode, Encoding.ASCII };
            tab.Convert(encodings[Convert.ToInt32(item.Tag.ToString())]);
            toolStripStatusLabel1.Text = tab.encoding.EncodingName;
        }

        private void toolStripMenuItem12_Click(object sender, EventArgs e)
        {
            var tab = customTabControl1.SelectedTab as CustomTabPage;
            if (tab.autoSave)
                tab.timer.Stop();
            else
                tab.timer.Start();
            tab.autoSave = !tab.autoSave;

        }

        private void toolStripMenuItem12_Paint(object sender, PaintEventArgs e)
        {
            var item = sender as ToolStripMenuItem;
            var tab = customTabControl1.SelectedTab as CustomTabPage;
            if (tab != null)
            {
                if (tab.autoSave)
                    e.Graphics.FillEllipse(Brushes.Red, 10, 5, 10, 10);
                else
                    e.Graphics.FillEllipse(Brushes.Gray, 10, 5, 10, 10);
            }
        }


        private void toolStripMenuItem14_Click(object sender, EventArgs e)
        {
            var item = sender as ToolStripMenuItem;
            int num = Convert.ToInt32(item.Tag);
            var time = new int[] { 10000, 30000, 60000, 120000 };
            var tab = customTabControl1.SelectedTab as CustomTabPage;
            tab.selectedInterval = item.Tag.ToString();
            tab.timer.Interval = time[num];
        }

        private void toolStripMenuItem14_Paint(object sender, PaintEventArgs e)
        {
            var item = sender as ToolStripMenuItem;
            var tab = customTabControl1.SelectedTab as CustomTabPage;
            if (item.Tag.ToString() == tab.selectedInterval.ToString())
                e.Graphics.FillEllipse(Brushes.Red, 10, 5, 10, 10);

        }

        private void toolStripMenuItem22_Paint(object sender, PaintEventArgs e)
        {
            var item = sender as ToolStripMenuItem;
            var tab = customTabControl1.SelectedTab as CustomTabPage;
            if (tab != null)
            {
                if (item.Text == tab.Lang)
                    e.Graphics.FillEllipse(Brushes.Red, 10, 5, 10, 10);
            }
        }

        private void toolStripMenuItem22_Click(object sender, EventArgs e)
        {
            var item = sender as ToolStripMenuItem;
            (customTabControl1.SelectedTab as CustomTabPage).Lang = item.Text;
        }

        public static bool darkTheme = false;
        private void toolStripMenuItem25_Click(object sender, EventArgs e)
        {
            darkTheme = !darkTheme;
            if (darkTheme)
            {
                menuStrip1.Renderer = new MenuDarkRenderer();
                statusStrip1.Renderer = new MenuDarkRenderer();
                menuStrip1.BackColor = Color.FromArgb(48, 48, 48);
                statusStrip1.BackColor = Color.FromArgb(48, 48, 48);
                this.BackColor = Color.FromArgb(48, 48, 48);
                customTabControl1.DisplayStyleProvider.TextColor = Color.White;
            }    
            else
            {
                menuStrip1.Renderer = new MenuLightRenderer();
                statusStrip1.Renderer = new MenuLightRenderer();
                menuStrip1.BackColor = SystemColors.ControlLight;
                statusStrip1.BackColor = SystemColors.ControlLight;
                this.BackColor = SystemColors.ControlLight;
                customTabControl1.DisplayStyleProvider.TextColor = Color.Black;
            }
            foreach (CustomTabPage i in customTabControl1.TabPages)
            {
                i.DarkTheme = !i.DarkTheme;
            }
        }
       
        private void toolStripMenuItem1_DropDownOpening(object sender, EventArgs e)
        {
            var item = sender as ToolStripMenuItem;
            int i = 0;
            if (item.Text == "Файл")
                i = 2;
            if (customTabControl1.TabCount == 0)
            {

                for (; i < item.DropDownItems.Count; i++)
                    item.DropDownItems[i].Enabled = false;
            }
            else
            {
                for (; i < item.DropDownItems.Count; i++)
                    item.DropDownItems[i].Enabled = true;
            }
            menuStrip1.Invalidate();
        }
        
        private void toolStripMenuItem1_DropDownItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            var obj = sender as ToolStripMenuItem;
            obj.HideDropDown();
            var item = e.ClickedItem;
            switch(item.Text)
            {
                case "Создать":
                    var newTab = new CustomTabPage(statusStrip1);
                    customTabControl1.Controls.Add(newTab);
                    customTabControl1.SelectedTab = newTab;
                    break;
                case "Открыть":
                    OpenFile();
                    break;
            }
            if (customTabControl1.TabPages.Count == 0)
                return;
            var selectedTab = customTabControl1.SelectedTab as CustomTabPage;
            switch (item.Text)
            {
                case "Сохранить (Ctrl + S)":
                    selectedTab.Save();
                    break;
                case "Сохранить как (Ctrl + Shift + S)":
                    selectedTab.SaveAs();
                    break;
                case "Печать":
                    selectedTab.textBox.Print(new PrintDialogSettings() { ShowPrintPreviewDialog = true });
                    break;
                case "Найти (Ctrl + F)":
                    selectedTab.textBox.ShowFindDialog();
                    break;
                case "Заменить (Ctrl + H)":
                    selectedTab.textBox.ShowReplaceDialog();
                    break;
            }
        }
    }

    public class CustomTabPage : TabPage
    {
        public string filePath = "";
        public bool saved = false;
        public bool autoSave = false;
        public ExFastColoredTextBox textBox;
        public Encoding encoding = Encoding.Default;
        public StatusStrip statusStrip;
        private string lang = "Не выбран";
        public string Lang
        {
            get => lang;
            set
            {
                lang = value;
                textBox.ClearStylesBuffer();
                textBox.Range.ClearStyle(StyleIndex.All);
                textBox.AutoIndentNeeded -= AutoIndentNeeded;
                if(lang != "Не выбран")
                    textBox.OnTextChanged();
                textBox.OnSyntaxHighlight(new TextChangedEventArgs(textBox.Range));
            }
        }
        public string selectedInterval = "3";
        public MyScrollBar hscrollBar;
        public MyScrollBar vscrollBar;
        public CustomTabPage(StatusStrip status, ExFastColoredTextBox tBox = null, OpenFileDialog fileDialog = null) : base()
        {
            statusStrip = status;
            Padding = Padding.Empty;
            Margin = Padding.Empty;
            if (textBox != null)
                textBox = tBox;
            else
                textBox = new ExFastColoredTextBox();

            ImageIndex = 1;
            if (fileDialog != null)
            {
                saved = true;
                ImageIndex = 0;
                Text = fileDialog.SafeFileName;
                filePath = fileDialog.FileName;
                var detenc = UtfUnknown.CharsetDetector.DetectFromFile(filePath).Detected;
                if (detenc != null)
                    encoding = detenc.Encoding;
                textBox.Text = File.ReadAllText(filePath, encoding);
                setLanguageFromFileName(fileDialog.SafeFileName);
            }
            else
                Text = "Новый";

            
            timer = new Timer();
            timer.Tick += timer_Tick;

            hscrollBar = new MyScrollBar();
            hscrollBar.Orientation = ScrollOrientation.HorizontalScroll;
            hscrollBar.Dock = DockStyle.Bottom;
            hscrollBar.Height = 20;
            hscrollBar.Padding = Padding.Empty;
            hscrollBar.Margin = Padding.Empty;
            hscrollBar.BorderColor = Color.Transparent;
            hscrollBar.Scroll += scrollBar_Scroll;

            vscrollBar = new MyScrollBar();
            vscrollBar.Orientation = ScrollOrientation.VerticalScroll;
            vscrollBar.Dock = DockStyle.Right;
            vscrollBar.Width = 20;
            vscrollBar.Padding = Padding.Empty;
            vscrollBar.Margin = Padding.Empty;
            vscrollBar.BorderColor = Color.Transparent;
            vscrollBar.Scroll += scrollBar_Scroll;

            textBox.TextChanged += textBox_TextChanged;
            textBox.KeyDown += textBox_KeyDown;
            textBox.SelectionChanged += textBox_SelectionChanged;
            textBox.ScrollbarsUpdated += textBox_ScrollbarsUpdated;
            textBox.Language = Language.Custom;
            textBox.Dock = DockStyle.Fill;
            textBox.ShowScrollBars = false;

            Controls.Add(textBox);
            Controls.Add(hscrollBar);
            Controls.Add(vscrollBar);

            DarkTheme = Form1.darkTheme;

        }
        private void AdjustScrollbars()
        {
            var textboxrect = textBox.TextAreaRect;
            var thumbSize1 = textBox.ClientSize.Height > textboxrect.Height ? 0 : textBox.ClientSize.Height * textBox.ClientSize.Height / textboxrect.Height;
            var thumbSize2 = textBox.ClientSize.Width > textboxrect.Width ? 0 : textBox.ClientSize.Width * textBox.ClientSize.Width / textboxrect.Width;
            AdjustScrollbar(vscrollBar, textBox.VerticalScroll.Maximum, textBox.VerticalScroll.Value, thumbSize1);
            AdjustScrollbar(hscrollBar, textBox.HorizontalScroll.Maximum, textBox.HorizontalScroll.Value, thumbSize2);
        }

        private void AdjustScrollbar(MyScrollBar scrollBar, int max, int value, int thumbsize)
        {
            scrollBar.Maximum = max;
            scrollBar.Visible = max > 0;
            scrollBar.ThumbSize = thumbsize > 20 ? thumbsize : 20;
            scrollBar.Value = Math.Min(scrollBar.Maximum, value);
        }

        private void textBox_ScrollbarsUpdated(object sender, EventArgs e)
        {
            AdjustScrollbars();
        }

        private void scrollBar_Scroll(object sender, ScrollEventArgs e)
        {
            textBox.OnScroll(e, e.Type != ScrollEventType.ThumbTrack && e.Type != ScrollEventType.ThumbPosition);
        }
        private void textBox_KeyDown(object sender, KeyEventArgs e)
        {
            var tab = (sender as Control).Parent as CustomTabPage;
            if (e.Control)
            {
                if (e.KeyCode == Keys.S)
                {
                    if (e.Shift)
                        tab.SaveAs();
                    else
                        tab.Save();
                }
            }
        }

        private void textBox_SelectionChanged(object sender, EventArgs e)
        {
            var tbox = sender as FastColoredTextBox;
            var tab = tbox.Parent as CustomTabPage;
            tab.statusStrip.Items[1].Text = $"Line: {tbox.Selection.Start.iLine + 1} Col: {tbox.Selection.Start.iChar + 1} Length: {tbox.Selection.Length}";

        }
        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            var tbox = sender as FastColoredTextBox;
            var tab = tbox.Parent as CustomTabPage;
            if (tab.saved)
            {
                tab.saved = false;
                tab.ImageIndex = 1;
                tab.Parent.Invalidate();
            }
            tab.statusStrip.Items[0].Text = $"Lines: {tbox.LinesCount} Length: {tbox.Text.Length}";

            switch (Lang)
            {
                case "Не выбран":
                default:

                    CustomSyntaxHighlight(e);
                    tbox.AutoIndentNeeded += AutoIndentNeeded;
                    break;
            }
        }
        TextStyle BlueStyle = new TextStyle(new SolidBrush(Color.FromArgb(62, 138, 184)), null, FontStyle.Bold);
        TextStyle BoldStyle1 = new TextStyle(null, null, FontStyle.Bold | FontStyle.Underline);
        TextStyle BoldStyle2 = new TextStyle(Brushes.White, null, FontStyle.Bold | FontStyle.Underline);
        TextStyle GrayStyle = new TextStyle(Brushes.Gray, null, FontStyle.Regular);
        TextStyle MagentaStyle = new TextStyle(Brushes.Magenta, null, FontStyle.Regular);
        TextStyle GreenStyle = new TextStyle(Brushes.Green, null, FontStyle.Italic);
        TextStyle BrownStyle = new TextStyle(Brushes.Brown, null, FontStyle.Italic);
        public static TextStyle WhiteStyle = new TextStyle(Brushes.White, null, FontStyle.Regular);
        public static TextStyle BlackStyle = new TextStyle(Brushes.Black, null, FontStyle.Regular);
        private void CustomSyntaxHighlight(TextChangedEventArgs e)
        {

            textBox.LeftBracket = '(';
            textBox.RightBracket = ')';
            textBox.LeftBracket2 = '\x0';
            textBox.RightBracket2 = '\x0';
            TextStyle Bold = Form1.darkTheme ? BoldStyle2 : BoldStyle1;
            //clear style of changed range
            e.ChangedRange.ClearStyle(BlueStyle, Bold, GrayStyle, MagentaStyle, GreenStyle, BrownStyle);

            e.ChangedRange.SetStyle(BrownStyle, @"""""|@""""|''|@"".*?""|(?<!@)(?<range>"".*?[^\\]"")|'.*?[^\\]'");
            //comment highlighting
            e.ChangedRange.SetStyle(GreenStyle, @"//.*$", RegexOptions.Multiline);
            e.ChangedRange.SetStyle(GreenStyle, @"(/\*.*?\*/)|(/\*.*)", RegexOptions.Singleline);
            e.ChangedRange.SetStyle(GreenStyle, @"(/\*.*?\*/)|(.*\*/)", RegexOptions.Singleline | RegexOptions.RightToLeft);
            //number highlighting
            e.ChangedRange.SetStyle(MagentaStyle, @"\b\d+[\.]?\d*([eE]\-?\d+)?[lLdDfF]?\b|\b0x[a-fA-F\d]+\b");
            
            
            if (Lang == "C")
            {
                e.ChangedRange.SetStyle(Bold, @"\b(struct|enum)\s+(?<range>\w+?)\b");
                e.ChangedRange.SetStyle(BlueStyle, @"\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)\b");
            }
            if(Lang == "C++")
            {
                e.ChangedRange.SetStyle(Bold, @"\b(class|struct|enum)\s+(?<range>\w+?)\b");
                e.ChangedRange.SetStyle(BlueStyle, @"\b(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while|asm|bool|catch|class|const_cast|delete|dynamic_cast|explicit|export|false|friend|inline|mutable|namespace|new|operator|private|protected|public|reinterpret_cast|static_cast|template|this|throw|true|try|typeid|typename|using|virtual|wchar_t)\b");
            }
            if(Lang == "C#")
            {
                e.ChangedRange.SetStyle(Bold, @"\b(class|struct|enum|interface)\s+(?<range>\w+?)\b");
                e.ChangedRange.SetStyle(BlueStyle, @"\b(abstract|as|base|bool|break|byte|case|catch|char|checked|class|const|continue|decimal|default|delegate|do|double|else|enum|event|explicit|extern|false|finally|fixed|float|for|foreach|goto|if|implicit|in|int|interface|internal|is|lock|long|namespace|new|null|object|operator|out|override|params|private|protected|public|readonly|ref|return|sbyte|sealed|short|sizeof|stackalloc|static|string|struct|switch|this|throw|true|try|typeof|uint|ulong|unchecked|unsafe|ushort|using|virtual|void|volatile|while|add|alias|ascending|descending|dynamic|from|get|global|group|into|join|let|orderby|partial|remove|select|set|value|var|where|yield)\b|#region\b|#endregion\b");
                e.ChangedRange.SetFoldingMarkers(@"#region\b", @"#endregion\b");//allow to collapse #region blocks
            }

            ////clear folding markers
            e.ChangedRange.ClearFoldingMarkers();

            ////set folding markers
            e.ChangedRange.SetFoldingMarkers("{", "}");//allow to collapse brackets block
            
            e.ChangedRange.SetFoldingMarkers(@"/\*", @"\*/");//allow to collapse comment block
        }
        private void AutoIndentNeeded(object sender, AutoIndentEventArgs args)
        {
            if (Regex.IsMatch(args.LineText, @"^[^""']*\{.*\}[^""']*$"))
                return;
            if (Regex.IsMatch(args.LineText, @"^[^""']*\{"))
            {
                args.ShiftNextLines = args.TabLength;
                return;
            }
            if (Regex.IsMatch(args.LineText, @"}[^""']*$"))
            {
                args.Shift = -args.TabLength;
                args.ShiftNextLines = -args.TabLength;
                return;
            }
            if (Regex.IsMatch(args.LineText, @"^\s*\w+\s*:\s*($|//)") &&
                !Regex.IsMatch(args.LineText, @"^\s*default\s*:"))
            {
                args.Shift = -args.TabLength;
                return;
            }
            if (Regex.IsMatch(args.LineText, @"^\s*(case|default)\b.*:\s*($|//)"))
            {
                args.Shift = -args.TabLength / 2;
                return;
            }
            if (Regex.IsMatch(args.PrevLineText, @"^\s*(if|for|foreach|while|[\}\s]*else)\b[^{]*$"))
                if (!Regex.IsMatch(args.PrevLineText, @"(;\s*$)|(;\s*//)"))//operator is unclosed
                {
                    args.Shift = args.TabLength;
                    return;
                }
        }
        public Timer timer;
        void timer_Tick(object sender, EventArgs e)
        {
            if (!saved)
            {
                timer.Stop();
                Save();
                timer.Start();
            }
        }
        public void Save()
        {
            if (filePath == "")
            {
                SaveAs();
                return;
            }
            else
            {
                using (var writer = new StreamWriter(filePath, false, encoding))
                {
                    writer.Write(textBox.Text);
                }
            }
            saved = true;
            this.ImageIndex = 0;
            this.Parent.Invalidate();
        }
        public void SaveAs()
        {
            using var saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "txt files (*.txt)|*.txt|c files (*.c)|*.c|cs files (*.cs)|*.cs|h files (*.h)|*.h|cpp files (*.cpp)|*.cpp|All files (*.*)|*.*";
            if (saveFileDialog.ShowDialog() == DialogResult.Cancel)
            {
                saved = false;
                return;
            }
            filePath = saveFileDialog.FileName;
            var filename = filePath.Substring(filePath.LastIndexOf("\\") + 1);
            setLanguageFromFileName(filename);
            Text = filename;
            Save();
        }
        private void setLanguageFromFileName(string filename)
        {
            var match = Regex.Match(filename, "\\.(cs|c|cpp|h)$");
            textBox.Language = Language.Custom;
            if (match.Success)
            {
                switch (match.Value)
                {
                    case ".cs": Lang = "C#"; break;
                    case ".c": Lang = "C"; break;
                    case ".h": Lang = "C"; break;
                    case ".cpp": Lang = "C++"; break;
                    default: Lang = "Не выбран"; break;
                }
            }
        }
        public void Clear()
        {
            textBox.Dispose();
            textBox = null;
            this.Dispose();
        }
        public void Convert(Encoding choosenEncoding)
        {
            var currentEncoding = encoding;
            var bytes = currentEncoding.GetBytes(textBox.Text);
            byte[] choosenEncodingBytes = Encoding.Convert(currentEncoding, choosenEncoding, bytes);

            char[] choosenChars = new char[choosenEncoding.GetCharCount(choosenEncodingBytes, 0, choosenEncodingBytes.Length)];
            choosenEncoding.GetChars(choosenEncodingBytes, 0, choosenEncodingBytes.Length, choosenChars, 0);

            string choosenString = new string(choosenChars);
            textBox.SelectAll();
            textBox.SelectedText = choosenString;
            encoding = choosenEncoding;
            Save();

            textBox.ClearUndo();
        }

        private bool _darkTheme;
        public bool DarkTheme
        {
            get => _darkTheme;
            set
            {
                _darkTheme = value;
                if(_darkTheme)
                {
                    textBox.BackColor = Color.FromArgb(48, 48, 48);
                    textBox.DefaultStyle = WhiteStyle;
                    textBox.CaretColor = Color.FromArgb(48, 48, 48);
                    textBox.IndentBackColor = Color.FromArgb(48, 48, 48);
                    Lang = Lang;
                    hscrollBar.BackColor = Color.FromArgb(64, 60, 68); 
                    hscrollBar.ThumbColor = Color.FromArgb(112, 108, 108); 
                    vscrollBar.BackColor = Color.FromArgb(64, 60, 68); 
                    vscrollBar.ThumbColor = Color.FromArgb(112, 108, 108);
                }
                else
                {
                    textBox.BackColor = Color.White;
                    textBox.DefaultStyle = BlackStyle;
                    textBox.CaretColor = Color.White;
                    textBox.IndentBackColor = Color.White;
                    Lang = Lang;
                    hscrollBar.BackColor = Control.DefaultBackColor;
                    hscrollBar.ThumbColor = Color.Gray;
                    vscrollBar.BackColor = Control.DefaultBackColor;
                    vscrollBar.ThumbColor = Color.Gray;
                }

            }
        }



    }
    public class MyScrollBar : Control
    {
        private int @value;

        public int Value
        {
            get { return value; }
            set
            {
                if (this.value == value)
                    return;
                this.value = value;
                Invalidate();
                OnScroll();
            }
        }

        private int maximum = 100;
        public int Maximum
        {
            get { return maximum; }
            set { maximum = value; Invalidate(); }
        }

        private int thumbSize = 10;
        public int ThumbSize
        {
            get { return thumbSize; }
            set { thumbSize = value; Invalidate(); }
        }

        private Color thumbColor = Color.Gray;
        public Color ThumbColor
        {
            get { return thumbColor; }
            set { thumbColor = value; Invalidate(); }
        }

        private Color borderColor = Color.Silver;
        public Color BorderColor
        {
            get { return borderColor; }
            set { borderColor = value; Invalidate(); }
        }

        private ScrollOrientation orientation;
        public ScrollOrientation Orientation
        {
            get { return orientation; }
            set { orientation = value; Invalidate(); }
        }

        public event ScrollEventHandler Scroll;

        public MyScrollBar()
        {
            SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.OptimizedDoubleBuffer | ControlStyles.UserPaint, true);
        }

        protected override void OnMouseDown(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
                MouseScroll(e);
            base.OnMouseDown(e);
        }

        protected override void OnMouseMove(MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
                MouseScroll(e);
            base.OnMouseMove(e);
        }

        private void MouseScroll(MouseEventArgs e)
        {
            int v = 0;
            switch (Orientation)
            {
                case ScrollOrientation.VerticalScroll: v = Maximum * (e.Y - thumbSize / 2) / (Height - thumbSize); break;
                case ScrollOrientation.HorizontalScroll: v = Maximum * (e.X - thumbSize / 2) / (Width - thumbSize); break;
            }
            Value = Math.Max(0, Math.Min(Maximum, v));
        }

        public virtual void OnScroll(ScrollEventType type = ScrollEventType.ThumbPosition)
        {
            if (Scroll != null)
                Scroll(this, new ScrollEventArgs(type, Value, Orientation));
        }

        protected override void OnPaint(PaintEventArgs e)
        {
            if (Maximum <= 0)
                return;

            Rectangle thumbRect = Rectangle.Empty;
            switch (Orientation)
            {
                case ScrollOrientation.HorizontalScroll:
                    thumbRect = new Rectangle(value * (Width - thumbSize) / Maximum, 2, thumbSize, Height - 4);
                    break;
                case ScrollOrientation.VerticalScroll:
                    thumbRect = new Rectangle(2, value * (Height - thumbSize) / Maximum, Width - 4, thumbSize);
                    break;
            }

            using (var brush = new SolidBrush(thumbColor))
                e.Graphics.FillRectangle(brush, thumbRect);

            using (var pen = new Pen(borderColor))
                e.Graphics.DrawRectangle(pen, new Rectangle(0, 0, Width - 1, Height - 1));
        }
    }

    public class ExFastColoredTextBox : FastColoredTextBox
    {
        protected override void OnSizeChanged(EventArgs e)
        {
            // Hack to set needRecalc member to true, otherwise AutoScrollMinSize isn't set
            LineNumberStartValue = LineNumberStartValue;
            base.OnSizeChanged(e);
        }
    }
    class MenuDarkRenderer : ToolStripProfessionalRenderer
    {
        public MenuDarkRenderer() : base(new DarkColorTable()) { }
        protected override void OnRenderArrow(ToolStripArrowRenderEventArgs e)
        {
            e.ArrowColor = Color.White;
            base.OnRenderArrow(e);
        }
        protected override void OnRenderItemText(ToolStripItemTextRenderEventArgs e)
        {
            e.TextColor = Color.White;
            base.OnRenderItemText(e);
        }
    }
    class MenuLightRenderer : ToolStripProfessionalRenderer
    {
        public MenuLightRenderer() : base(new ProfessionalColorTable()) { }
        protected override void OnRenderArrow(ToolStripArrowRenderEventArgs e)
        {
            e.ArrowColor = Color.Black;
            base.OnRenderArrow(e);
        }
        protected override void OnRenderItemText(ToolStripItemTextRenderEventArgs e)
        {
            e.TextColor = Color.Black;
            base.OnRenderItemText(e);
        }
    }

    class DarkColorTable : ProfessionalColorTable
    {
        //граница выпадающего списка
        public override Color MenuBorder
        {
            get { return Color.FromArgb(64, 60, 68); }
        }
        //граница любого
        public override Color MenuItemBorder
        {
            get { return Color.FromArgb(48, 48, 48); }
        }
        //при наведении на активный
        public override Color MenuItemSelectedGradientBegin
        {
            get { return Color.Gray; }
        }
        public override Color MenuItemSelectedGradientEnd
        {
            get { return Color.Gray; }
        }
        //цвет выпадающих эдементов
        public override Color ToolStripDropDownBackground
        {
            get { return Color.FromArgb(48, 48, 48); }
        }
        //левая часть
        public override Color ImageMarginGradientBegin
        {
            get { return Color.FromArgb(48, 48, 48); }
        }
        public override Color ImageMarginGradientMiddle
        {
            get { return Color.FromArgb(48, 48, 48); }
        }

        public override Color ImageMarginGradientEnd
        {
            get { return Color.FromArgb(48, 48, 48); }
        }
        //когда нажал
        public override Color MenuItemPressedGradientBegin
        {
            get { return Color.FromArgb(48, 48, 48); }
        }
        public override Color MenuItemPressedGradientEnd
        {
            get { return Color.FromArgb(48, 48, 48); }
        }
    }



}

