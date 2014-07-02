#ifndef _ROS_flexcraft_msgs_thrusters8_h
#define _ROS_flexcraft_msgs_thrusters8_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace flexcraft_msgs
{

  class thrusters8 : public ros::Msg
  {
    public:
      uint32_t seq;
      uint8_t thrusters;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->seq >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->seq >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->seq >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->seq >> (8 * 3)) & 0xFF;
      offset += sizeof(this->seq);
      *(outbuffer + offset + 0) = (this->thrusters >> (8 * 0)) & 0xFF;
      offset += sizeof(this->thrusters);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->seq =  ((uint32_t) (*(inbuffer + offset)));
      this->seq |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->seq |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->seq |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->seq);
      this->thrusters =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->thrusters);
     return offset;
    }

    const char * getType(){ return "flexcraft_msgs/thrusters8"; };
    const char * getMD5(){ return "370bbe62d17a52f681cf14a95ef34b00"; };

  };

}
#endif