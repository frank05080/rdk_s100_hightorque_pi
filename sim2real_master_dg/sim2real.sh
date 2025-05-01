#! /bin/bash
sleep 1
gnome-terminal --title="sim2real" -- bash -c "cd /home/orangepi/dreamwaq_test/sim2real_master_dreamwaq_series;source ./devel/setup.bash; roslaunch sim2real_master joy_control.launch"
wait

