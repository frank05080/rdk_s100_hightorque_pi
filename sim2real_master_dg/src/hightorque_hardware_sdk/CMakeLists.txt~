cmake_minimum_required(VERSION 3.0.2)
project(hightorque_hardware_sdk)
set(CMAKE_CXX_STANDARD 17)


set(PythonInterp_DIR /usr/bin/python3)

add_definitions(-DCMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  geometry_msgs
)

add_message_files(
  FILES
  usr2ctrl.msg
  ctrl2usr.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)

catkin_package(
    LIBRARIES ${PROJECT_NAME}_lib
    CATKIN_DEPENDS roscpp std_msgs rospy message_runtime geometry_msgs
) 

include_directories(
  include/hightorque_hardware_sdk
  ${catkin_INCLUDE_DIRS}
  #/opt/ros/noetic/include
  #../../devel/include
)

set(HIGHTORQUE_HARDWARE_SDK_SRC
    include/hightorque_hardware_sdk/comm.h
    include/hightorque_hardware_sdk/hightorque_hardware_sdk.h
    include/hightorque_hardware_sdk/pi_const.h
    include/hightorque_hardware_sdk/usr.h
    src/usr.cpp
    src/comm.cpp
    #src/main.cpp
)

link_directories(${PROJECT_SOURCE_DIR}/lib)
# add_executable(${PROJECT_NAME}_node src/main.cpp)

# if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
# target_link_libraries(${PROJECT_NAME}_node libhightorque_hardware_sdk_arm_lib.so ${catkin_LIBRARIES} )
add_executable(${PROJECT_NAME}_node ${HIGHTORQUE_HARDWARE_SDK_SRC} src/main.cpp) 

add_dependencies(${PROJECT_NAME}_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
target_link_libraries(${PROJECT_NAME}_node  ${catkin_LIBRARIES} )
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
target_link_libraries(${PROJECT_NAME}_node libhightorque_hardware_sdk_x86_lib.so ${catkin_LIBRARIES} )
endif()

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64")
add_library(${PROJECT_NAME}_arm_lib ${HIGHTORQUE_HARDWARE_SDK_SRC})
target_include_directories(${PROJECT_NAME}_arm_lib PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}_arm_lib 
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_arm_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
add_library(${PROJECT_NAME}_x86_lib ${HIGHTORQUE_HARDWARE_SDK_SRC})
target_include_directories(${PROJECT_NAME}_x86_lib PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}_x86_lib 
  ${catkin_LIBRARIES}
)
add_dependencies(${PROJECT_NAME}_x86_lib ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
endif()

install(TARGETS ${PROJECT_NAME}_node
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )

 #install(DIRECTORY launch/
    #DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch
 #)

 #install(DIRECTORY config/
 #   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/config
 #   )


