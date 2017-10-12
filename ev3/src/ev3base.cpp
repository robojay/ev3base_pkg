#include <ros.h>
#include <std_msgs/String.h>
#include <stdio.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Int32.h>
#include <std_msgs/UInt32.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <math.h>
#include <limits.h>
#include <string>
#include <chrono>
#include <ev3base_pkg/Encoder.h>
#include <ev3base_pkg/MotorState.h>
#include "ev3dev.h"
#include "ev3geometry.h"
#include "ev3base.h"



Ev3Base::Ev3Base() {

	leftMotor = ev3dev::large_motor(LeftMotorPort);
	rightMotor = ev3dev::large_motor(RightMotorPort);
	
	leftMotor.reset();
	rightMotor.reset();

	//double countsPerRotation = leftMotor.count_per_rot();
	//distancePerCountM = WheelCircumferenceM / countsPerRotation;

	maxSpeedMetersPerSecond = leftMotor.max_speed() * DistancePerCountM;  // this is wrong!

	maxSpeedMMPerSecond = 0.9 * leftMotor.max_speed() * DistanceMMtoCountsLeft;

	relativeMoveLinearMetersPerSecond = 0.0;
	relativeMoveAngularRadiansPerSecond = 0.0;

	leftMotor.set_command(ev3dev::motor::command_stop);
	rightMotor.set_command(ev3dev::motor::command_stop);
	leftMotor.set_stop_action(ev3dev::motor::stop_action_hold);
	rightMotor.set_stop_action(ev3dev::motor::stop_action_hold);

	motorsRunning = false;
	motorsRelative = false;


}

Ev3Base::motorHandler() {
	enum MotorState {idle, rampUp, hold, rampDown, stop};
	static MotorState motorState = stop;

	bool forwards = (startCounts > goalCounts) ? false : true;
	int position;
	int deltaUp;
	int deltaDown;

	if (forwards) {
		position = leftMotor.position() - startCounts;
		deltaUp = rampUpCount - startCounts;
		deltaDown = goalCounts - rampDownCount;
	}
	else {
		position = leftMotor.position() - startCounts;
		deltaUp = rampUpCount - startCounts;
		deltaDown = goalCounts - rampDownCount;		
	}

	switch(motorState) {
		case idle:
			if (relativeMove) {
				leftMotor.set_speed_sp(ev3Base.minSpeedCountsLeft);
				rightMotor.set_speed_sp(ev3Base.minSpeedCountsRight);
				motorState = rampUp;
			}
			else {
				motorState = idle;
			}
		case rampUp:
			if (forwards) {
				if (position < rampUpCount) {
					int leftSpeed = (((maxSpeedCountsLeft - minSpeedCountsLeft) /
					                (rampUpCount - startCounts)) * position) + 
									minSpeedCountsLeft;
					int rightSpeed = (((maxSpeedCountsRight - minSpeedCountsRight) /
					                (rampUpCount - startCounts)) * position) + 
									minSpeedCountsRight;

					leftMotor.set_speed_sp(leftSpeed);
					rightMotor.set_speed_sp(rightSpeed);
					motorState = rampUp;
				}
				else {
					leftMotor.set_speed_sp(maxSpeedCountsLeft);
					rightMotor.set_speed_sp(maxSpeedCountsRight);
					motorState = hold;
				}
			}
			else {
				if (position > rampUpCount) {
					int leftSpeed = (((maxSpeedCountsLeft - minSpeedCountsLeft) /
					                (-rampUpCount + startCounts)) * position) + 
									minSpeedCountsLeft;
					int rightSpeed = (((maxSpeedCountsRight - minSpeedCountsRight) /
					                (-rampUpCount + startCounts)) * position) + 
									minSpeedCountsRight;

					leftMotor.set_speed_sp(leftSpeed);
					rightMotor.set_speed_sp(rightSpeed);
					motorState = rampUp;
				}
				else {
					leftMotor.set_speed_sp(maxSpeedCountsLeft);
					rightMotor.set_speed_sp(maxSpeedCountsRight);
					motorState = hold;
				}
			}

	}








				else if ((position >= rampUpCount) && (position < rampDownCount)) {}


	if (motorsRunning) {

		if (goalCounts < startCounts) {
			// going backwards
		}
		else {
			// going forwards
			if (leftMotor.position)			
		}

		int position = leftMotor.position - 

		leftMotor.position();

		leftMotor.set_speed_sp(ev3Base.minSpeedCountsLeft);
		rightMotor.set_speed_sp(ev3Base.minSpeedCountsRight);

	}
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
		cmdLeft = vl / DistancePerCountM;
		cmdRight = vr / DistancePerCountM;

		ev3Base.leftMotor.set_speed_sp((int)round(cmdLeft));
		ev3Base.rightMotor.set_speed_sp((int)round(cmdRight));
		ev3Base.leftMotor.set_command(ev3dev::motor::command_run_forever);
		ev3Base.rightMotor.set_command(ev3dev::motor::command_run_forever);

		lastLinearX = twistMessage.linear.x;
		lastAngularZ = twistMessage.angular.z;
	}
}

void relativeLinearCallback(const std_msgs::Float32& relativeLinearValue) {
	ev3Base.relativeMoveLinearMetersPerSecond = relativeLinearValue.data;
}

void relativeAngularCallback(const std_msgs::Float32& relativeAngularValue) {
	ev3Base.relativeMoveAngularRadiansPerSecond = relativeAngularValue.data;
}


void relativeMoveCallback(const geometry_msgs::Pose2D& relativeMessage) {
	// will move relative forward/back based on X
	// or will pivot relative based on Theta
	// X will take priority
	// Theta will be examined if X = 0
	// motors will be stopped first
	// this can be used to stop motors by sending all zeros
	// Y is ignored
	//
	// uses linear and angular speeds via other messages

	ev3Base.leftMotor.set_command(ev3dev::motor::command_stop);
	ev3Base.rightMotor.set_command(ev3dev::motor::command_stop);
	ev3Base.leftMotor.set_stop_action(ev3dev::motor::stop_action_hold);
	ev3Base.rightMotor.set_stop_action(ev3dev::motor::stop_action_hold);

	double cmd;
	double speed;

	double countsLeft;
	double countsRight;
	double speedLeft;
	double speedRight;
	double dGoal;

	if (relativeMessage.x != 0) {
		// convert goal distance to mm 
		dGoal = relativeMessage.x * 1000.0;

		// assume left wheel is "master"
		speedLeft = (ev3Base.relativeMoveLinearMetersPerSecond * 1000.0);
		if (speed > ev3Base.maxSpeedMMPerSecond) {
			speed = ev3Base.maxSpeedMMPerSecond;
		}
		else if (speed < -ev3Base.maxSpeedMMPerSecond) {
			speed = -ev3Base.maxSpeedMMPerSecond;
		}

		speedRight = speedLeft * WheelDiameterRatio;

		speedLeft *=  DistanceMMtoCountsLeft;
		speedRight *=  DistanceMMtoCountsRight;

		ev3Base.minSpeedCountsLeft = (int)(round(speedLeft * 0.25));
		ev3Base.minSpeedCountsRight = (int)(round(speedRight * 0.25));
		ev3Base.maxSpeedCountsLeft = (int)(round(speedLeft));
		ev3Base.maxSpeedCountsRight = (int)(round(speedRight));

		countsLeft = dGoal * DistanceMMtoCountsLeft;
		countsRight = Goal * DistanceMMtoCountsRight;

		ev3Base.startCounts = ev3Base.leftMotor.position();
		ev3Base.goalCounts = ev3Base.startCounts + int(round(countsLeft)); 

		if (ev3Base.startCounts > ev3Base.goalCounts) {
			// backwards
			ev3Base.rampUpCount = ev3Base.startCounts - ev3Base.goalCounts / 4;
			ev3Base.rampDownCount = ev3Base.goalCounts + ev3Base.goalCounts / 4;
		}
		else {
			// forwards
			ev3Base.rampUpCount = ev3Base.startCounts + ev3Base.goalCounts / 4;
			ev3Base.rampDownCount = ev3Base.goalCounts - ev3Base.goalCounts / 4;
		}


		printf("linear = [%f, %f] [%f, %f]\n", speedLeft, countsLeft, speedRight, countsRight);

		//ev3Base.leftMotor.set_speed_sp(ev3Base.minSpeedCountsLeft);
		//ev3Base.rightMotor.set_speed_sp(ev3Base.minSpeedCountsRight);
		ev3Base.leftMotor.set_position_sp((int)round(countsLeft));
		ev3Base.rightMotor.set_position_sp((int)round(countsRight));
		ev3Base.leftMotor.set_command(ev3dev::motor::command_run_to_rel_pos);
		ev3Base.rightMotor.set_command(ev3dev::motor::command_run_to_rel_pos);
		ev3Base.relativeMove = true;

	}
	// if (relativeMessage.x != 0) {
	// 	cmd = relativeMessage.x / DistancePerCountM;
	// 	speed = ev3Base.relativeMoveLinearMetersPerSecond / DistancePerCountM;
	// 	double max = ev3Base.maxSpeedMetersPerSecond / DistancePerCountM;
	// 	if (speed > max) {
	// 		speed = max;
	// 	}
	// 	else if (speed < -max) {
	// 		speed = -max;
	// 	}

	// 	printf("counts = %f\n", cmd);

	// 	ev3Base.leftMotor.set_speed_sp((int)round(speed));
	// 	ev3Base.rightMotor.set_speed_sp((int)round(speed));
	// 	ev3Base.leftMotor.set_position_sp((int)round(cmd));
	// 	ev3Base.rightMotor.set_position_sp((int)round(cmd));
	// 	ev3Base.leftMotor.set_command(ev3dev::motor::command_run_to_rel_pos);
	// 	ev3Base.rightMotor.set_command(ev3dev::motor::command_run_to_rel_pos);
	// }
	else if (relativeMessage.theta != 0) {

		cmd = ((relativeMessage.theta * TurningCircumferenceMM) / (2 * M_PI)) / DistancePerCountMM;
		speed = ((ev3Base.relativeMoveAngularRadiansPerSecond * TurningCircumferenceMM) / (2 * M_PI)) / DistancePerCountMM;
		double max = ev3Base.maxSpeedMetersPerSecond / DistancePerCountM;
		if (speed > max) {
			speed = max;
		}
		else if (speed < -max) {
			speed = -max;
		}

		printf("counts = %f\n", cmd);

		ev3Base.leftMotor.set_speed_sp((int)round(speed));
		ev3Base.rightMotor.set_speed_sp((int)round(speed));
		ev3Base.leftMotor.set_position_sp(-(int)round(cmd));
		ev3Base.rightMotor.set_position_sp((int)round(cmd));
		ev3Base.leftMotor.set_command(ev3dev::motor::command_run_to_rel_pos);
		ev3Base.rightMotor.set_command(ev3dev::motor::command_run_to_rel_pos);

	}

}

void publishEncoders() {

	encoderMessage.header.stamp = nh.now();
	encoderMessage.count[Left] = ev3Base.leftMotor.position();
	encoderMessage.count[Right] = ev3Base.rightMotor.position();
	encoders.publish(&encoderMessage);
} 


void publishMotorStates() {
	motorStateMessage.header.stamp = nh.now();

	if (ev3Base.leftMotor.state().empty()) {
		ev3Base.leftMotorStatus = "idle";
	}
	else {
		ev3Base.leftMotorStatus = "not_idle";

		//for(auto s : ev3Base.leftMotor.state()) {
		//	ev3Base.leftMotorStatus = "foo";
		//} 
	}

	if (ev3Base.rightMotor.state().empty()) {
		ev3Base.rightMotorStatus = "idle";
	}
	else {
		ev3Base.rightMotorStatus = "not_idle";

		//for(auto s : ev3Base.leftMotor.state()) {
		//	ev3Base.leftMotorStatus = "foo";
		//} 
	}

	motorStateMessage.state[Left] = (char *)ev3Base.leftMotorStatus.c_str();
	motorStateMessage.state[Right] = (char *)ev3Base.rightMotorStatus.c_str();

	motorStates.publish(&motorStateMessage);
}



int main() {
	ros::Subscriber<geometry_msgs::Twist> twist("/cmd_vel_mux/input/teleop", twistCallback);
	ros::Subscriber<geometry_msgs::Pose2D> relativeMove("/cmd_relative_move", relativeMoveCallback);
	ros::Subscriber<std_msgs::Float32> relativeLinear("/relative_linear_speed", relativeLinearCallback);
	ros::Subscriber<std_msgs::Float32> relativeAngular("/relative_angular_speed", relativeAngularCallback);

	std::chrono::time_point<std::chrono::steady_clock> now;
	std::chrono::time_point<std::chrono::steady_clock> odometryTimer;

	now = std::chrono::steady_clock::now();
	odometryTimer = now;

	nh.initNode(RosSrvrIp);
	nh.advertise(encoders);
	nh.advertise(motorStates);

	nh.subscribe(twist);
	nh.subscribe(relativeMove);
	nh.subscribe(relativeLinear);
	nh.subscribe(relativeAngular);

	ev3Base.leftMotor.set_command(ev3dev::motor::command_stop);
	ev3Base.rightMotor.set_command(ev3dev::motor::command_stop);

	while(1) {
		now = std::chrono::steady_clock::now();
		if (now >= odometryTimer) {
			odometryTimer = now + OdometryTime;
			publishEncoders();
			publishMotorStates();
		}
		nh.spinOnce();
	}
}
