#include "multi_navi.h"
#include "pump_sender.h"

#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <ros/ros.h>
#include <std_msgs/String.h>

#include <pthread.h>

//- 是否允许添加导航目标点
bool add_point = true;
//- 机器人是否停止
bool is_robot_stop = true;
//- 与单片机的通信
int fd = -1;
MyMBClient *multi_navi_client;
Pump *pump_sender;

void pump_state_cb(const std_msgs::String::ConstPtr &msg) {
  ROS_INFO("**pump_state_cb receive: [%s]", msg->data.c_str());
  if (strcmp(msg->data.c_str(), "0") == 0) {
    //- 关闭水泵
    pump_sender->send_state(false, -1);
  } else {
    //- 打开水泵
    pump_sender->send_state(true, -1);
  }
}

void camera_angle_cb(const std_msgs::String::ConstPtr &msg) {
  ROS_INFO("**camera_angle_cb receive: [%s]", msg->data.c_str());
  if (strcmp(msg->data.c_str(), "up") == 0) {
    pump_sender->send_state(pump_sender->is_pump_open,
                            pump_sender->current_angle + 5);
  } else {
    pump_sender->send_state(pump_sender->is_pump_open,
                            pump_sender->current_angle - 5);
  }
}
void *run_navi_node(void *ptr) {
  multi_navi_client->start_navi();
  return NULL;
}

void robot_walk_cb(const std_msgs::String::ConstPtr &msg) {
  ROS_INFO("**robot_walk_cb receive: [%s]", msg->data.c_str());
  if (strcmp(msg->data.c_str(), "0") == 0) {
    //- 已经停止了
    if (is_robot_stop) {
      return;
    }
    is_robot_stop = true;
    multi_navi_client->cancel_navi();
  } else {
    //- 机器人正在运动中
    if (!is_robot_stop) {
      return;
    }
    is_robot_stop = false;
    pthread_t tid;
    pthread_create(&tid, NULL, run_navi_node, NULL);
  }
}

//- 处理来自multi_navi_goal_panel.cpp的消息发布
void start_multi_navi(const std_msgs::String::ConstPtr &msg) {
  ROS_INFO("**start_multi_navi receive: [%s]", msg->data.c_str());
  is_robot_stop = false;
  add_point = false;
  //- 调用pthread开启
  pthread_t tid;
  pthread_create(&tid, NULL, run_navi_node, NULL);
  return;
}

//- 处理添加目标点请求
void navi_point_cb(const geometry_msgs::PoseStamped::ConstPtr &pose) {
  ROS_INFO("**navi_point_cb");
  //- 先判断还能不能加点
  if (add_point) {
    multi_navi_client->add_point(pose);
  }
}

// void go_to_dest_cb(const std_msgs::String::ConstPtr &msg1) {
//   multi_navi_client->go_to_point(2);
//   ros::Publisher pub_arrive = n.advertise<std_msgs::String>("arrive_dest", 100);
//   std_msgs::String msg;
//   std::stringstream ss;
//   ss << "hello world ";
//   msg.data = ss.str();
//   pub_arrive.publish(msg);
//   is_robot_stop = false;
//   pthread_t tid;
//   pthread_create(&tid, NULL, run_navi_node, NULL);
// }

int main(int argc, char **argv) {
  ros::init(argc, argv, "hm_controller");
  multi_navi_client = new MyMBClient();
  pump_sender = new Pump();
  ros::NodeHandle n;
  
  ros::Subscriber sub_pump_state =
      n.subscribe("pump_start", 1000, pump_state_cb);
  ros::Subscriber sub_camera_angle =
      n.subscribe("camera_angle", 1000, camera_angle_cb);
  ros::Subscriber sub_robot_walk =
      n.subscribe("robot_walk", 1000, robot_walk_cb);

  ros::Subscriber sub_multi_navi =
      n.subscribe("move_base_multi_navi", 1000, start_multi_navi);

  ros::Subscriber sub_navi_point = n.subscribe<geometry_msgs::PoseStamped>(
      "move_base_simple/goal_temp", 1000, navi_point_cb);

  // ros::Subscriber sub_to_dest = n.subscribe("go_to_dest", 100, go_to_dest_cb);

  ros::spin();

  return 0;
}