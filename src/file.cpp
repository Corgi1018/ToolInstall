#include "file.h"
#include <fstream>
#include <ShlObj.h>
#include <algorithm>
#include <sstream>
#include <string>
#include <boost/process/detail/child_decl.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/buffer.hpp>

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
void MayaGather::folder::setMel(std::string &in_name, std::filesystem::path &in_directory, std::string &in_content)
{
    fs::create_directories(in_directory);
    std::ofstream ostrm(in_directory / in_name, std::ios::out);
    ostrm << in_content;
}
//  MayaGather::startThread::startThread()
//     : 
//         child(),
//         out_attr(),
//         err_attr(),
//         out_str(std::make_shared<boost::asio::streambuf>()),
//         err_str(std::make_shared<boost::asio::streambuf>()) {}


// void MayaGather::startThread::run(const std::vector<std::string> &in_args){
//     using namespace std::literals;
//     child=std::make_shared<boost::process::child>(
//         boost::process::system(
//         boost::process::args=in_args,
//         boost::process::std_out>*out_attr,
//         boost::process::std_err>*err_attr
//     ));
//     boost::process::on_exit =
//           [this](int in_exit, const std::error_code& in_error_code) {
//            (!in_error_code);
//            (!in_exit);
//           };
//     // read_(out_attr, out_str);
//     // read_(err_attr, err_str);

// }

// void MayaGather::startThread::read_(
//     const std::shared_ptr<boost::process::pipe>& in_pipe, const std::shared_ptr<boost::asio::streambuf>& in_str
// ){
    
//     boost::asio::read_until(*in_pipe, *in_str, '\n', const boost::system::error_code& ec, std::size_t in_n){
//     if (!ec) {      
//       std::string l_line{};
//       std::istream l_istream{in_str.get()};
//       std::getline(l_istream, l_line);
//     } else {
//     }
//   });
// }