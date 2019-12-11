#!/bin/sh

export ROBOT_INITIAL_POSE="-x 0 -y 0 -Y 1.5708"

xterm -e " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/6_PathPlanningAndNavigation/Project7_HomeServiceRobot/catkin_ws/src/my_robot/worlds/UdacityOffice.world " &
sleep 5

xterm -e " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/6_PathPlanningAndNavigation/Project7_HomeServiceRobot/catkin_ws/src/my_robot/maps/map.yaml " &
sleep 5

xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 5

xterm -e " rosrun pick_objects pick_objects.cpp "
