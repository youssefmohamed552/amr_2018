#include <iostream>
#include "ros/ros.h"

int
main(int argc, char* argv[]){
	ros::init( argc, argv, "innerprocess_communication_node" );
	ros::NodeHandle node_handle;

	std::cout << "starting timer " << std::endl;

	ros::Rate timer(1);
	
	while(ros::ok()){
		std::cout << " innerprocess communication node loop running " << std::endl;
		ros::spinOnce();
		timer.sleep();
	}
	return 0;
}

