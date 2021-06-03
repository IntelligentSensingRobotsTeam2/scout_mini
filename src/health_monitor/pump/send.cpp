#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

int main() {
  int USB = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);

  struct termios tty;
  struct termios tty_old;
  memset(&tty, 0, sizeof tty);

  /* Error Handling */
  if (tcgetattr(USB, &tty) != 0) {
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
  tcflush(USB, TCIFLUSH);
  if (tcsetattr(USB, TCSANOW, &tty) != 0) {
    std::cout << "Error " << errno << " from tcsetattr" << std::endl;
  }

  for (int ii = 0; ii < 10; ii++) {
    std::cout << "ii = " << ii << std::endl;
    //- Start writing
    unsigned char cmd[] = "1\0";
    unsigned char cmd2[] = "0\0";
    
    int n_written = 0, spot = 0;
    do {
      if (ii%2 == 0) {
        n_written = write(USB, &cmd[spot], 1);
      } else {
        n_written = write(USB, &cmd2[spot], 1);
      }
      
      spot += n_written;
    } while (cmd[spot - 1] != '\n' && n_written > 0);
    //- my version
    // unsigned int w = 1;
    // int n_written = write(USB, &w, sizeof(w));
    // std::cout << "n_written: " << n_written << std::endl;

    //- Start reading
    int n = 0, spot2 = 0;
    char buf = '\0';

    /* Whole response*/
    char response[1024];
    memset(response, '\0', sizeof response);

    do {
      n = read(USB, &buf, 1);
      sprintf(&response[spot2], "%c", buf);
      spot2 += n;
    } while (buf != '\n' && n > 0);

    if (n < 0) {
      std::cout << "Error reading: " << strerror(errno) << std::endl;
    } else if (n == 0) {
      std::cout << "Read nothing!" << std::endl;
    } else {
      std::cout << "Response: " << response << std::endl;
    }
    sleep(3);
  }

  return 0;
}
