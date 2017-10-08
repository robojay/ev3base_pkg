#ifndef _ROS_ev3base_pkg_MotorState_h
#define _ROS_ev3base_pkg_MotorState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace ev3base_pkg
{

  class MotorState : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      char* state[2];

    MotorState():
      header(),
      state()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 2; i++){
      uint32_t length_statei = strlen(this->state[i]);
      varToArr(outbuffer + offset, length_statei);
      offset += 4;
      memcpy(outbuffer + offset, this->state[i], length_statei);
      offset += length_statei;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 2; i++){
      uint32_t length_statei;
      arrToVar(length_statei, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_statei; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_statei-1]=0;
      this->state[i] = (char *)(inbuffer + offset-1);
      offset += length_statei;
      }
     return offset;
    }

    const char * getType(){ return "ev3base_pkg/MotorState"; };
    const char * getMD5(){ return "ebf1fee43bb5a850f0495036704a02da"; };

  };

}
#endif