#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <boost/process.hpp>
// #include <boost/test/tools/interface.hpp>
// #include <boost/test/unit_test_log.hpp>
 
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
// struct startThread{
//     std::shared_ptr<boost::process::child>child;
//     std::shared_ptr<boost::process::async_pipe> out_attr;
//     std::shared_ptr<boost::process::async_pipe> err_attr;
//     std::shared_ptr<boost::asio::streambuf>out_str{};
//     std::shared_ptr<boost::asio::streambuf>err_str{};

//     explicit startThread();
//     void run(const std::vector<std::string>& in_args);
//     static void read_(
//       const std::shared_ptr<boost::process::pipe>& in_pipe, const std::shared_ptr<boost::asio::streambuf>& in_str
//   );
// };
};
