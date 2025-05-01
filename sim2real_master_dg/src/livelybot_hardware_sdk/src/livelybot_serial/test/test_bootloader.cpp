#include "ros/ros.h"
#include "serial_struct.h"
#include "robot.h"
#include <iostream>
#include <thread>
#include <condition_variable>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "test_bootloader");
    ros::NodeHandle n;
    ros::Rate r(1);
    livelybot_serial::robot rb;

    ros::ok();
    
    rb.canboard_bootloader();
}

