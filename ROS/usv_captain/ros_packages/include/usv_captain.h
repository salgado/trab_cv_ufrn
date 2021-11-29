#pragma once
#ifndef USV_CAPTAIN_H
#define USV_CAPTAIN_H

/* includes //{ */

/* each ROS nodelet must have these */
#include <ros/ros.h>
#include <ros/package.h>
#include <nodelet/nodelet.h>

/* include std_msgs message */
#include <std_msgs/Float32.h>

/* include sensor_msgs message */
#include <sensor_msgs/Image.h>

/* ROS includes for working with OpenCV */
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

/* some OpenCV includes */
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

//}

namespace usv_captain {

/* class USVCaptain */
class USVCaptain : public nodelet::Nodelet {

public:
  virtual void onInit();

private:
  /* flags must be initialized with the default value */
  bool is_initialized_ = false;

  // | ---------------------- subscribers ----------------------- |

  void callbackSubWAMVCameraFrontRightColor(const sensor_msgs::ImageConstPtr& msg);
  image_transport::Subscriber sub_wamv_camera_front_right_color_;

  // | ----------------------- publishers ----------------------- |

  ros::Publisher pub_thruster_left_angle_;
  ros::Publisher pub_thruster_left_cmd_;
  ros::Publisher pub_thruster_right_angle_;
  ros::Publisher pub_thruster_right_cmd_;
};

//}

} // namespace usv_captain

#endif