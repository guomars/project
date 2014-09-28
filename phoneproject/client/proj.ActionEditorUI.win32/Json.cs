using System;
using System.Collections.Generic;
using System.Text;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.IO;
using System.Windows.Forms;

namespace ActionEditorUI
{
    class UIWidget
    {
        public String name;
        public String className;

        public UIWidget(String _name, String _className)
        {
            this.name = _name;
            this.className = _className;
        }
    }

    class UITree
    {
        internal Dictionary<String, UIWidget> widgets = new Dictionary<String, UIWidget>();

        public UIWidget findByName(String name)
        {
            if (!widgets.ContainsKey(name)) return null;
            return widgets[name];
        }

        public UITree(String jsonFileName)
        {
            String jsonFilePath = ActionParamTemplate.FindResPath(jsonFileName);
            if (jsonFilePath == null) throw new Exception("jsonFile not find in Res Path: " + jsonFileName);

            StreamReader sr = new StreamReader(jsonFilePath);
            String tmpLine = null;
            String line2 = "";
            String line1 = "";
            while ((tmpLine = sr.ReadLine()) != null) {
                line1 = line2;
                line2 = tmpLine;

                if (!line1.Contains("classname") || !line2.Contains("name") || line1.Contains("null") || line2.Contains("null"))
                {
                    continue;
                }

                String className = "";
                String name = "";
                {
                    Match match = Regex.Match(line1.Trim(), "\"classname\": \"(.*)\".*");
                    if (match == null) throw new Exception("Illegal classname Jason: line1=" + line1);
                    className = match.Groups[1].ToString();
                }
                {
                    Match match = Regex.Match(line2.Trim(), "\"name\": \"(.*)\".*");
                    if (match == null) throw new Exception("Illegal name Jason: line1=" + line1);
                    name = match.Groups[1].ToString();
                }

                Console.WriteLine("Widget: name=" + name + ",className=" + className);
                if (!widgets.ContainsKey(name))
                {
                    widgets.Add(name, new UIWidget(name, className));
                }
                else
                {
                    MessageBox.Show("jsonFileName:" + jsonFileName + " 里面有重复的控件名：" + name);
                }
            }
        }
    }
}
