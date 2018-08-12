#include <ros/ros.h>
#include <ros/spinner.h>
#include "epos_hardware/epos_hardware.h"
#include <controller_manager/controller_manager.h>
#include <vector>
#include "std_msgs/Float32.h"
#include <sstream>

 //extern ros::Publisher pub;

int main(int argc, char** argv) {
  ros::init(argc, argv, "epos_velocity_hardware");
  ros::NodeHandle nh;
  ros::NodeHandle pnh("~");

  //ros::Publisher pub=nh.advertise<std_msgs::Float32>("EPOS_motor_angle",5);

  std::vector<std::string> motor_names;
  for(int i = 0; i < argc-1; ++i) {
    motor_names.push_back(argv[i+1]);
  }
  epos_hardware::EposHardware robot(nh, pnh, motor_names);
  controller_manager::ControllerManager cm(&robot, nh);

  ros::AsyncSpinner spinner(10);
  spinner.start();

  ROS_INFO("Initializing Motors");
  if(!robot.init()) {
    ROS_FATAL("Failed to initialize motors");
    return 1;
  }
  ROS_INFO("Motors Initialized");

  ros::Rate controller_rate(2000);
  ros::Time last = ros::Time::now();
  while (ros::ok()) {
    ros::Time FunctionStart = ros::Time::now();
    robot.read();
    //ros::Time readEnd = ros::Time::now();

    ros::Time now = ros::Time::now();
    //ros::Time updateStart = ros::Time::now();
    cm.update(now, now-last);
    //ros::Time updateEnd = ros::Time::now();

    //ros::Time writeStart = ros::Time::now();
    robot.write();
    //ros::Time writeEnd = ros::Time::now();

    last = now;
    ros::Time updateDiagStart = ros::Time::now();
    //robot.update_diagnostics();
    ros::Time FunctionEnd = ros::Time::now();

    //std::cout<<"\n Function Took:"<<FunctionEnd - FunctionStart;

    controller_rate.sleep();
  }

}
