#include "maya_plugin.h"
const std::filesystem::path frompath[]{
    "//192.168.10.240/public/mygwaibao2/Tool/share",
    "//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/packages",
    "//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/rez",
    "//192.168.10.240/public/mygwaibao2/Tool/rigTool/netease_heymaker",
    "//192.168.10.240/public/mygwaibao2/Tool/rigTool/maya2018.bat"};
const std::filesystem::path topath[]{
    maya::get_env_path(FOLDERID_Documents) / "Maya" / "share",
    maya::get_env_path(FOLDERID_Profile) / "packages",
    "D:/rez",
    maya::get_env_path(FOLDERID_Documents) / "maya" / "netease_heymaker",
    maya::get_env_path(FOLDERID_Profile) / "Desktop",
};
constexpr std::pair<std::string_view, std::string_view> path[]{
    {"//192.168.10.240/public/mygwaibao2/Tool/share", "maya/share"},
    {"//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/packages", "packages"},
    {"//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/rez", "D:/rez"},
    {"//192.168.10.240/public/mygwaibao2/Tool/rigTool/netease_heymaker", "maya/netease_heymaker"},
    {"//192.168.10.240/public/mygwaibao2/Tool/rigTool/maya2018.bat", "Desktop"}};
const std::string melname{"shelf_Tool.mel"};
const std::filesystem::path dir{
    maya::get_env_path(FOLDERID_Documents) / "maya" / "2018" / "zh_CN" / "prefs" / "shelves"};

const maya::Mel rig_button{
    "HY_rig", "bind.png", "bind.png",
    "import sys,os; "
    "sys.path.append(r'C:\\\\Users\\\\{user}\\\\Documents\\\\maya\\\\2018\\\\scripts'.format(user=os.environ['"
    "USERNAME']))"
    "\\n\\n\\nimport cgyun.link\\nwith cgyun.link.enable('http://riggerstankplugin.cgyun.cn:18889'):\\nimport "
    "rigstorm.LZ_cartonFace.add_stretch_win\\nimport tools_personal.LZ_Tools_UI as "
    "heymaker\\nheymaker.LZ_tools().LZ_Tools_UI()"};
const maya::Mel dyn_button{
    "HY_dyn", "rigidBind.png", "rigidBind.png",
    "import sys,os; "
    "sys.path.append(r'C:\\\\Users\\\\{user}\\\\Documents\\\\maya\\\\2018\\\\scripts'.format(user=os.environ['"
    "USERNAME']))"
    "\\n\\n\\n\\nimport cgyun.link\\nwith cgyun.link.enable_default():\\n    import "
    "rigstorm.LZ_cartonFace.add_stretch_win\\n    import maya_pipe.tools.rig.dyn_system as dyn_system\\n    "
    "dyn_system.main()"};
const maya::Mel share_button{
    "share", "activeSelectedAnimLayer.png", "activeSelectedAnimLayer.png",
    fmt::format(
        "import maya.cmds as cmds\\nimport sys\\nimport maya.mel as mel\\nsys.path.append(r'{}')\\nimport "
        "systemUpdate.project_UpdateWin_gz as puw ;reload(puw)\\nqqq = puw.mainUpdateWins()\\nqqq._mianWins()",
        topath[0].generic_string()
    )};
const std::string mel_content{
    R"(global proc {}() {{
        global string $gBuffStr;
        global string $gBuffStr0;
        global string $gBuffStr1;


       {}
    }}
    )"};
const std::string mel_fun{"shelf_Tool"};
const std::vector<std::string> rig_args{
    "//192.168.10.240/public/mygwaibao2/Tool/rigTool/CGMeshInstaller v0.6.2.exe /exenoui /qn"};
const std::string button_content{
    R"(
        shelfButton
            -enableCommandRepeat 1
            -enable 1
            -width 21
            -height 21
            -manage 1
            -visible 1
            -preventOverride 0
            -annotation "{}" 
            -enableBackground 0
            -backgroundColor 0 0 0 
            -highlightColor 0.321569 0.521569 0.65098 
            -align "center" 
            -label "install" 
            -labelOffset 0
            -rotation 0
            -flipX 0
            -flipY 0
            -useAlpha 1
            -font "plainLabelFont" 
            -overlayLabelColor 0.8 0.8 0.8 
            -overlayLabelBackColor 0 0 0 0.5 
            -image "{}" 
            -image1 "{}" 
            -style "iconOnly" 
            -marginWidth 1
            -marginHeight 1
            -command "{}"
            -sourceType "python" 
            -commandRepeatable 1
            -flat 1
    ;
    )"};