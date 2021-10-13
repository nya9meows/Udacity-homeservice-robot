#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

visualization_msgs::Marker marker;
double pick_position_x = -7.29;
double pick_position_y = -2.52;
double drop_position_x = -7.34;
double drop_position_y = 2.86;
double error_allowed = 0.4;

double turtlebot_x = 100.0;
double turtlebot_y = 100.0;

int marker_states = 0; //0:stay there 1:pick 2:drop

void odom_callback(const nav_msgs::Odometry::ConstPtr& msg){
  turtlebot_x = msg->pose.pose.position.x;
  turtlebot_y = msg->pose.pose.position.y;
  
 double diff_pick = sqrt(pow(turtlebot_x - pick_position_x, 2) + pow(turtlebot_y - pick_position_y, 2));
 double diff_drop = sqrt(pow(turtlebot_x - drop_position_x, 2) + pow(turtlebot_y - drop_position_y, 2));
  
 ROS_INFO("diff_pick: %f; diff_drop: %f",diff_pick,diff_drop);
  
  if(diff_pick < error_allowed){
    marker_states = 1;
  }
  if(diff_drop < error_allowed){
    marker_states = 2;
  }
//   else{
//    marker_states = 2; 
//   }
    
}

void add_marker(double marker_x, double marker_y, bool action){

  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "basic_shapes";
  marker.id = 0;
  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = visualization_msgs::Marker::CUBE;
  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  if(action){
    marker.action = visualization_msgs::Marker::ADD;
  }
  else{
    marker.action = visualization_msgs::Marker::DELETE;
  }
  
  // Set the pose, scan and color of the marker. 
  marker.pose.position.x = marker_x;
  marker.pose.position.y = marker_y;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = 1.0;
  marker.scale.y = 1.0;
  marker.scale.z = 1.0;
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();

  
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_for_rubic");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("/odom", 10, odom_callback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  
  

  while (ros::ok())
  {
    
       
//     ROS_INFO("turtlebot_x: %f; turtlebot_y: %f",turtlebot_x, turtlebot_y);
    //start to add markers
    
    if(marker_states == 1){
    sleep(4);
    add_marker(pick_position_y, -pick_position_x, false);
    //Publish the marker
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
    
    }
    
        
    else if(marker_states == 2){
      sleep(4);
        add_marker(drop_position_y, -drop_position_x, true);
    //Publish the marker
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
          
    }
    
    
    else {
       add_marker(pick_position_y, -pick_position_x, true);
    //Publish the marker
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
          
    }
    ros::spinOnce();
  }
}