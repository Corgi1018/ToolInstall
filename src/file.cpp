#include "file.h"
#include <fstream>
#include <ShlObj.h>
#include <algorithm>
namespace fs = std::filesystem;
void folder::Createdir(fs::path Path)
{
    /**
     * 异常不能非常量引用
     * 异常不捕获基类异常
    */
    try
    {
        folder_exists(Path);
    }
    catch (std::exception &e)
    {   
        std::cout<<e.what();
        fs::create_directory(Path);
    }
}
void folder::folder_exists(const fs::path &p, fs::file_status s)
{
    std::cout << p;
    if (fs::status_known(s) ? fs::exists(s) : fs::exists(p))
        std::cout << "exists\n";
    else /// 不抛出基本异常
        throw std::exception{"does not exists\n"};
};


void folder::Copyfile(const fs::path& from,const fs::path& to){
 const auto copyOptions=std::filesystem::copy_options::update_existing
                          |std::filesystem::copy_options::recursive
                          ;
                          /// 不捕获任何异常
    try{
        fs::copy(from,to,copyOptions);
    }
    catch(fs::filesystem_error const& ex){
        std::cout<<"what():"<<ex.what()<<'\n';
        
    }
   
}
fs::path folder::getDocumentPath(){
    /// 这里我们手动做一些工作
    /// 获取环境变量 FOLDERID_Documents
    PWSTR pManager;
    SHGetKnownFolderPath(FOLDERID_Documents, NULL, nullptr, &pManager);
    auto k_path = fs::path{pManager};
    /// 多复制了一次
    auto dir=fs::path(k_path)/"Maya"/"rigTool";
    CoTaskMemFree(pManager);
    return dir;
}

