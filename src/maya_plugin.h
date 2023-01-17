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
bool install_plugin(std::shared_ptr<mayaPlugin>& l_p);
std::filesystem::path get_env_path(const KNOWNFOLDERID& in_env);
std::vector<std::string> create_button(std::vector<struct Mel> in_mel);
void copy_file(const std::filesystem::path& in_from, const std::filesystem::path& in_to);
void create_shelf(
    const std::string& in_shelfname, const std::string& in_fun, std::vector<struct Mel> mel,
    const std::filesystem::path& in_directory
);
std::vector<std::string> setup_exe(const std::vector<std::string>& in_arg);
struct Mel {
  std::string in_button;
  std::string in_image;
  std::string in_image1;
  std::string in_buttonCommand;
};
class shareTool : public mayaPlugin {
 public:
  void install() override;
};
class rigTool : public mayaPlugin {
 public:
  void install() override;
};

}  // namespace maya