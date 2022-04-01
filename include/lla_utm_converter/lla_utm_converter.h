#ifndef LLA_UTM_CONVERTER_H
#define LLA_UTM_CONVERTER_H

#include <iostream>
#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"
#include "geometry_msgs/Point.h"
#include <GeographicLib/TransverseMercator.hpp>


using namespace GeographicLib;
using namespace std; 

class lla_utm_converter{
	public:
		lla_utm_converter(int zone, bool northp, double origin_x, double origin_y, double origin_z);
		virtual ~lla_utm_converter();

		// GeographicLib functions
		void lla_to_utm();
		void Forward(double lat, double lon, double&x, double&y);
		
		// ROS functions	
		void handle_fix(const sensor_msgs::NavSatFix::ConstPtr& msg);
		void publish_position();
		ros::Publisher utm_publisher; 

	private:
		// GeographicLib variables
		int meridian_proj;
		const double false_easting = 500000.0;
		double false_northing;
		double utm_x;
		double utm_y;
	        double utm_z;	
		double origin_x;
		double origin_y;
		double origin_z;

		TransverseMercator tm; 
	
		// ROS variables
		sensor_msgs::NavSatFix lla; 	
		geometry_msgs::Point utm_pos; 
};

#endif
