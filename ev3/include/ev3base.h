#ifndef _EV3BASE_HPP_
#define _EV3BASE_HPP_

char RosSrvrIp[] = "192.168.8.50";
const std::chrono::milliseconds OdometryTime(20);
char EncodersTopic[] = "/ev3/encoders";

ros::NodeHandle nh;

ev3base_pkg::Encoder encoderMessage;
ros::Publisher encoders(EncodersTopic, &encoderMessage);

const int Left = 0;
const int Right = 1;

class Ev3Base {
	public:
		const ev3dev::address_type LeftMotorPort = ev3dev::OUTPUT_A;
		const ev3dev::address_type RightMotorPort = ev3dev::OUTPUT_D;

		//double distancePerCountM;
		double maxSpeedMetersPerSecond;
		ev3dev::large_motor leftMotor;
		ev3dev::large_motor rightMotor;

		Ev3Base();
};

Ev3Base ev3Base;

#endif
