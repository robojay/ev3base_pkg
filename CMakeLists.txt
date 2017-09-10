cmake_minimum_required(VERSION 2.8.3)
project(ev3base_pkg)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  message_generation
  sensor_msgs
  tf
)

find_package(Boost REQUIRED COMPONENTS system)

add_message_files(
   FILES
   Encoder.msg
)


## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs
   geometry_msgs  
 )


catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
)


add_executable(ev3base_node src/ev3base_node.cpp)

target_link_libraries(ev3base_node
   ${catkin_LIBRARIES}
 )

