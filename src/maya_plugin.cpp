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

std::vector<std::string> create_button(std::vector<struct Mel> mel) {
  std::vector<std::string> button_data;
  for (int i = 0; i < mel.size(); i++) {
    std::string in_content =
        fmt::format(button_content, mel[i].in_button, mel[i].in_image, mel[i].in_image1, mel[i].in_buttonCommand);
    button_data.push_back(in_content);
  };
  return button_data;
}

void create_shelf(
    const std::string& in_shelfname, const std::string& in_fun, std::vector<struct Mel> mel,
    const std::filesystem::path& in_directory
) {
  fs::create_directories(in_directory);
  std::vector<std::string> in_button = maya::create_button(mel);
  std::string in_content             = fmt::format(mel_content, in_fun, fmt::join(in_button,""));
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
  std::cout << "file from" << frompath[0] << "copy to" << topath[0] << std::endl;
  maya::create_shelf(melname[0], mel_fun[0], shareMel, dir);
  std::cout << "Created successfully"
            << " " << melname[0] << std::endl;
};

void rigTool::install() {
  maya::setup_exe(rig_args);
  for (int i = 1; i < 5; i++) {
    maya::copy_file(frompath[i], topath[i]);
    std::cout << "file from" << frompath[i] << "copy to" << topath[i] << std::endl;
  }
  maya::create_shelf(melname[1], mel_fun[1], rigMel, dir);
  std::cout << "Created successfully"
            << " " << melname[1] << std::endl;
};

bool install_plugin(std::shared_ptr<mayaPlugin>& l_p) {
  try {
    l_p->install();
    return true;
  } catch (...) {
    std::cout << "install faild" << std::endl;
    return false;
  }
};
}  // namespace maya