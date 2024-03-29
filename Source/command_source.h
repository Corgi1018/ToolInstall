constexpr std::string_view command{R"(
import maya.cmds as cmd
class Shelf():
    _instances=set()
    def __init__(self,name="Shelf",iconPath=""):
        self._instances.add(self)
        self.name=name
        self.iconPath=iconPath
        self.labelBackground=(0,0,0,0)
        self.labelColour=(.9,.9,.9)
        self._cleanOldShelf()
        cmd.setParent(self.name)
        self.build()
    def build(self):
        pass
    def addButton(self, label, icon="commandButton.png",
                 command="", doubleCommand="",
                 noDefaultPopup_=False):
        cmd.setParent(self.name)
        if icon:
            icon = self.iconPath + icon
        return cmd.shelfButton(width=37, height=37, image=icon, l=label, command=command, dcc=doubleCommand,
                                imageOverlayLabel=label,
                                olb=self.labelBackground, olc=self.labelColour,
                                noDefaultPopup=noDefaultPopup_)
    def addMenuItem(self, parent, label, command="", icon=""):
        '''Adds a shelf button with the specified label, command, double click command and image.'''
        if icon:
            icon = self.iconPath + icon
        return cmd.menuItem(p=parent, l=label, c=command, i="")

    def addSubMenu(self, parent, label, icon=None):
        '''Adds a sub menu item with the specified label and icon to the specified parent popup menu.'''
        if icon:
            icon = self.iconPath + icon
        return cmd.menuItem(p=parent, l=label, i=icon, subMenu=1)

    def _cleanOldShelf(self):
        '''Checks if the shelf exists and empties it if it does or creates it if it does not.'''
        if cmd.shelfLayout(self.name, ex=1):
            if cmd.shelfLayout(self.name, q=1, ca=1):
                for each in cmd.shelfLayout(self.name, q=1, ca=1):
                    cmd.deleteUI(each)
        else:
            cmd.shelfLayout(self.name, p="ShelfLayout")

    @staticmethod
    def create():
        Shelf.__init__("Tool")

    @staticmethod
    def deleteSelf():
        for inst in tuple(Shelf._instances):
            if cmd.shelfLayout(inst.name, ex=1):
                try:
                    cmd.deleteUI(inst.name)
                except RuntimeError:
                    pass
            Shelf._instances.discard(inst)

class Toolshelf(Shelf):
    def build(self):     
        self.addButton("share",icon="alignOnMax.png",command=lambda :self.share_button())
        self.addButton("rig",icon="addSkinInfluence.png",command=lambda :self.rig_button())
        self.addButton("dyn",icon="rigidBind.png",command=lambda :self.dyn_button())
        self.addButton("export_weight",icon="exportSmoothSkin.png",command=lambda :self.export_weight_button())
        self.addButton("copy_weight",icon="copySkinWeight.png",command=lambda :self.copy_weight_button())
        self.addButton("eye",icon="ambientlight.png",command=lambda:self.eye_button())

    def share_button(self):
        import maya.cmds as cmds
        import sys
        import os
        import maya.mel as mel
        sys.path.append(r'C:\Users\{user}\Documents\maya\share'.format(user=os.environ['USERNAME']))  # 更改文件的路径
        import systemUpdate.project_UpdateWin_gz as puw ;reload(puw)
        qqq = puw.mainUpdateWins()
        qqq._mianWins()

    def rig_button(self):
        import sys,os; sys.path.append(r'C:\Users\{user}\Documents\maya\2018\scripts'.format(user=os.environ['USERNAME']))
        import cgyun.link
        with cgyun.link.enable('http://riggerstankplugin.cgyun.cn:18889'):
            import rigstorm.LZ_cartonFace.add_stretch_win
            import tools_personal.LZ_Tools_UI as heymaker
            heymaker.LZ_tools().LZ_Tools_UI()
       
    def dyn_button(self):
        import sys,os; sys.path.append(r'C:\Users\{user}\Documents\maya\2018\scripts'.format(user=os.environ['USERNAME']))
        import cgyun.link
        with cgyun.link.enable_default():
            import rigstorm.LZ_cartonFace.add_stretch_win
            import maya_pipe.tools.rig.dyn_system as dyn_system
            dyn_system.main()
    def export_weight_button(self):
        import sys
        import os
        sys.path.append(r'C:\Users\{user}\Documents\maya\2018\scripts'.format(user=os.environ['USERNAME']))
        import rig_ch.skinClusterWeight as skWt
        skWt.win()

    def copy_weight_button(self):
        import maya.mel as mel 
        mel.eval(r'''
        global proc kk_copyWeightFromOneToManyUI()
        {
            if(`window -ex kk_copyWeightFromOneToMany_Win`)
                deleteUI kk_copyWeightFromOneToMany_Win;
            window kk_copyWeightFromOneToMany_Win;
            columnLayout -adj 1;
            textFieldButtonGrp -cw3 50 100 100 -l "source" -ed 0 -tx "" -bl "road" -bc kk_copyWeightFromOneToMany_road kk_copyWeightFromOneToMany_TFBG;
            button -l "copy" -c kk_copyWeightFromOneToMany;
            showWindow kk_copyWeightFromOneToMany_Win;
        }
        kk_copyWeightFromOneToManyUI;
        global proc kk_copyWeightFromOneToMany_road()
        {
            $sl=`ls -sl`;
            textFieldButtonGrp -e -tx $sl[0] kk_copyWeightFromOneToMany_TFBG;
        }
        global proc kk_copyWeightFromOneToMany()
        {
            $mesh=`textFieldButtonGrp -q -tx kk_copyWeightFromOneToMany_TFBG`;
            $skinNode=`findRelatedSkinCluster($mesh)`;
            for($each in `ls -sl`)
            {
                $sn=`findRelatedSkinCluster($each)`;
                if ($sn == "")
                    {
                    $jntList = `skinCluster -query -influence $skinNode`;  
                    $newSn = `skinCluster -tsb $jntList $each`;
                    copySkinWeights -ss $skinNode -ds $newSn -noMirror -surfaceAssociation closestPoint -influenceAssociation closestJoint;
                    }
                else 
                    copySkinWeights -ss $skinNode -ds $sn -noMirror -surfaceAssociation closestPoint -influenceAssociation closestJoint;
            }
        }
        ''')
    def eye_button(self):
        import sys
        import os
        sys.path.append(r'C:\Users\{user}\Documents\maya\2018\scripts'.format(user=os.environ['USERNAME']))
        import UKDP_AER as aer
        aer.AER()
        aer.AER().UI() # load UI

        
Toolshelf.deleteSelf()     
Toolshelf()
        
    

        )"};

