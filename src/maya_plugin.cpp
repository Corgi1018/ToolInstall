#include "file.h"
#include <fstream>
#include <iostream>
namespace maya {
namespace fs = std::filesystem;
void copy_file(const std::filesystem::path& in_from, const std::filesystem::path& in_to) {
  fs::create_directories(in_to);
  const auto copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;
  fs::copy(in_from, in_to, copyOptions);
};
void create_shelf(const std::string& in_shelfname, struct Mel mel, const std::filesystem::path& in_directory) {
  std::string in_content =
      fmt::format(mel_content, mel.in_fun, mel.in_button, mel.in_image, mel.in_image1, mel.in_buttonCommand);
  fs::create_directories(in_directory);
  std::ofstream ostrm(in_directory / in_shelfname, std::ios::out);
  ostrm << in_content;
};
std::filesystem::path get_env_path(const KNOWNFOLDERID& in_env) {
  /// 这里我们手动做一些工作
  /// 获取环境变量 FOLDERID_Documents
  PWSTR pManager;
  SHGetKnownFolderPath(in_env, NULL, nullptr, &pManager);
  auto k_path = fs::path{pManager};
  CoTaskMemFree(pManager);
  return k_path;
};
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
void shareTool::install() {
  maya::copy_file(frompath[0], topath[0]);
  maya::create_shelf(melname[0], shareMel, dir);
};
void rigTool::install() {
  maya::setup_exe(rig_args);
  for (int i = 1; i < 5; i++) {
    maya::copy_file(frompath[i], topath[i]);
  }
  maya::create_shelf(melname[1], rigMel_HY_rig, dir);
};

bool install_plugin(std::shared_ptr<mayaPlugin>& l_p) {
  try {
    l_p->install();
    std::cout << "install sucess" << std::endl;
    return true;
  } catch (...) {
    std::cout  << "install faild" << std::endl;
    return false;
  }
};
}  // namespace maya