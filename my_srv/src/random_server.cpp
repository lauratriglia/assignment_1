#include "ros/ros.h"
#include "my_srv/Server1.h"
#include <math.h>


//The bool pos_random gives us the random targes, with x and y coordinates between -6 and 6
bool pos_random (my_srv::Server1::Request &req, my_srv::Server1::Response &res)
{
	res.x = (rand()%13)-6;
	res.y = (rand()%13)-6;
    return true;
}


//In the main function we can define the services /random
int main(int argc, char **argv)
{
   ros::init(argc, argv, "random_server");
   ros::NodeHandle n;
   ros::ServiceServer service= n.advertiseService("/random", pos_random);
   ros::spin();

   return 0;
}
