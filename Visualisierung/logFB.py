#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import telnetlib
import datetime
import time

FB_varnames = (
# "fb_par.reg_kp",        
# "fb_par.reg_ki",        
# "fb_par.reg_tn",        
# "fb_par.TA",            
# "fb_par.tvl_absenk",    
# "fb_par.tvl_steigung",  
# "fb_par.tvl_niveau",    
# "fb_par.tvl_min",       
# "fb_par.tvl_max",       
# "fb_par.at_start",      
# "fb_par.frostschutz",   
# "fb_par.tr_sw",         

"fb_in.tau_mw",         
"fb_in.sek_tvl_mw",     
"fb_in.zustand",        
"fb_in.partytime_flg",  

"fb_out.tvl_sw",        
"fb_out.prim_mv_y.y",   
"fb_out.prim_mv_y.x[0]",
"fb_out.prim_mv_y.x[1]",
"fb_out.prim_mv_y.x[2]",
"fb_out.prim_mv_y.x[3]",
"fb_out.prim_pu_sb",    
"fb_out.sek_pu_sb",     

# "fb_q.TA",              
# "fb_q.kp",              
# "fb_q.ki",              
# "fb_q.lower_limit",     
# "fb_q.upper_limit"
)


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

tn.read_very_eager()     # lese Ueberschriftenblock
          
fd = open( Filename_Prefix+"_IO.csv", "w" )

# Kopfzeile der Tabelle schreiben
kopfstr = "Zeit;"
for name in FB_varnames:
    kopfstr += name+";"
    
fd.write( kopfstr+"\n" )
print( kopfstr )

fd.close()

def getValues( cmdstr ):
    tn.write(cmdstr)
    time.sleep(1)
    buffer = tn.read_very_eager()
    bufdecode = buffer.decode('utf8')
    lines = bufdecode.splitlines()
    return lines

while (time.time() < (startTime+logTime)):

    lines = getValues( b"GET VFB\n" )
    # alle Variablen auf unplausible Werte initialisieren
    FB_v = []
    for i in range(len(FB_varnames)):
        FB_v.append(-9999.9)

    for line in lines:
        i = 0
        for name in FB_varnames:
            if (line.startswith(name)):
                FB_v[i] = float(line.split('=')[1])
            i += 1

    
    now = datetime.datetime.now()
    # Mikrosekundenteil auf 0 setzen, damit Excel den ISO Zeitstring versteht
    now = datetime.datetime( now.year, now.month, now.day, now.hour, now.minute, now.second )
    csvstr = now.isoformat(' ') + ";";

    for i in range(len(TEMPNAMES)):
        csvstr += "{0:.1f};".format( temp[i] )
                   
    fd = open( Filename_Prefix+"_IO.csv", "a" )
    fd.write( csvstr + "\n" )
    fd.close()
    print( csvstr )
    time.sleep(1)

# Logzeit abgelaufen:    
tn.close()



