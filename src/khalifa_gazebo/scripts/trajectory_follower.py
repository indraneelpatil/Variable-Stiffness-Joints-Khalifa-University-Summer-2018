#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String,Float64
from numpy import float64
import math

global l1
l1 =1
global l2
l2 =1

def talker():
    pub_1 = rospy.Publisher('/rrserial/joint1_position_controller/command', Float64, queue_size=10)
    pub_2 = rospy.Publisher('/rrserial/joint2_position_controller/command', Float64, queue_size=10)
    
    rospy.init_node('trajectory_follower', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    
    
    while not rospy.is_shutdown():
        x= input("Enter x co-ordinate :")
        z= input("Enter z co-ordinate :")
    
        z= z-1.95
    
        c= (x*x)+(z*z)-(l1*l1)-(l2*l2)
       
        t2=math.acos(c/(2*l1*l2))
    
        k1=l1+l2*math.cos(t2)
        k2=l2*math.sin(t2)
    
        t1=math.atan2(z,x) - math.atan2(k2, k1)
    
        rospy.loginfo(t1)
        rospy.loginfo(t2)
        
        
        pub_1.publish(t1)
        pub_2.publish(t2)
        
        rate.sleep()

if __name__ == '__main__':
    try:
        
        talker()
    except rospy.ROSInterruptException:
        pass