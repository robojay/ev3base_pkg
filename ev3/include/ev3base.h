#ifndef _EV3BASE_HPP_
#define _EV3BASE_HPP_


char RosSrvrIp[] = "192.168.8.50";
const std::chrono::milliseconds OdometryTime(100);
char EncodersTopic[] = "/ev3/encoders";


//std_msgs::Int32 encodersMessage[2];
//ros::Publisher encoders(EncodersTopic, &encodersMessage);


class Ev3Base {
	public:
		const ev3dev::address_type LeftMotorPort = ev3dev::OUTPUT_A;
		const ev3dev::address_type RightMotorPort = ev3dev::OUTPUT_D;

		double distancePerCountM;
		double maxSpeedMetersPerSecond;
		ev3dev::large_motor leftMotor;
		ev3dev::large_motor rightMotor;

		struct Encoders {
			int dLeft;
			int dRight;
		};

		Encoders encoders;

		Ev3Base();
		void updateEncoders();
};

#endif
