#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"

// pickup position, drop off position, robot position
double pickupx = 1, pickupy = -3;
double dropoffx = -1, dropoffy = -2;
double posx = 0, posy = 0;

void callBack(const nav_msgs::Odometry::ConstPtr& msg){
  posx = msg->pose.pose.position.x;
  posy = msg->pose.pose.position.y;
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  // add_markers node should subscribe to odometry to keep track of robot pose
  ros::Subscriber odom_sub = n.subscribe("/odom", 1000, callBack);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  while (ros::ok())
  {
    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  
      // Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER 
      // Here, we don't cycle shapes
    marker.type = shape;



    double dist_pickup = 100000000, dist_dropoff = 100000000;
    double min_dist = 0.4;

    ROS_INFO("Publish the marker at the pickup zone");
    // [1] Initially show the marker at the pickup zone
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 1;
    marker.pose.position.y = -3;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = -1.5708;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.5;
    marker.scale.y = 0.5;
    marker.scale.z = 0.5;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      // ros::Duration(3).sleep();
      // ROS_INFO("1");
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);
    ros::spinOnce();



    // [2] Hide the marker once your robot reaches the pickup zone
    // minimum interval 0.5 second
    ros::Duration(0.5).sleep();

    // check every second if the robot is close enough to pickup zone
    ROS_INFO("pickup zone distance calculating...");
    while(dist_pickup > min_dist){
      dist_pickup = sqrt(pow(pickupx - posx, 2) + pow(pickupy - posy, 2));
      // std::cout << dist_pickup << std::endl;
      ros::spinOnce();
      ros::Duration(1).sleep();
    }
    ROS_INFO("Hide the marker");
    marker.action = visualization_msgs::Marker::DELETEALL;
    marker_pub.publish(marker);
    ros::spinOnce();



    // // Cycle between different shapes
    // switch (shape)
    // {
    // case visualization_msgs::Marker::CUBE:
    //   shape = visualization_msgs::Marker::SPHERE;
    //   break;
    // case visualization_msgs::Marker::SPHERE:
    //   shape = visualization_msgs::Marker::ARROW;
    //   break;
    // case visualization_msgs::Marker::ARROW:
    //   shape = visualization_msgs::Marker::CYLINDER;
    //   break;
    // case visualization_msgs::Marker::CYLINDER:
    //   shape = visualization_msgs::Marker::CUBE;
    //   break;
    // }



    // [3] Wait 5 seconds to simulate a pickup
    ros::Duration(5).sleep();



    // [4] Show the marker at the drop off zone once your robot reaches it 
    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -1;
    marker.pose.position.y = -2;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.5708;

    marker.lifetime = ros::Duration();



    // check every second if the robot is close enough to drop off zone
    ROS_INFO("drop off zone distance calculating...");
    while(dist_dropoff > min_dist){
      dist_dropoff = sqrt(pow(dropoffx - posx, 2) + pow(dropoffy - posy, 2));
      // std::cout << dist_dropoff << std::endl;
      ros::spinOnce();
      ros::Duration(1).sleep();
    }

    ROS_INFO("Publish the marker at the drop off zone");
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);
    ros::spinOnce();



    ROS_INFO("Simulation terminate...");
    ros::Duration(10).sleep();

    r.sleep();
  }
}
