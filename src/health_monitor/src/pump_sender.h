#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
// #include <boost/archive/


class Pump {
public:
  int lowest_angle = 0;
  int highest_angle = 45;
  //- 初始角度为35度
  int current_angle = 35;
  bool is_pump_open = false;
  int fd = -1;
  //- 在构造函数中开启串口，并设置相关参数
  Pump() {
    fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY);
    if (fd < 0) {
      std::cout << "Error Can't connect pump." << errno << std::endl;
      return;
    }
    struct termios tty;
    struct termios tty_old;
    memset(&tty, 0, sizeof tty);

    /* Error Handling */
    if (tcgetattr(fd, &tty) != 0) {
      std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno)
                << std::endl;
    }

    /* Save old tty parameters */
    tty_old = tty;

    /* Set Baud Rate */
    cfsetospeed(&tty, (speed_t)B9600);
    cfsetispeed(&tty, (speed_t)B9600);

    /* Setting other Port Stuff */
    tty.c_cflag &= ~PARENB; // Make 8n1
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;

    tty.c_cflag &= ~CRTSCTS;       // no flow control
    tty.c_cc[VMIN] = 0;            // read doesn't block
    tty.c_cc[VTIME] = 0;           // 0.5 seconds read timeout
    tty.c_cflag |= CREAD | CLOCAL; // turn on READ & ignore ctrl lines

    /* Make raw */
    cfmakeraw(&tty);

    /* Flush Port, then applies attributes */
    tcflush(fd, TCIFLUSH);
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
      std::cout << "Error " << errno << " from tcsetattr" << std::endl;
    }
  }

  //- angle不在范围内时，不需要设置角度
  int send_state(bool open_pump, int angle) {
    std::cout << "send_state open_pump = " << open_pump << "; angle = " << angle << std::endl;
    std::cout << "send_state is_open_pump = " << is_pump_open << "; cur_angle = " << current_angle << std::endl;
    if (fd < 0) return -1;
    // bool change_angle = angle >= lowest_angle && angle <= highest_angle;
    bool change_angle = (angle != -1);
    bool change_pump_state = (open_pump != is_pump_open);
    //- 水泵已经设置为相应状态，可以直接返回成功
    if (!change_pump_state && !change_angle) {
      return 0;
    }
    unsigned char cmd[4];
    cmd[0] = is_pump_open ? '1' : '0';
    //- '0'的ascii码是48
    cmd[1] = current_angle / 10 + 48;
    cmd[2] = current_angle % 10 + 48;
    cmd[3] = '\0';
    if (change_pump_state) {
      is_pump_open = open_pump;
      cmd[0] = open_pump ? '1' : '0';      
    }
    if (change_angle) {
      if (angle <= lowest_angle) angle = lowest_angle;
      if (angle >= highest_angle) angle = highest_angle;
      current_angle = angle;
      cmd[1] = angle / 10 + 48;
      cmd[2] = angle % 10 + 48;
    }
    std::cout << "send_state final res: " << cmd << std::endl;

    int n_written = 0, spot = 0;
    do {
      n_written = write(fd, &cmd[spot], 1);
      spot += n_written;
    } while (cmd[spot - 1] != '\n' && n_written > 0);

    // //- Start reading
    // int n = 0, spot2 = 0;
    // char buf = '\0';

    // /* Whole response*/
    // char response[1024];
    // memset(response, '\0', sizeof response);

    // do {
    //   n = read(fd, &buf, 1);
    //   sprintf(&response[spot2], "%c", buf);
    //   spot2 += n;
    // } while (buf != '\n' && n > 0);
    // // } while (n > 0);

    // if (n < 0) {
    //   std::cout << "Error reading: " << strerror(errno) << std::endl;
    // } else if (n == 0) {
    //   std::cout << "Read nothing!" << std::endl;
    // } else {
    //   std::cout << "Response: " << response << std::endl;
    // }
    return 0;
  }
};