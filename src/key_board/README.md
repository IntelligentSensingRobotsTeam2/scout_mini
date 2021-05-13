# 本仓库是ros的一个package(C++)，通过读取键盘按键"w"，"a"，"s"，"d"按键指令发送指定的topic，此package可以用来简单控制机器人移动
topic名称为`cmd_vel`，数据类型为`geometry_msgs::Twist`，控制的是机器人的**速度**
# 1.编译安装
将此仓库clone到`catkin_ws/src`后，回到`catkin_ws`工作路径下，执行编译命令即可


注意：如何提示找不到`boost`库，需要安装`boost`库。`sudo apt-get install boost`
# 2.运行
运行：`rosrun keyboard keyboard_node`
# 3.使用
鼠标选中运行节点的终端，"w"，"a"，"s"，"d"键控制前后左右运动(shift+"w"会加速)


**如果希望机器人一直运动，按下按键不动即可循环发送命令，松开则机器人停止**
# 4.代码机制
**当按键按下时才会发布topic，按键未按下时不会发布topic**


按下按键后会发送两次topic，第一次是设定的速度，第二次是将速度置为0后再次发出，避免机器人一直是设定的速度


