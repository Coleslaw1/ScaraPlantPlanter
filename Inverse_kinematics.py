# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from math import sin, cos, acos, atan, degrees, pow
import matplotlib.pyplot as plt

la1 = 215
la2 = 165

arm_2_angle_limit = 150

x = 100     
y = 200
q2_old = 0
q1_old = 0

q1_array=[]
q2_array=[]
x_pos_array=[]
y_pos_array=[]

##To do:
# - Toevoegen limieten op de basis van de Z-as


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
    
    print("q2: ",q2," q1: ",q1)
    print("Difference q2: ",(q2-q2_deg_old),"difference q1: ",(q1-q1_deg_old), "\n")
    return q2, q1

for i in range (-200, 200, 11): #Range in de X-richting
    q2_old, q1_old = inv_kinematics(i,150, q2_old, q1_old)
    x_pos_array.append(i)
    y_pos_array.append(200)
    
plt.plot(x_pos_array, y_pos_array)
plt.xlabel("x-position (mm) -->")
plt.ylabel("y-position (mm) -->")
plt.grid()
plt.show()    

  

