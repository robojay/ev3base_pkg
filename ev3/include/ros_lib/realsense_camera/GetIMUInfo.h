#ifndef _ROS_SERVICE_GetIMUInfo_h
#define _ROS_SERVICE_GetIMUInfo_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "realsense_camera/IMUInfo.h"

namespace realsense_camera
{

static const char GETIMUINFO[] = "realsense_camera/GetIMUInfo";

  class GetIMUInfoRequest : public ros::Msg
  {
    public:

    GetIMUInfoRequest()
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

    const char * getType(){ return GETIMUINFO; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetIMUInfoResponse : public ros::Msg
  {
    public:
      typedef realsense_camera::IMUInfo _accel_type;
      _accel_type accel;
      typedef realsense_camera::IMUInfo _gyro_type;
      _gyro_type gyro;
      double depth_to_fisheye_rotation[9];
      double fisheye_to_imu_rotation[9];
      double fisheye_to_imu_translation[3];
      double depth_to_fisheye_translation[3];

    GetIMUInfoResponse():
      accel(),
      gyro(),
      depth_to_fisheye_rotation(),
      fisheye_to_imu_rotation(),
      fisheye_to_imu_translation(),
      depth_to_fisheye_translation()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->accel.serialize(outbuffer + offset);
      offset += this->gyro.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 9; i++){
      union {
        double real;
        uint64_t base;
      } u_depth_to_fisheye_rotationi;
      u_depth_to_fisheye_rotationi.real = this->depth_to_fisheye_rotation[i];
      *(outbuffer + offset + 0) = (u_depth_to_fisheye_rotationi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_depth_to_fisheye_rotationi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_depth_to_fisheye_rotationi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_depth_to_fisheye_rotationi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_depth_to_fisheye_rotationi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_depth_to_fisheye_rotationi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_depth_to_fisheye_rotationi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_depth_to_fisheye_rotationi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->depth_to_fisheye_rotation[i]);
      }
      for( uint32_t i = 0; i < 9; i++){
      union {
        double real;
        uint64_t base;
      } u_fisheye_to_imu_rotationi;
      u_fisheye_to_imu_rotationi.real = this->fisheye_to_imu_rotation[i];
      *(outbuffer + offset + 0) = (u_fisheye_to_imu_rotationi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fisheye_to_imu_rotationi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fisheye_to_imu_rotationi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fisheye_to_imu_rotationi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_fisheye_to_imu_rotationi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_fisheye_to_imu_rotationi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_fisheye_to_imu_rotationi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_fisheye_to_imu_rotationi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->fisheye_to_imu_rotation[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_fisheye_to_imu_translationi;
      u_fisheye_to_imu_translationi.real = this->fisheye_to_imu_translation[i];
      *(outbuffer + offset + 0) = (u_fisheye_to_imu_translationi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_fisheye_to_imu_translationi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_fisheye_to_imu_translationi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_fisheye_to_imu_translationi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_fisheye_to_imu_translationi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_fisheye_to_imu_translationi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_fisheye_to_imu_translationi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_fisheye_to_imu_translationi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->fisheye_to_imu_translation[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_depth_to_fisheye_translationi;
      u_depth_to_fisheye_translationi.real = this->depth_to_fisheye_translation[i];
      *(outbuffer + offset + 0) = (u_depth_to_fisheye_translationi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_depth_to_fisheye_translationi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_depth_to_fisheye_translationi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_depth_to_fisheye_translationi.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_depth_to_fisheye_translationi.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_depth_to_fisheye_translationi.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_depth_to_fisheye_translationi.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_depth_to_fisheye_translationi.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->depth_to_fisheye_translation[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->accel.deserialize(inbuffer + offset);
      offset += this->gyro.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 9; i++){
      union {
        double real;
        uint64_t base;
      } u_depth_to_fisheye_rotationi;
      u_depth_to_fisheye_rotationi.base = 0;
      u_depth_to_fisheye_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_depth_to_fisheye_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_depth_to_fisheye_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_depth_to_fisheye_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_depth_to_fisheye_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_depth_to_fisheye_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_depth_to_fisheye_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_depth_to_fisheye_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->depth_to_fisheye_rotation[i] = u_depth_to_fisheye_rotationi.real;
      offset += sizeof(this->depth_to_fisheye_rotation[i]);
      }
      for( uint32_t i = 0; i < 9; i++){
      union {
        double real;
        uint64_t base;
      } u_fisheye_to_imu_rotationi;
      u_fisheye_to_imu_rotationi.base = 0;
      u_fisheye_to_imu_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fisheye_to_imu_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fisheye_to_imu_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fisheye_to_imu_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_fisheye_to_imu_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_fisheye_to_imu_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_fisheye_to_imu_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_fisheye_to_imu_rotationi.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->fisheye_to_imu_rotation[i] = u_fisheye_to_imu_rotationi.real;
      offset += sizeof(this->fisheye_to_imu_rotation[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_fisheye_to_imu_translationi;
      u_fisheye_to_imu_translationi.base = 0;
      u_fisheye_to_imu_translationi.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_fisheye_to_imu_translationi.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_fisheye_to_imu_translationi.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_fisheye_to_imu_translationi.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_fisheye_to_imu_translationi.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_fisheye_to_imu_translationi.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_fisheye_to_imu_translationi.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_fisheye_to_imu_translationi.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->fisheye_to_imu_translation[i] = u_fisheye_to_imu_translationi.real;
      offset += sizeof(this->fisheye_to_imu_translation[i]);
      }
      for( uint32_t i = 0; i < 3; i++){
      union {
        double real;
        uint64_t base;
      } u_depth_to_fisheye_translationi;
      u_depth_to_fisheye_translationi.base = 0;
      u_depth_to_fisheye_translationi.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_depth_to_fisheye_translationi.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_depth_to_fisheye_translationi.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_depth_to_fisheye_translationi.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_depth_to_fisheye_translationi.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_depth_to_fisheye_translationi.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_depth_to_fisheye_translationi.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_depth_to_fisheye_translationi.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->depth_to_fisheye_translation[i] = u_depth_to_fisheye_translationi.real;
      offset += sizeof(this->depth_to_fisheye_translation[i]);
      }
     return offset;
    }

    const char * getType(){ return GETIMUINFO; };
    const char * getMD5(){ return "2d50f0ecc87320a6b38a82a867759f22"; };

  };

  class GetIMUInfo {
    public:
    typedef GetIMUInfoRequest Request;
    typedef GetIMUInfoResponse Response;
  };

}
#endif
