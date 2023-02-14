#include "maya_plugin.h"
#include "../../Source/command_source.h"
#include <maya/MFnPlugin.h>
#include <maya/MString.h>
namespace mayaPlugin {

test_plugin::test_plugin() { MGlobal::displayInfo("init plugin"); }
test_plugin::~test_plugin() { MGlobal::displayInfo("uninit plugin"); }
MStatus test_plugin::doIt(const MArgList& args) {
  MGlobal::displayInfo("Hello, Maya");
  return MS::kSuccess;
}
void *test_plugin::creator() { return new test_plugin(); }

}  // namespace mayaPlugin

MStatus initializePlugin(MObject obj) {

  MFnPlugin plugin(obj, "test", "1.0");
  MStatus status;
  MString Mcommand{};
  Mcommand.setUTF8(command.data());
  status=MGlobal::executePythonCommand(Mcommand);
  if (!status) status.perror("register command myCmd1 failed");
  return MS::kSuccess;
}

// 卸载插件时取消注册
MStatus uninitializePlugin(MObject obj) {
  MFnPlugin plugin(obj, "test2", "2.0");
  MStatus status;
  return MS::kSuccess;
}
