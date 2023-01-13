#include <iostream>
#include <filesystem>
#include <fstream>
#include <ShlObj.h>
#include <fmt/core.h>
// #include <boost/test/tools/interface.hpp>
// #include <boost/test/unit_test_log.hpp>
 
namespace MayaGather{
class folder {

    
    public:
    void createShelf(std::string& in_shelfname,struct Mel mel,std::filesystem::path& in_directory);
    void createDir(std::filesystem::path& in_path);
    void copyFile(const std::filesystem::path& in_from,const std::filesystem::path& in_to);
    bool folderExists(const std::filesystem::path&in_path);
    std::filesystem::path getEnvPath(const KNOWNFOLDERID& in_env);
    void installTool(std::vector<std::string> &in_name,std::vector<std::filesystem::path>& from_path,std::vector<std::filesystem::path>& to_path,std::vector<std::filesystem::path>& in_directory, std::vector<std::string> &in_content);
    private:
    };
    struct Mel{
    std::string in_fun;
    std::string in_button;
    std::string in_image;
    std::string in_image1;
    std::string in_buttonCommand;
    };

};
