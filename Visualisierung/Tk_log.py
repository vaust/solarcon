#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import telnetlib
import datetime
import time
import tkinter 

TEMPNAMES = ( "ALL_Tau_MW", "SOL_KOLL_T_MW", "SOL_SP1_To_MW", "SOL_SP1_Tu_MW", "SOL_SP2_To_MW",
              "SOL_SP2_Tu_MW", "KES_Tvl_MW", "KES_Trl_MW", "HK_Tvl_MW", "HK_Trl_MW",
              "FB_PRIM_Trl_MW", "FB_SEK_Tvl_MW", "WW_HZG_Tvl_MW", "WW_HZG_Trl_MW", "WW_Tww_MW",
              "Tau_1h_mittel", "Tau_36h_mittel" )        

HOST = "localhost"
PORT = 1969

'''
tn = telnetlib.Telnet()
tn.open(HOST, PORT)

tn.read_very_eager()     # lese Ueberschriftenblock
'''

#   GUI erzeugen:

Bttn_list = {}

win = tkinter.Tk()
win.title('Mein Fenster')

def close_app():
    win.quit()
    quit()

cnames = tkinter.StringVar(value=TEMPNAMES)
List = tkinter.Listbox( listvariable=cnames)
Scrl = tkinter.Scrollbar()

#for name in TEMPNAMES:
#    List.insert(tkinter.END, name)


List.pack(side='left', fill=tkinter.Y)
Scrl.pack(side='right', fill=tkinter.Y)

Lbl = tkinter.Label()
Lbl.pack()

def poll():
    Lbl.after(200, poll)
    sel=List.curselection()
    if len(sel)==1:
        i = int(sel[0])
        code = TEMPNAMES[i]
        Lbl.config(text=code)
    
quit_button = tkinter.Button(text='Quit', command=close_app )
quit_button.pack()

poll()
win.mainloop()

'''    
fd.close()

def getValues( cmdstr ):
    tn.write(cmdstr)
    time.sleep(1)
    buffer = tn.read_very_eager()
    bufdecode = buffer.decode('utf8')
    lines = bufdecode.splitlines()
    return lines

while (time.time() < (startTime+logTime)):

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
    # alle AO auf unplausible Strings initialisieren
    ao = []
    for i in range(len(AONAMES)):
        ao.append( -99.9 )

    for line in lines:
        i = 0
        for name in AONAMES:
            if (line.startswith(name)):
                ao[i] = float(line.split('=')[1].split('pct')[0])
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
    time.sleep(1)

# Logzeit abgelaufen:    
tn.close()

'''



