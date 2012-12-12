/**
 * @file /auto_docking/include/auto_docking/auto_docking_ros.hpp
 *
 * @brief File comment
 *
 * File comment
 *
 * @date Nov 30, 2012
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef AUTO_DOCKING_ROS_HPP_
#define AUTO_DOCKING_ROS_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>

#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <kobuki_msgs/SensorState.h>
#include <kobuki_msgs/DockInfraRed.h>
#include <kobuki_msgs/MotorPower.h>


#include <sstream>
#include <vector>
#include <ecl/geometry/pose2d.hpp>
#include <kdl/frames.hpp>
#include <kdl_conversions/kdl_msg.h>
#include "dock_drive.hpp"

namespace kobuki 
{

typedef message_filters::sync_policies::ApproximateTime<
  nav_msgs::Odometry,
  kobuki_msgs::SensorState,
  kobuki_msgs::DockInfraRed
> SyncPolicy;

class AutoDockingROS
{
public:
  AutoDockingROS();
  ~AutoDockingROS();

  bool init(ros::NodeHandle& nh);
  void spin();

private:
  AutoDockingROS* self;
  DockDrive dock_;

  bool shutdown_requested_;

  ros::Subscriber do_dock_, cancel_dock_, debug_;
  ros::Publisher velocity_commander_, motor_power_enabler_, debug_jabber_;

  boost::shared_ptr<message_filters::Subscriber<nav_msgs::Odometry> > odom_sub_;
  boost::shared_ptr<message_filters::Subscriber<kobuki_msgs::DockInfraRed> > ir_sub_;
  boost::shared_ptr<message_filters::Subscriber<kobuki_msgs::SensorState> > core_sub_;
  boost::shared_ptr<message_filters::Synchronizer<SyncPolicy> > sync_;


  void doCb(const std_msgs::StringConstPtr& msg);
  void cancelCb(const std_msgs::StringConstPtr& msg);
  void debugCb(const std_msgs::StringConstPtr& msg);
  void syncCb(const nav_msgs::OdometryConstPtr& odom,
              const kobuki_msgs::SensorStateConstPtr& core,
               const kobuki_msgs::DockInfraRedConstPtr& ir);
};

} //namespace kobuki
#endif /* AUTO_DOCKING_ROS_HPP_ */

