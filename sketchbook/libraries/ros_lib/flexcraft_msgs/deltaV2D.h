#ifndef _ROS_flexcraft_msgs_deltaV2D_h
#define _ROS_flexcraft_msgs_deltaV2D_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace flexcraft_msgs
{

  class deltaV2D : public ros::Msg
  {
    public:
      float deltaVX;
      float deltaVY;
      float alpha;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_deltaVX;
      u_deltaVX.real = this->deltaVX;
      *(outbuffer + offset + 0) = (u_deltaVX.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_deltaVX.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_deltaVX.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_deltaVX.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->deltaVX);
      union {
        float real;
        uint32_t base;
      } u_deltaVY;
      u_deltaVY.real = this->deltaVY;
      *(outbuffer + offset + 0) = (u_deltaVY.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_deltaVY.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_deltaVY.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_deltaVY.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->deltaVY);
      union {
        float real;
        uint32_t base;
      } u_alpha;
      u_alpha.real = this->alpha;
      *(outbuffer + offset + 0) = (u_alpha.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_alpha.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_alpha.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_alpha.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->alpha);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_deltaVX;
      u_deltaVX.base = 0;
      u_deltaVX.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_deltaVX.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_deltaVX.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_deltaVX.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->deltaVX = u_deltaVX.real;
      offset += sizeof(this->deltaVX);
      union {
        float real;
        uint32_t base;
      } u_deltaVY;
      u_deltaVY.base = 0;
      u_deltaVY.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_deltaVY.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_deltaVY.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_deltaVY.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->deltaVY = u_deltaVY.real;
      offset += sizeof(this->deltaVY);
      union {
        float real;
        uint32_t base;
      } u_alpha;
      u_alpha.base = 0;
      u_alpha.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_alpha.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_alpha.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_alpha.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->alpha = u_alpha.real;
      offset += sizeof(this->alpha);
     return offset;
    }

    const char * getType(){ return "flexcraft_msgs/deltaV2D"; };
    const char * getMD5(){ return "f241871ae291386cceaa12204ef3c616"; };

  };

}
#endif