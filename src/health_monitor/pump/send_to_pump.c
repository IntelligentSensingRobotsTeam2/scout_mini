#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
// #include <iostream>

int set_opt(int, int, int, char, int);
int set_speed(int, int);
int uart_send(int fd, void *buf, int len);
int read_opt(int fd);

int main() {
  int fd, ret, i = 3;
  char *uart3 = "/dev/ttyUSB0";
  char *buffer = "1";
  int wirte_content = 1;

  printf("\r\nitop4412 uart3 writetest start\r\n");

  if ((fd = open(uart3, O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
    printf("open %s is failed", uart3);
  } else {
    // set_speed(fd, 9600);
    read_opt(fd);
    printf("open %s is success\n", uart3);
    // set_opt(fd, 115200, 8, 'N', 1);
    while (i--) {
      ret = uart_send(fd, buffer, strlen(buffer));
      //   ret = uart_send(fd, &wirte_content, sizeof(int));
      if (ret < 0)
        printf("write failed\n");
      else {
        printf("wr_static is %d\n", ret);
        /* Allocate memory for read buffer */
        char buf[256];
        memset(&buf, '\0', sizeof buf);
        /* *** READ *** */
        int n = read(fd, &buf, sizeof buf);
        printf("n = %d, Read Content: %s\n", n, buf);
      }
      if (!i)
        break;
      sleep(5);
    }
  }
  //   read_opt(fd);
  close(fd);
  return 0;
}

int read_opt(int fd) {
  struct termios oldtio;
  /*获取原有串口配置*/
  if (tcgetattr(fd, &oldtio) != 0) {
    perror("SetupSerial 1");
    return -1;
  }
  printf("Baud rate: %d\n", oldtio.c_ospeed);
  printf("Baud rate: %d\n", oldtio.c_ispeed);
  return 0;
}

int set_speed(int fd, int nSpeed) {
  struct termios newtio, oldtio;
  /*获取原有串口配置*/
  if (tcgetattr(fd, &oldtio) != 0) {
    perror("SetupSerial 1");
    return -1;
  }
  memset(&newtio, 0, sizeof(newtio));
  newtio.c_cflag = oldtio.c_cflag;
  newtio.c_iflag = oldtio.c_iflag;
  /* 设置波特率 */
  int baud_ret = 0;
  baud_ret = cfsetispeed(&newtio, B9600);
  printf("baud_ret = %d\n", baud_ret);
  baud_ret = cfsetospeed(&newtio, B9600);
  printf("baud_ret = %d\n", baud_ret);

  /*设置最少字符和等待时间，对于接收字符和等待时间没有特别的要求时*/
  newtio.c_cc[VTIME] = 0; /*非规范模式读取时的超时时间；*/
  newtio.c_cc[VMIN] = 0;  /*非规范模式读取时的最小字符数*/
  /*tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来
   */
  tcflush(fd, TCIFLUSH);
  if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) {
    perror("com set error");
    return -1;
  }
  printf("Set done! Baud rate: %d\n", newtio.c_ospeed);
  return 0;
}

int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop) {
  struct termios newtio, oldtio;
  /*获取原有串口配置*/
  if (tcgetattr(fd, &oldtio) != 0) {
    perror("SetupSerial 1");
    return -1;
  }
  memset(&newtio, 0, sizeof(newtio));
  /*CREAD 开启串行数据接收，CLOCAL并打开本地连接模式*/
  newtio.c_cflag |= CLOCAL | CREAD;

  /*设置数据位*/
  newtio.c_cflag &= ~CSIZE;
  switch (nBits) {
  case 7:
    newtio.c_cflag |= CS7;
    break;
  case 8:
    newtio.c_cflag |= CS8;
    break;
  }
  /* 设置奇偶校验位 */
  switch (nEvent) {
  case 'O':
    newtio.c_cflag |= PARENB;
    newtio.c_cflag |= PARODD;
    newtio.c_iflag |= (INPCK | ISTRIP);
    break;
  case 'E':
    newtio.c_iflag |= (INPCK | ISTRIP);
    newtio.c_cflag |= PARENB;
    newtio.c_cflag &= ~PARODD;
    break;
  case 'N':
    newtio.c_cflag &= ~PARENB;
    break;
  }
  /* 设置波特率 */
  switch (nSpeed) {
  case 2400:
    cfsetispeed(&newtio, B2400);
    cfsetospeed(&newtio, B2400);
    break;
  case 4800:
    cfsetispeed(&newtio, B4800);
    cfsetospeed(&newtio, B4800);
    break;
  case 9600:
    cfsetispeed(&newtio, B9600);
    cfsetospeed(&newtio, B9600);
    break;
  case 115200:
    cfsetispeed(&newtio, B115200);
    cfsetospeed(&newtio, B115200);
    break;
  case 460800:
    cfsetispeed(&newtio, B460800);
    cfsetospeed(&newtio, B460800);
    break;
  default:
    cfsetispeed(&newtio, B9600);
    cfsetospeed(&newtio, B9600);
    break;
  }
  /*设置停止位*/
  if (nStop ==
      1) /*设置停止位；若停止位为1，则清除CSTOPB，若停止位为2，则激活CSTOPB*/
    newtio.c_cflag &= ~CSTOPB; /*默认为一位停止位； */
  else if (nStop == 2)
    newtio.c_cflag |= CSTOPB;
  /*设置最少字符和等待时间，对于接收字符和等待时间没有特别的要求时*/
  newtio.c_cc[VTIME] = 0; /*非规范模式读取时的超时时间；*/
  newtio.c_cc[VMIN] = 0;  /*非规范模式读取时的最小字符数*/
  /*tcflush清空终端未完成的输入/输出请求及数据；TCIFLUSH表示清空正收到的数据，且不读取出来
   */
  tcflush(fd, TCIFLUSH);
  if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) {
    perror("com set error");
    return -1;
  }
  //  printf("set done!\n\r");
  return 0;
}

int uart_send(int fd, void *buf, int len) {
  int ret = 0;
  int count = 0;

  tcflush(fd, TCIFLUSH);

  while (len > 0) {

    ret = write(fd, (char *)buf + count, len);
    if (ret < 1) {
      break;
    }
    count += ret;
    len = len - ret;
  }

  return count;
}