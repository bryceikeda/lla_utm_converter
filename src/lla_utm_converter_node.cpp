#include "lla_utm_converter/lla_utm_converter.h"

int
main(int argc, char* argv[]){
	ros::init(argc, argv, "lla_utm_converter_node");
	ros::NodeHandle node_handle; 

	// UTM zone and hemisphere	
	int zone; 
	bool northp;
	double origin_x;
	double origin_y;
	double origin_z;
		
	node_handle.getParam("origin_x", zone);
	node_handle.getParam("origin_y", zone);
	node_handle.getParam("origin_z", zone);
	
	node_handle.getParam("zone", zone);
	node_handle.getParam("is_north_hemisphere", northp);

	lla_utm_converter converter(zone, northp, origin_x, origin_y, origin_z); 

	// Subscribe to the GPS fix messages
	ros::Subscriber fix_subscriber = node_handle.subscribe("fix", 1, &lla_utm_converter::handle_fix, &converter);

	// Publish converted UTM messages
	converter.utm_publisher = node_handle.advertise<geometry_msgs::Point>("utm", 1, true);
	
	
	ros::Duration(2.0).sleep();
	ros::Rate loop_rate(10); 
	while(ros::ok()){
		converter.lla_to_utm();
		converter.publish_position(); 
		ros::spinOnce();
		loop_rate.sleep(); 
	}
	return 0; 
}
