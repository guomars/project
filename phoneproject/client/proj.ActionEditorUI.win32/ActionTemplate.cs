using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.Text.RegularExpressions;
using System.IO;
using System.Windows.Forms;
using System.Drawing;
using System.Diagnostics;

namespace ActionEditorUI
{

    enum EActionType
    {
        CCActionInstant,
        CCActionInterval,
        CCGridAction,
    }

    enum EParamType
    {
        PARAM_TYPE_INT,
        PARAM_TYPE_FLOAT,
        PARAM_TYPE_BEZIER,
        PARAM_TYPE_POINT,
        PARAM_TYPE_STR,
        PARAM_TYPE_STRS,
    }

    enum EBlendFactor
    {
        GL_ZERO,
        GL_ONE,
        GL_SRC_COLOR,   
        GL_ONE_MINUS_SRC_COLOR,
        GL_SRC_ALPHA,          
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,          
        GL_ONE_MINUS_DST_ALPHA,

        GL_DST_COLOR,           
        GL_ONE_MINUS_DST_COLOR, 
        GL_SRC_ALPHA_SATURATE,
    }

    enum ESysParticleType
    {
        CCParticleFire,
        CCParticleSun,
        CCParticleFireworks,
        CCParticleGalaxy,
        CCParticleFlower,
        CCParticleMeteor,
        CCParticleSpiral,
        CCParticleExplosion,
        CCParticleSmoke,
        CCParticleSnow,
        CCParticleRain,
    }

    class CCPoint
    {
        internal enum EPointParam { NULL, P1, P2, P3, P4, P5, }

        public EPointParam eParam = EPointParam.NULL;
        public float x = 0f;
        public float y = 0f;

        public CCPoint() { }

        public CCPoint(String str)
        {
            if (str.Length == 2) {
                switch (str) {
                    case "P1": eParam = EPointParam.P1; break;
                    case "P2": eParam = EPointParam.P2; break;
                    case "P3": eParam = EPointParam.P3; break;
                    case "P4": eParam = EPointParam.P4; break;
                    case "P5": eParam = EPointParam.P5; break;
                    default: throw new Exception("Illegal CCPoint Format: " + str);
                }
            } else {
                Match match = Regex.Match(str, "\\(([\\d\\.+-]*),([\\d\\.+-]*)\\)");
                if (match == null) throw new Exception("Illegal CCPoint Format: " + str);

                x = float.Parse(match.Groups[1].ToString());
                y = float.Parse(match.Groups[2].ToString());
            }
        }

        public CCPoint(CCPoint other)
        {
            this.x = other.x;
            this.y = other.y;
        }

        public CCPoint(float _x, float _y)
        {
            this.x = _x;
            this.y = _y;
        }

        override public String ToString()
        {
            StringBuilder sb = new StringBuilder();
            if (eParam != EPointParam.NULL)
            {
                switch (eParam)
                {
                    case EPointParam.P1: sb.Append("P1"); break;
                    case EPointParam.P2: sb.Append("P2"); break;
                    case EPointParam.P3: sb.Append("P3"); break;
                    case EPointParam.P4: sb.Append("P4"); break;
                    case EPointParam.P5: sb.Append("P5"); break;
                    default: sb.Append("(").Append(x).Append(",").Append(y).Append(")"); break; // eat error.
                }
            }
            else
            {
                sb.Append("(").Append(x).Append(",").Append(y).Append(")");
            }
            return sb.ToString();
        }
    }

    class Color3
    {
        public byte r;
        public byte g;
        public byte b;

        public Color3() { r = 255; g = 255; b = 255; }

        public Color3(String str)
        {
            Match match = Regex.Match(str, "\\(([\\d]*),([\\d]*),([\\d]*)\\)");
            if (match == null) throw new Exception("Illegal CCPoint Format: " + str);

            r = byte.Parse(match.Groups[1].ToString());
            g = byte.Parse(match.Groups[2].ToString());
            b = byte.Parse(match.Groups[2].ToString());
        }

        public Color3(Color3 other)
        {
            this.r = other.r;
            this.g = other.g;
            this.b = other.b;
        }

        override public String ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("(").Append(r).Append(",").Append(g).Append(",").Append(b).Append(")");
            return sb.ToString();
        }
    }

    class Bezier
    {
        public CCPoint endPoint;
        public CCPoint ctrlPoint1;
        public CCPoint ctrlPoint2;

        public Bezier()
        {
            endPoint = new CCPoint();
            ctrlPoint1 = new CCPoint();
            ctrlPoint2 = new CCPoint();
        }

        public Bezier(String str)
        {
            Match match = Regex.Match(str, "\\((\\([\\d\\.+-]*,[\\d\\.+-]*\\)),(\\([\\d\\.+-]*,[\\d\\.+-]*\\)),(\\([\\d\\.+-]*,[\\d\\.+-]*\\))\\)");
            if (match == null) throw new Exception("Illegal CCPoint Format: " + str);

            endPoint = new CCPoint(match.Groups[1].ToString());
            ctrlPoint1 = new CCPoint(match.Groups[2].ToString());
            ctrlPoint2 = new CCPoint(match.Groups[3].ToString());
        }

        public Bezier(Bezier other)
        {
            this.endPoint = new CCPoint(other.endPoint);
            this.ctrlPoint1 = new CCPoint(other.ctrlPoint1);
            this.ctrlPoint2 = new CCPoint(other.ctrlPoint2);
        }

        override public String ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("(").Append(endPoint.ToString()).Append(",").Append(ctrlPoint1.ToString()).Append(",").Append(ctrlPoint2.ToString()).Append(")");
            return sb.ToString();
        }
    }

    class ActionParamTemplate
    {
        public static String[] resPaths = new String[] { "./common/", "./ipad/", "./iphone4/", "./iphone5/" };

        public static String FindResPath(String path)
        {
            String fileName = Process.GetCurrentProcess().MainModule.FileName;
            String moduleName = Process.GetCurrentProcess().MainModule.ModuleName;
            String moduleDir = Regex.Replace(fileName, moduleName, "");
            foreach (String yyy in resPaths)
            {
                String testPath = (moduleDir + yyy + path).ToString().Replace('/', '\\');
                Console.WriteLine(testPath);
                try { 
                    if (File.OpenRead(testPath) != null) 
                        return testPath;
                } catch (Exception) {
                    //MessageBox.Show(e.ToString() + " " + testPath);
                }
            }
            return null;
        }

        public String name;
        public EParamType type;
        public String note;
        public Dictionary<String, String> strValidSet = new Dictionary<String, String>();

        // dynamic
        public int var_int = 0;
        public float var_float = 0f;
        public CCPoint var_point = new CCPoint();
        public String var_str = "";
        public List<String> var_strs = new List<String>();
        public Bezier var_bezier = new Bezier();

        public ActionParamTemplate(XmlElement e)
        {
            this.name = e.GetAttribute("name");
            this.type = ActionTemplate.parseParamType(e.GetAttribute("type"));
            this.note = e.GetAttribute("note");

            if (e.HasAttribute("default")) {
                setDynamic(e.GetAttribute("default"));
            }
            if (e.HasAttribute("set"))
            {
                foreach (String split in Regex.Split(e.GetAttribute("set"), ";"))
                {
                    strValidSet.Add(Regex.Split(split, ",")[0], Regex.Split(split, ",")[1]);
                }
            }
        }

        public ActionParamTemplate(ActionParamTemplate other)
        {
            this.name = other.name;
            this.type = other.type;
            this.note = other.note;

            // dynamic, for default reason
            this.var_int = other.var_int;
            this.var_float = other.var_float;
            this.var_str = other.var_str;
            if (other.var_point != null)
                this.var_point = new CCPoint(other.var_point);
            if (other.var_bezier != null)
                this.var_bezier = new Bezier(other.var_bezier);
        }

        public void setDynamic(String str)
        {
            this.var_strs.Clear();
            if (type != EParamType.PARAM_TYPE_STR && type != EParamType.PARAM_TYPE_STRS && str == "") return;
            switch (type)
            {
                case EParamType.PARAM_TYPE_INT: this.var_int = System.Int32.Parse(str); break;
                case EParamType.PARAM_TYPE_FLOAT: this.var_float = float.Parse(str); break;
                case EParamType.PARAM_TYPE_POINT: this.var_point = new CCPoint(str); break;
                case EParamType.PARAM_TYPE_BEZIER: this.var_bezier = new Bezier(str); break;
                case EParamType.PARAM_TYPE_STR: this.var_str = str; break;
                case EParamType.PARAM_TYPE_STRS:
                    foreach (String split in Regex.Split(str, ","))
                    {
                        String trimed = split.Trim().Replace('\\', '/');
                        if (trimed.Length > 0)
                        {
                            this.var_strs.Add(trimed);
                        }
                       
                    }
                    break;
                default:
                    throw new Exception("Parse Param Format Error, type = " + type + ", str = " + str);
            }
            this.var_str = this.var_str.Replace('\\', '/');
        }

        public String toDynamicStr()
        {
            StringBuilder sb = new StringBuilder();
            switch (type)
            {
                case EParamType.PARAM_TYPE_INT: sb.Append(var_int); break;
                case EParamType.PARAM_TYPE_FLOAT: sb.Append(var_float); break;
                case EParamType.PARAM_TYPE_POINT: sb.Append(var_point.ToString()); break;
                case EParamType.PARAM_TYPE_BEZIER: sb.Append(var_bezier.ToString()); break;
                case EParamType.PARAM_TYPE_STR:
                    sb.Append(var_str.ToString()); break;
                case EParamType.PARAM_TYPE_STRS:
                    for (int i = 0; i < var_strs.Count; ++i)
                    {
                        sb.Append(var_strs[i]);
                        if (i != var_strs.Count)
                        {
                            sb.Append(",");
                        }
                    }
                    break;
                default:
                    throw new Exception("Parse Param Format Error, type = " + type);
            }
            return sb.ToString();
        }
    }

    class ActionTemplate
    {
        public static EActionType parseActionType(String str)
        {
            switch (str) {
                case "CCActionInstant": return EActionType.CCActionInstant;
                case "CCActionInterval": return EActionType.CCActionInterval;
                case "CCGridAction": return EActionType.CCGridAction;
                default: throw new Exception("Unkowned EActionType: " + str);
            }
        }

        public static EParamType parseParamType(String str)
        {
            switch (str)
            {
                case "int": return EParamType.PARAM_TYPE_INT;
                case "float": return EParamType.PARAM_TYPE_FLOAT;
                case "CCPoint": return EParamType.PARAM_TYPE_POINT;
                case "Bezier": return EParamType.PARAM_TYPE_BEZIER;
                case "str": return EParamType.PARAM_TYPE_STR;
                case "strs": return EParamType.PARAM_TYPE_STRS;
                default: throw new Exception("Unkowned EParamType: " + str);
            }
        }

        public float __duration = 0.0f;
        public int __spanStart = 0;                 // 时间轴的起始高度
        public int __spanHeight = 0;                // 时间轴的层次高度
        public float __passed = 0.0f;               // 该动作的延迟时间

        public String name;
        public EActionType eActionType;
        public String note;
        public int actionList;
        public int targetTag = 0;
        public bool isUi = false;
        public bool isGridEffect = false;
        public bool onlyUi = false;
        public bool onlyFight = false;
        public List<ActionParamTemplate> actionParams = new List<ActionParamTemplate>();

        public List<ActionTemplate> subActionList = new List<ActionTemplate>();

        private TreeNode _treeNode = new TreeNode();

        public ActionParamTemplate getParamByName(String name)
        {
            foreach (ActionParamTemplate xxx in actionParams) {
                if (xxx.name == name) return xxx;
            }
            return null;
        }

        public void recursiveUpdateTreeNode()
        {
            foreach (ActionTemplate xxx in subActionList)
            {
                xxx.recursiveUpdateTreeNode();
            }
            updateActionTreeNode();
        }

        public int calculateSpanHeight(int curStart)
        {
            __spanStart = curStart;
            __spanHeight = 0;
            if (name == "CCSequence")
            {
                foreach (ActionTemplate xxx in subActionList) {
                    if (xxx.targetTag == 0)
                        __spanHeight = Math.Max(xxx.calculateSpanHeight(curStart), __spanHeight);
                }
            }
            else if (name == "CCSpawn")
            {
                int addedHeight = 0;
                foreach (ActionTemplate xxx in subActionList)
                {
                    if (xxx.targetTag == 0)
                    {
                        addedHeight += xxx.calculateSpanHeight(curStart + addedHeight);
                    }
                }
                __spanHeight += addedHeight;
            }
            else if (subActionList.Count == 1)
            {
                if (subActionList[0].targetTag == 0)
                {
                    __spanHeight = subActionList[0].calculateSpanHeight(curStart);
                }
            }
            else
            {
                __spanHeight = 1;
            }
            return __spanHeight;
        }

        public float calcSeconds(float passed)
        {
            float t = 0;
            if (eActionType == EActionType.CCActionInstant) {
                // no time
            } else if (name == "CCSequence") {
                foreach (ActionTemplate xxx in subActionList) {
                    if (xxx.targetTag == 0)
                        t += xxx.calcSeconds(t + passed);
                }
            } 
            else if (name == "CCSpawn") {
                foreach (ActionTemplate xxx in subActionList)
                {
                    if (xxx.targetTag == 0)
                        t = Math.Max(xxx.calcSeconds(passed), t);
                }
            }
            else if (name == "CCRepeat")
            {
                ActionParamTemplate param = getParamByName("times");
                if (param != null && subActionList.Count > 0 && subActionList[0].targetTag == 0)
                {
                    t = param.var_int * subActionList[0].calcSeconds(passed);
                }
            }
            else if (name == "CCRepeatForEver")
            {
                t = 999999;
            }
            else if (name == "CCSpeed")
            {
                if (subActionList.Count > 0) {
                    t = subActionList[0].calcSeconds(passed) / getParamByName("speed").var_float;
                }
            }
            else if (name == "CCAnimate") { // TODO 序列帧改成总时间
                // TODO 
                //t = 
            }
            else if (subActionList.Count == 1)
            {
                if (subActionList[0].targetTag == 0)
                    t = subActionList[0].calcSeconds(passed);
            }
            else if (getParamByName("duration") != null && getParamByName("duration").type == EParamType.PARAM_TYPE_FLOAT)
            {
                t = getParamByName("duration").var_float;
            }
            else if (getParamByName("t") != null && getParamByName("t").type == EParamType.PARAM_TYPE_FLOAT)
            {
                t = getParamByName("t").var_float;
            }
            else if (getParamByName("d") != null && getParamByName("d").type == EParamType.PARAM_TYPE_FLOAT)
            {
                t = getParamByName("d").var_float;
            }

            __passed = passed;
            __duration = t;
            return t;
        }

        public bool isContainGridSubAction()
        {
            foreach (ActionTemplate xxx in subActionList) {
                if (xxx.eActionType == EActionType.CCGridAction) return true;
            }
            return false;
        }

        public void updateActionTreeNode()
        {
            StringBuilder sb = new StringBuilder();
            if (targetTag != 0)
            {
                sb.Append("[目标Tag=").Append(targetTag).Append("]");
            }
            //sb.Append("[层起=" + __spanStart + "]");
            //sb.Append("[层高=" + __spanHeight + "]");
            sb.Append("[" + __passed + "秒]");
            sb.Append(note);

            if (name == "AE_Condition")
            {
                sb.Append(" { ");
                String xxx = "";
                switch (actionParams[0].var_str)
                {
                    case "EQUAL": xxx = "等于"; break;
                    case "GREAT_EQUAL": xxx = "大于等于"; break;
                    case "GREAT": xxx = "大于"; break;
                    case "LESS_EQUAL": xxx = "小于"; break;
                    case "LESS": xxx = "小于等于"; break;
                }
                sb.Append(xxx).Append(" ").Append(actionParams[1].var_int);
                sb.Append(" }");
            } else if (actionParams.Count > 0) { 
                sb.Append(" { ");
                for (int i = 0; i < actionParams.Count; ++i)
                {
                    ActionParamTemplate param = actionParams[i];
                    sb.Append(param.note).Append("=").Append(param.toDynamicStr());
                    if (i != actionParams.Count - 1) {
                        sb.Append("; ");
                    }
                }
                sb.Append(" }");
            }
            sb.Append(" <共 " + __duration + " 秒>");

            _treeNode.Text = sb.ToString();

            if (name.Contains("CCSpawn") || name.Contains("Sequence"))
            {
                _treeNode.ForeColor = Color.Orchid;
            }
            else if (name.Contains("Ease")) {
                _treeNode.ForeColor = Color.Green;
            }
            else if (name.Contains("Repeat"))
            {
                _treeNode.ForeColor = Color.Orchid;
            }
            //else {
            //    switch (eActionType)
            //    {
            //        case EActionType.CCActionInstant: _treeNode.ForeColor = Color.Black; break;
            //        case EActionType.CCActionInterval: _treeNode.ForeColor = Color.Black; break;
            //        case EActionType.CCGridAction: _treeNode.ForeColor = Color.OrangeRed; break;
            //    }
            //}
        }

        public TreeNode getTreeNode()
        {
            return _treeNode;
        }

        public ActionTemplate(ActionTemplate other)
        {
            this.name = other.name;
            this.eActionType = other.eActionType;
            this.isUi = other.isUi;
            this.isGridEffect = other.isGridEffect;
            this.onlyUi = other.onlyUi;
            this.onlyFight = other.onlyFight;
            this.note = other.note;
            this.actionList = other.actionList;
            foreach (ActionParamTemplate xxx in other.actionParams) {
                this.actionParams.Add(new ActionParamTemplate(xxx));
            }
            this.targetTag = other.targetTag;

            //updateActionTreeNode();
        }

        public ActionTemplate(XmlElement e)
        {
            name = e.GetAttribute("name");
            eActionType = parseActionType(e.GetAttribute("type"));
            isUi = e.GetAttribute("isToUI").Equals("true");
            isGridEffect = e.GetAttribute("isGridEffect").Equals("true");
            onlyUi = e.GetAttribute("isOnlyUI").Equals("true");
            onlyFight = e.GetAttribute("isOnlyFight").Equals("true");
            note = e.GetAttribute("note");
            actionList = e.GetAttribute("actionList") != "" ? System.Int32.Parse(e.GetAttribute("actionList")) : 0;
            foreach (XmlNode eParam in e.SelectNodes("param")) {
                actionParams.Add(new ActionParamTemplate((XmlElement)eParam));
            }
            targetTag = 0; // not dynamic

            //updateActionTreeNode();
        }

        public void addSubAction(ActionTemplate action, ActionTemplate neighbor = null, bool isBefore = false)
        {
            if (actionList == 0) throw new Exception("actionList == 0 && try add subAction");
            if (actionList == 1 && subActionList.Count == 1) throw new Exception("actionList == 1 && curSubAction.Count = 1 && try add subAction");

            if (neighbor == null)
            {
                subActionList.Add(action);
                _treeNode.Nodes.Add(action.getTreeNode());
            }
            else
            {
                {
                    int index = subActionList.IndexOf(neighbor);
                    subActionList.Insert(isBefore ? index : index + 1, action);
                }
                {
                    int index = _treeNode.Nodes.IndexOf(neighbor.getTreeNode());
                    _treeNode.Nodes.Insert(isBefore ? index : index + 1, action.getTreeNode());
                }
            }
        }

        public void replaceAction(ActionTemplate actionToReplace, ActionTemplate action)
        {
            int indexOfAction = this.subActionList.IndexOf(actionToReplace);
            int indexOfNode = this._treeNode.Nodes.IndexOf(actionToReplace.getTreeNode());
            if (indexOfAction < 0 || indexOfNode < 0) return;

            this.subActionList.RemoveAt(indexOfAction);
            this._treeNode.Nodes.RemoveAt(indexOfNode);

            this.subActionList.Insert(indexOfAction, action);
            this._treeNode.Nodes.Insert(indexOfAction, action.getTreeNode());
        }

        public void removeSubAction(ActionTemplate subAction, bool isCheckSub = true)
        {
            if (!this.subActionList.Contains(subAction)) return;

            if (isCheckSub)
            {
                if (actionList >= 1 && subActionList.Count == 1)
                    throw new Exception("actionList >= 1 && subAction.Count == 1 && try remove subAction");
            }

            this.subActionList.Remove(subAction);
            this._treeNode.Nodes.Remove(subAction._treeNode);
        }

        public void moveSubAction(ActionTemplate action, bool isBefore)
        {
            {
                int index = subActionList.IndexOf(action);
                if (isBefore)
                {
                    if (index <= 0) return;
                    subActionList.Remove(action);
                    subActionList.Insert(index - 1, action);
                }
                else
                {
                    if (index >= subActionList.Count - 1) return;
                    subActionList.Remove(action);
                    subActionList.Insert(index + 1, action);
                }
            }

            {
                int index = _treeNode.Nodes.IndexOf(action.getTreeNode());
                _treeNode.Nodes.Remove(action.getTreeNode());
                _treeNode.Nodes.Insert(isBefore ? index - 1 : index + 1, action.getTreeNode());
            }
        }

        public void setDynamic(XmlElement e, ActionTemplateTable table)
        {
            // targetTag
            targetTag = e.HasAttribute("targetTag") ? int.Parse(e.GetAttribute("targetTag")) : 0;

            // params
            foreach (ActionParamTemplate xxx in actionParams)
            {
                if (e.HasAttribute(xxx.name))
                {
                    xxx.setDynamic(e.GetAttribute(xxx.name));
                } // else default value
            }
            // sub action list
            foreach (XmlNode node in e.SelectNodes("action")) {
                addSubAction(table.createAction((XmlElement)node));
            }

            if (actionList > 1 && subActionList.Count == 0) {
                throw new Exception("actionList > 1 && subActionList.Count == 0");
            }

            //updateActionTreeNode();
        }

        public ActionTemplate copy(ActionTemplateTable table)
        {
            String xml = toDynamicXmlStr(0);
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.LoadXml(xml);

            return table.createAction((XmlElement)xmlDoc.SelectNodes("action")[0]);
        }

        public String toDynamicXmlStr(int ntab)
        {
            String strNTab = "";
            for (int i = 0; i < ntab; ++i) {
                strNTab += "\t";
            }

            StringBuilder sb = new StringBuilder();
            sb.Append(strNTab).Append("<action name=\"").Append(name).Append("\"");
            sb.Append(" ").Append("targetTag=\"").Append(targetTag).Append("\"");
            foreach (ActionParamTemplate param in actionParams)
            {
                sb.Append(" ").Append(param.name).Append("=\"").Append(param.toDynamicStr()).Append("\"");
            }
            if (subActionList.Count == 0)
            {
                sb.Append("/>\n");
                return sb.ToString();
            }
            else
            {
                sb.Append(">\n");
            }


            foreach (ActionTemplate sub in subActionList) {
                sb.Append(sub.toDynamicXmlStr(ntab + 1));
            }

            sb.Append(strNTab);
            sb.Append("</action>\n");
            return sb.ToString();
        }
    }

    class ActionTemplateTable
    {
        public enum EActionFilterType {
            SPAWN_AND_SEQUENCE,
            ACTION_LIST_0,
            ACTION_LIST_1,
            ACTION_LIST_2,
            GRID,
        }

        public Dictionary<String, ActionTemplate> actionTemplates = new Dictionary<String, ActionTemplate>();

        private bool isIgnore(ActionTemplate action, EActionFilterType[] ignores)
        {
            foreach (EActionFilterType xxx in ignores) {
                if (action.actionList == 0 && xxx == EActionFilterType.ACTION_LIST_0) return true;
                if (action.actionList == 1 && xxx == EActionFilterType.ACTION_LIST_1) return true;
                if (action.actionList > 1 && xxx == EActionFilterType.ACTION_LIST_2) return true;
                if (action.eActionType == EActionType.CCGridAction && xxx == EActionFilterType.GRID) return true;
                if ((action.name.Contains("Spawn") || action.name.Contains("Sequence")) && xxx == EActionFilterType.SPAWN_AND_SEQUENCE) return true;
            }
            return false;
        }

        private bool isPrefer(ActionTemplate action, EActionFilterType[] prefers)
        {
            foreach (EActionFilterType xxx in prefers)
            {
                if ((action.actionList == 0 && xxx == EActionFilterType.ACTION_LIST_0)
                    || (action.actionList == 1 && xxx == EActionFilterType.ACTION_LIST_1)
                    || (action.actionList > 1 && xxx == EActionFilterType.ACTION_LIST_2)
                    || (action.eActionType == EActionType.CCGridAction && xxx == EActionFilterType.GRID)
                    || ((action.name.Contains("Spawn") || action.name.Contains("Sequence")) && xxx == EActionFilterType.SPAWN_AND_SEQUENCE))
                    return true;
            }
            return false;
        }

        public List<String> getActionsByIgnoreList(EAeDataType eType, params EActionFilterType[] ignores)
        {
            List<String> ret = new List<String>();
            foreach (ActionTemplate xxx in actionTemplates.Values)
            {
                if (eType == EAeDataType.Ui && !xxx.isUi) continue;
                if (eType != EAeDataType.Ui && xxx.onlyUi) continue;
                if (eType != EAeDataType.Skill && xxx.onlyFight) continue;
                if (isIgnore(xxx, ignores)) continue;
                ret.Add(xxx.note);
            }
            return ret;
        }

        public List<String> getActionsByPerferList(EAeDataType eType, params EActionFilterType[] prefers)
        {
            List<String> ret = new List<String>();
            foreach (ActionTemplate xxx in actionTemplates.Values)
            {
                if (eType == EAeDataType.Ui && !xxx.isUi) continue;
                if (eType != EAeDataType.Ui && xxx.onlyUi) continue;
                if (eType != EAeDataType.Skill && xxx.onlyFight) continue;
                if (isPrefer(xxx, prefers)) {
                    ret.Add(xxx.note);
                }
            }
            return ret;
        }

        public ActionTemplateTable(String fileName)
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(fileName);

            foreach (XmlNode eAction in doc.SelectNodes("templates/action"))
            {
                ActionTemplate actionTemplate = new ActionTemplate((XmlElement)eAction);
                actionTemplates.Add(actionTemplate.name, actionTemplate);
            }
        }

        public ActionTemplate createAction(String name)
        {
            ActionTemplate stub = actionTemplates[name];
            if (stub == null) throw new Exception(name);
            return new ActionTemplate(stub);
        }

        public ActionTemplate createActionByNote(String note)
        {
            foreach (ActionTemplate stub in actionTemplates.Values) {
                if (stub.note == note) return new ActionTemplate(stub);
            }
            return null;
        }

        public ActionTemplate createAction(XmlElement e)
        {
            ActionTemplate ret = createAction(e.GetAttribute("name"));
            ret.setDynamic(e, this);
            return ret;
        }
    }

    abstract class AEConfig
    {
        protected TreeNode _treeNode = new TreeNode();

        public TreeNode getTreeNode()
        {
            return _treeNode;
        }

        public abstract void updateTreeNode();

        public abstract void init(XmlElement e);

        public abstract String toXmlStr(int ntab);
    }

    class SkillAEConfig : AEConfig
    {
        public String testBackGround = "";
        public bool testChangePart = false;     // 换阵营
        public float totalSecond = 2.0f;        // 总时间

        public SkillAEConfig()
        {
            updateTreeNode();
        }

        public override void updateTreeNode()
        {
            _treeNode.Text = "[配置]{测试背景(可以为ae)=" + testBackGround + ",技能总时间=" + totalSecond + ",测试换阵营=" + (testChangePart ? 1 : 0) 
                + "}";
        }

        public override void init(XmlElement e)
        {
            testBackGround = e.HasAttribute("testBackGround") ? e.GetAttribute("testBackGround").Replace("\\", "/") : "";
            totalSecond = float.Parse(e.GetAttribute("totalSecond"));
            testChangePart = e.HasAttribute("testChangePart") ? int.Parse(e.GetAttribute("testChangePart")) > 0 : false;

            updateTreeNode();
        }

        public override String toXmlStr(int ntab)
        {
            String strNTab = "";
            for (int i = 0; i < ntab; ++i)
            {
                strNTab += "\t";
            }

            StringBuilder sb = new StringBuilder();
            sb.Append(strNTab);
            sb.Append("<config ");
            sb.Append("totalSecond=\"").Append(totalSecond).Append("\" ");
            sb.Append("testBackGround=\"").Append(testBackGround).Append("\" ");
            sb.Append("testChangePart=\"").Append(testChangePart ? 1 : 0).Append("\" ");
            sb.Append("/>\n");
            return sb.ToString();
        }
    }

    class UiAEConfig : AEConfig
    {
        public float testDelaySecond = 0;
        public String testBackGround = "";
        public int condition = 0;
        public String jasonFile = "";
        public UITree uiTree = null;
        public String[] strs = new String[5];
        public CCPoint[] points = new CCPoint[5];


        public UiAEConfig()
        {
            for (int i = 0; i < 5; i++)
            {
                strs[i] = "";
                points[i] = new CCPoint();
            }
            updateTreeNode();
        }

        public override void updateTreeNode()
        {
            _treeNode.Text = "[配置]{分支条件=" + condition + ",jasonFile=" + jasonFile + ",测试背景=" + testBackGround + ",测试延迟=" + testDelaySecond + "}";
        }

        public void setJasonFile(String jasonFile)
        {
            this.jasonFile = jasonFile;

            uiTree = new UITree(jasonFile);
            updateTreeNode();
        }

        public override void init(XmlElement e)
        {
            testDelaySecond = e.HasAttribute("testDelaySecond") ? float.Parse(e.GetAttribute("testDelaySecond")) : 0;
            testBackGround = e.HasAttribute("testBackGround") ? e.GetAttribute("testBackGround").Replace("\\", "/") : "";
            condition = e.HasAttribute("condition") ? int.Parse(e.GetAttribute("condition")) : 0;
            jasonFile = e.GetAttribute("jasonFile");
            if (jasonFile != null && jasonFile != "")
            {
                uiTree = new UITree(jasonFile); // throw exception
            }
            
            for (int i = 0; i < 5; i++)
            {
                if (e.HasAttribute("str" + (i + 1)))
                    strs[i] = e.GetAttribute("str" + (i + 1));
                else
                    strs[i] = "";
                if (e.HasAttribute("point" + (i + 1)))
                    points[i] = new CCPoint(e.GetAttribute("point" + (i + 1)));
                else
                    points[i] = new CCPoint();
            }

            updateTreeNode();
        }

        public override String toXmlStr(int ntab)
        {
            String strNTab = "";
            for (int i = 0; i < ntab; ++i)
            {
                strNTab += "\t";
            }

            StringBuilder sb = new StringBuilder();
            sb.Append(strNTab);
            sb.Append("<config ");
            sb.Append("jasonFile=\"").Append(jasonFile).Append("\" ");
            sb.Append("testDelaySecond=\"").Append(testDelaySecond).Append("\" ");
            sb.Append("condition=\"").Append(condition).Append("\" ");
            for (int i = 0; i < 5; i++)
            {
                sb.Append("str" + (i + 1) + "=\"").Append(strs[i]).Append("\" ");
                sb.Append("point" + (i + 1) + "=\"").Append(points[i]).Append("\" ");
            }
            sb.Append("testBackGround=\"").Append(testBackGround).Append("\"");
            sb.Append("/>\n");
            return sb.ToString();
        }
    }

    class CocosAEConfig : AEConfig
    {
        public float totalSecond = 10;
        public float playSpeed = 1;
        public float testDelaySecond = 0;
        public String testBackGround = "";
        public String nextAE = "";
        public String[] strs = new String[5];
        public CCPoint[] points = new CCPoint[5];

        public CocosAEConfig() {
            for (int i = 0; i < 5; i++)
            {
                strs[i] = "";
                points[i] = new CCPoint();
            }
            updateTreeNode();
        }

        public override void updateTreeNode()
        {
            _treeNode.Text = "[配置]{总时间=" + totalSecond + "秒,测试背景资源=" + testBackGround + ",测试延迟=" + testDelaySecond +
                ",播放速率=" + playSpeed + ",下个播放的动画=" + nextAE + "}";
        }

        public void setTotalSecond(int _totalSecond)
        {
            this.totalSecond = _totalSecond;
            updateTreeNode();
        }

        public override void init(XmlElement e) {
            totalSecond = float.Parse(e.GetAttribute("totalSecond"));
            playSpeed = e.HasAttribute("playSpeed") ? float.Parse(e.GetAttribute("playSpeed")) : 1;
            nextAE = e.HasAttribute("nextAE") ? e.GetAttribute("nextAE") : "";
            testDelaySecond = e.HasAttribute("testDelaySecond") ? float.Parse(e.GetAttribute("testDelaySecond")) : 0;
            testBackGround = e.HasAttribute("testBackGround") ? e.GetAttribute("testBackGround").Replace("\\", "/") : "";
            for (int i = 0; i < 5; i++)
            {
                if (e.HasAttribute("str" + (i + 1)))
                    strs[i] = e.GetAttribute("str" + (i + 1));
                else
                    strs[i] = "";
                if (e.HasAttribute("point" + (i + 1)))
                    points[i] = new CCPoint(e.GetAttribute("point" + (i + 1)));
                else
                    points[i] = new CCPoint();
            }

            updateTreeNode();
        }

        public override String toXmlStr(int ntab) 
        {
            String strNTab = "";
            for (int i = 0; i < ntab; ++i)
            {
                strNTab += "\t";
            }

            StringBuilder sb = new StringBuilder();
            sb.Append(strNTab);
            sb.Append("<config ");
            sb.Append("totalSecond=\"").Append(totalSecond).Append("\" ");
            sb.Append("playSpeed=\"").Append(playSpeed).Append("\" ");
            sb.Append("nextAE=\"").Append(nextAE).Append("\" ");
            sb.Append("testDelaySecond=\"").Append(testDelaySecond).Append("\" ");
            for (int i = 0; i < 5; i++)
            {
                sb.Append("str" + (i + 1) + "=\"").Append(strs[i]).Append("\" ");
                sb.Append("point" + (i + 1) + "=\"").Append(points[i]).Append("\" ");
            }
            sb.Append("testBackGround=\"").Append(testBackGround).Append("\"");
            sb.Append("/>\n");
            return sb.ToString();
        }
    }

    abstract class AESprite
    {
        public String name = "";
        public List<ActionTemplate> actions = new List<ActionTemplate>();

        public bool _canMove = true;
        public bool _canDelete = true;
        public int __spanHeight = 0;    // 时间轴的层次高度

        protected TreeNode _treeNode = new TreeNode();

        public TreeNode getTreeNode()
        {
            return _treeNode;
        }

        public void recalcAndUpdate()
        {
            __spanHeight = 0;
            foreach (ActionTemplate xxx in actions)
            {
                if (this is SkillAESprite)
                {
                    xxx.calcSeconds(((SkillAESprite)this).dynamic_delaySecond);
                }
                else
                {
                    xxx.calcSeconds(0);
                }

                __spanHeight += xxx.calculateSpanHeight(__spanHeight);

                xxx.recursiveUpdateTreeNode();
            }
            updateSpriteTreeNode();
        }

        public abstract void updateSpriteTreeNode();

        public abstract void init(XmlElement e, ActionTemplateTable table);

        public abstract String toXmlStr(int ntab);

        public AESprite(String name)
        {
            this.name = name;
        }

        public void removeAction(ActionTemplate action)
        {
            this.actions.Remove(action);
            this._treeNode.Nodes.Remove(action.getTreeNode());
        }

        public void replaceAction(ActionTemplate actionToReplace, ActionTemplate action)
        {
            int indexOfAction = this.actions.IndexOf(actionToReplace);
            int indexOfNode = this._treeNode.Nodes.IndexOf(actionToReplace.getTreeNode());
            if (indexOfAction < 0 || indexOfNode < 0) return;

            this.actions.RemoveAt(indexOfAction);
            this._treeNode.Nodes.RemoveAt(indexOfNode);

            this.actions.Insert(indexOfAction, action);
            this._treeNode.Nodes.Insert(indexOfAction, action.getTreeNode());
        }

        public void moveAction(ActionTemplate action, bool isBefore)
        {
            {
                int index = actions.IndexOf(action);
                if (isBefore)
                {
                    if (index <= 0) return;
                    actions.Remove(action);
                    actions.Insert(index - 1, action);
                }
                else
                {
                    if (index >= actions.Count - 1) return;
                    actions.Remove(action);
                    actions.Insert(index + 1, action);
                }
            }

            {
                int index = _treeNode.Nodes.IndexOf(action.getTreeNode());
                _treeNode.Nodes.Remove(action.getTreeNode());
                _treeNode.Nodes.Insert(isBefore ? index - 1 : index + 1, action.getTreeNode());
            }
        }

        public void addAction(ActionTemplate action, ActionTemplate neighbor = null, bool isBefore = false)
        {
            if (action.isGridEffect) {
                if (!(this is CocosAESprite) || !((CocosAESprite)this).isGridEffect) {
                    MessageBox.Show("精灵没有开启新网格");
                    return;
                }
            }

            if (neighbor == null)
            {
                actions.Add(action);
                _treeNode.Nodes.Add(action.getTreeNode());
            }
            else
            {
                {
                    int index = actions.IndexOf(neighbor);
                    actions.Insert(isBefore ? index : index + 1, action);
                }
                {
                    int index = _treeNode.Nodes.IndexOf(neighbor.getTreeNode());
                    _treeNode.Nodes.Insert(isBefore ? index : index + 1, action.getTreeNode());
                }
            }
        }
    }

    enum ESkillSpriteType
    {
        Performer,
        Target,
        Dynamic,
    }

    enum EOffsetType
    {
        Performer_Position,     // 相对于施放者
        Performer_Upper,
        Performer_Middle,
        Performer_Bottom,

        Target_Position,        // 相对于目标       
        Target_Upper,
        Target_Middle,
        Target_Bottom,

        Screen_Position,        // 相对于屏幕
    }

    class SkillAESprite : AESprite
    {
        public ESkillSpriteType spriteType = ESkillSpriteType.Dynamic;
        public String res;                                                       // 资源
        public float scale = 1.0f;                                               // 缩放
        public int zOrder = 0;                                                   // zOrder
        public CCPoint performer_posGrid = new CCPoint(2, 2);                    // 施放者，格子坐标 5*9 x in [0,4] y in [0,8]
        public float performer_skillNameSecond = 1;                              // 施放者，播放技能名时间
        public CCPoint target_posGrid1 = new CCPoint(2, 6);                      // 目标，格子坐标 5*9 x in [0,4] y in [0,8]
        public CCPoint target_posGrid2 = new CCPoint(-1, -1);                    // 目标，格子坐标 5*9 x in [0,4] y in [0,8]
        public CCPoint target_posGrid3 = new CCPoint(-1, -1);                    // 目标，格子坐标 5*9 x in [0,4] y in [0,8]
        public CCPoint target_posGrid4 = new CCPoint(-1, -1);                    // 目标，格子坐标 5*9 x in [0,4] y in [0,8]
        public CCPoint target_posGrid5 = new CCPoint(-1, -1);                    // 目标，格子坐标 5*9 x in [0,4] y in [0,8]
        public float target_hitSecond = 2;                                       // 目标，播放伤害时机
        public EOffsetType dynamic_offsetType = EOffsetType.Screen_Position;     // 动态精灵，偏移坐标中心
        public int dynamic_col_delta = 0;                                        // 动态精灵，行偏移
        public CCPoint dynamic_offset = new CCPoint(0, 0);                       // 动态精灵，偏移坐标
        public CCPoint dynamic_anchor = new CCPoint(0.5f, 0.5f);                 // 动态精灵，锚点
        public float dynamic_delaySecond = 0;                                    // 动态精灵，出现时间
        public bool dynamic_isPerTarget = true;                                  // 动态精灵，是否每个目标构建一份
        public bool dynamic_isOrientAdjust = false;                              // 动态精灵，是否根据施放者阵营调整方向
        public bool dynamic_use_new_grid = false;                                // 动态精灵，开启新网格

        public override void updateSpriteTreeNode()
        {
            if (spriteType == ESkillSpriteType.Performer)
            { // 施放者
                _treeNode.Text = "[施放者]" + "{资源=" + res + ",缩放=" + scale + 
                    ",格子位置=" + performer_posGrid.ToString() 
                    + ",根据阵营调整方向=" + (dynamic_isOrientAdjust ? 1 : 0) + "}";
            }
            else if (spriteType == ESkillSpriteType.Target)
            { // 目标
                String strPosGrid = "";
                if (target_posGrid1.x >= 0 && target_posGrid1.y >= 0) strPosGrid += target_posGrid1.ToString();
                if (target_posGrid2.x >= 0 && target_posGrid2.y >= 0) strPosGrid += target_posGrid2.ToString();
                if (target_posGrid3.x >= 0 && target_posGrid3.y >= 0) strPosGrid += target_posGrid3.ToString();
                if (target_posGrid4.x >= 0 && target_posGrid4.y >= 0) strPosGrid += target_posGrid4.ToString();
                if (target_posGrid5.x >= 0 && target_posGrid5.y >= 0) strPosGrid += target_posGrid5.ToString();
                _treeNode.Text = "[目标]" + "{资源=" + res + ",缩放=" + scale + ",格子位置=" + strPosGrid.ToString() 
                    + ",播放伤害时间=" + target_hitSecond
                    + "}";
            }
            else if (spriteType == ESkillSpriteType.Dynamic)
            { // 动态精灵
                String strOffsetType = "";
                switch (dynamic_offsetType)
                {
                    case EOffsetType.Performer_Position: strOffsetType = "施放者_中心"; break;
                    case EOffsetType.Performer_Upper: strOffsetType = "施放者_行顶"; break;
                    case EOffsetType.Performer_Middle: strOffsetType = "施放者_行中"; break;
                    case EOffsetType.Performer_Bottom: strOffsetType = "施放者_行底"; break;
                    case EOffsetType.Target_Position: strOffsetType = "目标_位置"; break;
                    case EOffsetType.Target_Upper: strOffsetType = "目标_行顶"; break;
                    case EOffsetType.Target_Middle: strOffsetType = "目标_行中"; break;
                    case EOffsetType.Target_Bottom: strOffsetType = "目标_行底"; break;
                    case EOffsetType.Screen_Position: strOffsetType = "屏幕坐标"; break;
                }
                _treeNode.Text = (dynamic_use_new_grid ? "[新网格]" : "") + "[动态精灵]" + "{资源=" + res + ",延迟=" + dynamic_delaySecond + ",锚点=" + dynamic_anchor.ToString()
                    + ",坐标=" + strOffsetType.ToString() + (dynamic_col_delta != 0 ? ("+(" + dynamic_col_delta + "列)+") : "+") + dynamic_offset.ToString() 
                    + ",每个目标创建=" + (dynamic_isPerTarget ? 1 : 0) + ",阵营翻转方向=" + (dynamic_isOrientAdjust ? 1 : 0)
                    + "}";
            }
        }

        public SkillAESprite(String name, ESkillSpriteType eSkillSpriteType)
            : base(name)
        {
            this.spriteType = eSkillSpriteType;
            if (eSkillSpriteType == ESkillSpriteType.Performer || eSkillSpriteType == ESkillSpriteType.Target)
            {
                _canDelete = false;
                _canMove = false;
                zOrder = 100;
                scale = 0.52f;
            }
            recalcAndUpdate();
        }

        public override void init(XmlElement e, ActionTemplateTable table)
        {
            name = e.GetAttribute("name");
            spriteType = (ESkillSpriteType)Enum.Parse(typeof(ESkillSpriteType), e.GetAttribute("spriteType"));
            res = e.GetAttribute("res");
            if (e.HasAttribute("scale")) scale = float.Parse(e.GetAttribute("scale"));
            if (e.HasAttribute("zOrder")) zOrder = int.Parse(e.GetAttribute("zOrder"));
            if (e.HasAttribute("performer_posGrid")) performer_posGrid = new CCPoint(e.GetAttribute("performer_posGrid"));
            if (e.HasAttribute("performer_skillNameSecond")) performer_skillNameSecond = float.Parse(e.GetAttribute("performer_skillNameSecond"));
            if (e.HasAttribute("target_posGrid1")) target_posGrid1 = new CCPoint(e.GetAttribute("target_posGrid1"));
            if (e.HasAttribute("target_posGrid2")) target_posGrid2 = new CCPoint(e.GetAttribute("target_posGrid2"));
            if (e.HasAttribute("target_posGrid3")) target_posGrid3 = new CCPoint(e.GetAttribute("target_posGrid3"));
            if (e.HasAttribute("target_posGrid4")) target_posGrid4 = new CCPoint(e.GetAttribute("target_posGrid4"));
            if (e.HasAttribute("target_posGrid5")) target_posGrid5 = new CCPoint(e.GetAttribute("target_posGrid5"));
            if (e.HasAttribute("target_hitSecond")) target_hitSecond = float.Parse(e.GetAttribute("target_hitSecond"));
            if (e.HasAttribute("dynamic_offsetType")) dynamic_offsetType = (EOffsetType)EOffsetType.Parse(typeof(EOffsetType), e.GetAttribute("dynamic_offsetType"));
            if (e.HasAttribute("dynamic_offset")) dynamic_offset = new CCPoint(e.GetAttribute("dynamic_offset"));
            if (e.HasAttribute("dynamic_col_delta")) dynamic_col_delta = int.Parse(e.GetAttribute("dynamic_col_delta"));
            if (e.HasAttribute("dynamic_anchor")) dynamic_anchor = new CCPoint(e.GetAttribute("dynamic_anchor"));
            if (e.HasAttribute("dynamic_delaySecond")) dynamic_delaySecond = float.Parse(e.GetAttribute("dynamic_delaySecond"));
            if (e.HasAttribute("dynamic_isPerTarget")) dynamic_isPerTarget = int.Parse(e.GetAttribute("dynamic_isPerTarget")) != 0;
            if (e.HasAttribute("dynamic_isOrientAdjust")) dynamic_isOrientAdjust = int.Parse(e.GetAttribute("dynamic_isOrientAdjust")) != 0;
            if (e.HasAttribute("dynamic_use_new_grid")) dynamic_use_new_grid = int.Parse(e.GetAttribute("dynamic_use_new_grid")) != 0;

            foreach (XmlNode node in e.SelectNodes("action"))
            {
                addAction(table.createAction((XmlElement)node));
            }
            recalcAndUpdate();
        }

        public override String toXmlStr(int ntab)
        {
            String strNTab = "";
            for (int i = 0; i < ntab; ++i)
            {
                strNTab += "\t";
            }

            StringBuilder sb = new StringBuilder();

            sb.Append(strNTab);
            sb.Append("<sprite ");
            sb.Append("name=\"").Append(name).Append("\" ");
            sb.Append("res=\"").Append(res).Append("\" ");
            sb.Append("zOrder=\"").Append(zOrder).Append("\" ");
            sb.Append("scale=\"").Append(scale).Append("\" ");
            sb.Append("spriteType=\"").Append(spriteType.ToString()).Append("\" ");
            if (spriteType == ESkillSpriteType.Performer)
            { // 施放者
                sb.Append("performer_posGrid=\"").Append(performer_posGrid.ToString()).Append("\" ");
                sb.Append("performer_skillNameSecond=\"").Append(performer_skillNameSecond.ToString()).Append("\" ");
            }
            else if (spriteType == ESkillSpriteType.Target)
            { // 目标
                sb.Append("target_posGrid1=\"").Append(target_posGrid1.ToString()).Append("\" ");
                sb.Append("target_posGrid2=\"").Append(target_posGrid2.ToString()).Append("\" ");
                sb.Append("target_posGrid3=\"").Append(target_posGrid3.ToString()).Append("\" ");
                sb.Append("target_posGrid4=\"").Append(target_posGrid4.ToString()).Append("\" ");
                sb.Append("target_posGrid5=\"").Append(target_posGrid5.ToString()).Append("\" ");
                sb.Append("target_hitSecond=\"").Append(target_hitSecond).Append("\" ");
            }
            else if (spriteType == ESkillSpriteType.Dynamic)
            { // 动态精灵
                sb.Append("dynamic_offsetType=\"").Append(dynamic_offsetType.ToString()).Append("\" ");
                sb.Append("dynamic_offset=\"").Append(dynamic_offset.ToString()).Append("\" ");
                sb.Append("dynamic_col_delta=\"").Append(dynamic_col_delta.ToString()).Append("\" ");
                sb.Append("dynamic_anchor=\"").Append(dynamic_anchor.ToString()).Append("\" ");
                sb.Append("dynamic_delaySecond=\"").Append(dynamic_delaySecond.ToString()).Append("\" ");
                sb.Append("dynamic_isPerTarget=\"").Append(dynamic_isPerTarget ? "1" : "0").Append("\" ");
                sb.Append("dynamic_isOrientAdjust=\"").Append(dynamic_isOrientAdjust ? "1" : "0").Append("\" ");
                sb.Append("dynamic_use_new_grid=\"").Append(dynamic_use_new_grid ? "1" : "0").Append("\" ");
            }
            sb.Append(">\n");

            foreach (ActionTemplate xxx in actions)
            {
                sb.Append(xxx.toDynamicXmlStr(ntab + 1));
            }

            sb.Append(strNTab);
            sb.Append("</sprite>\n");
            return sb.ToString();
        }
    }

    class UiAESprite : AESprite
    {
        public String uiClassName = "";
        public CCPoint initOffset = new CCPoint(0, 0);
        public int visible = 2;     // 0/1/2   隐藏/显示/不管

        public override void updateSpriteTreeNode()
        {
            String strVisible = "";
            if (visible == 0) strVisible = "隐藏";
            else if (visible == 1) strVisible = "显示";
            else strVisible = "不管";
            _treeNode.Text = "[控件] {列表=" + name + "," + "类=" + uiClassName + ",初始偏移=" + initOffset + ",初始可见=" + strVisible + "}";
        }

        public UiAESprite(String name, String uiClassName)
            : base(name)
        {
            this.uiClassName = uiClassName;
            recalcAndUpdate();
        }

        public override void init(XmlElement e, ActionTemplateTable table)
        {
            name = e.GetAttribute("name");
            if (e.HasAttribute("initOffset"))
            {
                initOffset = new CCPoint(e.GetAttribute("initOffset"));
            }
            if (e.HasAttribute("visible"))
            {
                if (e.GetAttribute("visible").Equals("true"))
                {
                    visible = 1;
                }
                else if (e.GetAttribute("visible").Equals("false"))
                {
                    visible = 0;
                }
                else
                {
                    visible = int.Parse(e.GetAttribute("visible"));
                }
            }

            foreach (XmlNode node in e.SelectNodes("action"))
            {
                addAction(table.createAction((XmlElement)node));
            }
            recalcAndUpdate();
        }

        public override String toXmlStr(int ntab)
        {
            String strNTab = "";
            for (int i = 0; i < ntab; ++i)
            {
                strNTab += "\t";
            }

            StringBuilder sb = new StringBuilder();

            sb.Append(strNTab);
            sb.Append("<sprite ");
            sb.Append("name=\"").Append(name).Append("\" ");
            sb.Append("initOffset=\"").Append(initOffset.ToString()).Append("\" ");
            sb.Append("visible=\"").Append(visible).Append("\" ");
            sb.Append(">\n");

            foreach (ActionTemplate xxx in actions)
            {
                sb.Append(xxx.toDynamicXmlStr(ntab + 1));
            }

            sb.Append(strNTab);
            sb.Append("</sprite>\n");
            return sb.ToString();
        }
    }

    class CocosAESprite : AESprite
    {
        public String res = "";
        public float rotate = 0.0f;
        public String aeRenderTarget = "";
        public CCPoint aeRenderTargetSize = new CCPoint(768, 1024);
        public CCPoint aeRenderTargetCenter = new CCPoint(384, 512);
        public CCPoint aeRenderTargetRegion = new CCPoint(768, 1024);
        public String label = "";
        public String font = "";
        public int fontSize = 12;
        public Color3 fontColor = new Color3();
        public String fontDefPath = "";
        public float scale = 1.0f;
        public int zOrder = 0;
        public CCPoint pos = new CCPoint();
        public CCPoint anchorPos = new CCPoint(0.5f, 0.5f);
        public bool isCloseButton = false;
        public String ryFileName = "";
        public String openNewAEButton = "";
        public bool isHide = false;
        public EBlendFactor srcBlendFactor = EBlendFactor.GL_SRC_ALPHA;
        public EBlendFactor dstBlendFactor = EBlendFactor.GL_ONE_MINUS_SRC_ALPHA;
        public bool isGridEffect = false;
        public float extraDeviceScale = 1.0f;


        public override void updateSpriteTreeNode()
        {
            bool isBlendChanged = srcBlendFactor != EBlendFactor.GL_SRC_ALPHA || dstBlendFactor != EBlendFactor.GL_ONE_MINUS_SRC_ALPHA;
            _treeNode.Text = "[精灵" + ((aeRenderTarget == "") ? "" : ("(画" + aeRenderTarget + ")")) + (isBlendChanged ? "(混合)" : "") + "]{名字=" + name + ",隐藏=" +
                (isHide ? 1 : 0) + ",资源=" + res + ",zOder=" + zOrder + ",pos=" + pos + ",锚点=" +
                anchorPos + (fontDefPath == "" ? (",font=" + font + ",fontSize=" + fontSize + ",fontColor=" + fontColor) : (",fontDef=" + fontDefPath)) 
                + (scale != 1.0f ? ("缩放=" + scale) : "")
                + (ryFileName != "" ? ",ry=" + ryFileName : "") +
                (isCloseButton ? ",关闭此关卡" : "") + (openNewAEButton != "" ? (",打开新关卡:" + openNewAEButton) : "")
                + (isGridEffect ? ",启用新网格" : "")  + "}";
        }

        public CocosAESprite(String name) : base(name)
        {

        }

        public override void init(XmlElement e, ActionTemplateTable table)
        {
            name = e.GetAttribute("name");
            res = e.GetAttribute("res").Replace("\\", "/");
            zOrder = System.Int32.Parse(e.GetAttribute("zOrder"));
            if (e.HasAttribute("pos"))
            {
                pos = new CCPoint(e.GetAttribute("pos"));
            }
            label = e.HasAttribute("label") ? e.GetAttribute("label") : "";
            font = e.HasAttribute("font") ? e.GetAttribute("font") : "";
            fontSize = e.HasAttribute("fontSize") ? int.Parse(e.GetAttribute("fontSize")) : 0;
            fontColor = e.HasAttribute("fontColor") ? new Color3(e.GetAttribute("fontColor")) : new Color3();
            fontDefPath = e.HasAttribute("fontDefPath") ? fontDefPath : "";
            rotate = e.HasAttribute("rotate") ? float.Parse(e.GetAttribute("rotate")) : 0;
            isCloseButton = e.HasAttribute("isCloseButton") ? (int.Parse(e.GetAttribute("isCloseButton")) > 0) : false;
            openNewAEButton = e.HasAttribute("openNewAEButton") ? e.GetAttribute("openNewAEButton") : "";
            ryFileName = e.HasAttribute("ry") ? e.GetAttribute("ry") : "";
            isHide = e.HasAttribute("isHide") ? int.Parse(e.GetAttribute("isHide")) > 0 : false;
            if (e.HasAttribute("scale"))
            {
                scale = float.Parse(e.GetAttribute("scale"));
            }
            if (e.HasAttribute("srcBlendFactor"))
            {
                srcBlendFactor = (EBlendFactor)Enum.Parse(typeof(EBlendFactor), e.GetAttribute("srcBlendFactor"));
            }
            if (e.HasAttribute("dstBlendFactor"))
            {
                dstBlendFactor = (EBlendFactor)Enum.Parse(typeof(EBlendFactor), e.GetAttribute("dstBlendFactor"));
            }
            if (e.HasAttribute("aeRenderTarget"))
            {
                aeRenderTarget = e.GetAttribute("aeRenderTarget");
            }
            if (e.HasAttribute("aeRenderTargetSize"))
            {
                aeRenderTargetSize = new CCPoint(e.GetAttribute("aeRenderTargetSize"));
            }
            if (e.HasAttribute("aeRenderTargetCenter"))
            {
                aeRenderTargetCenter = new CCPoint(e.GetAttribute("aeRenderTargetCenter"));
            }
            if (e.HasAttribute("aeRenderTargetRegion"))
            {
                aeRenderTargetRegion = new CCPoint(e.GetAttribute("aeRenderTargetRegion"));
            }
            if (e.HasAttribute("anchorPos"))
            {
                anchorPos = new CCPoint(e.GetAttribute("anchorPos"));
            }
            if (e.HasAttribute("isGridEffect"))
            {
                isGridEffect = int.Parse(e.GetAttribute("isGridEffect")) > 0;
            }
            if (e.HasAttribute("extraDeviceScale"))
            {
                extraDeviceScale = float.Parse(e.GetAttribute("extraDeviceScale"));
            }

            foreach (XmlNode node in e.SelectNodes("action"))
            {
                addAction(table.createAction((XmlElement)node));
            }

            recalcAndUpdate();
        }

        public override String toXmlStr(int ntab)
        {
            String strNTab = "";
            for (int i = 0; i < ntab; ++i)
            {
                strNTab += "\t";
            }

            StringBuilder sb = new StringBuilder();

            sb.Append(strNTab);
            sb.Append("<sprite ");
            sb.Append("name=\"").Append(name).Append("\" ");
            sb.Append("res=\"").Append(res).Append("\" ");
            sb.Append("rotate=\"").Append(rotate).Append("\" ");
            sb.Append("label=\"").Append(label).Append("\" ");
            sb.Append("isCloseButton=\"").Append(isCloseButton ? "1" : "0").Append("\" ");
            sb.Append("openNewAEButton=\"").Append(openNewAEButton).Append("\" ");
            sb.Append("font=\"").Append(font).Append("\" ");
            sb.Append("fontSize=\"").Append(fontSize).Append("\" ");
            sb.Append("fontColor=\"").Append(fontColor).Append("\" ");
            if (fontDefPath != "") {
                sb.Append("fontDefPath=\"").Append(fontDefPath).Append("\" ");
            }
            sb.Append("isHide=\"").Append(isHide ? 1 : 0).Append("\" ");
            sb.Append("ry=\"").Append(ryFileName).Append("\" ");
            sb.Append("pos=\"").Append(pos.ToString()).Append("\" ");
            sb.Append("anchorPos=\"").Append(anchorPos.ToString()).Append("\" ");
            sb.Append("srcBlendFactor=\"").Append(Enum.GetName(typeof(EBlendFactor), srcBlendFactor)).Append("\" ");
            sb.Append("dstBlendFactor=\"").Append(Enum.GetName(typeof(EBlendFactor), dstBlendFactor)).Append("\" ");
            sb.Append("aeRenderTarget=\"").Append(aeRenderTarget).Append("\" ");
            sb.Append("aeRenderTargetSize=\"").Append(aeRenderTargetSize.ToString()).Append("\" ");
            sb.Append("aeRenderTargetCenter=\"").Append(aeRenderTargetCenter.ToString()).Append("\" ");
            sb.Append("aeRenderTargetRegion=\"").Append(aeRenderTargetRegion.ToString()).Append("\" ");
            sb.Append("isGridEffect=\"").Append(isGridEffect ? 1 : 0).Append("\" ");
            sb.Append("scale=\"").Append(scale).Append("\" ");
            if (extraDeviceScale != 1.0f)
            {
                sb.Append("extraDeviceScale=\"").Append(extraDeviceScale).Append("\" ");
            }
            sb.Append("zOrder=\"").Append(zOrder).Append("\"");
            sb.Append(">\n");

            foreach (ActionTemplate xxx in actions)
            {
                sb.Append(xxx.toDynamicXmlStr(ntab + 1));
            }

            sb.Append(strNTab);
            sb.Append("</sprite>\n");
            return sb.ToString();
        }
    }

    class SkillAESpritePropForm : AESpritePropForm
    {
        public SkillAESpritePropForm(AEData aeData, AESprite aeSprite, MainFrame mainForm) : base(aeData, aeSprite, mainForm) { }

        public override void initFrom()
        {
            if (!(__aeSprite is SkillAESprite)) throw new Exception("__aeSprite is not SkillAESprite");
            SkillAESprite aeSprite = (SkillAESprite)__aeSprite;

            this.addProp(EPropType.ePropType_Str, "" + aeSprite.name, "名字");
            this.addProp(EPropType.ePropType_Str, "" + aeSprite.res, "资源");
            this.addProp(EPropType.ePropType_Float, "" + aeSprite.scale, "缩放");
            this.addProp(EPropType.ePropType_Int, "" + aeSprite.zOrder, "zOrder");
            if (aeSprite.spriteType == ESkillSpriteType.Performer)
            { // 施放者
                props[0].tb.Enabled = false;        // 不能修改名字
                this.addProp(EPropType.ePropType_Point, "" + aeSprite.performer_posGrid, "格子位置 xy范围：[0,4][0,8]");
                this.addProp(EPropType.ePropType_Float, "" + aeSprite.performer_skillNameSecond, "技能名出现时间");
            }
            else if (aeSprite.spriteType == ESkillSpriteType.Target)
            { // 目标
                props[0].tb.Enabled = false;        // 不能修改名字
                this.addProp(EPropType.ePropType_Point, "" + aeSprite.target_posGrid1, "格子位置1 xy范围：[0,4][0,8]");
                this.addProp(EPropType.ePropType_Point, "" + aeSprite.target_posGrid2, "格子位置2 xy范围：[0,4][0,8]");
                this.addProp(EPropType.ePropType_Point, "" + aeSprite.target_posGrid3, "格子位置3 xy范围：[0,4][0,8]");
                this.addProp(EPropType.ePropType_Point, "" + aeSprite.target_posGrid4, "格子位置4 xy范围：[0,4][0,8]");
                this.addProp(EPropType.ePropType_Point, "" + aeSprite.target_posGrid5, "格子位置5 xy范围：[0,4][0,8]");
                this.addProp(EPropType.ePropType_Float, "" + aeSprite.target_hitSecond, "冒血时间");
            }
            else if (aeSprite.spriteType == ESkillSpriteType.Dynamic)
            { // 动态精灵
                this.addProp(EPropType.ePropType_OffsetType, "" + aeSprite.dynamic_offsetType, "偏移类型");
                this.addProp(EPropType.ePropType_Point, "" + aeSprite.dynamic_offset, "偏移像素坐标");
                this.addProp(EPropType.ePropType_Int, "" + aeSprite.dynamic_col_delta, "偏移列");
                this.addProp(EPropType.ePropType_Point, "" + aeSprite.dynamic_anchor, "锚点");
                this.addProp(EPropType.ePropType_Float, "" + aeSprite.dynamic_delaySecond, "延迟时间");
                this.addProp(EPropType.ePropType_Int, "" + (aeSprite.dynamic_isPerTarget ? 1 : 0), "是否绑定目标: 1/0 是/否");
                this.addProp(EPropType.ePropType_Int, "" + (aeSprite.dynamic_isOrientAdjust ? 1 : 0), "是否根据阵营旋转: 1/0 是/否");
                this.addProp(EPropType.ePropType_Int, "" + (aeSprite.dynamic_use_new_grid ? 1 : 0), "是否使用新网格: 1/0 是/否");
            }
        }

        public override void setBack()
        {
            if (!(__aeSprite is SkillAESprite)) throw new Exception("__aeSprite is not CocosAESprite");
            SkillAESprite aeSprite = (SkillAESprite)__aeSprite;

            int cur = 0;
            aeSprite.name = props[cur++].tb.Text;
            aeSprite.res = props[cur++].tb.Text;
            aeSprite.res.Replace("\\", "/");
            aeSprite.scale = float.Parse(props[cur++].tb.Text);
            aeSprite.zOrder = int.Parse(props[cur++].tb.Text);
            if (aeSprite.spriteType == ESkillSpriteType.Performer)
            { // 施放者
                aeSprite.performer_posGrid = new CCPoint(props[cur++].tb.Text);
                aeSprite.performer_skillNameSecond = float.Parse(props[cur++].tb.Text);
            }
            else if (aeSprite.spriteType == ESkillSpriteType.Target)
            { // 目标
                aeSprite.target_posGrid1 = new CCPoint(props[cur++].tb.Text);
                aeSprite.target_posGrid2 = new CCPoint(props[cur++].tb.Text);
                aeSprite.target_posGrid3 = new CCPoint(props[cur++].tb.Text);
                aeSprite.target_posGrid4 = new CCPoint(props[cur++].tb.Text);
                aeSprite.target_posGrid5 = new CCPoint(props[cur++].tb.Text);
                aeSprite.target_hitSecond = float.Parse(props[cur++].tb.Text);
            }
            else if (aeSprite.spriteType == ESkillSpriteType.Dynamic)
            { // 动态精灵
                aeSprite.dynamic_offsetType = (EOffsetType)Enum.Parse(typeof(EOffsetType), props[cur++].tb.Text);
                aeSprite.dynamic_offset = new CCPoint(props[cur++].tb.Text);
                aeSprite.dynamic_col_delta = int.Parse(props[cur++].tb.Text);
                aeSprite.dynamic_anchor = new CCPoint(props[cur++].tb.Text);
                aeSprite.dynamic_delaySecond = float.Parse(props[cur++].tb.Text);
                aeSprite.dynamic_isPerTarget = int.Parse(props[cur++].tb.Text) != 0;
                aeSprite.dynamic_isOrientAdjust = int.Parse(props[cur++].tb.Text) != 0;
                aeSprite.dynamic_use_new_grid = int.Parse(props[cur++].tb.Text) != 0;
            }
        }
    }

    class UiAESpritePropForm : AESpritePropForm
    {
        public UiAESpritePropForm(AEData aeData, AESprite aeSprite, MainFrame mainForm) : base(aeData, aeSprite, mainForm) { }

        public override void initFrom()
        {
            if (!(__aeSprite is UiAESprite)) throw new Exception("__aeSprite is not CocosAESprite");
            UiAESprite aeSprite = (UiAESprite)__aeSprite;

            this.addProp(EPropType.ePropType_Strs, "" + aeSprite.name, "控件列表");
            this.addProp(EPropType.ePropType_Point, "" + aeSprite.initOffset, "初始偏移");
            this.addProp(EPropType.ePropType_Int, "" + aeSprite.visible, "是否初始显示(0/1/2: 隐藏/显示/不管)");
        }

        public override void setBack()
        {
            if (!(__aeSprite is UiAESprite)) throw new Exception("__aeSprite is not CocosAESprite");
            UiAESprite aeSprite = (UiAESprite)__aeSprite;

            aeSprite.name = "";
            aeSprite.uiClassName = "";
            {
                UiAEConfig aeConfig = (UiAEConfig)aeData.aeConfig;
                foreach (String split in Regex.Split(props[0].tb.Text, ","))
                {
                    UIWidget uiWidget = aeConfig.uiTree.findByName(split);
                    if (uiWidget == null)
                    {
                        MessageBox.Show("not has Widget: " + split);
                        aeSprite.uiClassName += "????,";
                    }
                    else
                    {
                        aeSprite.uiClassName += uiWidget.className + ",";
                    }
                }
            }

            aeSprite.name = props[0].tb.Text;
            aeSprite.initOffset = new CCPoint(props[1].tb.Text);
            aeSprite.visible = int.Parse(props[2].tb.Text);
            if (aeSprite.visible < 0) aeSprite.visible = 0;
            if (aeSprite.visible > 2) aeSprite.visible = 2;
        }
    }

    class CocosAESpritePropForm : AESpritePropForm
    {
        public CocosAESpritePropForm(AEData aeData, AESprite aeSprite, MainFrame mainForm) : base(aeData, aeSprite, mainForm) { }

        public override void initFrom()
        {
            if (!(__aeSprite is CocosAESprite)) throw new Exception("__aeSprite is not CocosAESprite");
            CocosAESprite aeSprite = (CocosAESprite)__aeSprite;

            this.addProp(EPropType.ePropType_Str, "" + aeSprite.name, "精灵名字（索引用，必须唯一）");
            this.addProp(EPropType.ePropType_Str, "" + aeSprite.res, "精灵资源", true);
            this.addProp(EPropType.ePropType_Str, "" + aeSprite.label, "文本内容");
            this.addProp(EPropType.ePropType_Str, "" + aeSprite.fontDefPath, "字体描述文件", true);
            this.addProp(EPropType.ePropType_Str, "" + aeSprite.font, "字体");
            this.addProp(EPropType.ePropType_Int, "" + aeSprite.fontSize, "字体大小");
            this.addProp(EPropType.ePropType_Str, "" + aeSprite.fontColor, "字体颜色（rgb）");
            this.addProp(EPropType.ePropType_Int, "" + aeSprite.zOrder, "zOrder（大的靠前显示）");
            this.addProp(EPropType.ePropType_Point, "" + aeSprite.pos, "初始坐标");
            this.addProp(EPropType.ePropType_Point, "" + aeSprite.anchorPos, "锚点坐标");
            this.addProp(EPropType.ePropType_Float, "" + aeSprite.scale, "缩放比例");
            this.addProp(EPropType.ePropType_Float, "" + aeSprite.rotate, "子旋转（>0生效, RenderTarget实现）");
            //this.addProp(EPropType.ePropType_Str, "" + aeSprite.aeRenderTarget, "画AE(RenderTarget实现)", true);
            //this.addProp(EPropType.ePropType_Point, "" + aeSprite.aeRenderTargetSize, "画AE纹理大小", true);
            //this.addProp(EPropType.ePropType_Point, "" + aeSprite.aeRenderTargetCenter, "画AE中心", true);
            //this.addProp(EPropType.ePropType_Point, "" + aeSprite.aeRenderTargetRegion, "画AE区域", true);
            this.addProp(EPropType.ePropType_Str, "" + aeSprite.ryFileName, "区域震动效果文件", true);
            this.addProp(EPropType.ePropType_Int, "" + (aeSprite.isCloseButton ? 1 : 0), "是否关闭本关卡");
            this.addProp(EPropType.ePropType_Str, "" + aeSprite.openNewAEButton, "开启新关卡（关卡名）", true);
            this.addProp(EPropType.ePropType_Int, "" + (aeSprite.isHide ? 1 : 0), "是否隐藏");
            //this.addProp(EPropType.ePropType_GL_BlendFactor, Enum.GetName(typeof(EBlendFactor), aeSprite.srcBlendFactor), "GL源系数[当前纹理]");
            //this.addProp(EPropType.ePropType_GL_BlendFactor, Enum.GetName(typeof(EBlendFactor), aeSprite.dstBlendFactor), "GL目标系数[背景]");
            this.addProp(EPropType.ePropType_Int, "" + (aeSprite.isGridEffect ? 1 : 0), "是否启用新网格[震动，翻转等]");
            this.addProp(EPropType.ePropType_Float, "" + aeSprite.extraDeviceScale, "设备额外缩放(例如:iphone可能用小图)");
        }

        public override void setBack()
        {
            if (!(__aeSprite is CocosAESprite)) throw new Exception("__aeSprite is not CocosAESprite");
            CocosAESprite aeSprite = (CocosAESprite)__aeSprite;

            int i = 0;
            aeSprite.name = props[i++].tb.Text;
            aeSprite.res = props[i++].tb.Text;
            aeSprite.label = props[i++].tb.Text;
            aeSprite.fontDefPath = props[i++].tb.Text;
            aeSprite.font = props[i++].tb.Text;
            aeSprite.fontSize = int.Parse(props[i++].tb.Text);
            aeSprite.fontColor = new Color3(props[i++].tb.Text);
            aeSprite.zOrder = int.Parse(props[i++].tb.Text);
            aeSprite.pos = new CCPoint(props[i++].tb.Text);
            aeSprite.anchorPos = new CCPoint(props[i++].tb.Text);
            aeSprite.scale = float.Parse(props[i++].tb.Text);
            aeSprite.rotate = float.Parse(props[i++].tb.Text);
            //aeSprite.aeRenderTarget = props[i++].tb.Text;
            //aeSprite.aeRenderTargetSize = new CCPoint(props[i++].tb.Text);
            //aeSprite.aeRenderTargetCenter = new CCPoint(props[i++].tb.Text);
            //aeSprite.aeRenderTargetRegion = new CCPoint(props[i++].tb.Text);
            aeSprite.ryFileName = props[i++].tb.Text;
            aeSprite.isCloseButton = int.Parse(props[i++].tb.Text) > 0;
            aeSprite.openNewAEButton = props[i++].tb.Text;
            aeSprite.isHide = int.Parse(props[i++].tb.Text) > 0;
            //aeSprite.srcBlendFactor = (EBlendFactor)Enum.Parse(typeof(EBlendFactor), props[i++].tb.Text);
            //aeSprite.dstBlendFactor = (EBlendFactor)Enum.Parse(typeof(EBlendFactor), props[i++].tb.Text);
            aeSprite.isGridEffect = int.Parse(props[i++].tb.Text) > 0;
            aeSprite.extraDeviceScale = float.Parse(props[i++].tb.Text);
        }
    }

    abstract class AESpritePropForm : PropForm
    {
        protected AEData aeData;
        protected AESprite __aeSprite;
        MainFrame mainForm;

        public abstract void initFrom();
        public abstract void setBack();

        public AESpritePropForm(AEData aeData, AESprite aeSprite, MainFrame mainForm)
        {
            this.aeData = aeData;
            this.__aeSprite = aeSprite;
            this.mainForm = mainForm;

            initFrom();
        }

        override protected void btnOk_Click(object sender, EventArgs e)
        {
            try
            {
                base.btnOk_Click(sender, e);

                foreach (AESprite xxx in aeData.aeSprites)
                {
                    if (xxx == __aeSprite) continue;

                    if (xxx.name == props[0].tb.Text)
                    {
                        props[0].tb.ForeColor = Color.Red;
                        //MessageBox.Show("名字跟其它精灵重复");
                        return;
                    }
                }

                setBack();
            }
            catch (Exception)
            {
                //MessageBox.Show("参数不合法！！！");
                return;
            }

            __aeSprite.recalcAndUpdate();
            mainForm.setDirty(true);
            this.Close();
        }
    }

    abstract class AEConfigPropForm : PropForm
    {
        protected AEConfig __aeConfig;
        MainFrame mainForm;

        public abstract void initFrom();
        public abstract void setBack();

        public AEConfigPropForm(AEConfig aeConfig, MainFrame mainForm)
        {
            this.__aeConfig = aeConfig;
            this.mainForm = mainForm;

            initFrom();
        }

        override protected void btnOk_Click(object sender, EventArgs e)
        {
            try
            {
                base.btnOk_Click(sender, e);

                setBack();
            }catch(Exception) {
                //MessageBox.Show("参数不合法" + ex);
                return;
            }

            __aeConfig.updateTreeNode();
            mainForm.setDirty(true);
            this.Close();
        }
    }

    class SkillAEConfigPropForm : AEConfigPropForm
    {
        public SkillAEConfigPropForm(AEConfig aeConfig, MainFrame mainForm) : base(aeConfig, mainForm) { }

        public override void initFrom()
        {
            if (!(__aeConfig is SkillAEConfig)) throw new Exception("__aeConfig is not SkillAEConfig !!!");

            SkillAEConfig aeConfig = (SkillAEConfig)__aeConfig;
            this.addProp(EPropType.ePropType_Float, "" + aeConfig.totalSecond, "技能总时间（秒）");
            this.addProp(EPropType.ePropType_Str, "" + aeConfig.testBackGround, "测试背景", true);
            this.addProp(EPropType.ePropType_Int, "" + (aeConfig.testChangePart ? 1 : 0), "测试换阵营", true);
        }

        public override void setBack()
        {
            if (!(__aeConfig is SkillAEConfig)) throw new Exception("__aeConfig is not SkillAEConfig !!!");

            int cur = 0;
            SkillAEConfig aeConfig = (SkillAEConfig)__aeConfig;
            aeConfig.totalSecond = float.Parse(props[cur++].tb.Text);
            aeConfig.testBackGround = props[cur++].tb.Text;
            aeConfig.testChangePart = int.Parse(props[cur++].tb.Text) > 0;
        }
    }

    class UiAEConfigPropForm : AEConfigPropForm
    {
        public UiAEConfigPropForm(AEConfig aeConfig, MainFrame mainForm) : base(aeConfig, mainForm) { }

        public override void initFrom()
        {
            if (!(__aeConfig is UiAEConfig)) throw new Exception("__aeConfig is not UIAEConfig !!!");

            UiAEConfig aeConfig = (UiAEConfig)__aeConfig;

            this.addProp(EPropType.ePropType_Float, "" + aeConfig.testDelaySecond, "测试延迟（秒）");
            this.addProp(EPropType.ePropType_Str, "" + aeConfig.testBackGround, "测试背景", true);
            this.addProp(EPropType.ePropType_Int, "" + aeConfig.condition, "分支条件", false);
            this.addProp(EPropType.ePropType_Str, "" + aeConfig.jasonFile, "jason文件", true);
            for (int i = 0; i < 5; ++i)
            {
                this.addProp(EPropType.ePropType_Str, "" + aeConfig.strs[i], "字符串变量, S" + (i + 1));
            }
            for (int i = 0; i < 5; ++i)
            {
                this.addProp(EPropType.ePropType_Point, "" + aeConfig.points[i], "坐标变量, P" + (i + 1));
            }
        }

        public override void setBack()
        {
            if (!(__aeConfig is UiAEConfig)) throw new Exception("__aeConfig is not UIAEConfig !!!");

            int cur = 0;
            UiAEConfig aeConfig = (UiAEConfig)__aeConfig;
            aeConfig.testDelaySecond = float.Parse(props[cur++].tb.Text);
            aeConfig.testBackGround = props[cur++].tb.Text;
            aeConfig.condition = int.Parse(props[cur++].tb.Text);
            aeConfig.setJasonFile(props[cur++].tb.Text);
            for (int i = 0; i < 5; ++i)
            {
                aeConfig.strs[i] = props[cur++].tb.Text;
            }
            for (int i = 0; i < 5; ++i)
            {
                aeConfig.points[i] = new CCPoint(props[cur++].tb.Text);
            }
        }
    }

    class CocosAEConfigPropForm : AEConfigPropForm
    {
        public CocosAEConfigPropForm(AEConfig aeConfig, MainFrame mainForm) : base(aeConfig, mainForm) { }

        public override void initFrom()
        {
            if (!(__aeConfig is CocosAEConfig)) throw new Exception("__aeConfig is not SpriteAEConfig !!!");

            CocosAEConfig aeConfig = (CocosAEConfig)__aeConfig;
            this.addProp(EPropType.ePropType_Float, "" + aeConfig.totalSecond, "动画总时间（秒）");
            this.addProp(EPropType.ePropType_Float, "" + aeConfig.playSpeed, "播放速率");
            this.addProp(EPropType.ePropType_Str, "" + aeConfig.nextAE, "下个播放的动画");
            this.addProp(EPropType.ePropType_Float, "" + aeConfig.testDelaySecond, "测试延迟（秒）");
            this.addProp(EPropType.ePropType_Strs, "" + aeConfig.testBackGround, "测试背景资源", true);
            for (int i = 0; i < 5; ++i)
            {
                this.addProp(EPropType.ePropType_Str, "" + aeConfig.strs[i], "字符串变量, S" + (i + 1));
            }
            for (int i = 0; i < 5; ++i)
            {
                this.addProp(EPropType.ePropType_Point, "" + aeConfig.points[i], "坐标变量, P" + (i + 1));
            }
        }

        public override void setBack()
        {
            if (!(__aeConfig is CocosAEConfig)) throw new Exception("__aeConfig is not SpriteAEConfig !!!");

            CocosAEConfig aeConfig = (CocosAEConfig)__aeConfig;
            aeConfig.totalSecond = float.Parse(props[0].tb.Text);
            aeConfig.playSpeed = float.Parse(props[1].tb.Text);
            aeConfig.nextAE = props[2].tb.Text;
            aeConfig.testDelaySecond = float.Parse(props[3].tb.Text);
            aeConfig.testBackGround = props[4].tb.Text;
            for (int i = 0; i < 5; ++i)
            {
                aeConfig.strs[i] = props[5 + i].tb.Text;
            }
            for (int i = 0; i < 5; ++i)
            {
                aeConfig.points[i] = new CCPoint(props[10 + i].tb.Text);
            }
        }
    }

    class ActionPropForm : PropForm
    {
        ActionTemplate action;
        MainFrame mainForm;

        private EPropType transferParam(ActionParamTemplate param, out bool isFileName) {
            isFileName = false;
            if (param.type == EParamType.PARAM_TYPE_STR || param.type == EParamType.PARAM_TYPE_STRS)
            {
                if (param.name.Contains("fileName") || param.name.Contains("plist"))
                {
                    isFileName = true;
                }
            }
            //this.addProp(EPropType.ePropType_GL_BlendFactor, Enum.GetName(typeof(EBlendFactor), aeSprite.srcBlendFactor), "GL源系数[当前纹理]");

            switch (param.type)
            {
                case EParamType.PARAM_TYPE_INT: return EPropType.ePropType_Int;
                case EParamType.PARAM_TYPE_FLOAT: return EPropType.ePropType_Float;
                case EParamType.PARAM_TYPE_BEZIER: return EPropType.ePropType_Bezier;
                case EParamType.PARAM_TYPE_POINT: return EPropType.ePropType_Point;
                case EParamType.PARAM_TYPE_STR:
                    {
                        if (param.name == "srcBlendFactor" || param.name == "dstBlendFactor") {
                            return EPropType.ePropType_GL_BlendFactor;
                        } else {
                            return EPropType.ePropType_Str;
                        }
                    }
                case EParamType.PARAM_TYPE_STRS: return EPropType.ePropType_Strs;
                default: throw new Exception("" + param.type);
            }
        }

        public ActionPropForm(ActionTemplate action, MainFrame mainForm)
        {
            this.action = action;
            foreach (ActionParamTemplate param in action.actionParams) {
                bool isFileName = false;
                EPropType ePropType = transferParam(param, out isFileName);
                this.addProp(ePropType, "" + param.toDynamicStr(), param.note, isFileName);
            }
            this.addProp(EPropType.ePropType_Int, "" + action.targetTag, "执行动作的子物体Tag(非零生效)");
            this.mainForm = mainForm;
        }

        override protected void btnOk_Click(object sender, EventArgs e)
        {
            try
            {
                int i = 0;
                base.btnOk_Click(sender, e);

                foreach (ActionParamTemplate param in action.actionParams)
                {
                    param.setDynamic(props[i++].tb.Text);
                }
                this.action.targetTag = int.Parse(props[i++].tb.Text);
            }
            catch (Exception)
            {
                //MessageBox.Show("参数不合法" + ex);
                return;
            }

            if (mainForm.curEditAEData != null)
            {
                mainForm.curEditAEData.recalcAndUpdate();
            }
            mainForm.setDirty(true);
            this.Close();
        }
    }

    public enum ECondType
    {
        EQUAL,
        GREAT_EQUAL,
        GREAT,
        LESS,
        LESS_EQUAL,
    }

    public enum EAeDataType {
        Cocos,
        Ui,
        Skill,
    }

    internal class AEData
    {
        internal EAeDataType eType;
        public AEConfig aeConfig;
        public List<AESprite> aeSprites = new List<AESprite>();

        public String fileName = "NewCreated";
        public bool isHasFile = false;
        private TreeNode _rootNode = new TreeNode();

        //static void recursiveUpdateActionTN(ActionTemplate actionTemplate)
        //{
        //    actionTemplate.updateActionTreeNode();
        //    foreach (ActionTemplate sub in actionTemplate.subActionList)
        //    {
        //        if (sub.subActionList.Count > 0)
        //        {
        //            recursiveUpdateActionTN(sub);
        //        }
        //    }
        //}

        public void recalcAndUpdate()
        {
            if (aeConfig != null)
                aeConfig.updateTreeNode();
            foreach (AESprite aeSprite in aeSprites) {
                aeSprite.recalcAndUpdate();
            }

            if (TimeSpanForm.instance != null)
            {
                TimeSpanForm.instance.updateActionBox(this);
            }
        }

        private bool isHasSpriteName(String spriteName)
        {
            foreach (AESprite aeSprite in aeSprites) {
                if (aeSprite.name == spriteName) return true;
            }
            return false;
        }

        private String createNewSpriteName() {
            String ret = null;
            for (int i = 1; ; ++i)
            {
               ret = "NoNamed_" + i;
               if (!isHasSpriteName(ret)) break;
            }
            return ret;
        }

        public AESprite createSprite() {
            switch (eType) {
                case EAeDataType.Cocos:
                    return new CocosAESprite(createNewSpriteName());
                case EAeDataType.Ui:
                    return new UiAESprite("???", "???");
                case EAeDataType.Skill:
                    return new SkillAESprite(createNewSpriteName(), ESkillSpriteType.Dynamic);
                default:
                    throw new Exception("eType = " + eType);
            }
        }

        public AESprite copySprite(AESprite oth, ActionTemplateTable table)
        {
            String xml = oth.toXmlStr(0);
            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.LoadXml(xml);

            AESprite ret = createSprite();
            ret.init((XmlElement)xmlDoc.SelectNodes("sprite")[0], table);
            ret.name = createNewSpriteName();
            ret.recalcAndUpdate();
            return ret;
        }

        public AESpritePropForm createSpritePropForm(AESprite aeSprite, MainFrame mainForm)
        {
            switch (eType) {
                case EAeDataType.Cocos:
                    return new CocosAESpritePropForm(this, aeSprite, mainForm);
                case EAeDataType.Skill:
                    return new SkillAESpritePropForm(this, aeSprite, mainForm);
                case EAeDataType.Ui:
                    return new UiAESpritePropForm(this, aeSprite, mainForm);
                default:
                    throw new Exception("eType = " + eType);
            }
        }

        public AEConfigPropForm createConfigPropForm(MainFrame mainForm)
        {
            switch (eType) {
                case EAeDataType.Cocos:
                    return new CocosAEConfigPropForm(aeConfig, mainForm);
                case EAeDataType.Skill:
                    return new SkillAEConfigPropForm(aeConfig, mainForm);
                case EAeDataType.Ui:
                    return new UiAEConfigPropForm(aeConfig, mainForm);
                default:
                    throw new Exception("eType = " + eType);
            }
        }

        public ActionTemplate getActionBindedObject(ActionTemplate actionTemplate, TreeNode treeNode) {
            if (actionTemplate.getTreeNode() == treeNode) {
                return actionTemplate;
            }

            foreach (ActionTemplate actionTemplate2 in actionTemplate.subActionList)
            {
                ActionTemplate ret = getActionBindedObject(actionTemplate2, treeNode);
                if (ret != null) return ret;
            }
            return null;
        }

        // AEData  AEConfig  AESprite  ActionTemplate
        public Object getNodeBindedObject(TreeNode treeNode)
        {
            if (_rootNode == treeNode) {
                return this;
            } else if (aeConfig.getTreeNode() == treeNode) {
                return aeConfig;
            } else {
                foreach (AESprite aeSprite in aeSprites) {
                    if (aeSprite.getTreeNode() == treeNode) {
                        return aeSprite;
                    }

                    foreach (ActionTemplate actionTemplate in aeSprite.actions) {
                        ActionTemplate ret = getActionBindedObject(actionTemplate, treeNode);
                        if (ret != null) return ret;
                    }
                }

                return null; // 真的找不到 ...
            }
        }

        public AEData(EAeDataType eType)
        {
            init(eType);
            _rootNode.ForeColor = Color.Red;
            if (eType == EAeDataType.Skill)
            {
                addSprite(new SkillAESprite("performer", ESkillSpriteType.Performer));
                addSprite(new SkillAESprite("target", ESkillSpriteType.Target));
            }
        }

        private void init(EAeDataType eType)
        {
            this.eType = eType;

            switch (eType)
            {
                case EAeDataType.Cocos:
                    aeConfig = new CocosAEConfig();
                    break;
                case EAeDataType.Skill:
                    aeConfig = new SkillAEConfig();
                    break;
                case EAeDataType.Ui:
                    aeConfig = new UiAEConfig();
                    break;
            }


            _rootNode.Text = "[" + fileName + "]";
            _rootNode.Nodes.Add(aeConfig.getTreeNode());
        }

        public static AEData create(String fileName, ActionTemplateTable table)
        {
            return new AEData(fileName, table);
        }

        private AEData(String fileName, ActionTemplateTable table)
        {
            this.fileName = fileName;

            EAeDataType eType = EAeDataType.Cocos;
            if (fileName.EndsWith(".ae")) {
                eType = EAeDataType.Cocos;
            } else if (fileName.EndsWith(".ue")) {
                eType = EAeDataType.Ui;
            } else if (fileName.EndsWith(".se")) {
                eType = EAeDataType.Skill;
            } else {
                throw new Exception("what aeType is? fileName = " + fileName);
            }
            init(eType);

            XmlDocument xmlDoc = new XmlDocument();
            xmlDoc.Load(fileName);

            XmlNodeList nodeList = xmlDoc.SelectNodes("aeditor");
            if (nodeList.Count == 0) throw new Exception("load AEData, not find <aeditor>");

            this.fileName = fileName;
            this.isHasFile = true;

            init((XmlElement)(nodeList.Item(0)), table);
        }

        public void removeSprite(AESprite aeSprite)
        {
            if (!aeSprite._canDelete) return;

            aeSprites.Remove(aeSprite);
            _rootNode.Nodes.Remove(aeSprite.getTreeNode());
        }

        public AESprite getUpperSprite(AESprite aeSprite)
        {
            int index = aeSprites.IndexOf(aeSprite);
            if (index <= 0) return null;
            return aeSprites[index - 1];
        }

        public void moveSprite(AESprite aeSprite, bool isBefore)
        {
            if (!aeSprite._canMove) return;

            {
                int index = aeSprites.IndexOf(aeSprite);
                if (isBefore)
                {
                    if (index <= 0) return;
                    aeSprites.Remove(aeSprite);
                    aeSprites.Insert(index - 1, aeSprite);
                }
                else
                {
                    if (index >= aeSprites.Count - 1) return;
                    aeSprites.Remove(aeSprite);
                    aeSprites.Insert(index + 1, aeSprite);
                }
            }

            {
                int index = _rootNode.Nodes.IndexOf(aeSprite.getTreeNode());
                _rootNode.Nodes.Remove(aeSprite.getTreeNode());
                _rootNode.Nodes.Insert(isBefore ? index - 1 : index + 1, aeSprite.getTreeNode());
            }
        }

        public void addSprite(AESprite aeSprite, AESprite neighbor = null, bool isBefore = false)
        {
            
            if (neighbor == null) 
            { 
                aeSprites.Add(aeSprite);
                _rootNode.Nodes.Add(aeSprite.getTreeNode());
            }
            else
            {
                {
                    int index = aeSprites.IndexOf(neighbor);
                    aeSprites.Insert(isBefore ? index : index + 1, aeSprite);
                }
                {
                    int index = _rootNode.Nodes.IndexOf(neighbor.getTreeNode());
                    _rootNode.Nodes.Insert(isBefore ? index : index + 1, aeSprite.getTreeNode());
                }
            }
        }

        private void init(XmlElement e, ActionTemplateTable table)
        {
            XmlNodeList nodeList = e.SelectNodes("config");
            if (nodeList.Count == 0) throw new Exception("load AEData, not find <aeditor><config>");

            _rootNode.Text = "[" + fileName + "]";

            aeConfig.init((XmlElement)nodeList.Item(0));

            foreach (XmlNode __eNode in e.SelectNodes("sprite")) {
                XmlElement eNode = (XmlElement)__eNode;
                switch (eType) {
                case EAeDataType.Cocos:
                    {
                        CocosAESprite aeSprite = new CocosAESprite(eNode.GetAttribute("name"));
                        aeSprite.init(eNode, table);
                        addSprite(aeSprite);
                        break;
                    }
                case EAeDataType.Ui:
                    {
                        String name = eNode.GetAttribute("name");
                        String className = "";
                        UiAEConfig uiAeConfig = (UiAEConfig)aeConfig;
                        foreach (String uiWidgetName in Regex.Split(name, ",")) {
                            if (uiAeConfig.uiTree != null)
                            {
                                UIWidget uiWidget = uiAeConfig.uiTree.findByName(uiWidgetName);
                                if (uiWidget != null)
                                {
                                    className += uiWidget.className + ",";
                                }
                                else
                                {
                                    className += "null,";
                                }
                            }
                        }
                        UiAESprite aeSprite = new UiAESprite(name, className);
                        aeSprite.init(eNode, table);
                        addSprite(aeSprite);
                        break;
                    }
                case EAeDataType.Skill:
                    {
                        String name = eNode.GetAttribute("name");
                        ESkillSpriteType eSpriteType = (ESkillSpriteType)Enum.Parse(typeof(ESkillSpriteType), eNode.GetAttribute("spriteType"));
                        SkillAESprite aeSprite = new SkillAESprite(name, eSpriteType);
                        aeSprite.init(eNode, table);
                        addSprite(aeSprite);
                        break;
                    }
                default:
                    throw new Exception("init sprite, unknown type = " + eType);
                }
            }

            recalcAndUpdate();
        }

        public void addToView(TreeView view)
        {
            // remove old
            view.Nodes.Clear();
            view.Nodes.Add(_rootNode);
        }

        public String toXmlStr()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
            sb.Append("<aeditor>\n");
            sb.Append("\n");
            sb.Append(aeConfig.toXmlStr(1));
            sb.Append("\n");
            foreach (AESprite xxx in aeSprites) {
                sb.Append(xxx.toXmlStr(1));
                sb.Append("\n");
            }
            sb.Append("</aeditor>\n");
            return sb.ToString();
        }

        public void WriteToFile(String fileName)
        {
            StreamWriter sw = new StreamWriter(new FileStream(fileName, FileMode.Create), new UTF8Encoding(false));
            try {
                sw.Write(toXmlStr());
            } finally {
                sw.Close();
            }
            this.fileName = fileName;
            _rootNode.Text = "[" + fileName + "]";
            _rootNode.ForeColor = Color.Black;
            this.isHasFile = true;
        }
    }
}
