#include "src/maya_plugin.h"
#include <iostream>
#include <list>

int main(int, char**) {
  auto share_ptr{std::make_shared<maya::shareTool>()};
  auto rig_ptr{std::make_shared<maya::rigTool>()};
  auto shelf_ptr{std::make_shared<maya::shelf>()};
  auto export_weight_ptr{std::make_shared<maya::export_weightTool>()};
  std::list<std::shared_ptr<maya::mayaPlugin>> ptr{shelf_ptr,export_weight_ptr,share_ptr,rig_ptr};
  for (auto& p : ptr) {
    maya::install_plugin(p);
  };
}


