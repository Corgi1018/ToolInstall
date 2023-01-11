#pragma once
#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <sstream>
#include <string> 
#include <boost/process.hpp>
#include "src/file.h"
void installShare(){

    MayaGather::folder f;
    std::filesystem::path fromPath{"//192.168.10.240/public/mygwaibao2/Tool/share"};
    std::filesystem::path toPath=f.getDocumentPath() / "Maya" / "share";
    std::filesystem::path InDirectory=f.getDocumentPath()/"maya"/"2018"/"zh_CN"/"prefs"/"shelves";
    std::string fileName{"shelf_Share.mel"};
    std::string rig_header=R"(
    global proc shelf_Share () {


        shelfButton
            -enableCommandRepeat 1
            -enable 1
            -width 21
            -height 21
            -manage 1
            -visible 1
            -preventOverride 0
            -annotation "User Script" 
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
            -image "activeSelectedAnimLayer.png" 
            -image1 "activeSelectedAnimLayer.png" 
            -style "iconOnly" 
            -marginWidth 1
            -marginHeight 1
    )";

    std::stringstream rig_path;
    rig_path<<toPath;
    std::string rig_command_path=rig_path.str();
    rig_command_path.erase(remove( rig_command_path.begin(), rig_command_path.end(), '\"' ),rig_command_path.end());;
    std::stringstream rig_command;
    rig_command<<R"(
            -command "import maya.cmds as cmds\nimport sys\nimport maya.mel as mel\nsys.path.append(r')";
    rig_command<<rig_command_path;
    rig_command<<"\'\)";
    rig_command<<R"(\nimport systemUpdate.project_UpdateWin_gz as puw ;reload(puw)\nqqq = puw.mainUpdateWins()\nqqq._mianWins())";
    rig_command<<"\"";

    std::string rig_end=R"(
            -sourceType "python" 
            -commandRepeatable 1
            -flat 1
        ;
    }
    )";
    std::string InContent=rig_header+rig_command.str()+rig_end;
    f.setMel(fileName,InDirectory,InContent);
    std::cout<<"path:"<<toPath<<'\n';
    try
    {
        f.copyFile(fromPath, toPath);
    }
    catch (std::filesystem::filesystem_error const &ex)
    {
        std::cout << "what():" << ex.what() << '\n';
    }

}

void installRigtool(){

    MayaGather::folder f;
    std::filesystem::path fromPath1{"//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/packages"};
    std::filesystem::path fromPath2{"//192.168.10.240/public/mygwaibao2/Tool/rigTool/tools_env/rez"};
    std::filesystem::path fromPath3{"//192.168.10.240/public/mygwaibao2/Tool/rigTool/netease_heymaker"};
    std::filesystem::path userPath = getenv("USERPROFILE");
    std::cout<<"userprofile:"<<userPath<<std::endl;
    std::filesystem::path toPath1=userPath /"package";
    std::filesystem::path toPath2="D:/rez";
    std::filesystem::path toPath3=f.getDocumentPath()/"maya"/"netease_heymaker";
    // try
    // {
    //     f.copyFile(fromPath1,toPath1);
    //     f.copyFile(fromPath2,toPath2);
    //     f.copyFile(fromPath3,toPath3);
    // }
    // catch (std::filesystem::filesystem_error const &ex)
    // {
    //     std::cout << "what():" << ex.what() << '\n';
    // }



}

int main(int, char **)
{
    namespace bp = boost::process; 
    bp::child c("D:/rez/Scripts/rez/rez.exe");
    c.wait();
    int result=c.exit_code();
    return result;
    

}

