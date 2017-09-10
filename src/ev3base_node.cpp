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
	odometryTopic = "/odom";

	odometryFrameId = "odom";
	baseFrameId = "base_link";

	try {
		nh.getParam("encoders_topic", encodersTopic);
		nh.getParam("odometry_topic", odometryTopic);
		nh.getParam("odometry_frame_id", odometryFrameId);
		nh.getParam("base_frame_id", baseFrameId);
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

	if ((lastEncoderTime != 0.0) && (dt > 0.0)) {
		double dLeft = left - lastLeftCount;
		double dRight = right - lastRightCount;

		double leftM = dLeft * DistancePerCountM;
		double rightM = dRight * DistancePerCountM;

		double dDistance = (rightM + leftM) / 2.0;
		double dTheta = (rightM - leftM) / WheelSpacingM;

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

		odometryMessage.pose.pose.position.x = pose.x;
		odometryMessage.pose.pose.position.y = pose.y;
		odometryMessage.pose.pose.position.z = 0.0;
		odometryMessage.pose.pose.orientation = odomQuaternion;
		odometryMessage.twist.twist.linear.x = velocity.x;
		odometryMessage.twist.twist.linear.y = velocity.y;			
		odometryMessage.twist.twist.angular.z = velocity.theta;

		odometry.publish(odometryMessage);

		odometryTransformMessage.header.stamp = encoderMessage.header.stamp;
		odometryTransformMessage.header.frame_id = odometryFrameId;
		odometryTransformMessage.child_frame_id = baseFrameId;
		odometryTransformMessage.transform.translation.x = pose.x;
		odometryTransformMessage.transform.translation.y = pose.y;
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


