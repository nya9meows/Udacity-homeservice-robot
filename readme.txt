UPDATES:

This project runs on Udacity Project Workspace (ROS Kinetic)

1. possible error when lauch world:
	no module named rospkg
solution:
	"pip install rospkg" and then "catkin_make"

2. add "add_maker_for_rubic" and modified "add_markers.sh" to meet the request of rubic

3. add three new .gif files : "add_markers_new.gif", "pick_objects_new.gif", "home_service_new.gif"

4. response to the review:
4.1 pick_objects
You've created a pick_objects.sh file that will send multiple goals for the robot to reach. Your robot travels to the desired pickup zone, displays a message that it reached its destination, waits 5 seconds.
After that, your robot is not moving towards drop off zone.
------
answer: when the robot reached the desired position (x,y), it might also need to adjust its posture to meet the orientation.w, the, after 5 seconds, it start to chase the next goal. 
I run the project for several times, it works. The only reason I can think about is the waiting time is sensuously longer than 5 seconds since the robot will slow down and might still needs to adjust the posture after it reached around the right position, so I make the waiting time shorter to save the time for the reviewers.

4.2 add_markers
You've created a add_marker.sh file that will publish a marker to rviz. The marker is initially published at the pickup zone. After 5 seconds it is hidden.
It doesn't show up in the drop off zone after 5 seconds.
------
I add "add_maker_for_rubic" and modified "add_markers.sh" so that no re-catkin_make is needed (in the last version there are two add_markers cpp files, one for home_service, one for add_markers). 

4.3 home_service
You have written a home_service.sh script that runs all the nodes in this project.
Initially marker is shown at the pickup zone.
Marker is hidden once the robot reaches the pickup zone (Assume that the robot laid its hands on the package lol)
Pickup is simulated for 5 seconds (Picking up the package...1 2 3 4 Boom..! 5 seconds over)
However, Robot doesn't move after it reaches the pickup zone.
------
same as 4.1




===================================================================
Some modifications on packages (and the reasons):
1. modified the "turtlebot_world.launch" file in turtlebot_gazebo pkg to enable loading my own world.
2. modified the "amcl_demo.launch" file in turtlebot_gazebo pkg to enable loading my own map.


The turtlebot drives around and scan the house with laser sensor, thus we can generate maps about surroundings. With the local map, the turtlebot uses data from odometry and laser sensor to localize itself with Adaptive Monte Carlo Localization (AMCL). The turtlebot use Dijkstra algorithm to generate trajectory given a goal.

Following pkgs are used in this project:
map-server(dynamically generated map service)
amcl(localization)
slam-gmapping(laser based slam)
move_base(navigation)
teleop_twist_keyboard(for keyboard control)
turtlebot(simulation environment)




