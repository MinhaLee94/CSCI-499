from mpl_toolkits import mplot3d

import sys
import os.path
from os import path
import math
import numpy as np
import matplotlib.pyplot as plt


# Getting p value text document
p_value_file = input("Enter p value file (pvalueAnam.txt, pvalueMehrab.txt, pvalueMinha.txt): ")

while not path.exists(p_value_file):
    p_value_file = input("File does not exist. Please enter another file (pvalueAnam.txt, pvalueMehrab.txt, pvalueMinha.txt): ")


# Getting w value text document    
w_value_file = input("Enter w value file (wvalueAnam.txt, wvalueMehrab.txt, wvalueMinha.txt): ")

while not path.exists(w_value_file):
    w_value_file = input("File does not exist. Please enter another file (wvalueAnam.txt, wvalueMehrab.txt, wvalueMinha.txt): ")

# Reading p values
p_file = open(p_value_file, "r")
p_values = p_file.read()
p_values_list_floats = [float(p) for p in p_values.split()]

# Reading w values
w_file = open(w_value_file, "r")
w_values = w_file.read()
w_values_list_floats = [float(w) for w in w_values.split()]


# Graph function: -(((w1 * x^p1) + (w2 * y^p2)) / w3) ^ (1 / 3)
def f(x, y, p_values, w_values):
    base = np.abs(-1 * (w_values[0] * pow(x, p_values[0]) + w_values[1] * pow(y, p_values[1]) / w_values[2]))
    power = 1 / p_values[2]
    ans = pow(base, power) - 0.5
    return ans

x = np.linspace(1, 100, 30)
y = np.linspace(1, 100, 30)

X, Y = np.meshgrid(x, y)

axes = plt.axes(projection='3d')
axes.set_rasterized(True)


# Continuously read w values list until there are no more values
while w_values_list_floats:  
    plt.ion()

    plt.show()
    plt.cla()

    axes.set_xlabel('x')
    axes.set_ylabel('y')
    axes.set_zlabel('z');
    axes.grid(False)
    Z = f(X, Y, p_values_list_floats, w_values_list_floats)

    axes.contour3D(X, Y, Z, 50, cmap='binary')
    
    del w_values_list_floats[0:3]
    plt.pause(0.75)
    
