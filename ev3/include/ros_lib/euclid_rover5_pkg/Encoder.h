#ifndef _ROS_euclid_rover5_pkg_Encoder_h
#define _ROS_euclid_rover5_pkg_Encoder_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace euclid_rover5_pkg
{

  class Encoder : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      int32_t count[4];

    Encoder():
      header(),
      count()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_counti;
      u_counti.real = this->count[i];
      *(outbuffer + offset + 0) = (u_counti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_counti.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_counti.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_counti.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->count[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 4; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_counti;
      u_counti.base = 0;
      u_counti.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_counti.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_counti.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_counti.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->count[i] = u_counti.real;
      offset += sizeof(this->count[i]);
      }
     return offset;
    }

    const char * getType(){ return "euclid_rover5_pkg/Encoder"; };
    const char * getMD5(){ return "31c84ba1655ee25f3f582ccc7da7f6a4"; };

  };

}
#endif