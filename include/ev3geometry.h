#ifndef _EV3GEOMETRY_H_
#define _EV3GEOMETRY_H_

#include<math.h>

const double WheelSpacingMM = 150.45;  // was 127.0
const double WheelDiameterMM = 69.8;  // was 68.8
const double WheelCircumferenceMM = M_PI * WheelDiameterMM;

const int CountsPerRotation = 360;

const double DistancePerCountMM = WheelCircumferenceMM / CountsPerRotation;

#endif
