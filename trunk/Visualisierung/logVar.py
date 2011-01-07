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

stopTime  = time.time()+logTime*60.0 # logTime in Sekunden umrechnen
tn = telnetlib.Telnet()
tn.open(HOST, PORT)

befehl = 'GET '+input('Modul und Nummer fuer 1. Variable : ')
b_befehl_1 = befehl.encode('utf8')
befehl = 'GET '+input('Modul und Nummer fuer 2. Variable : ')
b_befehl_2 = befehl.encode('utf8')

fd = open( Filename_Prefix+'_IO.csv', 'w' )
fd.write( 'einzelne Variable\n' )
fd.close()

def getValues( cmdstr ):
    tn.write(cmdstr)
    time.sleep(0.5)
    buffer = tn.read_very_eager()
    bufdecode = buffer.decode('utf8')
    lines = bufdecode.splitlines()
    return lines

def parseValues( lines ):
    for line in lines:
        if (line.find('>')>0): # Hilfetexte herausfiltern
            continue
        if (line.find('=')>0):
            evalstr = line
            token = evalstr.split('=')
            name =  str(token[0].strip('(0123456789) '))
            value = token[1]
            # now = datetime.datetime.now()
            # Mikrosekundenteil auf 0 setzen, damit Excel den ISO Zeitstring versteht
            # now = datetime.datetime( now.year, now.month, now.day, now.hour, now.minute, now.second )
            zeitstempel = time.time()
            print( '{2};{0};{1};'.format(name, value, zeitstempel) )
            fd = open( Filename_Prefix+'_IO.csv', 'a' )
            fd.write( '{2};{0};{1};\n'.format(name, value, zeitstempel) )
            fd.close()
            
while (time.time() < stopTime):
    lines = getValues( b_befehl_1 )
    parseValues( lines )
    lines = getValues( b_befehl_2 )
    parseValues( lines )

# Logzeit abgelaufen:    
tn.close()
fd.close()



