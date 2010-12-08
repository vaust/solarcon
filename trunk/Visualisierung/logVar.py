#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import telnetlib
import datetime
import time

Filename_Prefix = str(int(time.time()))

if (len(sys.argv) > 1):
    HOST = str(sys.argv[1])
    if (len(sys.argv) > 2):
        PORT = int(sys.argv[2])
        if (len(sys.argv) > 3):
            logTime = int(sys.argv[3])
        else:
            logTime = 10 # min
    else:
        PORT = 1969
        logTime = 10 # min
else:
    HOST = "localhost"
    PORT = 1969
    logTime = 10 # min

startTime = time.time()  # Ermittle Programmstart in sec
logTime   *= 60.0        # logTime in Sekunden umrechnen
tn = telnetlib.Telnet()
tn.open(HOST, PORT)

# tn.read_very_eager()     # lese Ueberschriftenblock

befehl = input("Bitte gib den GET Befehl ein: ")
b_befehl = befehl.encode('utf8')

fd = open( Filename_Prefix+"_IO.csv", "w" )
fd.write( "einzele variable\n" )
fd.close()

def getValues( cmdstr ):
    tn.write(cmdstr)
    time.sleep(0.25)
    buffer = tn.read_very_eager()
    bufdecode = buffer.decode('utf8')
    lines = bufdecode.splitlines()
    return lines

while (time.time() < (startTime+logTime)):
    lines = getValues( b_befehl )
    for line in lines:
        if(line.find('>') > 0): # Hilfetexte herausfiltern
            continue
        if(line.find('=')>0):
            evalstr = line
            token = evalstr.split('=')
            name =  str(token[0].strip('(0123456789) '))
            value = token[1]
            now = datetime.datetime.now()
            # Mikrosekundenteil auf 0 setzen, damit Excel den ISO Zeitstring versteht
            now = datetime.datetime( now.year, now.month, now.day, now.hour, now.minute, now.second )
            print( '{2};{0};{1};'.format(name, value, now.time()) )
            fd = open( Filename_Prefix+"_IO.csv", "a" )
            fd.write( '{2};{0};{1};\n'.format(name, value, now.time()) )
            fd.close()

# Logzeit abgelaufen:    
tn.close()
fd.close()



