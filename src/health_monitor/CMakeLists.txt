cmake_minimum_required(VERSION 2.8.3)
project(health_monitor)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
set(catkin_deps
  sensor_msgs
  roscpp
  geometry_msgs
  actionlib
  move_base_msgs
  )
find_package(catkin REQUIRED COMPONENTS
  ${catkin_deps}
)

find_package(Boost)

catkin_package(
  INCLUDE_DIRS include
#  LIBRARIES simple_car
  CATKIN_DEPENDS ${catkin_deps}
#  DEPENDS system_lib
)


## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

# add_executable(${PROJECT_NAME}_pump_controller src/pump_controller.cpp)
# target_link_libraries(${PROJECT_NAME}_pump_controller ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(hm_controller src/hm_controller.cpp)
target_link_libraries(hm_controller ${catkin_LIBRARIES})

# add_executable(multi_navi src/multi_navi.cpp)
# target_link_libraries(multi_navi ${catkin_LIBRARIES})