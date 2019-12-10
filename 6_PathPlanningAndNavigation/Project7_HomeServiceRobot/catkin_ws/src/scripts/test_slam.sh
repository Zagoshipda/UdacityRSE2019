#!/bin/sh

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/6_PathPlanningAndNavigation/Project7_HomeServiceRobot/catkin_ws/src/my_robot/worlds/UdacityOffice.world " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo gmapping_demo.launch " & 
sleep 5
xterm  -e  " roslaunch turtlebot_viz_launchers view_navigation.launch " & 
sleep 5
xterm  -e  " roslaunch turtlebot_teleop keyboard_teleop.launch " &