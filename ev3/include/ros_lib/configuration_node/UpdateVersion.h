#ifndef _ROS_SERVICE_UpdateVersion_h
#define _ROS_SERVICE_UpdateVersion_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace configuration_node
{

static const char UPDATEVERSION[] = "configuration_node/UpdateVersion";

  class UpdateVersionRequest : public ros::Msg
  {
    public:

    UpdateVersionRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return UPDATEVERSION; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class UpdateVersionResponse : public ros::Msg
  {
    public:
      typedef bool _res_type;
      _res_type res;

    UpdateVersionResponse():
      res(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_res;
      u_res.real = this->res;
      *(outbuffer + offset + 0) = (u_res.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->res);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_res;
      u_res.base = 0;
      u_res.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->res = u_res.real;
      offset += sizeof(this->res);
     return offset;
    }

    const char * getType(){ return UPDATEVERSION; };
    const char * getMD5(){ return "e27848a10f8e7e4030443887dfea101b"; };

  };

  class UpdateVersion {
    public:
    typedef UpdateVersionRequest Request;
    typedef UpdateVersionResponse Response;
  };

}
#endif
