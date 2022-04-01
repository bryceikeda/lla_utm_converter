#include "lla_utm_converter/lla_utm_converter.h"
#include <GeographicLib/TransverseMercator.hpp>

using namespace GeographicLib;


// Using default WGS84 a and f values and UTM central scale factor
lla_utm_converter::
lla_utm_converter(int zone, bool northp, double origin_x, double origin_y, double origin_z) :   tm(Constants::WGS84_a(), Constants::WGS84_f(), Constants::UTM_k0()), 
					  							false_northing((northp ? 0 : 100e5)), 
					   							meridian_proj(6 * zone - 183){
	if(!(zone >= 1 && zone <= 60)){
		throw GeographicErr("zone not in [1,60]");
	}
}
					   

lla_utm_converter::
~lla_utm_converter(){
}

void 
lla_utm_converter::
handle_fix(const sensor_msgs::NavSatFix::ConstPtr& msg)
{
	lla = *msg;
	return;
}

void 
lla_utm_converter::
Forward(double lat, double lon, double& x, double& y){
	tm.Forward(meridian_proj, lat, lon, x, y);
	x += false_easting; 
	y += false_northing; 
}

void
lla_utm_converter::
lla_to_utm(){	
	Forward(lla.latitude, lla.longitude, utm_x, utm_y);
	return;
}

void 
lla_utm_converter::
publish_position(){
	utm_pos.x = utm_x - origin_x;
	utm_pos.y = utm_y - origin_y;
	utm_pos.z = utm_z - origin_z; 	
	
	utm_publisher.publish(utm_pos);
}

