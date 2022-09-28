#include <ros/ros.h>
#include <ros/package.h>
#include "trainer/LUT.h"
#include <fstream>

//-----Timer
ros::Timer tim50hz_routine;

ros::Subscriber sub_LUT_buffer;

void cllbck_sub_LUT_buffer(const trainer::LUTConstPtr &msg)
{
    printf("LUT buffer size: %d last %d\n", msg->data.size(), msg->data[115199]);
    char buffer[230400];
    for (int i = 0; i < 115200; i++)
    {
        // printf("tes[%d] %d\n", i, msg->data[i]);
        memcpy(buffer + (i * 2), &msg->data[i], 2);
    }

    // memcpy(buffer,msg->data,)
    uint16_t cek;
    memcpy(&cek, buffer + 230398, 2);
    printf("lastt %d\n", cek);
    std::string path_buf = ros::package::getPath("trainer");
    char filename[64];
    sprintf(filename, "%s/../../LUT/LUT_fr2lap.bin", path_buf.c_str());
    printf("file: %s\n", filename);
    std::ofstream file(filename, std::ios::binary | std::ios::out);
    file.write(buffer, 230400);
    file.close();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "To_bytes");
    ros::NodeHandle NH;
    ros::MultiThreadedSpinner MTS;

    // while (1)
    // {
    //     uint16_t a = 100;
    //     uint64_t start = ros::Time::now().toNSec();
    //     if (a > 90)
    //         a = 90;
    //     printf("if: %ld\n", ros::Time::now().toNSec() - start);

    //     uint16_t b = 100;
    //     uint64_t start2 = ros::Time::now().toNSec();
    //     b %= 90;
    //     printf("mod: %ld\n", ros::Time::now().toNSec() - start2);
    // }

    sub_LUT_buffer = NH.subscribe("LUT_buffer", 16, cllbck_sub_LUT_buffer);

    MTS.spin();

    return 0;
}