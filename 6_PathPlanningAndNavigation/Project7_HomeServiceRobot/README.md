Robotics Software Engineer Nanodegree Program 2019 at Udacity
==========


 <br/><br/>


- [Robotics Software Engineer | Udacity](https://www.udacity.com/course/robotics-software-engineer--nd209)


 <br/><br/>


### Project7: Home Service Robot
- Program a home service robot that autonomously map an environment and navigate to pickup and deliver objects


 <br/><br/>


### How to use
- go to /catkin_ws

- catkin_make

- source devel/setup.bash

- go to /scripts

- chmod +x \<script name\>

- ./\<script name\>


 <br/><br/>


### About the packages
- add_markers : Add a cube marker in the map
    - The marker initially is published at the pickup zone.
    - After 5 seconds it should be hidden.
    - Then after another 5 seconds it should appear at the drop off zone.

- home_service : Home Service Robot project
    - Initially the marker is shown at the pickup zone.
    - Marker will disappear once the robot reach the pickup zone.
    - Wait 5 seconds to simulate a pickup.
    - Marker is now shown up at the drop off zone once the robot reaches it.

- pick_objects : The robot moves from pickup zone to drop off zone
    - The robot is initially at the starting point.
    - Then it travels to the pickup zone.
    - Terminal will display a message that it reached the pickup zone.
    - Waits 5 seconds.
    - Now the robot travels to the drop off zone.
    - Terminal will displays a message that it reached the drop off zone.

- slam_gmapping : With the gmapping_demo.launch file, you can easily perform SLAM and build a map of the environment with a robot equipped with laser range finder sensors or RGB-D cameras.

- turtlebot : With the keyboard_teleop.launch file, you can manually control a robot using keyboard commands.

- turtlebot_interactions : With the view_navigation.launch file, you can load a preconfigured rviz workspace. You’ll save a lot of time by launching this file, because it will automatically load the robot model, trajectories, and map for you.

- turtlebot_simulator : With the turtlebot_world.launch you can deploy a turtlebot in a gazebo environment by linking the world file to it.


 <br/><br/>


