#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"

class PoseConverter
{
public:
  PoseConverter()
  {
    pub_ = nh_.advertise<geometry_msgs::PoseStamped>("/iris/odometry_sensor1/posestamped", 10);
    sub_ = nh_.subscribe("/iris/odometry_sensor1/posestamped", 1, &PoseConverter::callback, this);
  }

  void callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr & msg)
  {
    geometry_msgs::PoseStamped transformed_pose;
    geometry_msgs::PoseWithCovarianceStamped current_pose;
    current_pose = *msg;
    transformed_pose.pose = current_pose.pose.pose;
    transformed_pose.header = current_pose.header;
    pub_.publish(transformed_pose);
  }

private:
  ros::NodeHandle nh_; 
  ros::Publisher pub_;
  ros::Subscriber sub_;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Pose converter");

  PoseConverter pose_conv_object;
  ros::spin();

  return 0;
}