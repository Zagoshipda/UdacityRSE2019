#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // [pickup zone] Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = -5.0;
  goal.target_pose.pose.position.y = -1.5;
  goal.target_pose.pose.orientation.w = -1.5708;

  // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal. Robot is traveling to the pickup zone");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal (pickup zone)
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the base reached pickup zone");

    // pause 5 seconds after reaching the pickup zone
    ros::Duration(5).sleep();

    // [drop off zone] Define a position and orientation for the robot to reach
    goal.target_pose.pose.position.x = 0.0;
    goal.target_pose.pose.position.y = 0.0;
    goal.target_pose.pose.orientation.w = 1.5708;

    // Send the goal position and orientation for the robot to reach
    ROS_INFO("Sending goal. Robot is traveling to the drop off zone");
    ac.sendGoal(goal);

    // Wait an infinite time for the results
    ac.waitForResult();

    // Check if the robot reached its goal (drop off zone) 
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Hooray, the base reached drop off zone");
    }
    else{
      ROS_INFO("The base failed to reach drop off zone for some reason");
    }
      
  }
  else{
    ROS_INFO("The base failed to reach pickup zone for some reason");
    
  }

  return 0;
}
