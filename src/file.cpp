#include "file.h"
#include <fstream>
#include <ShlObj.h>
#include <algorithm>
#include <sstream>
#include <string>
namespace fs = std::filesystem;
struct fsException : public fs::filesystem_error
{
    fsException();
};
 
fsException::fsException():fs::filesystem_error(std::string{""},std::error_code{}){};

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
fs::path MayaGather::folder::getDocumentPath()
{
    /// 这里我们手动做一些工作
    /// 获取环境变量 FOLDERID_Documents
    PWSTR pManager;
    SHGetKnownFolderPath(FOLDERID_Documents, NULL, nullptr, &pManager);
    auto k_path = fs::path{pManager};
    CoTaskMemFree(pManager);
    return k_path;
}
void MayaGather::folder::setMel(std::string& in_name,std::filesystem::path& in_directory,std::string& in_content){
    fs::create_directories(in_directory);
    std::ofstream ostrm(in_directory/in_name,std::ios::out); 
    ostrm<<in_content;
}
// void MayaGather::folder::startThread(){
//     bp::child c("D:/rez/Scripts/rez/rez.exe", "main.cpp");
// }