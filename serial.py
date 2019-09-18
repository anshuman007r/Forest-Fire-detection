import serial
import time
import numpy as np
import smtplib
emails = ["ayan.mukherjee2015@vit.ac.in","sarthak.patel2015@vit.ac.in"]
MY_ADDRESS = 'anshuman.anand2015@vit.ac.in'
MY_PASSWORD = '73867042'
s = smtplib.SMTP(host='smtp.gmail.com', port=587)
s.ehlo()
s.starttls()
s.login(MY_ADDRESS, MY_PASSWORD)
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
def send_mail(dest,i):
 msg = MIMEMultipart()
 message = "Fire at node "+str(i+1)
 print(message)
 msg['From']=MY_ADDRESS
 msg['To']=dest
 msg['Subject']="FIRE!"
 msg.attach(MIMEText(message, 'plain'))
 s.send_message(msg)
 del msg
 return
connected = False
ser=serial.Serial("COM6",9600,timeout=0,stopbits=serial.STOPBITS_TWO)
while(not connected):
 ser.read()
 connected = True
temp_vals=[np.array([0]*10),np.array([0]*10)]
hum_vals=[np.array([0]*10),np.array([0]*10)]
flame_vals=[np.array([0]*10),np.array([0]*10)]
last_sent_t = [time.time(),time.time()]
while(True):
 line = ser.readline()
 line = line.decode('ascii')
 nodes = line.split('#')
 vals = []
 for i in nodes:
 val = i.split(',')
 vals.append(val)
 if(len(vals)>1):
 for i in range(0,len(vals)):
 temp_vals[i]=list(temp_vals[i])
 temp_vals[i].pop(0)
 temp_vals[i].append(int(vals[i][1]))
 temp_vals[i]=np.array(temp_vals[i])
 hum_vals[i]=list(hum_vals[i])
 hum_vals[i].pop(0)
 hum_vals[i].append(int(vals[i][2]))
 hum_vals[i]=np.array(hum_vals[i])
 flame_vals[i]=list(flame_vals[i])
 flame_vals[i].pop(0)
 flame_vals[i].append(int(vals[i][3]))
 flame_vals[i]=np.array(flame_vals[i])
 print("\n --------------------------------- \n")
 print("Recent temperature values at node",i+1," : ",temp_vals[i])
 print("Recent rel. humidity values at node",i+1," : ",hum_vals[i])
 print("Recent flame sensor values at node",i+1," : ",flame_vals[i])
 print("\n --------------------------------- \n")
 t=time.time()
 if((temp_vals[i][-1]>50 and flame_vals[i][-1]<80) and t-last_sent_t[i]>=60):
 send_mail(emails[i],i)
 print("\nMail sent to node ",i+1,"\n")
 last_sent_t[i]=t
 time.sleep(2)
ser.close()
