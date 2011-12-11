#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import telnetlib
import datetime
import time
from tkinter import * 

TEMPNAMES = { "ALL_Tau_MW", "SOL_KOLL_T_MW", "SOL_SP1_To_MW", "SOL_SP1_Tu_MW", "SOL_SP2_To_MW",
              "SOL_SP2_Tu_MW", "KES_Tvl_MW", "KES_Trl_MW", "HK_Tvl_MW", "HK_Trl_MW",
              "FB_PRIM_Trl_MW", "FB_SEK_Tvl_MW", "WW_HZG_Tvl_MW", "WW_HZG_Trl_MW", "WW_Tww_MW",
              "Tau_1h_mittel", "Tau_36h_mittel" }        

HOST = "localhost"
PORT = 1969
temp = dict()


def getValues( cmdstr ):
    tn.write(cmdstr)
    time.sleep(1)
    buffer = tn.read_very_eager()
    bufdecode = buffer.decode('utf8')
    lines = bufdecode.splitlines()
    return lines

def getT():
    lines = getValues( b"GET T\n" )

    for line in lines:
        for name in TEMPNAMES:
            if (line.startswith(name)):
                temp[name] = str(line.split('=')[1].split('°')[0])

def get_Tau():
    getT()
    win.Tau_Txt.config( text=temp["ALL_Tau_MW"] )

def get_SOL():
    getT()
    win.SOL_Txt.config( text=temp["SOL_KOLL_T_MW"] )
 
tn = telnetlib.Telnet()
tn.open(HOST, PORT)
tn.read_very_eager()     # lese Ueberschriftenblock

#   GUI erzeugen:

win = Tk()
win.title('Mein Fenster')

win.Tau_Bttn = Button( win, text='Aussentemperatur', command = get_Tau )
win.Tau_Txt  = Label( win, relief=SUNKEN, bg='black', fg='red', width=10, font=('arial',18) )
win.Tau_Bttn.pack( padx=10, pady=10 )
win.Tau_Txt.pack( padx=10, pady=10 )

win.SOL_Bttn = Button( win, text='Solarkollektortemperatur', command = get_SOL )
win.SOL_Txt  = Label( win, relief=SUNKEN, bg='black', fg='red', width=10, font=('arial',18) )
win.SOL_Bttn.pack( padx=10, pady=10 )
win.SOL_Txt.pack( padx=10, pady=10 )


win.mainloop()
   
tn.close()






