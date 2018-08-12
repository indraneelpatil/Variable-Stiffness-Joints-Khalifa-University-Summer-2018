#!/usr/bin/env python
# license removed fpr brevity

import rospy
from std_msgs.msg import String, Float64
from diagnostic_msgs.msg import DiagnosticArray
from sensor_msgs.msg import JointState

i=0
start_position=0
current_position=0


def callback(data):
    
    torque = float(data.status[1].values[7].value)
    #rospy.loginfo(data.position[0])
    torque_pub.publish(torque)
    
    
def torque_pub():
    global torque_pub
    rospy.init_node('torque_publisher',anonymous=True)
    
    torque_pub= rospy.Publisher('torque_readings',Float64,queue_size=2)
    
    rospy.Subscriber("diagnostics",DiagnosticArray,callback)
    rospy.spin()
    
if __name__=='__main__':
    torque_pub()