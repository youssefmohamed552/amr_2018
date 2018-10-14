#include "ros/ros.h"
#include "innerprocess_communication/Update.h"

class InnerprocessCommunication{
	public:
		InnerprocessCommunication();
		virtual ~InnerprocessCommunication();

		void handle_update(const innerprocess_communication::Update::ConstPtr& msg);
};
