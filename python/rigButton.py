import sys,os; sys.path.append(r'C:\Users\{user}\Documents\maya\2018\scripts'.format(user=os.environ['USERNAME']))

import cgyun.link
with cgyun.link.enable('http://riggerstankplugin.cgyun.cn:18889'):
    import rigstorm.LZ_cartonFace.add_stretch_win
    import tools_personal.LZ_Tools_UI as heymaker
    heymaker.LZ_tools().LZ_Tools_UI()