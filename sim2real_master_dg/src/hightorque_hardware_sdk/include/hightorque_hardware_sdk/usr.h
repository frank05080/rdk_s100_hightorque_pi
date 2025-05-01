#ifndef __HIGHTORQUE_HARDWARE_SDK_USR_H__
#define __HIGHTORQUE_HARDWARE_SDK_USR_H__

#include "comm.h"
#include <stdint.h>
#include <pthread.h>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <hightorque_hardware_sdk/ctrl2usr.h> 
#include <hightorque_hardware_sdk/usr2ctrl.h>
#define Linear_Velocity_X 0
#define Linear_Velocity_Y 1
#define Linear_Velocity_Z 2
#define Angular_Velocity_X 3
#define Angular_Velocity_Y 4
#define Angular_Velocity_Z 5

namespace HighTorque_Hardware_SDK
{   
    typedef enum
    {
        DEFAULT = 0,
        CUSTOM = 1,
        REMOTE = 2,
    }USR_CTRL_mode_e;
    typedef enum
    {
        ROBOT_SHUT_DOWN = 0,
        ROBOT_INIT = 1,
        ROBOT_WAITING = 2,
        ROBOT_STANDBY = 3,
        ROBOT_RUNNING = 4,
    }Robot_Status_e;
    typedef struct
    {
        float quat[4];
        float angular_velocity[3];
        float linear_acceleration[3];
    }IMU_s;
    typedef union
    {
        struct
        {
            uint8_t LT:1;
            uint8_t RT:1;
            uint8_t LB:1;
            uint8_t RB:1;
            uint8_t A:1;
            uint8_t B:1;
            uint8_t X:1;
            uint8_t Y:1;
            uint8_t BACK:1;
            uint8_t START:1;
            uint8_t turbo:1;
            uint8_t shift:1;
            uint8_t left_stick:1;
            uint8_t right_stick:1;
        }Key;
        uint16_t key_value;
    }RC_KEY_s;
    typedef struct
    {
        RC_KEY_s key;
        float lx;
        float rx;
        float ly;
        float ry;
    }RC_Ctrl_s;
    typedef struct
    {
        USR_CTRL_mode_e robot_mode;
        double robot_speed[6];
        Robot_Status_e robot_status;
        IMU_s imu;
        RC_Ctrl_s rc_ctrl;
    }robot_data_t;
    // typedef struct
    // {
    //     USR_CTRL_mode_e robot_mode;
    //     double robot_speed[6];//@todo 应该不需要设置这么多
    // }robot_cmd_t;
    class USR
    {   
        private:
            uint8_t id;
        public:
            USR();
            ~USR();
            static USR* init(const std::string& robot_name, const std::string& ip_address);
            bool Set_Robot_Mode(uint8_t mode);
            uint8_t Get_Robot_Mode();
            bool Set_Robot_Status(uint8_t status);
            uint8_t Get_Robot_Status();
            bool Set_Robot_Speed(double speed, uint8_t index);
            double Get_Robot_Speed(uint8_t index);
            IMU_s Get_Imu_Data();
            hightorque_hardware_sdk::usr2ctrl robot_cmd;
            ros::NodeHandle nh;
            ros::Publisher usr_pub;
            ros::Subscriber usr_sub;
            ros::Subscriber joy_sub;
            uint8_t init_flag=0;

    };
void usr_callback(const hightorque_hardware_sdk::ctrl2usr::ConstPtr& msg_p);
void robot_loop(USR* robot);
}; // namespace 









#endif // 