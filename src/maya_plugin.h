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
void create_shelf();
bool install_plugin(std::shared_ptr<mayaPlugin>& l_p);
std::filesystem::path get_env_path(const KNOWNFOLDERID& in_env);
void copy_file(const std::filesystem::path& in_from, const std::filesystem::path& in_to);
std::vector<std::string> setup_exe(const std::string_view& in_arg);

class shareTool : public mayaPlugin {
 public:
  void install() override;
};

class rigTool : public mayaPlugin {
 public:
  void install() override;
};

class shelf:public mayaPlugin{
  public:
  void install() override;
};

}  // namespace maya