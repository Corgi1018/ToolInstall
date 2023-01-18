#include "file.h"
#include <fstream>
#include <iostream>
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

/**
 * 设置button
 */
std::string set_button(const struct Mel& in_mel) {
  std::string in_button =
      fmt::format(button_content, in_mel.in_button, in_mel.in_image, in_mel.in_image1, in_mel.in_buttonCommand);
  return in_button;
};

/**
 * 创建工具架
 */
void create_shelf(
    const std::string& in_shelfname, const std::string& in_fun, const std::vector<std::string>& in_button,
    const std::filesystem::path& in_directory
) {
  fs::create_directories(in_directory);
  std::string in_content = fmt::format(mel_content, in_fun, fmt::join(in_button, ""));
  std::ofstream ostrm(in_directory / in_shelfname, std::ios::out);
  ostrm << in_content;
};

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
std::vector<std::string> setup_exe(const std::vector<std::string>& in_arg) {
  boost::process::ipstream is;
  boost::process::ipstream erro;
  std::vector<std::string> data;
  auto rt = boost::process::system(in_arg, boost::process::std_out > is, boost::process::std_err > erro);
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
  maya::copy_file(frompath[0], topath[0]);
  std::cout << "file from" << frompath[0] << "copy to" << topath[0] << std::endl;
};
std::string shareTool::get_button_str() {
  std::string out_str = maya::set_button(share_button);
  return out_str;
};

/**
 * rig tool 安装
 */
void rigTool::install() {
  maya::setup_exe(rig_args);
  for (int i = 1; i < 5; i++) {
    maya::copy_file(frompath[i], topath[i]);
    std::cout << "file from" << frompath[i] << "copy to" << topath[i] << std::endl;
  }
};
std::string rigTool::get_button_str() {
  std::string out_str = maya::set_button(rig_button) + " " + maya::set_button(dyn_button);
  return out_str;
};

/**
 * 开始安装插件
 */
bool install_plugin(std::shared_ptr<mayaPlugin>& l_p,std::vector<std::string>& l_string_vector) {
  try {
    // l_p->install();
    auto in_button = l_p->get_button_str();
    l_string_vector.push_back(in_button);
    create_shelf(melname, mel_fun,l_string_vector, dir);
    return true;
  } catch (...) {
    std::cout << "install faild" << std::endl;
    return false;
  }
};
}  // namespace maya