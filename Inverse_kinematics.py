# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from math import sin, cos, acos, atan, degrees, pow
import matplotlib.pyplot as plt

la1 = 215 #Millimeters
la2 = 165 #Millimeters

arm_2_angle_limit = 150 #Degrees

q2_old = 0
q1_old = 0

q1_array=[]
q2_array=[]

q1_difference_array = []
q2_difference_array = []

x1_pos_array=[]
y1_pos_array=[]

##To do:
# - Toevoegen limieten op de basis van de Z-as

DEBUG = 0

def rounded_degrees(q2,q1):
    q2_deg_r = round(degrees(q2))
    q1_deg_r = round(degrees(q1))
    return(q2_deg_r,q1_deg_r)

def inv_kinematics(x,y, q2_deg_old, q1_deg_old):
    q2 = acos((pow(x,2)+pow(y,2)-pow(la1,2)-pow(la2,2))/(2*la1*la2))
    q1 = atan(y/x)-atan((la2*sin(q2))/(la1+la2*cos(q2)))
    q2,q1 = rounded_degrees(q2,q1)
    opening_angle = q2-q1
    if(opening_angle > arm_2_angle_limit or opening_angle < -arm_2_angle_limit):
        try:
            q2 = -acos((pow(x,2)+pow(y,2)-pow(la1,2)-pow(la2,2))/(2*la1*la2))
            q1 = atan(y/x)+atan((la2*sin(q2))/(la1+la2*cos(q2))) 
            q2,q1 = rounded_degrees(q2,q1)
        except:
            print("No possible angle combination found")
    else:
        pass
    
    q2_array.append(q2)
    q1_array.append(q1)
    
    q2_difference_array.append(q2-q2_deg_old)
    q1_difference_array.append(q1-q1_deg_old)
    
    if(DEBUG):
        print("q2: ",q2," q1: ",q1)
        print("Difference q2: ",(q2-q2_deg_old),"difference q1: ",(q1-q1_deg_old), "\n")
    return q2, q1

def C_array_print(q1_array, q2_array, q1_difference_array, q2_difference_array):
    if(DEBUG):
        print("int pickUp_locations_q1[12] = {",q1_array,"}")
        print("int pickUp_locations_q2[12] = {",q2_array,"}")
    print("int pickUp_difference_q1[12]= {",q1_difference_array,"}")
    print("int pickUp_difference_q2[12]= {",q2_difference_array,"}")

for i in range (-250, 200, 21): #Range in de X-richting
    y_distance = 50
    q2_old, q1_old = inv_kinematics(i,y_distance, q2_old, q1_old) #min applicable distance 50 mm 
    x1_pos_array.append(i)
    y1_pos_array.append(y_distance)

C_array_print(q1_array, q2_array, q1_difference_array, q2_difference_array)

if(DEBUG):
    plt.plot(x1_pos_array, y1_pos_array, "blue")
    plt.xlabel("x-position (mm) -->")
    plt.ylabel("y-position (mm) -->")
    plt.grid()
    plt.show()    

  

