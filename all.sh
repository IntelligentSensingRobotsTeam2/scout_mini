#!/usr/bin/zsh

# 开启 robot
roslaunch scout_base scout_base_debug.launch;
roslaunch scout_bringup scout_rtab.launch localization:=true;
roslaunch scout_bringup navi.launch
publishing and latching message. Press ctrl-C to terminate