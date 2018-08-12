#!/usr/bin/env python
# license removed fpr brevity

import rospy
from std_msgs.msg import String, Float64
from diagnostic_msgs.msg import DiagnosticArray
from sensor_msgs.msg import JointState

i=0
start_position=0
current_position=0
previous_position=0

def callback(data):
    global i,start_position,current_position,qm_pub,qmdot_pub, torque_pub, previous_position
    if i==0:
        start_position= data.position[0]
        i=i+1;
    #current_position= float(data.status[1].values[5].value)
    current_position=data.position[0]
    rotations= ((current_position-start_position)/82)
    qm_radians=rotations*6.28319
    qm_radians=qm_radians/91
    
    #rospy.loginfo(data.position[0])
    qm_pub.publish(qm_radians)
    
    velocity= (qm_radians-previous_position)/0.009   #velocity in radians with sampling time of 0.009
    #velocity=data.velocity[0]
    
    #qmdot_pub.publish(velocity*9.5295)  #(91*6.28319)/60
    qmdot_pub.publish(velocity)
    previous_position=qm_radians;
    #torque=data.effort[0]
    #torque_pub.publish(torque/100)
    
    
def diagnostic_pub():
    global qm_pub, qmdot_pub, torque_pub
    rospy.init_node('diagnostic_publisher',anonymous=True)
    qm_pub=rospy.Publisher('epos_hardware_qm',Float64,queue_size=2)
    
    qmdot_pub=rospy.Publisher('epos_hardware_qmdot',Float64,queue_size=2)
    torque_pub= rospy.Publisher('epos_hardware_torque',Float64,queue_size=2)
    
    rospy.Subscriber("joint_states",JointState,callback)
    
    
    
    rospy.spin()
    
if __name__=='__main__':
    diagnostic_pub()