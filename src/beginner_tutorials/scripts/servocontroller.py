#!/usr/bin/env python
# Software License Agreement (BSD License)

import Tkinter as tk
import rospy
from std_msgs.msg import UInt16
from std_msgs.msg import Bool
from std_msgs.msg import Int32MultiArray


class Pubber:
    global e0, e1
    
    def __init__(self):
        self.pub0 = rospy.Publisher('servo0', Int32MultiArray, queue_size=10)
        # self.pub1 = rospy.Publisher('servo1', UInt16, queue_size=10)  # Init the ROS Node
        self.pub2 = rospy.Publisher('stepperUP', Bool, queue_size=10)
        self.pub3 = rospy.Publisher('stepperDOWN', Bool, queue_size=10)
        self.pub4 = rospy.Publisher('stepperSTOP', Bool, queue_size=10)
        self.pub5 = rospy.Publisher('endeffecter', UInt16, queue_size=10)
        rospy.init_node('ServoController', anonymous=False)
        self.rate = rospy.Rate(10)  # 10hz
        print('  _____ ____   _____ _____   _____   ____   _____            _____  __  __')
        print(' |_   _|  _ \ / ____/ ____| |  __ \ / __ \ / ____|     /\   |  __ \|  \/  |')
        print('   | | | |_) | (___| (___   | |__) | |  | | (___      /  \  | |__) | \  / |')
        print('   | | |  _ < \___ \\\___ \  |  _  /| |  | |\___ \    / /\ \ |  _  /| |\/| |')
        print('  _| |_| |_) |____) |___) | | | \ \| |__| |____) |  / ____ \| | \ \| |  | |')
        print(' |_____|____/|_____/_____/  |_|  \_\\\____/|_____/  /_/    \_\_|  \_\_|  |_|)')
        rospy.loginfo("The node has been initialized.")

    def servorotate(self):
        # while not rospy.is_shutdown():
        rospy.loginfo("Servo 0 angle is "+str(e0.get()))
        rospy.loginfo("Servo 1 angle is " + str(e1.get()))
        pub_data = Int32MultiArray(data=[int(e0.get()), int(e1.get())])
        self.pub0.publish(pub_data)
        rospy.loginfo(pub_data)
        # self.rate.sleep()

    def steppermotorup(self):
        rospy.loginfo("UP")
        self.pub2.publish(True)

    def steppermotordown(self):
        rospy.loginfo("DOWN")
        self.pub3.publish(True)

    def steppermotorstop(self):
        rospy.loginfo("STOP")
        self.pub4.publish(True)

    def endcontrol(self, flag):
        rospy.loginfo("End Effecter Control Mode"+str(flag))
        self.pub5.publish(flag)



def initnode():
    global Pb
    Pb = Pubber()


def publishtotopic():
    global Pb
    Pb.servorotate()

def smup():
    global Pb
    Pb.steppermotorup()

def smdown():
    global Pb
    Pb.steppermotordown()

def smstop():
    global Pb
    Pb.steppermotorstop()

def ed1():
    global Pb
    Pb.endcontrol(1)

def ed2():
    global Pb
    Pb.endcontrol(2)

def ed3():
    global Pb
    Pb.endcontrol(3)

def ed4():
    global Pb
    Pb.endcontrol(4)

def ed5():
    global Pb
    Pb.endcontrol(5)

def ed6():
    global Pb
    Pb.endcontrol(6)

def ed7():
    global Pb
    Pb.endcontrol(7)

def ed8():
    global Pb
    Pb.endcontrol(8)

def ed9():
    global Pb
    Pb.endcontrol(9)


window = tk.Tk()
window.title('Servo Controller')
window.geometry('500x400')

b0 = tk.Button(window, text="Init ROS Node", width=15, height=3, command=initnode)
b1 = tk.Button(window, text="Publish Servo Data", width=15, height=3, command=publishtotopic)
b2 = tk.Button(window, text="Stepper Motor Up", width=15, height=3, command=smup)
b3 = tk.Button(window, text="Stepper Motor Down", width=15, height=3, command=smdown)
b4 = tk.Button(window, text="Stepper Motor Stop", width=15, height=3, command=smstop)
b5 = tk.Button(window, text="End Effecter Initialize", width=20, height=2, command=ed1)
b6 = tk.Button(window, text="15 degree angle", width=15, height=2, command=ed2)
b7 = tk.Button(window, text="30 degree angle", width=15, height=2, command=ed3)
b8 = tk.Button(window, text="45 degree angle", width=15, height=2, command=ed4)
b9 = tk.Button(window, text="60 degree angle", width=15, height=2, command=ed5)
b10 = tk.Button(window, text="75 degree angle", width=15, height=2, command=ed6)
b11 = tk.Button(window, text="90 degree angle", width=15, height=2, command=ed7)
b12 = tk.Button(window, text="Attach", width=15, height=2, command=ed8)
b13 = tk.Button(window, text="Deattach", width=15, height=2, command=ed9)


e0 = tk.Entry(window)
e1 = tk.Entry(window)
l0 = tk.Label(window, text="Servo 0:", width=12, height=3)
l1 = tk.Label(window, text="Servo 1:", width=12, height=3)
l2 = tk.Label(window, text="Author: IBSS NUAA")

b0.place(x=0, y=150, anchor='sw')
b1.place(x=300, y=150, anchor='se')
b2.place(x=0, y=250, anchor='sw')
b3.place(x=300, y=250, anchor='se')
b4.place(x=150, y=350, anchor='s')
b5.place(x=500, y=0, anchor='ne')
b6.place(x=500, y=40, anchor='ne')
b7.place(x=500, y=80, anchor='ne')
b8.place(x=500, y=120, anchor='ne')
b9.place(x=500, y=160, anchor='ne')
b10.place(x=500, y=200, anchor='ne')
b11.place(x=500, y=240, anchor='ne')
b12.place(x=500, y=280, anchor='ne')
b13.place(x=500, y=320, anchor='ne')

e0.place(x=100, y=10, anchor='nw')
e1.place(x=100, y=60, anchor='nw')
l0.place(x=0, y=0)
l1.place(x=0, y=50)
l2.place(x=370, y=380)
window.mainloop()
