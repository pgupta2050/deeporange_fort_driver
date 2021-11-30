cmake_minimum_required(VERSION 3.0.2)
project(deeporange_fort_driver)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  can_dbc_parser
  nodelet
  raptor_dbw_msgs
  roscpp
  rospy
  sensor_msgs
  std_msgs
  geometry_msgs
)

catkin_package(
  LIBRARIES
    ${PROJECT_NAME}
  INCLUDE
    include/
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}
  src/nodelet.cpp
  src/fortjoy_handler.cpp
)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
)

add_executable(${PROJECT_NAME}_node
  src/node.cpp
)

target_link_libraries(${PROJECT_NAME}_node
  ${PROJECT_NAME}
)

install(FILES do13_fort.dbc
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

add_executable(publisher22 src/publisher.cpp)
target_link_libraries(publisher22 ${catkin_LIBRARIES})


