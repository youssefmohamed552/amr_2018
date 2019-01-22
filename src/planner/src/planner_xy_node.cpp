#include <iostream>
#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include "nav_msgs/Path.h"
#include "planner/planner_xy.h"

using namespace std;

int
main( int argc , char* argv[] ){
	PlannerXY planner_xy;

	ros::init( argc , argv , "planner_xy_node" );
	ros::NodeHandle node_handle;
	ros::Subscriber odom_subscriber = node_handle.subscribe( "odom" , 1 , &PlannerXY::handle_odom , &planner_xy );
	ros::Subscriber goal_subscriber = node_handle.subscribe( "goal" , 1 , &PlannerXY::handle_goal , &planner_xy );
	planner_xy.openlistsize_publisher = node_handle.advertise< std_msgs::UInt32 >( "openlistsize" , 1 );
	planner_xy.closedlistsize_publisher = node_handle.advertise< std_msgs::UInt32 >( "closedlistsize" , 1 );
	planner_xy.path_publisher= node_handle.advertise< nav_msgs::Path >( "path" , 1 );

	ros::spin();
	return 0;
}

