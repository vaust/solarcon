'''
Created on 24.01.2012

@author: stegmv
'''
               
import telnetlib
import time

def connect(host, server):
    tn.open(host, server)
    tn.read_very_eager()

tn = telnetlib.Telnet()
 