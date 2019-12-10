#!/bin/sh

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch " & 
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo  amcl.launch " & 
sleep 5
xterm  -e  " roslaunch turtlebot_viz_launchers view_navigation.launch "
