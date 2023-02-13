#include <iostream>
constexpr std::pair<std::string_view, std::string_view> path[]{
    {"//192.168.10.240/public/mygwaibao2/Tool/share", "maya/share"},
    {"//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/packages", "packages"},
    {"//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/rez", "D:/rez"},
    {"//192.168.10.240/public/mygwaibao2/Tool/rigTool/netease_heymaker", "maya/netease_heymaker"},
    {"//192.168.10.240/public/mygwaibao2/Tool/rigTool/maya2018.bat", "Desktop"},
    {"//192.168.10.240/public/mygwaibao2/Tool/MayaGather_2018.mll","maya/modules/plug-ins"},
    {"//192.168.10.240/public/mygwaibao2/Tool/MayaGather_2018.mod","maya/modules"}};

constexpr std::string_view rig_args{
    "//192.168.10.240/public/mygwaibao2/Tool/rigTool/CGMeshInstaller v0.6.2.exe /exenoui /qn"};
