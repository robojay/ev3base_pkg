#ifndef _EV3GEOMETRY_H_
#define _EV3GEOMETRY_H_

#include<math.h>

//=========================================================
// Assuming equal wheel diameters

const double WheelSpacingMM = 144.0;  // was 127.0, 150.45
const double WheelDiameterMM = 67.0;  // was 68.8
const double WheelCircumferenceMM = M_PI * WheelDiameterMM;

const int CountsPerRotation = 360;

const double DistancePerCountMM = WheelCircumferenceMM / CountsPerRotation;

const double TurningCircumferenceMM = WheelSpacingMM * M_PI;

const double WheelSpacingM = WheelSpacingMM / 1000.0;
const double WheelDiameterM = WheelDiameterMM / 1000.0;
const double WheelCircumferenceM = WheelCircumferenceMM / 1000.0;

const double DistancePerCountM = DistancePerCountMM / 1000.0;

const double TurningCircumferenceM = TurningCircumferenceMM / 1000.0;

//=========================================================
// Assuming unequal wheel diameters

const double WheelDiameterLeftMM = 68.8;
const double WheelDiameterRightMM = 68.8;

const double CountsPerRadian = CountsPerRotation / (2.0 * M_PI);

const double DistanceMMtoCountsLeft = (2.0 * CountsPerRadian) / WheelDiameterLeftMM;
const double DistanceMMtoCountsRight = (2.0 * CountsPerRadian) / WheelDiameterRightMM;

const double WheelDiameterRatio = WheelDiameterLeftMM / WheelDiameterRightMM;

#endif
