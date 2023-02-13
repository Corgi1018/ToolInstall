#include <boost/process.hpp>
#include "src/maya_plugin.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fmt/format.h>

int main(int, char**) {
  auto share_ptr{std::make_shared<maya::shareTool>()};
  auto tool_ptr{std::make_shared<maya::rigTool>()};
  std::vector<std::shared_ptr<maya::mayaPlugin>> ptr{share_ptr, tool_ptr};
  for (auto& p : ptr) {
    maya::install_plugin(p);
  };
}


