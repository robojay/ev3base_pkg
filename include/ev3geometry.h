#ifndef _EV3GEOMETRY_H_
#define _EV3GEOMETRY_H_

#include<math.h>

const double WheelSpacingMM = 144.25;  // was 127.0, 150.45
const double WheelDiameterMM = 68.0;  // was 68.8
const double WheelCircumferenceMM = M_PI * WheelDiameterMM;

const int CountsPerRotation = 360;

const double DistancePerCountMM = WheelCircumferenceMM / CountsPerRotation;

const double TurningCircumferenceMM = WheelSpacingMM * M_PI;

const double WheelSpacingM = WheelSpacingMM / 1000.0;
const double WheelDiameterM = WheelDiameterMM / 1000.0;
const double WheelCircumferenceM = WheelCircumferenceMM / 1000.0;

const double DistancePerCountM = DistancePerCountMM / 1000.0;

const double TurningCircumferenceM = TurningCircumferenceMM / 1000.0;

#endif
