#include <usv_captain.h>

#include <pluginlib/class_list_macros.h>

namespace usv_captain {

  /* onInit() //{ */

  void USVCaptain::onInit() {

    /* obtain node handle */
    ros::NodeHandle nh("~");

    /* waits for the ROS to publish clock */
    ros::Time::waitForValid();

    // | ---------------------- subscribers ----------------------- |

    /* initialize the image transport */
    image_transport::ImageTransport it(nh);

    sub_wamv_camera_front_right_color_ = it.subscribe("/wamv/sensors/cameras/front_right_camera/image_raw", 1, &USVCaptain::callbackSubWAMVCameraFrontRightColor, this);

    // | ---------------------- publishers ------------------------ |

    pub_thruster_left_angle_  = nh.advertise<std_msgs::Float32>("/wamv/thrusters/left_thrust_angle", 1);
    pub_thruster_left_cmd_    = nh.advertise<std_msgs::Float32>("/wamv/thrusters/left_thrust_cmd", 1);
    pub_thruster_right_angle_ = nh.advertise<std_msgs::Float32>("/wamv/thrusters/right_thrust_angle", 1);
    pub_thruster_right_cmd_   = nh.advertise<std_msgs::Float32>("/wamv/thrusters/right_thrust_cmd", 1);

    ROS_INFO_ONCE("[USVCaptain]: initialized!");

    is_initialized_ = true;
  }

  //}

  /* callbackSubWAMVCameraFrontRightColor() //{ */

  void USVCaptain::callbackSubWAMVCameraFrontRightColor(const sensor_msgs::ImageConstPtr& msg) {
    if (!is_initialized_) {
      return;
    }

    /* create cmd message */
    std_msgs::Float32 message;
    message.data = 0.5;

    /* publish cmd */
    try{
      /* send cmd to the right thruster */
      pub_thruster_right_cmd_.publish(message);
    } catch(...) {
      ROS_ERROR("[USVCaptain]: Exception caught during publishing topic %s", pub_thruster_right_cmd_.getTopic().c_str());
    }
  } 

  //}

} // namespace usv_captain

PLUGINLIB_EXPORT_CLASS(usv_captain::USVCaptain, nodelet::Nodelet);