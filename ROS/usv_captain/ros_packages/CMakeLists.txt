cmake_minimum_required(VERSION 3.1.2)
project(usv_captain)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  sensor_msgs
  image_transport
  cv_bridge
)

find_package(OpenCV REQUIRED)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES USVCaptain
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs image_transport cv_bridge
)

include_directories(include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_library(USVCaptain src/usv_captain.cpp)

add_dependencies(USVCaptain
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

target_link_libraries(USVCaptain
  ${catkin_LIBRARIES}
  ${OpenCV_LIBRARIES}
)