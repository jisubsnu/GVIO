//TrafficLight : message
//traffic_light : topic
#include "ros/ros.h"
#include "sensor_msgs/NavSatFix.h"
#include "irp_sen_msgs/vrs.h"

ros::Publisher navsatfix_pub;

void vrscallback(const irp_sen_msgs::vrs& vrs){
    sensor_msgs::NavSatFix nav_;
    nav_.header = vrs.header;
    nav_.latitude = vrs.latitude;
    nav_.longitude = vrs.longitude;
    nav_.altitude = vrs.altitude;
    
    nav_.position_covariance[0] = vrs.lon_std;
    nav_.position_covariance[4] = vrs.lat_std;
    nav_.position_covariance[8] = vrs.altitude_std;

    navsatfix_pub.publish(nav_);
    
    return;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "vrs_to_navsatfix");
    ros::NodeHandle n;

    navsatfix_pub = n.advertise<sensor_msgs::NavSatFix>("/ref_gps/fix",1);
    ros::Subscriber vrs_sub = n.subscribe ("/vrs_gps_data", 1, vrscallback);
    ros::spin();

    return 0;
}

