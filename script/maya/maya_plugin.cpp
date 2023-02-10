#include "maya_plugin.h"
namespace mayaPlugin {

test_plugin::test_plugin() { MGlobal::displayInfo("init plugin"); }
test_plugin::~test_plugin() { MGlobal::displayInfo("uninit plugin"); }
MStatus test_plugin::doIt(const MArgList& args) {
  MGlobal::displayInfo("Hello, Maya");
  
  return MS::kSuccess;
}
void *test_plugin::creator() { return new test_plugin(); }

}  // namespace mayaPlugin
