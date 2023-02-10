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
  virtual std::string get_button_str() { return ""; };
};

bool install_plugin(std::shared_ptr<mayaPlugin>& l_p, std::vector<std::string>& in_str);
std::filesystem::path get_env_path(const KNOWNFOLDERID& in_env);
void copy_file(const std::filesystem::path& in_from, const std::filesystem::path& in_to);
std::string set_button(const struct Mel& in_mel);
void create_shelf(
    const std::string_view& in_shelfname, const std::string_view& in_fun, const std::vector<std::string>& in_button,
    const std::filesystem::path& in_directory
);
void init_plugin();
std::vector<std::string> setup_exe(const std::string_view& in_arg);

struct Mel {
  std::string_view in_button;
  std::string_view in_image;
  std::string_view in_image1;
  std::string_view in_buttonCommand;
};

class shareTool : public mayaPlugin {
 public:
  void install() override;
  std::string get_button_str() override;
};

class rigTool : public mayaPlugin {
 public:
  void install() override;
  std::string get_button_str() override;
};

}  // namespace maya