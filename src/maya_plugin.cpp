#include "file.h"
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <regex>
namespace maya {
namespace fs = std::filesystem;
/**
 * 拷贝文件
 */
void copy_file(const std::filesystem::path& in_from, const std::filesystem::path& in_to) {
  fs::create_directories(in_to);
  const auto copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;
  fs::copy(in_from, in_to, copyOptions);
};

// /**
//  * 设置button
//  */
// std::string set_button(const struct Mel& in_mel) {
//   std::string in_button =
//       fmt::format(button_content.data(), in_mel.in_button, in_mel.in_image, in_mel.in_image1, in_mel.in_buttonCommand);
//   return in_button;
// };

// /**
//  * 创建工具架
//  */
// void create_shelf(
//     const std::string_view& in_shelfname, const std::string_view& in_fun, const std::vector<std::string>& in_button,
//     const std::filesystem::path& in_directory
// ) {
//   std::regex re(R"(maya::get_env_path(FOLDERID_Documents))");//需要匹配
//   for (auto const& dir_entry : std::filesystem::recursive_directory_iterator(in_directory)) {
//     std::vector<std::string> dir_v{};
//     std::cout<<dir_entry<<std::endl;
//     auto dir = dir_entry.path().generic_string();
//     dir_v.emplace_back(dir);
//     std::smatch m;//匹配结果
//     for (const auto maya_dir : dir_v) {
//       if (std::regex_search(maya_dir, m, re)) {
//         std::cout << m.str() << std::endl;
//       } else {
//         std::cout << "no matches found" << std::endl;
//       };
//     }
//   }
//   fs::create_directories(in_directory);
//   std::string in_content = fmt::format(mel_content.data(), in_fun, fmt::join(in_button, ""));
//   std::ofstream ostrm(in_directory / in_shelfname, std::ios::out);
//   ostrm << in_content;
//   std::cout << "creat shelf success" << std::endl;
// };

/**
 * 获取用户的环境变量
 */
std::filesystem::path get_env_path(const KNOWNFOLDERID& in_env) {
  /// 这里我们手动做一些工作
  /// 获取环境变量 FOLDERID_Documents
  PWSTR pManager;
  SHGetKnownFolderPath(in_env, NULL, nullptr, &pManager);
  auto k_path = fs::path{pManager};
  CoTaskMemFree(pManager);
  return k_path;
};

/**
 * 启动exe子进程
 */
std::vector<std::string> setup_exe(const std::string_view& in_arg) {
  boost::process::ipstream is;
  boost::process::ipstream erro;
  std::vector<std::string> data;
  auto rt = boost::process::system(in_arg.data(), boost::process::std_out > is, boost::process::std_err > erro);
  if (!rt) {
    std::string l_line{};
    std::getline(is, l_line);
    data.push_back(l_line);
  } else {
    for (std::string error; std::getline(erro, error);) std::cout << "error is:" << error << std::endl;
  };
  return data;
};

/**
 * share tool 安装
 */
void shareTool::install() {
  std::filesystem::path frompath{path[0].first};
  std::filesystem::path topath{get_env_path(FOLDERID_Documents) / path[0].second};
  maya::copy_file(frompath, topath);
  std::cout << "file from" << frompath << "copy to" << topath << std::endl;
};
// std::string shareTool::get_button_str() {
//   std::string inbutton = maya::set_button(share_button);
//   std::filesystem::path topath{get_env_path(FOLDERID_Documents) / path[0].second};
//   std::string out_str = fmt::format(inbutton, topath.generic_string());
//   return out_str;
// };

/**
 * rig tool 安装
 */
void rigTool::install() {
  maya::setup_exe(rig_args);
  for (int i = 1; i < 5; i++) {
    std::filesystem::path frompath{path[i].first};
    std::filesystem::path topath{};
    // 判断是相对路径还是绝对路径
    if (fs::is_directory(path[i].second))
      topath = path[i].second;
    else if (path[i].second == "packages" || path[i].second == "Desktop")
      topath = get_env_path(FOLDERID_Profile) / path[i].second;
    else
      topath = get_env_path(FOLDERID_Documents) / path[i].second;
    maya::copy_file(frompath, topath);
    std::cout << "file from" << frompath << "copy to" << topath << std::endl;
  }
};
// std::string rigTool::get_button_str() {
//   std::string out_str = maya::set_button(rig_button) + " " + maya::set_button(dyn_button);
//   return out_str;
// };









/**
 * 开始安装插件
 */
bool install_plugin(std::shared_ptr<mayaPlugin>& l_p) {
  try {
    l_p->install();
    // auto in_button = l_p->get_button_str();
    // l_string_vector.push_back(in_button);
    // create_shelf(melname, mel_fun, l_string_vector, maya::get_env_path(FOLDERID_Documents) / dir);
    std::cout << "install success" << std::endl;
    return true;
  } catch (...) {
    std::cout << "install faild" << std::endl;
    return false;
  }
};
}  // namespace maya


