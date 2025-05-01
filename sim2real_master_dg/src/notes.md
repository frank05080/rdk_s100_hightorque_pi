第一个窗口
roscore

第二个窗口
rosparam load bridge.yaml
roslaunch sim2real sim2real.launch
先让机器人站起来

第三个窗口
source /opt/ros/foxy/setup.bash
source /opt/ros/noetic/setup.bash
ros2 run ros1_bridge parameter_bridge

第四个窗口
ros2 topic echo /input_data_topic

手柄操作机器人走起来