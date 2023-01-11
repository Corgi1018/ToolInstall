#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
 
namespace MayaGather{
class folder {
    
    public:
    void setMel(std::string& in_name,std::filesystem::path& in_directory,std::string& in_content);
    void createDir(std::filesystem::path& in_path);
    void copyFile(const std::filesystem::path& in_from,const std::filesystem::path& in_to);
    bool folderExists(const std::filesystem::path&in_path);
    std::filesystem::path getDocumentPath();
    void startThread();
    private:
    };
};
