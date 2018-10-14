#include <iostream>
#include "ros/ros.h"

#include "innerprocess_communication/innerprocess_communication.h"
#include "innerprocess_communication/Update.h"

int
main(int argc, char* argv[]){
	ros::init( argc , argv , "innerprocess_communication_publisher");
	ros::NodeHandle node_handle;
	ros::Publisher update_publisher = node_handle.advertise< innerprocess_communication::Update >( "update" , 1 , true );
	sleep( 1 );
	std::cout << "creating a message" << std::endl;
	innerprocess_communication::Update msg;
	msg.id = "test";
	msg.x = 5.0;
	msg.y = 2.0;
	msg.z = 1.0;
	std::cout << "message:" << std::endl << msg;

	std::cout << "publishing a message" << std::endl;
	update_publisher.publish( msg );
	sleep(1);

	std::cout << "done" << std::endl;

	return 0;
}

