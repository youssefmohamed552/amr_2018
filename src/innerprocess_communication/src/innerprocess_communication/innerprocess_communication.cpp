#include <iostream>
#include <Eigen/Dense>

#include "innerprocess_communication/innerprocess_communication.h"

InnerprocessCommunication::
InnerprocessCommunication(){

}

InnerprocessCommunication::
~InnerprocessCommunication(){

}

void
InnerprocessCommunication::
handle_update(const innerprocess_communication::Update::ConstPtr& msg){
	std::cout << "got update message " << msg->id << " and the values (x,y,z) = (" << msg->x << "," << msg->y << "," << msg->z << ")" << std::endl;
	Eigen::Vector3d a;
	a(0) = msg->x;
	a(1) = msg->y;
	a(2) = msg->z;
	std::cout << "a[" << a.size() << "]:{" << a(0) << "," << a(1) << "," << a(2) << "}" << std::endl;
	Eigen::Vector3d b = 2*a;
	std::cout << "b[" << b.size() << "]:{" << b(0) << "," << b(1) << "," << b(2) << "}" << std::endl;
	return;
}

