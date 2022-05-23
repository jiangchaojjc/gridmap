/*
author:jiangchao
date:2022.03.30
description:dynamic window algorithm
*/
#include "gridmap.h"

GridMap::GridMap()
{
    ROS_INFO("struct class");
    ros::NodeHandle nh_private("~");
    nh_private.param<std::string>("w_filename", this->w_filename, "/home/jc/Mapdata/040101.txt");
    this->sub = node_.subscribe("/map", 100, &GridMap::mapCallback, this);
}

void GridMap::mapCallback(const nav_msgs::OccupancyGrid& map)
{
    ROS_INFO("receive map data");
    map_info_.resolution = map.info.resolution;
    map_info_.width = map.info.width;
    map_info_.height = map.info.height;
    // world_map_ = new int *[height];
    // for(int i = 0; i< height; i++)
    // {
    //     world_map_[i] = new int[width];
    // }
    // for(int i = 0; i < width; i++)
    // {
    //     for(int j = 0; j < height; j++)s
    //     {
    //         world_map_[i][j] = map->data[i*width + j];
    //     }
    // }
    world_map_.clear();
    std::vector<int> tmp_row_map_;
    for(int i = 0; i < map_info_.height; i++)
    {
        for(int j =0;j < map_info_.width; j++)
        {
            tmp_row_map_.push_back(map.data[i*map_info_.width + j]);
        }
        world_map_.push_back(tmp_row_map_);
        tmp_row_map_.clear();
    }
    GridMap::writeGridMapToTxt(w_filename, world_map_);

}

void GridMap::writeGridMapToTxt(const string& filePath, const std::vector<std::vector<int> >& gridMap)
{
    ofstream output;
    output.open(filePath);
    if (!output)
    {
        ROS_INFO("have no grid map ");
    }
    else
    {
        output << "height" << " " << gridMap.size() << " " << "width" << " " << gridMap[2].size() << endl; 
        for (int i = 0; i < gridMap.size(); i++)
        {
            for (int j = 0; j < gridMap[i].size(); j++)
            {
                output << gridMap[i][j] << " "; 
            }
            output << endl;
        }

        // for (auto i = gridMap.begin(); i != gridMap.end(); i++)
		// {
		// 	for (auto j = (*i).begin(); j != (*i).end(); j++)
		// 	{
		// 		output << (*j) << " ";
		// 	}
        //     output << endl;
		// }
    }
    output.close();

}

GridMap::~GridMap()
{
    // for(int i = 0;i<width;i++ )
    // {
    //     delete[] world_map_[i];
    // }
    // delete[] world_map_;
    
    
}

int main(int argc, char * argv[]) 
{
    //string w_filename = "/home/jc/Mapdata/040101.txt";
    ros::init(argc, argv, "gridMap");
    ROS_INFO("gridmap node start! ");

    GridMap GridMap_;
    ros::spin();
    return 0;
}

