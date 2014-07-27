// File:           serial_port.cpp
// Creation Date:  Thursday, October  8 2009
// Author:         Julius Ziegler <ziegler@mrt.uka.de>

#include "serial_port.hpp"

/*****************************************************************************
 *
 *      Op2en and initialise serial port
 *
 ****************************************************************************/

int initport( std::string port ) {
  int fd = open( port.c_str(), O_RDWR | O_NOCTTY );

  struct termios options;
  // Get the current options for the port...
  tcgetattr(fd, &options);
  // Set the baud rates to 19200...
  cfsetispeed(&options, B115200);
  cfsetospeed(&options, B115200);
  // Enable the receiver and set local mode...

  // options.c_cflag |= (CLOCAL | CREAD);
  
  //   options.c_cflag &= ~PARENB;
  //   options.c_cflag &= ~CSTOPB;
  //   options.c_cflag &= ~CSIZE;
  //   options.c_cflag |= CS8;

  options.c_cflag = B115200 | 0 | CS8 | 0 | 0 | 0 | CLOCAL | CREAD;
  options.c_iflag = IGNBRK;
  options.c_oflag = 0;
  options.c_lflag = 0;
  
  options.c_cc[VTIME] = 1;
  options.c_cc[VMIN]  = 0;

  // Set the new options for the port...
  if( tcflush( fd, TCIOFLUSH ) ) {
    throw "Error calling tcflush";
  }

  if( tcsetattr( fd, TCSANOW, &options ) ) {
    throw "Error calling tcsetattr";
  }

  return fd;
}

