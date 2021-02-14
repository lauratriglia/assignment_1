#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "my_srv/Server1.h"

//Declare the publisher and the client 
ros::Publisher pub;
ros::ServiceClient client;

//Connect with the server
my_srv::Server1 rec_pos;

//Initialize the coordinate of the target
float x_target = 0;
float y_target = 0;

//The function positionCallback checks the robot and it asks if the target has been reached. In the case the taget is reached, the function asks for 
//a new target.
//If the distance is < 0.1 asks for a new a target, otherwise it sends commands to reach the target 
void positionCallback(const nav_msgs::Odometry::ConstPtr& msg)
{
  float x = msg->pose.pose.position.x;
  float y = msg->pose.pose.position.y;
  geometry_msgs::Twist vel;
  ROS_INFO("Robot position [%f, %f]",x,y);
  x_target =rec_pos.response.x;
  y_target =rec_pos.response.y;
  
  if (((abs(x - x_target) < 0.1) && (abs(y - y_target) < 0.1)))
  {
	ROS_INFO("Target Reached");
	//because the target is reached, we need a new target 
	my_srv::Server1 new_target;
	client.call(new_target);
	x_target = new_target.response.x;
	x_target = new_target.response.x;
  }
  //in the case the target is not reached
  else{
	geometry_msgs::Twist vel;
	vel.linear.x = 100*(x_target-x);
	vel.linear.y = 100*(y_target-y);
	pub.publish(vel); 
  }

}

int main(int argc, char **argv)
{
   ros::init(argc, argv, "robot_controller");
   ros::NodeHandle n;   
   pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
   ros::Subscriber sub = n.subscribe("/odom", 1000, positionCallback);
   client = n.serviceClient<my_srv::Server1>("/random");
   ros::spin();

   return 0;
}
