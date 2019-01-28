import serial
import firebase_admin
#import time
#import datetime
#import ast
from firebase_admin import db
from firebase_admin import credentials
import json
from firebase import firebase

#cred = credentials.Certificate("trashty-prototype-firebase-adminsdk-bfyfa-4376817406.json")
#
#
#app = firebase_admin.initialize_app(cred,
#        {'databaseURL': 'https://trashty-prototype.firebaseio.com/'
#        })
#
#dbRef = db.reference(path='/', app=app)
#
arduino_data = serial.Serial('COM3', 9600)
distance = []

while True:
    data = arduino_data.readline().decode('ascii')
#    print(data)
    fb = firebase.FirebaseApplication('https://trashty-prototype.firebaseio.com/', None)
    Result = fb.post('prototype_rev1/ultrasonic', {'distance': data})
    print(Result)
    
    
#
#ultrasonic = dbRef.child()
#print(ultrasonic)


#fb = firebase.FirebaseApplication('https://trashty-prototype.firebaseio.com/', None)
#print(arduino)
#
#while True:


#result = firebase.post({'Ultrasonic': arduino})
#print(result)


#count = False;
#count2 = False;


#t = ref.get()[0]
#sum_ = t[0]['counts']['count']
#latest = ref.child('0')
#print(latest)
#print(sum_)
#previous = int(round(time.time() * 1000))
#duration = 5000
#
#def toFirebase(sum_):
#    print(sum_)
#    print(datetime.datetime.now().time())
#    timeNow = datetime.datetime.now().time()
#    ref.child('0').push({ "count":sum_,"time":str(timeNow)})
#    ref.child('0').update({'counts':{"count":sum_,"time":str(timeNow)}})
#    
#while True:
#
#    data = arduino
#    millis = int(round(time.time() * 1000))
#    
#    if data!="":
#        
#        enter = ast.literal_eval(data)['enter']
#        exit1 = ast.literal_eval(data)['exit']
#        
#        if enter < 15:
#            count = True;
#        elif count == True:
#            print("enter")
#            print(enter)
#            sum_ = sum_ + 1
#            count = False;
#
#        if exit1 < 15:
#            count2 = True;
#        elif count2 == True:
#            print("exit")
#            print(exit1)
#            sum_ = sum_ -1
#            count2 = False;
#            
#
#    if millis - previous >= duration:
#        toFirebase(sum_)
#        previous = millis
