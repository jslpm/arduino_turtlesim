#!/usr/bin/env python3
import rospy
import std_srvs

from std_msgs.msg import Bool
from std_srvs.srv import Empty

def callback(data):
    rospy.loginfo(rospy.get_caller_id() + " I heard %s", data.data)
    if data.data is False: 
        rospy.logwarn("button pushed!")
        try:
            clear_service()
        except rospy.ServiceException as e:
            rospy.logerr("Service call failed: %s", e)

rospy.init_node("button_listener")
rospy.Subscriber("button_state", Bool, callback)

rospy.wait_for_service('clear')
clear_service = rospy.ServiceProxy('clear', Empty)

rospy.spin()
