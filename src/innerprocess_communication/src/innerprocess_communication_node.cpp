#include <iostream>
#include "ros/ros.h"

#include "innerprocess_communication/innerprocess_communication.h"

int
main(int argc, char* argv[]){
	InnerprocessCommunication innerprocess_communication;

	ros::init( argc, argv, "innerprocess_communication_node" );
	ros::NodeHandle node_handle;


	ros::Subscriber update_subscriber = node_handle.subscribe( "update" , 1, &InnerprocessCommunication::handle_update, &innerprocess_communication );

	ros::Rate timer(1);
	
	while(ros::ok()){
		ros::spinOnce();
		timer.sleep();
	}
	return 0;
}

