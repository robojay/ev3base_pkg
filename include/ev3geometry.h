#ifndef _EV3GEOMETRY_H_
#define _EV3GEOMETRY_H_

#include<math.h>

const double WheelSpacingM = 120.0 / 1000.0;
const double WheelDiameterM = 94.2 / 1000.0;
const double WheelCircumferenceM = M_PI * WheelDiameterM;

const int CountsPerRotation = 360;

const double DistancePerCountM = WheelCircumferenceM / CountsPerRotation;

#endif
