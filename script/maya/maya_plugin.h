#include <maya/MPxCommand.h>
#include <maya/MStatus.h>
#include <maya/MGlobal.h>

namespace mayaPlugin {
class test_plugin : public MPxCommand {
 public:
  test_plugin();
  ~test_plugin() override;
  MStatus doIt(const MArgList&) override;
  static void* creator();
};

}  // namespace mayaPlugin