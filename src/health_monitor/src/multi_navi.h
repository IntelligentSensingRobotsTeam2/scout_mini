#include <actionlib/client/client_helpers.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/simple_client_goal_state.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <ros/ros.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction>
    MoveBaseClient;
typedef actionlib::ClientGoalHandle<move_base_msgs::MoveBaseAction> GoalHandler;

class MyMBClient {
public:
  MoveBaseClient *mbc;
  std::vector<move_base_msgs::MoveBaseGoal> points;
  bool continue_navi;
  int next_visited;

  MyMBClient() {
    ROS_INFO("START MoveBaseClient......");
    // tell the action client that we want to spin a thread by default
    mbc = new MoveBaseClient("move_base", true);
    continue_navi = true;
    next_visited = 0;
    update_goals();
  }

  ~MyMBClient() { delete mbc; }

  void add_point(const geometry_msgs::PoseStamped::ConstPtr &input_pose) {
    // move_base_msgs::MoveBaseGoal temp;
    // temp.target_pose.header = input_pose->header;
    // temp.target_pose.pose = input_pose->pose;
    // points.push_back(temp);
  }

  void update_goals() {
    geometry_msgs::PoseStamped poses[8];
    for (int i = 0; i < 8; i++) {
      poses[i].header.seq = i;
      poses[i].header.frame_id = "map";
      poses[i].pose.position.z = 0.0;
      poses[i].pose.orientation.x = 0.0;
      poses[i].pose.orientation.y = 0.0;
    }
    // point 0
    poses[0].pose.position.x = -2.29340720177;
    poses[0].pose.position.y = 2.95441246033;
    poses[0].pose.orientation.z = 0.978049748461;
    poses[0].pose.orientation.w = 0.208371518052;

    // point 1
    poses[0].pose.position.x = -3.3362865448;
    poses[0].pose.position.y = 2.83931541443;
    poses[0].pose.orientation.z = 0.873498456754;
    poses[0].pose.orientation.w = -0.486826915904;

    // point 2
    poses[0].pose.position.x = -3.49701356888;
    poses[0].pose.position.y = 1.80556762218;
    poses[0].pose.orientation.z = -0.390330174908;
    poses[0].pose.orientation.w = 0.920674945111;

    // point 3
    poses[0].pose.position.x = -2.51073765755;
    poses[0].pose.position.y = 0.796154260635;
    poses[0].pose.orientation.z = -0.240420147513;
    poses[0].pose.orientation.w = 0.970668920214;

    // point 4
    poses[0].pose.position.x = -1.4834010601;
    poses[0].pose.position.y = 0.0788714885712;
    poses[0].pose.orientation.z = -0.183088773279;
    poses[0].pose.orientation.w = 0.98309638444;

    // point 5
    poses[0].pose.position.x = -0.582492828369;
    poses[0].pose.position.y = -0.0144414901733;
    poses[0].pose.orientation.z = 0.460476584339;
    poses[0].pose.orientation.w = 0.887671851123;

    // point 6
    poses[0].pose.position.x = -0.0586119890213;
    poses[0].pose.position.y = 1.14768576622;
    poses[0].pose.orientation.z = 0.961113978492;
    poses[0].pose.orientation.w = 0.276151987766;

    // point 7
    poses[0].pose.position.x = -1.12363874912;
    poses[0].pose.position.y = 2.04735898972;
    poses[0].pose.orientation.z = 0.969075905743;
    poses[0].pose.orientation.w = 0.246762819138;

    for (int i = 0; i < 8; i++) {
      move_base_msgs::MoveBaseGoal temp;
      temp.target_pose.header = poses[i].header;
      temp.target_pose.pose = poses[i].pose;
      points.push_back(temp);
    }
  }

  void start_navi() {
    continue_navi = true;
    int len = points.size();
    int idx = next_visited;
    next_visited = idx;
    while (continue_navi) {
      actionlib::SimpleClientGoalState st = mbc->sendGoalAndWait(points[idx]);
      idx++;
      idx = idx % len;
    }
  }

  void cancel_navi() {
    continue_navi = false;
    //   mbc->cancelAllGoals();
    mbc->cancelGoal();
  }
};