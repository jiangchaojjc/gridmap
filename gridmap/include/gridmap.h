/*
author:jiangchao
data:2022.03.30
description:dynamic window algorithm
*/

#ifndef GRIDMAP_H
#define GRIDMAP_H
#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "nav_msgs/OccupancyGrid.h"
#include <stdio.h>
#include <pthread.h> 
#include<iostream>
#include<memory>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
//地图类

using namespace std;
struct mapInfo
{
    uint width;
    uint height;
    double resolution;
};
class GridMap
{
    public:
        GridMap();
        ~GridMap();
        static void writeGridMapToTxt(const string& filePath,
		const std::vector<std::vector<int> > &clean_boundary);
        boost::shared_ptr<nav_msgs::OccupancyGrid const> map_;
    private:
        ros::NodeHandle node_;
        ros::Subscriber sub;
        void mapCallback(const nav_msgs::OccupancyGrid& map);
        //std::shared_ptr<int**> world_map_;
        //int** world_map_;
        std::vector<std::vector<int> > world_map_;
        mapInfo map_info_;
        double g_min_free_ratio; 
        double g_max_free_ratio;
        string w_filename = "/home/jc/Mapdata/040101.txt";


};

#endif