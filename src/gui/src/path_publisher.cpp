#include <iostream>
#include "ros/ros.h"
#include "nav_msgs/Path.h"

using namespace std;

geometry_msgs::PoseStamped
create_pose( const double& x , const double& y ){
	geometry_msgs::PoseStamped msg;
	msg.pose.position.x = x;
	msg.pose.position.y = y;
	msg.pose.position.z = 0.0;
	msg.pose.orientation.x = 0.0;
	msg.pose.orientation.y = 0.0;
	msg.pose.orientation.z = 0.0;
	msg.pose.orientation.w = 1.0;
	return msg;
}

int
main( int argc , char* argv[] ){
	ros::init( argc , argv , "gui_path_publisher");
	ros::NodeHandle node_handle;
	ros::Publisher path_publisher = node_handle.advertise< nav_msgs::Path >( "path" , 1 , true );

	sleep(1);
	std::cout << "create messages" << std::endl;

	nav_msgs::Path msg;

	msg.poses.push_back( create_pose( 0.0 , 0.0 ) );
	msg.poses.push_back( create_pose( 1.0 , 0.0 ) );
	msg.poses.push_back( create_pose( 2.0 , 1.0 ) );
	msg.poses.push_back( create_pose( 3.0 , 2.0 ) );
	msg.poses.push_back( create_pose( 4.0 , 3.0 ) );
	msg.poses.push_back( create_pose( 5.0 , 3.0 ) );

	std::cout << "message : " << std::endl << msg;

	std::cout << "publishing messaga" << std::endl;
	path_publisher.publish(msg);
	sleep(1);

	std::cout << "done" << std::endl;
	return 1;
}
