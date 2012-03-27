# -*- coding: utf-8 -*-
'''
Created on 10.01.2012

@author: stegmv
'''

# -*- coding: utf-8 -*-

import tkinter as tk
import tkinter.ttk as ttk

import gui_overview, gui_FB, gui_Param, gui_WW, gui_Text
import telnetIf
import time, sys, os, hashlib

PD = 2
PASSWORTMD5HASH = '7d589d8a1a5f52ab2bc55cade4c1c608'

root=tk.Tk()
root.title('Ruderclub Aschaffenburg Heizungsanlagenbedienung V0.2')
if (os.name.find('nt') >= 0):
    root.iconbitmap('RCA.ico')

'''
books = ('Text (Telnet)', 'Anlagengrafik', 'Solar', 'Warmwasser', 'Fußbodenheizung', 
         'Heizkörperheizung', 'Kessel', 'Störungen', 'Parameter', 'Zeitprogramm' )
'''
books = ('Text (Telnet)', 'Anlagengrafik', 'Warmwasser', 'Fußbodenheizung', 'Parameter' )    
    
nbook      = ttk.Notebook(root)
nbook.books = dict()

for bk in books:
    nbook.books[bk] = ttk.Frame(nbook)
    nbook.add(nbook.books[bk], text=bk)

nbook.pack(padx=PD, pady=PD, fill=tk.X)

guiAll = gui_overview.GuiOverview(nbook.books['Anlagengrafik'])
guiAll.pack()

guiFB = gui_FB.GuiFB(nbook.books['Fußbodenheizung'])
guiFB.pack()

guiParam = gui_Param.GuiParam(nbook.books['Parameter'])
guiParam.pack()

guiWW = gui_WW.GuiWW(nbook.books['Warmwasser'])
guiWW.pack( padx=PD, pady=PD )

guiText = gui_Text.GuiText(nbook.books['Text (Telnet)'])
guiText.pack( padx=PD, pady=PD )

servernameLbl   = tk.Label(root, text='Servername:')
serverlist      = ['192.168.1.2', '192.168.2.104', 'stegmann.homelinux.org']
servernameEntry = ttk.Combobox(root, width=32, values=serverlist)
passwordLbl     = tk.Label(root, text='Passwort:')
passwordEntry   = tk.Entry(root, width=16, show='*')

def connect():
    global iF
    srvname = servernameEntry.get()
    passwd = passwordEntry.get()
    h=hashlib.md5()
    h.update(passwd.encode())
    md5hex = h.hexdigest()
    if (md5hex.find(PASSWORTMD5HASH) >= 0):
        if (serverlist.count(srvname) == 0):
            serverlist.append(srvname)
            serverlist.sort()
            servernameEntry.config( values=serverlist )
    
        try:
            iF = telnetIf.TelnetInterface(srvname, 1969, 30)
            # Interface initialisieren
            guiFB.MvReglerParamSchreiben = iF.Fb_MvReglerParamSchreiben
            guiFB.MvReglerParamLesen     = iF.Fb_MvReglerParamLesen
            guiFB.schalte_PrimPumpe      = iF.Fb_Schalte_PrimPumpe
            guiFB.schalte_SekPumpe       = iF.Fb_Schalte_SekPumpe
            guiFB.wechsle_HandAuto       = iF.Fb_wechsle_HandAuto
            guiFB.leseMischventil        = iF.Fb_leseMischventil
            guiFB.schreibeMischventil    = iF.Fb_schreibeMischventil
    
            guiParam.getParam            = iF.Param_GetParam
            guiParam.putParam            = iF.Param_PutParam
    
            guiWW.PuReglerParamSchreiben = iF.WW_PuReglerParamSchreiben
            guiWW.PuReglerParamLesen     = iF.WW_PuReglerParamLesen
            guiWW.t0                     = time.time()
            guiWW.xt1.LastPhysX          = 0
            guiWW.xt2.LastPhysX          = 0
            guiWW.xt1.LastPhysY          = 40.0
            guiWW.xt2.LastPhysY          = 50.0
    
            guiText.exec_command         = iF.HoleAntwort
            
            connectBtn.config(state=tk.DISABLED)
            servernameEntry.config(state=tk.DISABLED)
    
            # Messwerterfassung starten
            update()
        except:
            pass
    else:
        pass
        
def update():
    global iF
    try:
        iF.ErmittleMesswerte()
        guiAll.updateLabels(iF.t, iF.pu, iF.mv, iF.di, iF.cnt, iF.av)
        guiFB.updateLabels(iF.t, iF.mv, iF.pu)
        guiWW.plot_MW(iF.t, iF.mv)
    except:
        pass
    if( Aktualisieren_state_tkbl.get() == True ):
        nbook.after_id = nbook.after(5000, update) # rekursiver Aufruf!
            
def beenden():
    global iF
    try:
        iF.beenden()
        iF.close()
    except:
        pass
    
    sys.exit()

def Aktualisieren_changed():
    if (Aktualisieren_state_tkbl.get() == True):
        update()
    else:
        nbook.after_cancel(nbook.after_id)
        
connectBtn = tk.Button(root, text='Verbinden', command=connect)
''' Checkbutton fuer Aktualisierung ein/aus '''
Aktualisieren_state_tkbl = tk.BooleanVar()
Aktualisieren_chkbttn = ttk.Checkbutton(root, text='Aktualisieren an/aus', variable=Aktualisieren_state_tkbl,
                                        command=Aktualisieren_changed)
quitBtn = tk.Button(root, text='Beenden', command=beenden)

servernameLbl.pack( padx=PD, pady=PD, side=tk.LEFT )
servernameEntry.pack( padx=PD, pady=PD, side=tk.LEFT )
connectBtn.pack( padx=PD, pady=PD, side=tk.LEFT )
quitBtn.pack( padx=PD, pady=PD, side=tk.LEFT )
Aktualisieren_chkbttn.pack( padx=PD, pady=PD, side=tk.LEFT )
passwordLbl.pack( padx=PD, pady=PD, side=tk.LEFT )
passwordEntry.pack( padx=PD, pady=PD, side=tk.LEFT )

root.mainloop()
