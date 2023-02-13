import sys,os; sys.path.append(r'C:\Users\{user}\Documents\maya\2018\scripts'.format(user=os.environ['USERNAME']))


import cgyun.link
with cgyun.link.enable_default():
    import rigstorm.LZ_cartonFace.add_stretch_win
    import maya_pipe.tools.rig.dyn_system as dyn_system
    dyn_system.main()