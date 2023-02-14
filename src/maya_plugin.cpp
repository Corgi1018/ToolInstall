#include "file.h"
#include "maya_plugin.h"
#include <fmt/format.h>
#include <fstream>

namespace maya {
namespace fs = std::filesystem;

void shelf::install(){
  for(int i=5;i<7;i++){
  std::filesystem::path frompath{path[i].first};
  std::filesystem::path topath{get_env_path(FOLDERID_Documents) / path[i].second};
  maya::copy_file(frompath,topath);
  std::cout << "file from" << frompath << "copy to" << topath << std::endl;
  }
};

void shareTool::install() {
  std::filesystem::path frompath{path[0].first};
  std::filesystem::path topath{get_env_path(FOLDERID_Documents) / path[0].second};
  maya::copy_file(frompath, topath);
  std::cout << "file from" << frompath << "copy to" << topath << std::endl;
};

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

void copy_file(const std::filesystem::path& in_from, const std::filesystem::path& in_to) {
  fs::create_directories(in_to);
  const auto copyOptions = std::filesystem::copy_options::update_existing | std::filesystem::copy_options::recursive;
  fs::copy(in_from, in_to, copyOptions);
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

bool install_plugin(std::shared_ptr<mayaPlugin>& l_p) {
  try {
    l_p->install();
    std::cout << "copy success" << std::endl;
    return true;
  } catch (...) {
    std::cout << "copy faild" << std::endl;
    return false;
  }
};

}  // namespace maya


