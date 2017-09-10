#ifndef __EV3BASE_NODE_H__
#define __EV3BASE_NODE_H__


class Encoders {
	public:
		ros::NodeHandle nh;

		ros::Subscriber encoders;
		ros::Publisher odometry;
		tf::TransformBroadcaster odometryTransform;

		nav_msgs::Odometry odometryMessage;
		geometry_msgs::TransformStamped odometryTransformMessage;

		std::string encodersTopic;
		std::string odometryTopic;

		std::string odometryFrameId;
		std::string baseFrameId;

		int lastLeftCount;
		int lastRightCount;
		double lastEncoderTime;

		struct Pose {
			double x;
			double y;
			double theta;
		};

		Pose pose;
		Pose velocity;

		Encoders();
		void encodersCallback(const ev3base_pkg::Encoder& encoderMessage);

};

#endif
