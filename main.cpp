#include "src/maya_plugin.h"
#include <iostream>
#include <list>

int main(int, char**) {
  auto share_ptr{std::make_shared<maya::shareTool>()};
  auto tool_ptr{std::make_shared<maya::rigTool>()};
  auto shelf_ptr{std::make_shared<maya::shelf>()};
  std::list<std::shared_ptr<maya::mayaPlugin>> ptr{share_ptr, tool_ptr,shelf_ptr};
  for (auto& p : ptr) {
    maya::install_plugin(p);
  };
}


