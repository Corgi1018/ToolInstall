#include <boost/process.hpp>

#include <ShlObj.h>
#include <filesystem>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <memory>
#include <vector>
namespace maya {

class mayaPlugin {
 public:
  virtual void install(){};
};

class shelf:public mayaPlugin{
  public:
  void install() override;
};

class shareTool : public mayaPlugin {
 public:
  void install() override;
};

class rigTool : public mayaPlugin {
 public:
  void install() override;
};

class export_weightTool:public mayaPlugin{
  public:
  void install() override;
};

class copy_weightTool:public mayaPlugin{
  public:
  void install() override;
};

class eyeTool:public mayaPlugin{
  public:
  void install() override;
};

bool install_plugin(std::shared_ptr<mayaPlugin>& l_p);//安装插件
std::filesystem::path get_env_path(const KNOWNFOLDERID& in_env);//获取环境变量
void copy_file(const std::filesystem::path& in_from, const std::filesystem::path& in_to);//拷贝文件
std::vector<std::string> setup_exe(const std::string_view& in_arg);//启动exe子进程

}  // namespace maya