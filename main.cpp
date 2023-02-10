#include <boost/process.hpp>
#include "script/maya/maya_plugin.h"
#include <maya/MFnPlugin.h>
#include <iostream>
#include <sstream>
#include <string>

// int main(int, char**) {
//   auto share_ptr{std::make_shared<maya::shareTool>()};
//   auto tool_ptr{std::make_shared<maya::rigTool>()};
//   std::vector<std::shared_ptr<maya::mayaPlugin>> ptr{share_ptr, tool_ptr};
//   std::vector<std::string> l_string_vector;
//   for (auto& p : ptr) {
//     maya::install_plugin(p,l_string_vector);
//   };
// }

MStatus initializePlugin(MObject obj) {

  MFnPlugin plugin(obj, "test", "1.0");
  MStatus status;
  status=MGlobal::executePythonCommand(R"()");
  // status = plugin.registerCommand("myCmd1", mayaPlugin::test_plugin::creator);  // 命令的名字可以随便定义
  if (!status) status.perror("register command myCmd1 failed");
  return MS::kSuccess;
}

// 卸载插件时取消注册
MStatus uninitializePlugin(MObject obj) {

  MFnPlugin plugin(obj, "test2", "2.0");
  MStatus status;
  // //取消注册
  status = plugin.deregisterCommand("myCmd1");  // 命令的名字与前面定义的一致
  if (!status) status.perror("deregister command myCmd1 failed");

  return MS::kFailure;
}

