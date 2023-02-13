import shelf
import maya.cmds as cmd
import python.shareButton
# import python.rigButton
# import python.dynButton

class Toolshelf(shelf.Shelf):
    def build(self):
        self.addButton("share",icon="alignOnMax.png",command="print")
        self.addButton("rig",icon="addSkinInfluence.png",command=self.rigButton)
        self.addButton("dyn",icon="rigidBind.png",command=self.dynButton)

    def shareButton(self):
        shareButton()
    def rigButton(self):
        rigButton()
    def dynButton(self):
        dynButton()






    
