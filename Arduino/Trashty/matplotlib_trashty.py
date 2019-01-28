
import numpy
import matplotlib.pyplot as plt
import sys, serial, argparse
import numpy as np
from time import sleep
import re

arduino_data = serial.Serial('COM3', 9600)
distance = []


data = arduino_data.readline().decode('ascii')
print(data)
