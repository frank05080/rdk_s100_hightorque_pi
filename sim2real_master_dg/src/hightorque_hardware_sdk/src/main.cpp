#include "comm.h"
#include "usr.h"
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h" 
#include <sstream>
#include "hightorque_hardware_sdk/usr2ctrl.h"//devel/include
#include "hightorque_hardware_sdk/ctrl2usr.h"//devel/include
#include "stdlib.h"
uint32_t motion_cnt = 0;
int main(int argc, char  *argv[])
{   
    ros::init(argc,argv,"usr");
    HighTorque_Hardware_SDK::USR* myrobot = HighTorque_Hardware_SDK::USR::init("hi", "192.168.1.1");    
    //逻辑(一秒10次)
    ros::Rate r(1);
    myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY);
    while (ros::ok())
    {
        if(motion_cnt <20)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY);
        }
        else if(motion_cnt < 25 && motion_cnt >= 20)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_RUNNING);
            myrobot->Set_Robot_Speed(0.1,Linear_Velocity_X);
        }
        else if(motion_cnt >= 25 && motion_cnt < 30)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY);
        }
        else if(motion_cnt >= 30 && motion_cnt < 35)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_RUNNING);
            myrobot->Set_Robot_Speed(0.1,Linear_Velocity_Y);
        }
        else if(motion_cnt >= 35 && motion_cnt < 40)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY);
        }
        else if(motion_cnt >= 40 && motion_cnt < 45)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_RUNNING);
            myrobot->Set_Robot_Speed(0.5,Angular_Velocity_Z);
        }
        else if(motion_cnt >= 45 && motion_cnt < 50)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY);
        }
        else if(motion_cnt >= 50 && motion_cnt < 55)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_RUNNING);
            myrobot->Set_Robot_Speed(-0.1,Linear_Velocity_X);
        }
        else if(motion_cnt >= 55 && motion_cnt < 60)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY);
        }
        else if(motion_cnt >= 60 && motion_cnt < 65)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_RUNNING);
            myrobot->Set_Robot_Speed(-0.1,Linear_Velocity_Y);
        }
        else if(motion_cnt >= 65 && motion_cnt < 70)
        {
            myrobot->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY);
        }

        
        motion_cnt++;
        switch(myrobot->Get_Robot_Status())
        {
            case HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY:
                std::cout << "ROBOT_STANDBY" << std::endl;
                break;
            case HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_RUNNING:
                std::cout << "ROBOT_RUNNING" << std::endl;
                break;
            default:
                break;
        }
        switch(myrobot->Get_Robot_Mode())
        {
            case HighTorque_Hardware_SDK::USR_CTRL_mode_e::DEFAULT:
                std::cout << "DEFAULT" << std::endl;
                break;
            case HighTorque_Hardware_SDK::USR_CTRL_mode_e::CUSTOM:
                std::cout << "CUSTOM" << std::endl;
                break;
            case HighTorque_Hardware_SDK::USR_CTRL_mode_e::REMOTE:
                std::cout << "REMOTE" << std::endl;
                break;
            default:
                break;
        }
        ROS_INFO("Robot_Command.vx: %f, Robot_Command.vy: %f, Robot_Command.dyaw: %f", myrobot->robot_cmd.robot_speed[0], myrobot->robot_cmd.robot_speed[1], myrobot->robot_cmd.robot_speed[5]);
        HighTorque_Hardware_SDK::robot_loop(myrobot);
        r.sleep();

        ros::spinOnce();
    }
    delete myrobot;

    return 0;
}
