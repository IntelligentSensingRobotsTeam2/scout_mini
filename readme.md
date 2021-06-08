## Introduction

Our *Health Monitor* is based on Scout Mini mobile robot, and this repo contains code related to its mapping and navigation functionality.

## Prerequisites

1. ROS:  *Health Monitor* is contrusted in the basis of ROS, so you need to install ROS before running. Code in this repo is tested in Ubuntu 18.04 with ROS melodic.
2. RTAB-Map: We select RTAB-Map as our SLAM library, and the relocalization of the robot is also done by RTAB-Map.  As a result, you need to install RTAB-Map before mapping and navigating.  Install RTAB-Map  from either ROS package or source code is fine.
3. Intel Realsense SDK for ROS: We use Intel Realsense D435 to offer RGB-D information, which is feeded to RTAB-Map, so related SDK should be installed.  
4. SLAMTEC RPLidar SDK for ROS: We use SLAMTEC RPLida A1 to generate laser scans, please install its ROS SDK in advance.

## Running

The ROS nodes in *Health Monitor* are separated by several launch files, and you can easily run our code by starting these launch files step by step.

#### Start Scout Mini

`roslaunch scout_base scout_base_debug.launch`

#### Start RTAB-Map for Mapping or Locolization
`roslaunch scout_bringup scout_rtab.launch`

#### Start Move Base for Navigation
`roslaunch scout_2dnav move_base.launch`

#### Start Controller to Send Command
`rosrun health_monitor hm_controller`

After finishing the above steps, you can generate map by using RTAB-Map and navigating by sending goals to move_base node directly. Moreover, you can also send multiple goals to the *Health Monitor* controller and then it will take charge of the navigation. 