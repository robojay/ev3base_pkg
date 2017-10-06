#include <ros/ros.h>
#include <ros/time.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <ev3base_pkg/Encoder.h>
#include <math.h>
#include <limits.h>
#include "ev3geometry.h"
#include "ev3base_node.h"


Encoders::Encoders() {
	encodersTopic = "/ev3/encoders";
	odometryTopic = "odom";

	odometryFrameId = "odom";
	baseFrameId = "base_link";

	try {
		nh.getParam("/ev3base/encoders_topic", encodersTopic);
		nh.getParam("ev3base/odometry_topic", odometryTopic);
		ROS_INFO_STREAM("Odometry Topic: " << odometryTopic);
		nh.getParam("ev3base/odometry_frame_id", odometryFrameId);
		ROS_INFO_STREAM("Odometry Frame Id: " << odometryFrameId);
		nh.getParam("/ev3base/base_frame_id", baseFrameId);
		ROS_INFO("Parameters loaded");
	}
	catch(int e) {
   		ROS_WARN("Parameters not loaded, using defaults");
	}

	lastLeftCount = 0;
	lastRightCount = 0;
	lastEncoderTime = 0.0;

	pose.x = 0.0;
	pose.y = 0.0;
	pose.theta = 0.0;

	velocity.x = 0.0;
	velocity.y = 0.0;
	velocity.theta = 0.0;

	encoders = nh.subscribe(encodersTopic, 1, &Encoders::encodersCallback, this);
	odometry = nh.advertise<nav_msgs::Odometry>(odometryTopic, 10);
}

void Encoders::encodersCallback(const ev3base_pkg::Encoder& encoderMessage) {

	double encoderTime = encoderMessage.header.stamp.toSec();
	double dt = encoderTime - lastEncoderTime;

	int left = encoderMessage.count[0];
	int right = encoderMessage.count[1];

	// printf("Encoder: [%d, %d]\n", left, right);

	if ((lastEncoderTime != 0.0) && (dt > 0.0)) {
		double dLeft = left - lastLeftCount;
		double dRight = right - lastRightCount;

		double leftMM = dLeft * DistancePerCountMM;
		double rightMM = dRight * DistancePerCountMM;

		double dDistance = (rightMM + leftMM) / 2.0;
		double dTheta = (rightMM - leftMM) / WheelSpacingMM;

		double dX = dDistance * cos(pose.theta);
		double dY = dDistance * sin(pose.theta);

		pose.x += dX;
		pose.y += dY;
		pose.theta += dTheta;

		// printf("Pose: [%f, %f, %f]\n", pose.x, pose.y, pose.theta);

		velocity.x = dX / dt;
		velocity.y = dY / dt;
		velocity.theta = dTheta / dt;

		// printf("Velocity: [%f, %f, %f]\n", velocity.x, velocity.y, velocity.theta);

		geometry_msgs::Quaternion odomQuaternion = tf::createQuaternionMsgFromYaw(pose.theta);

		odometryMessage.header.stamp = encoderMessage.header.stamp;
		odometryMessage.header.frame_id = odometryFrameId;
		odometryMessage.child_frame_id = baseFrameId;

		odometryMessage.pose.pose.position.x = pose.x / 1000.0;
		odometryMessage.pose.pose.position.y = pose.y / 1000.0;
		odometryMessage.pose.pose.position.z = 0.0;
		odometryMessage.pose.pose.orientation = odomQuaternion;
		odometryMessage.twist.twist.linear.x = velocity.x / 1000.0;
		odometryMessage.twist.twist.linear.y = velocity.y / 1000.0;			
		odometryMessage.twist.twist.angular.z = velocity.theta;


		// Covariance - not accurate yet
		odometryMessage.pose.covariance = { 1.0e-3, 0.0, 0.0, 0.0, 0.0, 0.0,
						       0.0, 1.0e-3, 0.0, 0.0, 0.0, 0.0,
						       0.0, 0.0, 1.0e6, 0.0, 0.0, 0.0,
						       0.0, 0.0, 0.0, 1.0e6, 0.0, 0.0,
						       0.0, 0.0, 0.0, 0.0, 1.0e6, 0.0,
						       0.0, 0.0, 0.0, 0.0, 0.0, 1.0e3 };

		odometryMessage.twist.covariance = { 1.0e-3, 0.0, 0.0, 0.0, 0.0, 0.0,
						       0.0, 1.0e-3, 0.0, 0.0, 0.0, 0.0,
						       0.0, 0.0, 1.0e6, 0.0, 0.0, 0.0,
						       0.0, 0.0, 0.0, 1.0e6, 0.0, 0.0,
						       0.0, 0.0, 0.0, 0.0, 1.0e6, 0.0,
						       0.0, 0.0, 0.0, 0.0, 0.0, 1.0e3 };
 
		odometry.publish(odometryMessage);

		odometryTransformMessage.header.stamp = encoderMessage.header.stamp;
		odometryTransformMessage.header.frame_id = odometryFrameId;
		odometryTransformMessage.child_frame_id = baseFrameId;
		odometryTransformMessage.transform.translation.x = pose.x / 1000.0;
		odometryTransformMessage.transform.translation.y = pose.y / 1000.0;
		odometryTransformMessage.transform.translation.z = 0.0;
		odometryTransformMessage.transform.rotation = odomQuaternion;

		odometryTransform.sendTransform(odometryTransformMessage);


	}

	lastLeftCount = left;
	lastRightCount = right;
	lastEncoderTime = encoderTime;

}


int main(int argc, char** argv) {
	ros::init(argc, argv, "EV3");
	Encoders encoders;

	ros::spin();

	return 0;
}


