#ifndef _ROS_realsense_camera_SamplingData_h
#define _ROS_realsense_camera_SamplingData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace realsense_camera
{

  class SamplingData : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef double _timestamp_type;
      _timestamp_type timestamp;
      typedef double _exposure_type;
      _exposure_type exposure;
      typedef int32_t _frame_number_type;
      _frame_number_type frame_number;

    SamplingData():
      header(),
      timestamp(0),
      exposure(0),
      frame_number(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_timestamp;
      u_timestamp.real = this->timestamp;
      *(outbuffer + offset + 0) = (u_timestamp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_timestamp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_timestamp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_timestamp.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_timestamp.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_timestamp.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_timestamp.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_timestamp.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->timestamp);
      union {
        double real;
        uint64_t base;
      } u_exposure;
      u_exposure.real = this->exposure;
      *(outbuffer + offset + 0) = (u_exposure.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_exposure.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_exposure.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_exposure.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_exposure.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_exposure.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_exposure.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_exposure.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->exposure);
      union {
        int32_t real;
        uint32_t base;
      } u_frame_number;
      u_frame_number.real = this->frame_number;
      *(outbuffer + offset + 0) = (u_frame_number.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_frame_number.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_frame_number.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_frame_number.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->frame_number);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      union {
        double real;
        uint64_t base;
      } u_timestamp;
      u_timestamp.base = 0;
      u_timestamp.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_timestamp.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_timestamp.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_timestamp.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_timestamp.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_timestamp.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_timestamp.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_timestamp.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->timestamp = u_timestamp.real;
      offset += sizeof(this->timestamp);
      union {
        double real;
        uint64_t base;
      } u_exposure;
      u_exposure.base = 0;
      u_exposure.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_exposure.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_exposure.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_exposure.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_exposure.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_exposure.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_exposure.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_exposure.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->exposure = u_exposure.real;
      offset += sizeof(this->exposure);
      union {
        int32_t real;
        uint32_t base;
      } u_frame_number;
      u_frame_number.base = 0;
      u_frame_number.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_frame_number.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_frame_number.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_frame_number.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->frame_number = u_frame_number.real;
      offset += sizeof(this->frame_number);
     return offset;
    }

    const char * getType(){ return "realsense_camera/SamplingData"; };
    const char * getMD5(){ return "6cc4d158d085cdb659cd17f8618832c0"; };

  };

}
#endif