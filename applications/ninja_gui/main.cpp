/// Sample Ccommandline Argument
// ./ninja_gui --file=/Users/Sina/rpg/datasets/meshes/lab.ply

#include <glog/logging.h>
#include <spirit/Gui.h>
#include <chrono>

DEFINE_string(file, "", "Specify File Path");
DEFINE_int32(verbosity, 2,
             "verbositylevel of node (the lower the less verbose)");

int main(int argc, char** argv) {
  // Read commandline args
  google::SetUsageMessage(
      "this is a massage to show how to use the code or"
      " info about the program.");
  google::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);

  // Initialize a spirit gui
  SpiritGui ninja_gui;

  // add a ground mesh to gui
  ninja_gui.AddGroundMesh(FLAGS_file.c_str());

  // add some axis
  for(int i=1 ; i<=5 ; i++) {
    Eigen::Vector6d axis_pose;
    axis_pose << i,1,1,0,0,0;
    ninja_gui.axes_.AddObj(axis_pose);
  }

  // remove the last axis
  ninja_gui.axes_.DelObj(ninja_gui.axes_.NumOfObjs()-1);

  // add some waypoints
  for(int i=1 ; i<=5 ; i++) {
    Eigen::Vector6d waypoint_pose;
    waypoint_pose << 0,i,1,0,0,0;
    ninja_gui.waypoints_.AddObj(waypoint_pose);
  }

  // remove the last waypoint
  ninja_gui.waypoints_.DelObj(ninja_gui.waypoints_.NumOfObjs()-1);

  while (ninja_gui.Render()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000/50));
  }

  return 0;
}
