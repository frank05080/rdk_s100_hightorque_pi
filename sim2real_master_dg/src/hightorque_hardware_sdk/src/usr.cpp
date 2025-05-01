#include "usr.h"
#include <iostream>


namespace HighTorque_Hardware_SDK{
static robot_data_t robot_data[5]; // 机器人数据,最多支持5个机器人
static uint8_t robot_index = 0; // 机器人索引
HighTorque_Hardware_SDK::USR::USR()
{

}

HighTorque_Hardware_SDK::USR::~USR()
{

}

HighTorque_Hardware_SDK::USR* HighTorque_Hardware_SDK::USR::init(const std::string& robot_name, const std::string& ip_address)//@tode:机器人实例因为静态变量，后续改为不需要ID，直接返回一个实例
{
    // 注册机器人逻辑
    std::cout << "Registering : " << robot_name << " and IP address: " << ip_address << std::endl;
    //@todo:待完善
    // 创建并返回一个新的 USR 实例
    USR* new_robot = new HighTorque_Hardware_SDK::USR();
    new_robot->nh = ros::NodeHandle();
    new_robot->usr_pub = new_robot->nh.advertise<hightorque_hardware_sdk::usr2ctrl>("usr2ctrl_data", 10);//@todo:以robot_name为参数
    new_robot->usr_sub = new_robot->nh.subscribe<hightorque_hardware_sdk::ctrl2usr>("ctrl2usr_data", 10, usr_callback);

    new_robot->id = robot_index;
    memset(&robot_data[robot_index], 0, sizeof(robot_data_t));
    robot_index++;

    return new_robot;
}

bool HighTorque_Hardware_SDK::USR::Set_Robot_Mode(uint8_t mode)
{   
    this->robot_cmd.robot_mode = static_cast<USR_CTRL_mode_e>(mode);
    
    return true;
}

bool HighTorque_Hardware_SDK::USR::Set_Robot_Status(uint8_t status)
{   
    if(this->Get_Robot_Status()==3 || this->Get_Robot_Status()==4 || this->Get_Robot_Status()==2)
    {
        this->Set_Robot_Mode(HighTorque_Hardware_SDK::USR_CTRL_mode_e::DEFAULT);

        if(status == HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_STANDBY)
        {
            for(int i = 0; i < 6; i++)
            {
                this->robot_cmd.robot_speed[i] = 0.0;
            }
        }
        this->robot_cmd.robot_status = static_cast<Robot_Status_e>(status);
    }
    else 
    {
        this->robot_cmd.robot_status = 1;
    }
    return true;
}

uint8_t HighTorque_Hardware_SDK::USR::Get_Robot_Mode()
{
    return robot_data[this->id].robot_mode;
}
uint8_t HighTorque_Hardware_SDK::USR::Get_Robot_Status()
{
    return robot_data[this->id].robot_status;
}
bool HighTorque_Hardware_SDK::USR::Set_Robot_Speed(double speed, uint8_t index)//如果目前是站立状态，设置速度会自动切换到运动状态
{ 
    this->Set_Robot_Mode(HighTorque_Hardware_SDK::USR_CTRL_mode_e::DEFAULT);  
    this->Set_Robot_Status(HighTorque_Hardware_SDK::Robot_Status_e::ROBOT_RUNNING);

    this->robot_cmd.robot_speed[index] = speed;
    ROS_INFO("Robto mode: %d, speed: %f", this->robot_cmd.robot_mode, this->robot_cmd.robot_speed[index]);
    return true;
}

double HighTorque_Hardware_SDK::USR::Get_Robot_Speed(uint8_t index)
{
    return robot_data[this->id].robot_speed[index];
}

IMU_s USR::Get_Imu_Data()
{
    return robot_data[this->id].imu;    
}

void usr_callback(const hightorque_hardware_sdk::ctrl2usr::ConstPtr& msg_p)
{
    for(uint8_t j = 0; j < robot_index; j++)
    {
        robot_data[j].robot_mode = static_cast<HighTorque_Hardware_SDK::USR_CTRL_mode_e>(msg_p->robot_mode);
        robot_data[j].robot_status = static_cast<HighTorque_Hardware_SDK::Robot_Status_e>(msg_p->robot_status);
        for(int i = 0; i < 6; i++)
        {
            robot_data[j].robot_speed[i] = msg_p->robot_speed[i];
        }
        for(int i = 0; i < 4; i++)
        {
            robot_data[j].imu.quat[i] = msg_p->quat[i];
        }
        for(int i = 0; i < 3; i++)
        {
            robot_data[j].imu.angular_velocity[i] = msg_p->angular_velocity[i];
        }
        for(int i = 0; i < 3; i++)
        {
            robot_data[j].imu.linear_acceleration[i] = msg_p->linear_acceleration[i];
        }        
    }
}

void robot_loop(USR* robot)
{
    robot->robot_cmd.twist_data.linear.x = robot->robot_cmd.robot_speed[0];
    robot->robot_cmd.twist_data.linear.y = robot->robot_cmd.robot_speed[1];
    robot->robot_cmd.twist_data.angular.z = robot->robot_cmd.robot_speed[5];
    robot->usr_pub.publish(robot->robot_cmd); 
}
}

