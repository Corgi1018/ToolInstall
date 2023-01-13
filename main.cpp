#include <boost/process.hpp>

#include "src/file.h"
#include <cstdlib>
#include <sstream>
#include <string>

// void installShare()
// {

//     MayaGather::folder f;
//     std::filesystem::path fromPath{"//192.168.10.240/public/mygwaibao2/Tool/share"};
//     std::filesystem::path toPath = f.getDocumentPath() / "Maya" / "share";
//     std::filesystem::path InDirectory = f.getDocumentPath() / "maya" / "2018" / "zh_CN" / "prefs" / "shelves";
//     std::string fileName{"shelf_Share.mel"};
//     std::string share_header = R"(
//     global proc shelf_Share () {

//         shelfButton
//             -enableCommandRepeat 1
//             -enable 1
//             -width 21
//             -height 21
//             -manage 1
//             -visible 1
//             -preventOverride 0
//             -annotation "User Script"
//             -enableBackground 0
//             -backgroundColor 0 0 0
//             -highlightColor 0.321569 0.521569 0.65098
//             -align "center"
//             -label "install"
//             -labelOffset 0
//             -rotation 0
//             -flipX 0
//             -flipY 0
//             -useAlpha 1
//             -font "plainLabelFont"
//             -overlayLabelColor 0.8 0.8 0.8
//             -overlayLabelBackColor 0 0 0 0.5
//             -image "activeSelectedAnimLayer.png"
//             -image1 "activeSelectedAnimLayer.png"
//             -style "iconOnly"
//             -marginWidth 1
//             -marginHeight 1
//     )";

//     std::stringstream share_path;
//     share_path << toPath;
//     std::string share_command_path = share_path.str();
//     share_command_path.erase(remove(share_command_path.begin(), share_command_path.end(), '\"'),
//     share_command_path.end());
//     ;
//     std::stringstream share_command;
//     share_command << R"(
//             -command "import maya.cmds as cmds\nimport sys\nimport maya.mel as mel\nsys.path.append(r')";
//     share_command << share_command_path;
//     share_command << "\')";
//     share_command << R"(\nimport systemUpdate.project_UpdateWin_gz as puw ;reload(puw)\nqqq =
//     puw.mainUpdateWins()\nqqq._mianWins())"; share_command << "\"";

//     std::string share_end = R"(
//             -sourceType "python"
//             -commandRepeatable 1
//             -flat 1
//         ;
//     }
//     )";
//     std::string InContent = share_header + share_command.str() + share_end;
//     f.createShelf(fileName, InDirectory, InContent);
//     std::cout << "path:" << toPath << '\n';
//     try
//     {
//         f.copyFile(fromPath, toPath);
//     }
//     catch (std::filesystem::filesystem_error const &ex)
//     {
//         std::cout << "what():" << ex.what() << '\n';
//     }
// }

// void installRigtool()
// {

//     MayaGather::folder f;
//     std::filesystem::path fromPath1{"//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/packages"};
//     std::filesystem::path fromPath2{"//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/rez"};
//     std::filesystem::path fromPath3{"//192.168.10.240/public/mygwaibao2/Tool/rigTool/netease_heymaker"};
//     std::filesystem::path fromPath4{"//192.168.10.240/public/mygwaibao2/Tool/rigTool/maya2018.bat"};
//     std::filesystem::path userPath = getenv("USERPROFILE");
//     std::cout << "userprofile:" << userPath << std::endl;
//     std::filesystem::path toPath1 = userPath / "packages";
//     std::filesystem::path toPath2 = "D:/rez";
//     std::filesystem::path toPath3 = f.getDocumentPath() / "maya" / "netease_heymaker";
//     std::filesystem::path toPath4 = userPath / "Desktop";
//     std::string fileName{"shelf_Rigtool.mel"};
//     std::string rig_header = R"()";
//     try
//     {
//         f.copyFile(fromPath1, toPath1);
//         f.copyFile(fromPath2, toPath2);
//         f.copyFile(fromPath3, toPath3);
//         f.copyFile(fromPath4, toPath4);
//     }
//     catch (std::filesystem::filesystem_error const &ex)
//     {
//         std::cout << "what():" << ex.what() << '\n';
//     }
// }

int main(int, char **) {
  MayaGather::folder f;
  std::vector<std::filesystem::path> fromPath{
      "//192.168.10.240/public/mygwaibao2/Tool/share",
      "//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/packages",
      "//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/rez",
      "//192.168.10.240/public/mygwaibao2/Tool/rigTool/netease_heymaker",
      "//192.168.10.240/public/mygwaibao2/Tool/rigTool/maya2018.bat"};
  std::vector<std::filesystem::path> toPath{
      f.getEnvPath(FOLDERID_Documents) / "Maya" / "share", f.getEnvPath(FOLDERID_Profile) / "packages", "D:/rez",
      f.getEnvPath(FOLDERID_Documents) / "maya" / "netease_heymaker", f.getEnvPath(FOLDERID_Profile) / "Desktop"};
  std::vector<std::string> toolName{"shelf_Share.mel", "shelf_Rigtool.mel", "shelf_test3.mel"};

  MayaGather::Mel shareMel{
      "shelf_test3", "share", "activeSelectedAnimLayer.png", "activeSelectedAnimLayer.png",
      fmt::format(
          "import maya.cmds as cmds\\nimport sys\\nimport maya.mel as mel\\nsys.path.append(r'{}')\\nimport "
          "systemUpdate.project_UpdateWin_gz as puw ;reload(puw)\\nqqq = puw.mainUpdateWins()\\nqqq._mianWins()",
          toPath[0].generic_string()
      )};
  std::filesystem::path path = f.getEnvPath(FOLDERID_Documents) / "maya" / "2018" / "zh_CN" / "prefs" / "shelves";
  try {
    f.createShelf(toolName[2], shareMel, path);
  } catch (std::filesystem::filesystem_error const &ex) {
    std::cout << "what():" << ex.what() << '\n';
  };
}
