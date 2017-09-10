#include <ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>
#include <std_msgs/UInt32.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <math.h>
#include <limits.h>
#include <string>
#include <chrono>
#include "ev3dev.h"
#include "ev3geometry.h"
#include "ev3base.h"

Ev3Base ev3Base;
ros::NodeHandle nh;


Ev3Base::Ev3Base() {

	leftMotor = ev3dev::large_motor(LeftMotorPort);
	rightMotor = ev3dev::large_motor(RightMotorPort);
	
	leftMotor.reset();
	rightMotor.reset();

	double countsPerRotation = leftMotor.count_per_rot();
	distancePerCountM = WheelCircumferenceM / countsPerRotation;

	maxSpeedMetersPerSecond = leftMotor.max_speed() * distancePerCountM;

	encoders.dLeft = 0;
	encoders.dRight = 0;
}



void Ev3Base::updateEncoders() {

	static bool firstPass = true;
	static int lastLeft;
	static int lastRight;


	int left = leftMotor.position();
	int right = rightMotor.position();


	if (firstPass) {
		firstPass = false;
	}
	else {
		encoders.dLeft = left - lastLeft;
		encoders.dRight = right - lastRight;
	}

	lastLeft = left;
	lastRight = right;
}


void twistCallback(const geometry_msgs::Twist& twistMessage) {
	static double lastLinearX = 0.0;
	static double lastAngularZ = 0.0;

	if ((twistMessage.linear.x != lastLinearX) ||
		(twistMessage.angular.z != lastAngularZ)) {

		// Twist units are m/s and rad/s
		// need to convert to left and right speed (counts per second)
		// given the known geometry of the robot
		// and the motor characteristics
		//
		// hints here: http://moorerobots.com/blog/post/4

		double vl, vr;
		double vc, wc;

		vc = twistMessage.linear.x;
		wc = twistMessage.angular.z;

		vr = ((2.0 * vc) + (wc * WheelSpacingM)) / 2.0;
		vl = ((2.0 * vc) - (wc * WheelSpacingM)) / 2.0;

		// clamp to limits

		double max = ev3Base.maxSpeedMetersPerSecond;

		if (vr > max) {
			vr = max;
		}
		else if (vr < -max) {
			vr = -max;
		}

		if (vl > max) {
			vl = max;
		}
		else if (vl < -max) {
			vl = -max;
		}

		// convert velocity to counts per second
		// taking care of units, we get...
		// (meters / second) * (counts/ meter) = counts / second

		double cmdLeft, cmdRight;
		cmdLeft = vl / ev3Base.distancePerCountM;
		cmdRight = vr / ev3Base.distancePerCountM;

		ev3Base.leftMotor.set_speed_sp((int)cmdLeft);
		ev3Base.rightMotor.set_speed_sp((int)cmdRight);
		ev3Base.leftMotor.set_command(ev3dev::motor::command_run_forever);
		ev3Base.rightMotor.set_command(ev3dev::motor::command_run_forever);

		lastLinearX = twistMessage.linear.x;
		lastAngularZ = twistMessage.angular.z;
	}
}


void publishOdometry() {
	ros::Time now = nh.now();

} 



int main() {
	ros::Subscriber<geometry_msgs::Twist> twist("/cmd_vel_mux/input/teleop", twistCallback);

	std::chrono::time_point<std::chrono::steady_clock> now;
	std::chrono::time_point<std::chrono::steady_clock> odometryTimer;

	now = std::chrono::steady_clock::now();
	odometryTimer = now;

	nh.initNode(RosSrvrIp);
	//nh.advertise(odometry);

	nh.subscribe(twist);
	while(1) {
		now = std::chrono::steady_clock::now();
		if (now >= odometryTimer) {
			odometryTimer = now + OdometryTime;
			ev3Base.updateEncoders();
			publishOdometry();
		}
		nh.spinOnce();
	}
}