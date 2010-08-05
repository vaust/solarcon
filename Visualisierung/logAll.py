#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import telnetlib
import datetime
import time

TEMPNAMES = ( "ALL_Tau_MW", "SOL_KOLL_T_MW", "SOL_SP1_To_MW", "SOL_SP1_Tu_MW", "SOL_SP2_To_MW",
              "SOL_SP2_Tu_MW", "KES_Tvl_MW", "KES_Trl_MW", "HK_Tvl_MW", "HK_Trl_MW",
              "FB_PRIM_Trl_MW", "FB_SEK_Tvl_MW", "WW_HZG_Tvl_MW", "WW_HZG_Trl_MW", "WW_Tww_MW",
              "Tau_1h_mittel_f", "Tau_36h_mittel_f" )        
DINAMES = ( "ALL_PARTY", "WW_PARTY", "KES_SSM", "KES_BR_BM", "FB_SEK_TW" )
DONAMES = ( "SOL_PU_SB", "SOL_SP1_AV_SB", "SOL_SP2_AV_SB", "KES_PU_SP1_SB", "KES_PU_SP2_SB",
            "HK_PU_SB", "FB_PRIM_PU_SB", "FB_SEK_PU_SB", "WW_HZG_VV_SB", "WW_HZG_PU_SB", "WW_ZIRK_PU_SB" )
AONAMES = ( "KES_Tvl_Y", "HK_MV_Y", "FB_PRIM_MV_Y", "WW_HZG_MV_Y", "WW_HZG_PU_Y" )

Filename_Prefix = str(int(time.time()))

if (len(sys.argv) > 1):
    HOST = str(sys.argv[1])
    if (len(sys.argv) > 2):
        PORT = int(sys.argv[2])
        if (len(sys.argv) > 3):
            MAX_N = int(sys.argv[3])
        else:
            MAX_N = 10
    else:
        PORT = 1969
        MAX_N = 10
else:
    HOST = "localhost"
    PORT = 1969
    MAX_N = 10

tn = telnetlib.Telnet()
tn.open(HOST, PORT)

# lese Ueberschriftenblock
tn.read_very_eager()
          
fd = open( Filename_Prefix+"_IO.csv", "w" )

# Kopfzeile der Tabelle schreiben
kopfstr = "Zeit;"
for name in TEMPNAMES:
    kopfstr += name+";"
for name in DINAMES:
    kopfstr += name+";"
for name in DONAMES:
    kopfstr += name+";"
for name in AONAMES:
    kopfstr += name+";"
    
kopfstr += "\n"

fd.write( kopfstr )
print( kopfstr )

fd.close()

def getValues( cmdstr ):
    tn.write(cmdstr)
    time.sleep(1)
    buffer = tn.read_very_eager()
    bufdecode = buffer.decode('utf8')
    lines = bufdecode.splitlines()
    return lines

for cnt in range(MAX_N):

    lines = getValues( b"GET T\n" )
    # alle Temperaturen auf unplausible Werte initialisieren
    temp = []
    for i in range(len(TEMPNAMES)):
        temp.append(-100.0)

    for line in lines:
        i = 0
        for name in TEMPNAMES:
            if (line.startswith(name)):
                temp[i] = float(line.split('=')[1].split('°')[0])
            i += 1

    lines = getValues( b"GET DI\n" )
    # alle DI auf unplausible Strings initialisieren
    din = []
    for i in range(len(DINAMES)):
        din.append( "NDEF" )

    for line in lines:
        i = 0
        for name in DINAMES:
            if (line.startswith(name)):
                din[i] = line.split('= ')[1]
            i += 1

    lines = getValues( b"GET DO\n" )
    # alle DO auf unplausible Strings initialisieren
    dout = []
    for i in range(len(DONAMES)):
        dout.append( "NDEF" )

    for line in lines:
        i = 0
        for name in DONAMES:
            if (line.startswith(name)):
                dout[i] = line.split('= ')[1]
            i += 1

    lines = getValues( b"GET AO\n" )
    # alle DO auf unplausible Strings initialisieren
    ao = []
    for i in range(len(AONAMES)):
        ao.append( -99 )

    for line in lines:
        i = 0
        for name in AONAMES:
            if (line.startswith(name)):
                ao[i] = int(line.split('=')[1].split('pct')[0])
            i += 1
    
    now = datetime.datetime.now()
    # Mikrosekundenteil auf 0 setzen, damit Excel den ISO Zeitstring versteht
    now = datetime.datetime( now.year, now.month, now.day, now.hour, now.minute, now.second )
    csvstr = now.isoformat(' ') + ";";

    for i in range(len(TEMPNAMES)):
        csvstr += "{0:.1f};".format( temp[i] )
    for i in range(len(DINAMES)):
        csvstr += din[i]+";"
    for i in range(len(DONAMES)):
        csvstr += dout[i]+";"
    for i in range(len(AONAMES)):
        csvstr += "{0};".format( ao[i] )
                   
    fd = open( Filename_Prefix+"_IO.csv", "a" )
    fd.write( csvstr + "\n" )
    fd.close()
    print( csvstr )
    cnt += 1
    time.sleep(1)
    
tn.close()



