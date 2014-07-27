// File:           serial_port.hpp
// Creation Date:  Thursday, October  8 2009
// Author:         Julius Ziegler <ziegler@mrt.uka.de>

#if !defined(SERIAL_PORT_HPP)
#define SERIAL_PORT_HPP

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <string>

extern int initport( std::string port );

#endif
