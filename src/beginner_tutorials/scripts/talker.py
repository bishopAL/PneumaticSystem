#~/PiBits/ServoBlaster/user sudo ./servod
#sudo ./servod --p1pins=7,11,12,13,15,16,18,22,29,31,32,33

import subprocess
import time
import math
import numpy as np
import rospy
from std_msgs.msg import Float64MultiArray as floatarray
class GeRo(object):
    def __init__(self):
        self.Author = 'IBSS'
        self._DATANUM_FOR_PERSTEP = 200
        self._TRANS_FREQ = 100
        self.adjust_rf0 = 0.0
        self.adjust_rf1 = 0.0
        self.adjust_rf2 = 0.0
        self.adjust_rh0 = 0.0
        self.adjust_rh1 = 0.0
        self.adjust_rh2 = 0.0
        self.adjust_lf0 = 0.0
        self.adjust_lf1 = 0.0
        self.adjust_lf2 = 0.0
        self.adjust_lh0 = 0.0
        self.adjust_lh1 = 0.0
        self.adjust_lh2 = 0.0
        self.l1 = 65.0
        self.l2 = 40.0
        self.l3 = 40.0#three parts of one leg
        self.rf_origin_x = 65.0
        self.rf_origin_y = 40.0
        self.rf_origin_z = -40.0
        self.rh_origin_x = 65.0
        self.rh_origin_y = 40.0
        self.rh_origin_z = -40.0
        self.lf_origin_x = 65.0
        self.lf_origin_y = 40.0
        self.lf_origin_z = -40.0
        self.lh_origin_x = 65.0
        self.lh_origin_y = 40.0
        self.lh_origin_z = -40.0#start point
    def ik(self,px,py,pz):#Input the target positon
        alpha=math.asin(-self.l3/(px**2+pz**2)**0.5)-math.atan2(pz,px)
        beta=math.asin((self.l1**2-self.l2**2-self.l3**2+px**2+py**2+pz**2)/(2*self.l1*(-self.l3**2+px**2+py**2+pz**2)**0.5))-math.atan2((px**2+pz**2-self.l3**2)**0.5,py)
        gamma=math.asin((self.l1**2+self.l2**2+self.l3**2-px**2-py**2-pz**2)/(2*self.l1*self.l2))
        return alpha,beta,gamma
    def generate_2d_gait_oneleg(self,flag,width=20.0,height=20.0):#generate the target positon list
        if flag=='rf':
            y_list_temp=list(np.linspace(0, width,self._DATANUM_FOR_PERSTEP))
            z_list_temp=[-(4*height)*y**2/(width**2)+(4*height)*y/width for y in y_list_temp]
            y_list=np.array([self.rf_origin_y+item for item in y_list_temp])
            z_list=np.array([self.rf_origin_z+item for item in z_list_temp])
            x_list=np.array([self.rf_origin_x for item in y_list_temp])
        if flag=='rh':
            width=-width
            y_list_temp=list(np.linspace(0, width,self._DATANUM_FOR_PERSTEP))
            z_list_temp=[-(4*height)*y**2/(width**2)+(4*height)*y/width for y in y_list_temp]
            y_list=np.array([self.rh_origin_y+item for item in y_list_temp])
            z_list=np.array([self.rh_origin_z+item for item in z_list_temp])
            x_list=np.array([self.rh_origin_x for item in y_list_temp])
        if flag=='lf':
            y_list_temp=list(np.linspace(0, width,self._DATANUM_FOR_PERSTEP))
            z_list_temp=[-(4*height)*y**2/(width**2)+(4*height)*y/width for y in y_list_temp]
            y_list=np.array([self.lf_origin_y+item for item in y_list_temp])
            z_list=np.array([self.lf_origin_z+item for item in z_list_temp])
            x_list=np.array([self.lf_origin_x for item in y_list_temp])
        if flag=='lh':
            width=-width
            y_list_temp=list(np.linspace(0, width,self._DATANUM_FOR_PERSTEP))
            z_list_temp=[-(4*height)*y**2/(width**2)+(4*height)*y/width for y in y_list_temp]
            y_list=np.array([self.lh_origin_y+item for item in y_list_temp])
            z_list=np.array([self.lh_origin_z+item for item in z_list_temp])
            x_list=np.array([self.lh_origin_x for item in y_list_temp])
        return x_list,y_list,z_list
    def servo_rotate(self,servo_number,servo_angle):
        servocmd="echo "+str(servo_number)+'='+str(int((servo_angle+90)*10/9+50))+" > /dev/servoblaster"
        subprocess.call(servocmd, shell=True)
    def generate_servoangle_array(self, flag, width=20.0, height=20.0):
        ###########################BIG NOTE#############################################
        #You can use this function to generate the whole gait planning 12 servos' angle#
        #rf_angle_list=[] and the others are set to restore the angle data for one leg##
        #Finally, they merge into one array and return it###############################
        ################################################################################
        rf_angle_list=[]
        rh_angle_list=[]
        lf_angle_list=[]
        lh_angle_list=[]
        # if flag == 'FAST_ON_GROUND':
        #########################First Step Start###################################################################
        rf_px_list,rf_py_list,rf_pz_list=self.generate_2d_gait_oneleg('rf')  
        rh_px_list,rh_py_list,rh_pz_list=self.generate_2d_gait_oneleg('rh', width=-width/3, height=0)  
        lf_px_list,lf_py_list,lf_pz_list=self.generate_2d_gait_oneleg('lf', width=-width/3, height=0)
        lh_px_list,lh_py_list,lh_pz_list=self.generate_2d_gait_oneleg('lh', width=-width/3, height=0)
        for i in range(len(rf_px_list)):
            rf_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(rf_px_list[i],rf_py_list[i],rf_pz_list[i])])
            rh_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(lf_px_list[i],lf_py_list[i],lf_pz_list[i])])
            lf_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(rh_px_list[i],rh_py_list[i],rh_pz_list[i])])
            lh_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(lh_px_list[i],lh_py_list[i],lh_pz_list[i])])
        self.rf_origin_y+=width
        self.rh_origin_y+=(width/3)
        self.lf_origin_y+=(-width/3)
        self.lh_origin_y+=(width/3)
        #########################First Step End######################################################################
        
        #########################Second Step Start###################################################################
        rf_px_list,rf_py_list,rf_pz_list=self.generate_2d_gait_oneleg('rf', width=-width/3, height=0)
        rh_px_list,rh_py_list,rh_pz_list=self.generate_2d_gait_oneleg('rh', width=-width/3, height=0)
        lf_px_list,lf_py_list,lf_pz_list=self.generate_2d_gait_oneleg('lf')
        lh_px_list,lh_py_list,lh_pz_list=self.generate_2d_gait_oneleg('lh', width=-width/3, height=0)
        for i in range(len(rf_px_list)):
            rf_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(rf_px_list[i],rf_py_list[i],rf_pz_list[i])])
            rh_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(lf_px_list[i],lf_py_list[i],lf_pz_list[i])])
            lf_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(rh_px_list[i],rh_py_list[i],rh_pz_list[i])])
            lh_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(lh_px_list[i],lh_py_list[i],lh_pz_list[i])])
        self.rf_origin_y+=(-width/3)
        self.rh_origin_y+=(width/3)
        self.lf_origin_y+=width
        self.lh_origin_y+=(width/3)
        #########################Second Step End######################################################################
        
        #########################Third Step Start###################################################################
        rf_px_list,rf_py_list,rf_pz_list=self.generate_2d_gait_oneleg('rf', width=-width/3, height=0)
        rh_px_list,rh_py_list,rh_pz_list=self.generate_2d_gait_oneleg('rh')
        lf_px_list,lf_py_list,lf_pz_list=self.generate_2d_gait_oneleg('lf', width=-width/3, height=0)
        lh_px_list,lh_py_list,lh_pz_list=self.generate_2d_gait_oneleg('lh', width=-width/3, height=0)
        for i in range(len(rf_px_list)):
            rf_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(rf_px_list[i],rf_py_list[i],rf_pz_list[i])])
            rh_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(lf_px_list[i],lf_py_list[i],lf_pz_list[i])])
            lf_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(rh_px_list[i],rh_py_list[i],rh_pz_list[i])])
            lh_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(lh_px_list[i],lh_py_list[i],lh_pz_list[i])])
        self.rf_origin_y+=(-width/3)
        self.rh_origin_y+=-width
        self.lf_origin_y+=(-width/3)
        self.lh_origin_y+=(width/3)
        #########################Third Step End######################################################################
        
        #########################Fourth Step Start###################################################################
        rf_px_list,rf_py_list,rf_pz_list=self.generate_2d_gait_oneleg('rf', width=-width/3, height=0)
        rh_px_list,rh_py_list,rh_pz_list=self.generate_2d_gait_oneleg('rh', width=-width/3, height=0)
        lf_px_list,lf_py_list,lf_pz_list=self.generate_2d_gait_oneleg('lf', width=-width/3, height=0)
        lh_px_list,lh_py_list,lh_pz_list=self.generate_2d_gait_oneleg('lh')
        for i in range(len(rf_px_list)):
            rf_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(rf_px_list[i],rf_py_list[i],rf_pz_list[i])])
            rh_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(lf_px_list[i],lf_py_list[i],lf_pz_list[i])])
            lf_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(rh_px_list[i],rh_py_list[i],rh_pz_list[i])])
            lh_angle_list.append([rad*180/3.14 for rad in geckorobot.ik(lh_px_list[i],lh_py_list[i],lh_pz_list[i])])
        self.rf_origin_y+=(-width/3)
        self.rh_origin_y+=(width/3)
        self.lf_origin_y+=(-width/3)
        self.lh_origin_y+=-width
        #########################Fourth Step End######################################################################
        
        #########################Merge into one Array#################################################################
        A=np.hstack((np.array(rf_angle_list),np.array(rh_angle_list),np.array(lf_angle_list),np.array(lh_angle_list)))
        return A
    
pub = rospy.Publisher('chatter', floatarray, queue_size=10)
geckorobot=GeRo()
rospy.init_node('talker', anonymous=False)
rate = rospy.Rate(geckorobot._TRANS_FREQ) # 100hz


outputarray=geckorobot.generate_servoangle_array()

for item in outputarray:
    fa = floatarray(data=[i for i in item])
    rospy.loginfo(fa)
    pub.publish(fa)
    rate.sleep()
