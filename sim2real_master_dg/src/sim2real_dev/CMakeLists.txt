cmake_minimum_required(VERSION 3.1.0)
project(sim2real_dev)



find_package(catkin REQUIRED COMPONENTS
    roscpp
    sensor_msgs
)

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

catkin_package()
set(DEV_CTRL_SRC
    include/dev/develop_controller.h
    src/main.cpp
    src/develop_controller.cpp

)

add_executable(${PROJECT_NAME}_node ${DEV_CTRL_SRC})
target_link_libraries(${PROJECT_NAME}_node ${catkin_LIBRARIES})
add_library(${PROJECT_NAME}_lib STATIC ${DEV_CTRL_SRC})
target_link_libraries(${PROJECT_NAME}_lib ${catkin_LIBRARIES})