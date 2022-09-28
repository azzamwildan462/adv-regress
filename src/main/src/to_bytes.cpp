// #include <ros/ros.h>
// #include "main/LUT.h"

// //-----Timer
// ros::Timer tim50hz_routine;

// ros::Subscriber sub_LUT_buffer;

// void cllbck_sub_LUT_buffer(const main::LUTConstPtr &msg)
// {
// }

// int main(int argc, char **argv)
// {
//     ros::init(argc, argv, "To_bytes");
//     ros::NodeHandle NH;
//     // ros::MultiThreadedSpinner MTS;

//     sub_LUT_buffer = NH.subscribe("LUT_buffer", 16, cllbck_sub_LUT_buffer);

//     return 0;
// }