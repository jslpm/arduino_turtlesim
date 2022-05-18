#!/usr/bin/env python3
import rospy
import std_msgs.msg

def callback(data):
    rospy.loginfo(f"I heard: {data.data}")

rospy.init_node("arduino_listener")
rospy.Subscriber("chatter", std_msgs.msg.String, callback)
rospy.spin()
