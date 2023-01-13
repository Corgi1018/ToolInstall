#include "file.h"
#include <algorithm>
#include <sstream>
#include <string>
namespace fs = std::filesystem;
struct fsException : public fs::filesystem_error
{
    fsException();
};

fsException::fsException() : fs::filesystem_error(std::string{""}, std::error_code{}){};

bool MayaGather::folder::folderExists(const fs::path &in_path)
{
    std::cout << in_path;
    auto l_r = fs::exists(in_path);
    return l_r;
};

void MayaGather::folder::copyFile(const fs::path &in_from, const fs::path &in_to)
{
    fs::create_directories(in_to);
    const auto copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;
    fs::copy(in_from, in_to, copyOptions);
}
fs::path MayaGather::folder::getEnvPath(const KNOWNFOLDERID &in_env)
{
    /// 这里我们手动做一些工作
    /// 获取环境变量 FOLDERID_Documents
    PWSTR pManager;
    SHGetKnownFolderPath(in_env, NULL, nullptr, &pManager);
    auto k_path = fs::path{pManager};
    CoTaskMemFree(pManager);
    return k_path;
}

void MayaGather::folder::createShelf(std::string& in_shelfname,struct Mel mel,std::filesystem::path &in_directory)
{
    
    std::string in_content=fmt::format(
    R"(global proc {}() {{
        global string $gBuffStr;
        global string $gBuffStr0;
        global string $gBuffStr1;


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
    }}
    )",mel.in_fun,mel.in_button,mel.in_image,mel.in_image1,mel.in_buttonCommand);
   
    fs::create_directories(in_directory);
    std::ofstream ostrm(in_directory / in_shelfname, std::ios::out);
    ostrm << in_content;
}

// void MayaGather::folder::installTool(std::vector<std::string> &in_name, std::vector<std::filesystem::path> &from_path, std::vector<std::filesystem::path> &to_path, std::vector<std::filesystem::path> &in_directory, std::vector<std::string> &in_content)
// {
//     for (int i = 0; i < from_path.size(); i++)
//         copyFile(from_path[i], to_path[i]);
//     for (int j = 0; j < in_directory.size(); j++)
//         createShelf(in_name[j], in_directory[j], in_content[j]);
// }