using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Text.RegularExpressions;
using System.IO;
using System.Xml;
using System.Diagnostics;

namespace ActionEditorUI
{
    public partial class MainFrame : Form
    {
        static ActionTemplateTable table = null;

        static List<String> resPath = new List<String>();

        internal static MainFrame instance = null;

        // status
        public bool isDirty = false;
        internal AEData curEditAEData = null;

        // 区域震动编辑对话框
        private RegionMoveForm regionMoveDialog = new RegionMoveForm();
        // 粒子编辑器
        private ParticleDesign particleDesignDialog = new ParticleDesign();

        private OpenFileDialog openCocosAEFileDialog = new OpenFileDialog();
        private SaveFileDialog saveCocosAEFileDialog = new SaveFileDialog();

        private OpenFileDialog openUiAEFileDialog = new OpenFileDialog();
        private SaveFileDialog saveUiAEFileDialog = new SaveFileDialog();

        private OpenFileDialog openSkillAEFileDialog = new OpenFileDialog();
        private SaveFileDialog saveSkillAEFileDialog = new SaveFileDialog();

        public OpenFileDialog getOpenFileDialog(EAeDataType eType)
        {
            switch (eType)
            {
                case EAeDataType.Cocos:
                    return openCocosAEFileDialog;
                case EAeDataType.Ui:
                    return openUiAEFileDialog;
                case EAeDataType.Skill:
                    return openSkillAEFileDialog;
                default:
                    throw new Exception("eType=" + eType + ", ???");
            }
        }

        public SaveFileDialog getSaveFileDialog(EAeDataType eType)
        {
            switch (eType)
            {
                case EAeDataType.Cocos:
                    return saveCocosAEFileDialog;
                case EAeDataType.Ui:
                    return saveUiAEFileDialog;
                case EAeDataType.Skill:
                    return saveSkillAEFileDialog;
                default:
                    throw new Exception("eType=" + eType + ", ???");
            }
        }

        private PropForm propForm = new PropForm();
        private ActionListForm alfForm = new ActionListForm();

        // png 美术资源
        private OpenFileDialog openPngFileDialog = new OpenFileDialog();
        // plist 粒子等资源
        private OpenFileDialog openPListFileDialog = new OpenFileDialog();

        private ContextMenu nodeContextMenu = new ContextMenu();

        private Object curTreeNodeBindedObject;
        private Object curToCopyed;

        private Process simulatedProcess;

        public void init(String fileName)
        {
            StreamReader sr = new StreamReader(new FileStream(fileName, FileMode.Open), new UTF8Encoding(false));
            String line = null;
            while ((line = sr.ReadLine()) != null) {
                if (Regex.Match(line, "^#.*").Success) continue; // ignore command

                Match match = null;
                if ((match = Regex.Match(line, "^ResPath=(.*)$")) != null)
                {
                    foreach(String split in Regex.Split(match.Groups[1].ToString(), ";")) {
                        if (split.Trim() == "") continue;

                        resPath.Add(split.Trim());
                    }
                }
            }

            openPngFileDialog.Filter = "图片png文件(*.png)|*.png";
            openPngFileDialog.RestoreDirectory = false;

            openCocosAEFileDialog.Filter = "精灵动作编辑器文件(*.ae)|*.ae";
            openCocosAEFileDialog.RestoreDirectory = false;
            saveCocosAEFileDialog.Filter = "精灵动作编辑器文件(*.ae)|*.ae";
            saveCocosAEFileDialog.RestoreDirectory = false;

            openUiAEFileDialog.Filter = "界面动作编辑器文件(*.ue)|*.ue";
            openUiAEFileDialog.RestoreDirectory = false;
            saveUiAEFileDialog.Filter = "界面动作编辑器文件(*.ue)|*.ue";
            saveUiAEFileDialog.RestoreDirectory = false;

            openSkillAEFileDialog.Filter = "技能动作编辑器文件(*.se)|*.se";
            openSkillAEFileDialog.RestoreDirectory = false;
            saveSkillAEFileDialog.Filter = "技能动作编辑器文件(*.se)|*.se";
            saveSkillAEFileDialog.RestoreDirectory = false;
        }

        void setAEData(AEData aeData)
        {
            curEditAEData = aeData;
            curEditAEData.addToView(treeView1);

            //默认不展开
            //treeView1.ExpandAll();
            treeView1.Nodes[0].EnsureVisible();

            updateStatus();
        }

        public void setDirty(bool isDirty)
        {
            if (this.isDirty != isDirty)
            {
                this.isDirty = isDirty;

                updateStatus();
            }
        }

        void updateStatus()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("ActionEditor");
            if (curEditAEData != null)
            {
                sb.Append(" -- ");
                sb.Append(curEditAEData.fileName);
                if (isDirty)
                {
                    sb.Append(" *");
                }
                btnSimulate.Enabled = curEditAEData.isHasFile;
            }
            else
            {
                btnSimulate.Enabled = false;
            }
            this.Text = sb.ToString();

            this.btnSave.Font = new Font(this.btnSave.Font.Name, this.btnSave.Font.Size, isDirty ? FontStyle.Bold : FontStyle.Regular);
        }

        public MainFrame(string[] args)
        {
            InitializeComponent();

            treeView1.NodeMouseClick += treeView_NodeClick;
            treeView1.KeyUp += treeView_KeyUp;
            treeView1.ContextMenu = nodeContextMenu;
                
            // init file
            init(".\\Editor\\aeditor\\aeditor.ini");
            // action template file
            table = new ActionTemplateTable(".\\Editor\\template.xml");

            MainFrame.instance = this;

            if (args.Length == 0)
            {
                setAEData(new AEData(EAeDataType.Cocos));
            }
            else
            {
                setAEData(AEData.create(args[0], table));
            }
        }

        //// true / false : res 
        //private String isFileInResDir(String strFile)
        //{
        //    foreach (String strResDir in resPath) {
        //        //File f;
        //    }
        //}

        //private String selectPngFileInResDir()
        //{
        //    if (DialogResult.OK == openPngFileDialog.ShowDialog(this))
        //    {
        //        String file = openPngFileDialog.FileName;

        //    }
        //}

        private void contextmenu_Click(object sender, EventArgs e)
        {
            if (curTreeNodeBindedObject == null) return;
            MenuItem item = sender as MenuItem;
            if (item == null) return;

            bool __isOpDirty = true;
            if (curTreeNodeBindedObject is AEData)
            { // AEData
                AEData aeData = (AEData)curTreeNodeBindedObject;
                if (item.Text == "新建精灵")
                {
                    AESprite aeSprite = aeData.createSprite();
                    aeData.addSprite(aeSprite);
                    treeView1.SelectedNode = aeSprite.getTreeNode();
                }
            }
            else if (curTreeNodeBindedObject is AEConfig)
            { // AEConfig
                if (item.Text == "修改配置") {
                    curEditAEData.createConfigPropForm(this).ShowDialog(this);
                    __isOpDirty = false; // 内部设置了Dirty
                }
            }
            else if (curTreeNodeBindedObject is AESprite)
            { // AESprite
                AESprite aeSprite = (AESprite)curTreeNodeBindedObject;
                if (item.Text == "新建精灵(上方)")
                {
                    AESprite newAESprite = curEditAEData.createSprite();
                    this.curEditAEData.addSprite(newAESprite, aeSprite, true);
                    treeView1.SelectedNode = newAESprite.getTreeNode();
                }
                else if (item.Text == "新建精灵(下方)")
                {
                    AESprite newAESprite = curEditAEData.createSprite();
                    this.curEditAEData.addSprite(newAESprite, aeSprite, false);
                    treeView1.SelectedNode = newAESprite.getTreeNode();
                }
                else if (item.Text == "上移精灵")
                {
                    this.curEditAEData.moveSprite(aeSprite, true);
                    treeView1.SelectedNode = aeSprite.getTreeNode();
                }
                else if (item.Text == "下移精灵")
                {
                    this.curEditAEData.moveSprite(aeSprite, false);
                    treeView1.SelectedNode = aeSprite.getTreeNode();
                }
                else if (item.Text == "删除精灵")
                {
                    this.curEditAEData.removeSprite(aeSprite);
                }
                else if (item.Text == "修改精灵")
                {
                    this.curEditAEData.createSpritePropForm(aeSprite, this).ShowDialog(this);
                    __isOpDirty = false;  // dirty setted in PropForm setBack
                }
                else if (item.Text == "复制精灵")
                {
                    curToCopyed = aeSprite;
                    __isOpDirty = false;
                }
                else if (item.Text == "粘贴精灵(上方)")
                {
                    AESprite newSprite = curEditAEData.copySprite((AESprite)curToCopyed, table);
                    this.curEditAEData.addSprite(newSprite, aeSprite, true);
                    newSprite.recalcAndUpdate();
                    treeView1.SelectedNode = newSprite.getTreeNode();
                }
                else if (item.Text == "粘贴精灵(下方)")
                {
                    AESprite newSprite = curEditAEData.copySprite((AESprite)curToCopyed, table);
                    this.curEditAEData.addSprite(newSprite, aeSprite, false);
                    newSprite.recalcAndUpdate();
                    treeView1.SelectedNode = newSprite.getTreeNode();
                }
                else if (item.Text == "新建动作")
                {
                    alfForm.setItems(table.getActionsByIgnoreList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1, ActionTemplateTable.EActionFilterType.ACTION_LIST_2));

                    if (alfForm.ShowDialog(this) == DialogResult.OK) { 

                        String selected = alfForm.getSelected();
                        if (selected != null)
                        {
                            ActionTemplate action = table.createActionByNote(selected);
                            aeSprite.addAction(action);
                            treeView1.SelectedNode = action.getTreeNode();
                        }
                    }
                }
                else if (item.Text == "粘贴动作")
                {
                    if (curToCopyed is ActionTemplate) {
                        aeSprite.addAction(((ActionTemplate)curToCopyed).copy(table));
                    }
                }
            }
            else if (curTreeNodeBindedObject is ActionTemplate)
            { // ActionTemplate
                ActionTemplate actionTemplate = (ActionTemplate)curTreeNodeBindedObject;
                Object parentBindedObject = curEditAEData.getNodeBindedObject(actionTemplate.getTreeNode().Parent);
                if (item.Text == "修改动作") {
                    new ActionPropForm(actionTemplate, this).ShowDialog(this);
                    __isOpDirty = false; // 内部设置了Dirty
                }
                if (item.Text == "复制动作")
                {
                    curToCopyed = actionTemplate.copy(table);
                    __isOpDirty = false; 
                }
                else if (item.Text == "添加子动作")
                {
                    if (actionTemplate.actionList == 0) return;
                    if (actionTemplate.actionList == 1 && actionTemplate.subActionList.Count >= 1) return;

                    if (!actionTemplate.isContainGridSubAction())
                    {
                        alfForm.setItems(table.getActionsByIgnoreList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1,
                            ActionTemplateTable.EActionFilterType.ACTION_LIST_2));
                    }
                    else
                    {
                        alfForm.setItems(table.getActionsByIgnoreList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1,
                            ActionTemplateTable.EActionFilterType.ACTION_LIST_2,
                            ActionTemplateTable.EActionFilterType.GRID));
                    }
                    if (alfForm.ShowDialog(this) == DialogResult.OK)
                    {
                        String selected = alfForm.getSelected();
                        if (selected != null)
                        {
                            ActionTemplate newAction = table.createActionByNote(selected);
                            actionTemplate.addSubAction(newAction);
                            treeView1.SelectedNode = newAction.getTreeNode();
                        }
                    }
                }
                else if (item.Text == "粘贴子动作")
                {
                    if (actionTemplate.actionList == 0) return;
                    if (actionTemplate.actionList == 1 && actionTemplate.subActionList.Count >= 1) return;
                    if (curToCopyed is ActionTemplate)
                    {
                        ActionTemplate newAction = ((ActionTemplate)curToCopyed).copy(table);
                        actionTemplate.addSubAction(newAction);
                        treeView1.SelectedNode = newAction.getTreeNode();
                    }
                }

                if (parentBindedObject is AESprite)
                {
                    AESprite parent = (AESprite)parentBindedObject;
                    if (item.Text == "覆盖动作 -- 使用复制") {
                        if (curToCopyed is ActionTemplate) {
                            ActionTemplate newAction = ((ActionTemplate)curToCopyed).copy(table);
                            parent.addAction(newAction, actionTemplate, true);
                            treeView1.SelectedNode = newAction.getTreeNode();
                            parent.removeAction(actionTemplate);
                        }
                    } 
                    else if (item.Text == "删除动作")
                    {
                        if (actionTemplate.subActionList.Count == 1)
                        {
                            ActionTemplate actionToAddBack = actionTemplate.subActionList[0];
                            actionTemplate.removeSubAction(actionToAddBack, false);
                            parent.replaceAction(actionTemplate, actionToAddBack);

                            treeView1.SelectedNode = actionToAddBack.getTreeNode();
                        }
                        else
                        {
                            parent.removeAction(actionTemplate);
                        }
                    }
                    else if (item.Text == "上移动作")
                    {
                        parent.moveAction(actionTemplate, true);
                    }
                    else if (item.Text == "下移动作")
                    {
                        parent.moveAction(actionTemplate, false);
                    }
                    else if (item.Text == "添加父动作")
                    {
                        if (actionTemplate.eActionType == EActionType.CCActionInstant)
                        {
                            alfForm.setItems(table.getActionsByPerferList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.SPAWN_AND_SEQUENCE));
                        } else {
                            alfForm.setItems(table.getActionsByPerferList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1,
                                ActionTemplateTable.EActionFilterType.ACTION_LIST_2));
                        }

                        if (alfForm.ShowDialog(this) == DialogResult.OK)
                        {
                            String selected = alfForm.getSelected();
                            if (selected != null)
                            {
                                ActionTemplate newAction = table.createActionByNote(selected);
                                parent.replaceAction(actionTemplate, newAction);
                                newAction.addSubAction(actionTemplate);
                                treeView1.SelectedNode = actionTemplate.getTreeNode();
                                newAction.getTreeNode().ExpandAll();
                            }
                        }
                    }
                }
                else if (parentBindedObject is ActionTemplate)
                {
                    ActionTemplate parent = (ActionTemplate)parentBindedObject;
                    if (item.Text == "覆盖动作 -- 使用复制")
                    {
                        if (curToCopyed is ActionTemplate)
                        {
                            ActionTemplate newAction = ((ActionTemplate)curToCopyed).copy(table);
                            parent.addSubAction(newAction, actionTemplate, true);
                            treeView1.SelectedNode = newAction.getTreeNode();
                            parent.removeSubAction(actionTemplate);
                        }
                    } 
                    else if (item.Text == "删除动作")
                    {
                        if (actionTemplate.subActionList.Count == 1)
                        {
                            ActionTemplate actionToAddBack = actionTemplate.subActionList[0];
                            actionTemplate.removeSubAction(actionToAddBack, false);
                            parent.replaceAction(actionTemplate, actionToAddBack);

                            treeView1.SelectedNode = actionToAddBack.getTreeNode();
                        }
                        else
                        {
                            parent.removeSubAction(actionTemplate);
                        }
                    }
                    else if (item.Text == "新建动作(上方)")
                    {
                        if (parent.actionList <= 1) return;
                        if (!parent.isContainGridSubAction())
                        {
                            alfForm.setItems(table.getActionsByIgnoreList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1,
                                ActionTemplateTable.EActionFilterType.ACTION_LIST_2));
                        }
                        else
                        {
                            alfForm.setItems(table.getActionsByIgnoreList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1,
                                ActionTemplateTable.EActionFilterType.ACTION_LIST_2,
                                ActionTemplateTable.EActionFilterType.GRID));
                        }
                        if (alfForm.ShowDialog(this) == DialogResult.OK)
                        {
                            String selected = alfForm.getSelected();
                            if (selected != null)
                            {
                                ActionTemplate newAction = table.createActionByNote(selected);
                                parent.addSubAction(newAction, actionTemplate, true);
                                treeView1.SelectedNode = newAction.getTreeNode();
                            }
                        }
                    }
                    else if (item.Text == "新建动作(下方)")
                    {
                        if (parent.actionList <= 1) return;
                        if (!parent.isContainGridSubAction())
                        {
                            alfForm.setItems(table.getActionsByIgnoreList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1,
                                ActionTemplateTable.EActionFilterType.ACTION_LIST_2));
                        }
                        else
                        {
                            alfForm.setItems(table.getActionsByIgnoreList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1,
                                ActionTemplateTable.EActionFilterType.ACTION_LIST_2,
                                ActionTemplateTable.EActionFilterType.GRID));
                        }
                        if (alfForm.ShowDialog(this) == DialogResult.OK)
                        {
                            String selected = alfForm.getSelected();
                            if (selected != null)
                            {
                                ActionTemplate newAction = table.createActionByNote(selected);
                                parent.addSubAction(newAction, actionTemplate, false);
                                treeView1.SelectedNode = newAction.getTreeNode();
                            }
                        }
                    }
                    else if (item.Text == "粘贴动作(上方)")
                    {
                        if (parent.actionList <= 1) return;
                        if (curToCopyed is ActionTemplate)
                        {
                            ActionTemplate newAction = ((ActionTemplate)curToCopyed).copy(table);
                            parent.addSubAction(newAction, actionTemplate, true);
                            treeView1.SelectedNode = newAction.getTreeNode();
                        }
                    }
                    else if (item.Text == "粘贴动作(下方)")
                    {
                        if (parent.actionList <= 1) return;
                        if (curToCopyed is ActionTemplate)
                        {
                            ActionTemplate newAction = ((ActionTemplate)curToCopyed).copy(table);
                            parent.addSubAction(newAction, actionTemplate, false);
                            treeView1.SelectedNode = newAction.getTreeNode();
                        }
                    }
                    else if (item.Text == "上移动作")
                    {
                        parent.moveSubAction(actionTemplate, true);
  
                    }
                    else if (item.Text == "下移动作")
                    {
                        parent.moveSubAction(actionTemplate, false);
                    }
                    else if (item.Text == "添加父动作")
                    {
                        if (actionTemplate.eActionType == EActionType.CCActionInstant)
                        {
                            alfForm.setItems(table.getActionsByPerferList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.SPAWN_AND_SEQUENCE));
                        } else {
                            alfForm.setItems(table.getActionsByPerferList(curEditAEData.eType, ActionTemplateTable.EActionFilterType.ACTION_LIST_1,
                                ActionTemplateTable.EActionFilterType.ACTION_LIST_2));
                        }

                        if (alfForm.ShowDialog(this) == DialogResult.OK)
                        {
                            String selected = alfForm.getSelected();
                            if (selected != null)
                            {
                                ActionTemplate newAction = table.createActionByNote(selected);
                                parent.replaceAction(actionTemplate, newAction);
                                newAction.addSubAction(actionTemplate);
                                treeView1.SelectedNode = actionTemplate.getTreeNode();
                                newAction.getTreeNode().ExpandAll();
                            }
                        }
                    }
                }
            }

            curEditAEData.recalcAndUpdate();
            if (__isOpDirty) { 
                setDirty(__isOpDirty);
            }
            curTreeNodeBindedObject = null;
            treeView1.Update();
        }

        private void treeView_KeyUp(object sender, KeyEventArgs e)
        {
            TreeNode node = treeView1.SelectedNode;
            if (node == null) return;

            curTreeNodeBindedObject = curEditAEData.getNodeBindedObject(node);
            if (curTreeNodeBindedObject == null) return;

            if (e.KeyCode == Keys.Enter) { 
                if (curTreeNodeBindedObject is AEData)
                {

                }
                else if (curTreeNodeBindedObject is AEConfig)
                {
                    curEditAEData.createConfigPropForm(this).ShowDialog(this);
                }
                else if (curTreeNodeBindedObject is AESprite)
                {
                    curEditAEData.createSpritePropForm((AESprite)curTreeNodeBindedObject, this).ShowDialog(this);
                }
                else if (curTreeNodeBindedObject is ActionTemplate)
                {
                    new ActionPropForm((ActionTemplate)curTreeNodeBindedObject, this).ShowDialog(this);
                }
            }
            else if (e.KeyCode == Keys.W)
            {
                if (curTreeNodeBindedObject is AESprite)
                {
                    this.curEditAEData.moveSprite((AESprite)curTreeNodeBindedObject, true);
                    treeView1.SelectedNode = ((AESprite)curTreeNodeBindedObject).getTreeNode();
                }
                else if (curTreeNodeBindedObject is ActionTemplate)
                {
                    ActionTemplate actionTemplate = (ActionTemplate)curTreeNodeBindedObject;
                    Object parentBindedObject = curEditAEData.getNodeBindedObject(actionTemplate.getTreeNode().Parent);
                    if (parentBindedObject is AESprite)
                    {
                        ((AESprite)parentBindedObject).moveAction(actionTemplate, true);
                        treeView1.SelectedNode = ((ActionTemplate)curTreeNodeBindedObject).getTreeNode();
                    }
                    else if (parentBindedObject is ActionTemplate)
                    {
                        ((ActionTemplate)parentBindedObject).moveSubAction(actionTemplate, true);
                        treeView1.SelectedNode = ((ActionTemplate)curTreeNodeBindedObject).getTreeNode();
                    }
                }
                setDirty(true);
                curEditAEData.recalcAndUpdate();
            }
            else if (e.KeyCode == Keys.S)
            {
                if (curTreeNodeBindedObject is AESprite)
                {
                    this.curEditAEData.moveSprite((AESprite)curTreeNodeBindedObject, false);
                    treeView1.SelectedNode = ((AESprite)curTreeNodeBindedObject).getTreeNode();
                }
                else if (curTreeNodeBindedObject is ActionTemplate)
                {
                    ActionTemplate actionTemplate = (ActionTemplate)curTreeNodeBindedObject;
                    Object parentBindedObject = curEditAEData.getNodeBindedObject(actionTemplate.getTreeNode().Parent);
                    if (parentBindedObject is AESprite)
                    {
                        ((AESprite)parentBindedObject).moveAction(actionTemplate, false);
                        treeView1.SelectedNode = ((ActionTemplate)curTreeNodeBindedObject).getTreeNode();
                    }
                    else if (parentBindedObject is ActionTemplate)
                    {
                        ((ActionTemplate)parentBindedObject).moveSubAction(actionTemplate, false);
                        treeView1.SelectedNode = ((ActionTemplate)curTreeNodeBindedObject).getTreeNode();
                    }
                }
                setDirty(true);
                curEditAEData.recalcAndUpdate();
            }
        }

        private void treeView_NodeClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (treeView1 != sender) return;
            Console.WriteLine("treeView_NodeClick");

            Point point = treeView1.PointToClient(Cursor.Position);
            TreeViewHitTestInfo info = treeView1.HitTest(point.X, point.Y);
            TreeNode node = info.Node;
            if (node == null) return;

            if (MouseButtons.Right == e.Button) {
                treeView1.SelectedNode = node;

                curTreeNodeBindedObject = curEditAEData.getNodeBindedObject(node);
                if (curTreeNodeBindedObject == null) return;

                this.nodeContextMenu.MenuItems.Clear();

                this.nodeContextMenu.MenuItems.Add(node.Text);
                this.nodeContextMenu.MenuItems.Add("-");
                this.nodeContextMenu.MenuItems[0].Enabled = false;
                if (curTreeNodeBindedObject is AEData)
                { // nothing
                    this.nodeContextMenu.MenuItems.Add("新建精灵");
                }
                else if (curTreeNodeBindedObject is AEConfig) 
                {
                    this.nodeContextMenu.MenuItems.Add("修改配置");
                }
                else if (curTreeNodeBindedObject is AESprite)
                {
                    AESprite __aeSprite = (AESprite)curTreeNodeBindedObject;
                    AESprite __upperSprite = curEditAEData.getUpperSprite(__aeSprite);
                    this.nodeContextMenu.MenuItems.Add("修改精灵");
                    this.nodeContextMenu.MenuItems.Add("覆盖动作 -- 使用复制").Enabled = (curToCopyed is ActionTemplate);
                    if (__aeSprite._canDelete)
                    {
                        this.nodeContextMenu.MenuItems.Add("删除精灵");
                    }
                    if (__aeSprite._canMove)
                    {
                        if (__upperSprite == null || __upperSprite._canMove) { 
                            this.nodeContextMenu.MenuItems.Add("上移精灵");
                        }
                        this.nodeContextMenu.MenuItems.Add("下移精灵");
                        this.nodeContextMenu.MenuItems.Add("新建精灵(上方)");
                        this.nodeContextMenu.MenuItems.Add("新建精灵(下方)");
                        this.nodeContextMenu.MenuItems.Add("-");
                    }

                    this.nodeContextMenu.MenuItems.Add("新建动作");
                    if (curToCopyed is ActionTemplate) {
                        this.nodeContextMenu.MenuItems.Add("当前复制: " + ((ActionTemplate)curToCopyed).getTreeNode().Text).Enabled = false;
                        this.nodeContextMenu.MenuItems.Add("粘贴动作");
                    }
                    this.nodeContextMenu.MenuItems.Add("-");
                    if (__aeSprite._canMove)
                    {
                        this.nodeContextMenu.MenuItems.Add("复制精灵");
                    }
                    if (curToCopyed != null && curToCopyed is AESprite)
                    {
                        this.nodeContextMenu.MenuItems.Add("当前复制: " + ((AESprite)curToCopyed).getTreeNode().Text).Enabled = false;
                        this.nodeContextMenu.MenuItems.Add("粘贴精灵(上方)");
                        this.nodeContextMenu.MenuItems.Add("粘贴精灵(下方)");
                    }
                }
                else if (curTreeNodeBindedObject is ActionTemplate)
                {
                    ActionTemplate actionTemplate = (ActionTemplate)curTreeNodeBindedObject;
                    Object parentBindedObject = curEditAEData.getNodeBindedObject(actionTemplate.getTreeNode().Parent);
                    this.nodeContextMenu.MenuItems.Add("修改动作").Enabled = (actionTemplate.actionParams.Count > 0);
                    this.nodeContextMenu.MenuItems.Add("覆盖动作 -- 使用复制").Enabled = (curToCopyed is ActionTemplate);
                    if (actionTemplate.actionList == 1 && actionTemplate.subActionList.Count == 0 
                        || actionTemplate.actionList > 1)
                    {
                        this.nodeContextMenu.MenuItems.Add("添加子动作");
                    }
                    if (parentBindedObject is ActionTemplate)
                    {
                        if (((ActionTemplate)parentBindedObject).subActionList.Count > 1) { 
                            this.nodeContextMenu.MenuItems.Add("删除动作");
                            this.nodeContextMenu.MenuItems.Add("上移动作");
                            this.nodeContextMenu.MenuItems.Add("下移动作");
                        }
                        else if (actionTemplate.subActionList.Count == 1)
                        {
                            this.nodeContextMenu.MenuItems.Add("删除动作");
                        }

                        if (((ActionTemplate)parentBindedObject).actionList > 1)
                        {
                            this.nodeContextMenu.MenuItems.Add("新建动作(上方)");
                            this.nodeContextMenu.MenuItems.Add("新建动作(下方)");
                            if (curToCopyed is ActionTemplate) { 
                                this.nodeContextMenu.MenuItems.Add("粘贴动作(上方)");
                                this.nodeContextMenu.MenuItems.Add("粘贴动作(下方)");
                            }
                        }
                    }
                    else 
                    {
                        this.nodeContextMenu.MenuItems.Add("删除动作");
                        this.nodeContextMenu.MenuItems.Add("上移动作");
                        this.nodeContextMenu.MenuItems.Add("下移动作");
                    }
                    this.nodeContextMenu.MenuItems.Add("添加父动作");
                    this.nodeContextMenu.MenuItems.Add("-");
                    this.nodeContextMenu.MenuItems.Add("复制动作");
                    if (curToCopyed != null && curToCopyed is ActionTemplate)
                    {
                        this.nodeContextMenu.MenuItems.Add("当前复制: " + ((ActionTemplate)curToCopyed).getTreeNode().Text).Enabled = false;

                        if (actionTemplate.actionList == 1 && actionTemplate.subActionList.Count == 0 || actionTemplate.actionList > 1)
                        {
                            this.nodeContextMenu.MenuItems.Add("粘贴子动作");
                        }
                    }
                }

                // 0 for Name
                for (int i = 1; i < this.nodeContextMenu.MenuItems.Count; i++)
                {
                    this.nodeContextMenu.MenuItems[i].Click += new EventHandler(contextmenu_Click);
                }
            }

            this.treeView1.Refresh();
        }

        private void btnNew_Click(object sender, EventArgs e)
        {
            if (isDirty && curEditAEData != null)
            { // Ask Is Needed Saving ??
                DialogResult dialogResult = MessageBox.Show("请问是否需要保存 " + curEditAEData.fileName + "?", "确认下 (^_^)", MessageBoxButtons.YesNoCancel);
                if (dialogResult == DialogResult.Cancel)
                {
                    return;
                } else if (dialogResult == DialogResult.Yes)
                {
                    curEditAEData.WriteToFile(curEditAEData.fileName);
                }
            }

            AETypeForm aeTypeForm = new AETypeForm();
            aeTypeForm.ShowDialog();
            if (aeTypeForm.DialogResult == DialogResult.OK)
            {
                setAEData(new AEData(aeTypeForm.getType()));

                isDirty = false;
            }
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            if (curEditAEData == null) return;

            if (!curEditAEData.isHasFile)
            {
                btnSaveTo_Click(sender, e);
            }
            else
            {
                curEditAEData.WriteToFile(curEditAEData.fileName);
                isDirty = false;

                updateStatus();
            }
        }


        private void btnSaveTo_Click(object sender, EventArgs e) {
            if (getSaveFileDialog(curEditAEData.eType).ShowDialog() == DialogResult.OK)
            {
                curEditAEData.WriteToFile(getSaveFileDialog(curEditAEData.eType).FileName);
                isDirty = false;

                updateStatus();
            }
        }

        private void btnSimulate_Click(object sender, EventArgs e)
        {
            if (!curEditAEData.isHasFile) return;
            if (isDirty)
            {
                curEditAEData.WriteToFile(curEditAEData.fileName);
                isDirty = false;
                updateStatus();
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
            GlobalConf.instance.getWindowResolution(ref width, ref height, ref scale);
            Info.Arguments = " " + width + " " + height + " " + scale + " " + curEditAEData.fileName + " ";
            simulatedProcess = System.Diagnostics.Process.Start(Info);

            // p.Exited += exist事件
        }

        private void btnOpen_Click(object sender, EventArgs e)
        {
            if (isDirty && curEditAEData != null)
            { // Ask Is Needed Saving ??
                DialogResult dialogResult = MessageBox.Show("请问是否需要保存 " + curEditAEData.fileName + "?", "确认下 (^_^)", MessageBoxButtons.YesNoCancel);
                if (dialogResult == DialogResult.Cancel)
                {
                    return;
                }
                else if (dialogResult == DialogResult.Yes)
                {
                    curEditAEData.WriteToFile(curEditAEData.fileName);
                }
            }

            AETypeForm aeTypeForm = new AETypeForm();
            aeTypeForm.ShowDialog();
            if (aeTypeForm.DialogResult == DialogResult.OK)
            {
                if (getOpenFileDialog(aeTypeForm.getType()).ShowDialog() == DialogResult.OK)
                {
                    String curfileName = getOpenFileDialog(aeTypeForm.getType()).FileName;
                    AEData aeData = AEData.create(curfileName, table);
                    if (aeData != null)
                    {
                        setAEData(aeData);
                    }
                }   
            }

            updateStatus();
        }

        private void btnRY_Click(object sender, EventArgs e)
        {
            regionMoveDialog.ShowDialog(this);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (particleDesignDialog.Visible == false)
            {
                particleDesignDialog = new ParticleDesign();
                particleDesignDialog.Visible = true;
            }
            else
            {
                particleDesignDialog.Show();
                particleDesignDialog.Activate();
            }
        }

        private void btnSetting_Click(object sender, EventArgs e)
        {
            new GlobalConfForm().ShowDialog();
        }

        private void btnTimeSpan_Click(object sender, EventArgs e)
        {
            if (TimeSpanForm.instance == null)
            {
                new TimeSpanForm().Show();
            }
            else
            {
                TimeSpanForm.instance.Activate();
            }
        }
    }
}
