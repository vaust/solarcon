# -*- coding: utf-8 -*-
VERSION = "0.4.3"

import tkinter as tk
import tkinter.ttk as ttk
import telnetlib
import time

#------- GUI aufbauen --------

def cllbck(event): # Callback zur Ermittlung der Koordinaten, auf denen die Labels gesetzt werden müssen
    print('Mouse clicked at ', all_main.canvasx(event.x), all_main.canvasy(event.y) )

root = tk.Tk()
root.title( "Ruder-Club-Aschaffenburg Visualisierung der Heizungsanlage  Version: "+VERSION )

PD = 5
nbook = ttk.Notebook(root)
page_ALL = ttk.Frame(nbook)
page_SOL = ttk.Frame(nbook)
page_WW = ttk.Frame(nbook)
page_FB = ttk.Frame(nbook)
page_HK = ttk.Frame(nbook)
page_KES = ttk.Frame(nbook)
page_ERR = ttk.Frame(nbook)
page_PAR = ttk.Frame(nbook)
page_ZEIT = ttk.Frame(nbook)
nbook.add(page_ALL, text='Gesamtübersicht')
nbook.add(page_SOL, text='Solarheizkreis')
nbook.add(page_WW, text='Warmwasser')
nbook.add(page_FB, text='Fußbodenheizung')
nbook.add(page_HK, text='Heizkörperheizung')
nbook.add(page_KES, text='Kesselsteuerung')
nbook.add(page_ERR, text='Störungsmeldungen')
nbook.add(page_PAR, text='Parameter')
nbook.add(page_ZEIT, text='Zeitprogramm')
nbook.pack(padx=PD, pady=PD, fill=tk.X)

#------- Inhalt der Gesamtübersicht ------

all_vbar = ttk.Scrollbar( page_ALL, orient=tk.VERTICAL)
all_hbar = ttk.Scrollbar( page_ALL, orient=tk.HORIZONTAL)

all_main = tk.Canvas(page_ALL, bg='white', scrollregion=(0,0,2000,2000),
                       yscrollcommand=all_vbar.set, xscrollcommand=all_hbar.set, width=1220, height=560)
all_main.bind('<Button-1>', cllbck)
bgpic = tk.PhotoImage(file='Visualisierung.gif')
all_main.create_image(1000,1000, image=bgpic)
                             
all_vbar.grid(row=0, column=1, sticky=tk.NS)
all_hbar.grid(row=1, column=0, sticky=tk.EW)
all_main.grid(row=0, column=0, sticky=tk.NSEW)

all_vbar.config(command=all_main.yview)
all_hbar.config(command=all_main.xview)

all_update_bttn = tk.Button( page_ALL, text='Aktualisieren' )
all_update_bttn.grid(row=2, column=0, padx=PD, pady=PD, sticky=tk.W)

#-------- Frame für die Verbindung mit dem Server ------

bttn_frame = tk.LabelFrame( root, text='Verbindung mit Server' )
# bttn_frame.grid(row=2, column=0, padx=10, pady=10, sticky=tk.EW)
bttn_frame.pack(padx=5, pady=5, side=tk.LEFT) #, fill=tk.X)

server_lbl = tk.Label(bttn_frame, text='Server: ')
server_entry = tk.Entry(bttn_frame, width=30, bg='LightGoldenrod1')
port_lbl = tk.Label(bttn_frame, text='Port: ')
port_entry = tk.Entry(bttn_frame, width=6, bg='LightGoldenrod1')

server_lbl.pack(padx=PD, pady=PD, side=tk.LEFT)
server_entry.pack(padx=PD, pady=PD, side=tk.LEFT)
port_lbl.pack(padx=PD, pady=PD, side=tk.LEFT)
port_entry.pack(padx=PD, pady=PD, side=tk.LEFT)

# Defaultwerte
server_entry.insert( tk.END, 'stegmann.homelinux.org' )
port_entry.insert( tk.END, '1969' )

connect_bttn = tk.Button( bttn_frame, text='Verbinden' )
connect_bttn.pack(padx=PD, pady=PD, side=tk.LEFT)

#----------- Gesamtübersicht mit Labels füllen ----------
'''
Widgets in Canvas plazieren:
1. Widget Objekt erzeugen auf Canvas (all_main)
2. Mit .create_window() Methode auf Canvas platzieren. Der Parameter window benennt das Widget Objekt
'''

SCHRIFT = ('Arial', 12, 'bold')
L       = 8
HFARBE  = 'LightGoldenrod1'

TEMP_NAMES = { "ALL_Tau_MW", "SOL_KOLL_T_MW", "SOL_SP1_To_MW", "SOL_SP1_Tu_MW", "SOL_SP2_To_MW",
              "SOL_SP2_Tu_MW", "KES_Tvl_MW", "KES_Trl_MW", "HK_Tvl_MW", "HK_Trl_MW",
              "FB_PRIM_Trl_MW", "FB_SEK_Tvl_MW", "WW_HZG_Tvl_MW", "WW_HZG_Trl_MW", "WW_Tww_MW",
              "Tau_1h_mittel", "Tau_36h_mittel" }        
temp_lbl = dict()
for t_name in TEMP_NAMES:
    temp_lbl[t_name] = tk.Label( all_main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---.-°C' )

PU_NAMES = { "WW_HZG_PU_SB", "HK_PU_SB", "WW_ZIRK_PU_SB", "HK_PU_SB", "FB_SEK_PU_SB", "FB_PRIM_PU_SB",
             "KES_PU_SP1_SB", "KES_PU_SP2_SB", "SOL_PU_SB" }
pu_lbl = dict()
for pu_name in PU_NAMES:
    pu_lbl[pu_name] = tk.Label( all_main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---' )

MV_NAMES = { "WW_HZG_MV_Y", "FB_PRIM_MV_Y", "HK_MV_Y", "WW_HZG_VV_Y" }
mv_lbl = dict()
for mv_name in MV_NAMES:
    mv_lbl[mv_name] = tk.Label( all_main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---%' )

CNT_NAMES = { "WW_WZ_MW" }
cnt_lbl = dict()
cnt_lbl["WW_WZ_MW"] = tk.Label( all_main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='-.---' )

AV_NAMES = { "SOL_SP1_AV_SB", "SOL_SP2_AV_SB" }
av_lbl = dict()
for av_name in AV_NAMES:
    av_lbl[av_name] = tk.Label( all_main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---' )

DI_NAMES = { "ALL_PARTY", "WW_PARTY" }
di_lbl = dict()
for di_name in DI_NAMES:
    di_lbl[di_name] = tk.Label( all_main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---' )
    
##
all_main.create_window(370, 441, window=temp_lbl["SOL_KOLL_T_MW"])
all_main.create_window(560, 476, window=temp_lbl["WW_Tww_MW"])
all_main.create_window(560, 812, window=temp_lbl["WW_HZG_Tvl_MW"])
all_main.create_window(658, 812, window=temp_lbl["WW_HZG_Trl_MW"])
all_main.create_window(1002, 555, window=temp_lbl["FB_SEK_Tvl_MW"])
all_main.create_window(1101, 813, window=temp_lbl["FB_PRIM_Trl_MW"])
all_main.create_window(483, 968, window=temp_lbl["SOL_SP1_To_MW"])
all_main.create_window(483, 1155, window=temp_lbl["SOL_SP1_Tu_MW"])
all_main.create_window(483, 1460, window=temp_lbl["SOL_SP2_To_MW"])
all_main.create_window(483, 1647, window=temp_lbl["SOL_SP2_Tu_MW"])
all_main.create_window(781, 812, window=temp_lbl["HK_Tvl_MW"])
all_main.create_window(879, 812, window=temp_lbl["HK_Trl_MW"])
all_main.create_window(1403, 1168, window=temp_lbl["KES_Tvl_MW"])
all_main.create_window(1403, 1355, window=temp_lbl["KES_Trl_MW"])
all_main.create_window(1742, 978, window=temp_lbl["ALL_Tau_MW"])
##
all_main.create_window(759, 755, window=pu_lbl["HK_PU_SB"])
all_main.create_window(980, 487, window=pu_lbl["FB_SEK_PU_SB"])
all_main.create_window(980, 756, window=pu_lbl["FB_PRIM_PU_SB"])
all_main.create_window(538, 756, window=pu_lbl["WW_HZG_PU_SB"])
all_main.create_window(861, 425, window=pu_lbl["WW_ZIRK_PU_SB"])
all_main.create_window(1289, 1157, window=pu_lbl["KES_PU_SP1_SB"])
all_main.create_window(1289, 1240, window=pu_lbl["KES_PU_SP2_SB"])
all_main.create_window(257, 996, window=pu_lbl["SOL_PU_SB"])
##    
# main.create_window(657, 427, window=cnt_lbl["WW_WZ_MW"])
##
all_main.create_window(550, 855, window=mv_lbl["WW_HZG_MV_Y"])
all_main.create_window(772, 855, window=mv_lbl["FB_PRIM_MV_Y"])
all_main.create_window(993, 855, window=mv_lbl["HK_MV_Y"])
all_main.create_window(750, 1071, window=mv_lbl["WW_HZG_VV_Y"])
##
all_main.create_window(403, 1252, window=av_lbl["SOL_SP1_AV_SB"])
all_main.create_window(335, 1714, window=av_lbl["SOL_SP2_AV_SB"])
##
all_main.create_window(1742, 1008, window=di_lbl["ALL_PARTY"])
all_main.create_window(1742, 1038, window=di_lbl["WW_PARTY"])

#-------- Eigentliche Gesamtübersichtsanwendung --------

def getValues( cmdstr ):
    tn.write(cmdstr)
    time.sleep(1)
    buffer = tn.read_very_eager()
    bufdecode = buffer.decode('utf8')
    lines = bufdecode.splitlines()
    return lines

def leseWerte():
    lines = getValues( b"GET T\n" )
    for t_name in TEMP_NAMES:
        for line in lines:
            if (line.startswith(t_name)):
                t_str = str( line.split('=')[1].split('°')[0] )
                temp_lbl[t_name].config( text=t_str+'°C' )
                
    lines = getValues( b"GET DO\n" )
    for pu_name in PU_NAMES:
        for line in lines:
            if (line.startswith(pu_name)):
                pu_str = str( line.split('=')[1] )
                pu_lbl[pu_name].config( text=pu_str )                   
                
    for av_name in AV_NAMES:
        for line in lines:
            if (line.startswith(av_name)):
                av_str = str( line.split('=')[1] )
                av_lbl[av_name].config( text=pu_str )

    lines = getValues( b"GET AO\n" )
    for mv_name in MV_NAMES:
        for line in lines:
            if (line.startswith(mv_name)):
                mv_str = str( line.split('=')[1].split('p')[0] )
                mv_lbl[mv_name].config( text=mv_str+'%' )

    lines = getValues( b"GET DI\n" )
    for di_name in DI_NAMES:
        for line in lines:
            if (line.startswith(di_name)):
                di_str = str( line.split('=')[1] )
                di_lbl[di_name].config( text=di_str )                   

#-------------

#-------- GUI für Fußbodenheizung -----------
# todo

fb_lblframe_handauto = tk.LabelFrame( page_FB, text='Prozesssteuerung')
fb_lblframe_handauto.pack(padx=PD, pady=PD, side=tk.TOP)

fb_handin_state_tkbl = tk.BooleanVar()
fb_handin_chkbttn = ttk.Checkbutton(fb_lblframe_handauto, text='Prozesseingabe auf Handbetrieb',
                                    variable=fb_handin_state_tkbl)
fb_handin_chkbttn.grid(column=0, row=0, padx=PD, pady=PD, sticky=tk.NW)

def fb_in_handauto():
    if (fb_handin_state_tkbl.get() == True):
        tn.write(b'hand infb')
    else:
        tn.write(b'auto infb')
    time.sleep(1)

fb_handin_chkbttn.config(command=fb_in_handauto)

#   ---   
fb_hand_state_tkbl = tk.BooleanVar()
fb_hand_chkbttn = ttk.Checkbutton(fb_lblframe_handauto, text='Prozess auf Handbetrieb',
                                    variable=fb_hand_state_tkbl)
fb_hand_chkbttn.grid(column=0, row=1, padx=PD, pady=PD, sticky=tk.NW)

def fb_handauto():
    if (fb_handin_state_tkbl.get() == True):
#        tn.write(b'hand fb')
        fb_PrimPumpe_chkbttn.config(state=tk.DISABLED)
#    else:
#        tn.write(b'auto fb')
    time.sleep(1)

fb_hand_chkbttn.config(command=fb_handauto)

#   --- Primärpumpe
fb_PrimPumpe_state_tkbl = tk.BooleanVar()
fb_PrimPumpe_chkbttn = ttk.Checkbutton(fb_lblframe_handauto, text='Prim�rpumpe',
                                    variable=fb_PrimPumpe_state_tkbl)
fb_PrimPumpe_chkbttn.grid(column=1, row=0, padx=PD, pady=PD, sticky=tk.NW)

#   --- Sekundärpumpe
fb_SekPumpe_state_tkbl = tk.BooleanVar()
fb_SekPumpe_chkbttn = ttk.Checkbutton(fb_lblframe_handauto, text='Sekund�rpumpe',
                                    variable=fb_SekPumpe_state_tkbl)
fb_SekPumpe_chkbttn.grid(column=1, row=1, padx=PD, pady=PD, sticky=tk.NW)

#   --- Mschventilstellung
fb_Mischventil_lbl = tk.Label(fb_lblframe_handauto, text='Mischventilstellung in %')
fb_Mischventil_lbl.grid( column=0, row=2, padx=PD, pady=PD, sticky=tk.SW) 
fb_Mischventil_scle = tk.Scale(fb_lblframe_handauto, orient=tk.HORIZONTAL, from_=0.0, to=100.0, length=300, resolution=0)
fb_Mischventil_scle.grid(column=1, row=2, padx=PD, pady=PD, sticky=tk.NW)


#   ---

#   --- FB Mischventilregler parametrieren ---
fb_lblframe_mvregler = tk.LabelFrame( page_FB, text='Mischventilregler Online Parametrierung')
fb_lblframe_mvregler.pack(padx=PD, pady=PD, side=tk.TOP)

fb_mvregler_Kp_lbl = tk.Label(fb_lblframe_mvregler, text='Proportionalbeiwert Kp:')
fb_mvregler_Kp_entry = tk.Entry(fb_lblframe_mvregler, width=8, bg='white')
fb_mvregler_KpUnit_lbl = tk.Label(fb_lblframe_mvregler, text='%/K')

fb_mvregler_Ki_lbl = tk.Label(fb_lblframe_mvregler, text='Integralbeiwert Ki:')
fb_mvregler_Ki_entry = tk.Entry(fb_lblframe_mvregler, width=8, bg='white')
fb_mvregler_KiUnit_lbl = tk.Label(fb_lblframe_mvregler, text='%/(K x sec)')

fb_mvregler_AP_lbl = tk.Label(fb_lblframe_mvregler, text='Arbeitspunkt AP:')
fb_mvregler_AP_entry = tk.Entry(fb_lblframe_mvregler, width=8, bg='white')
fb_mvregler_APUnit_lbl = tk.Label(fb_lblframe_mvregler, text='%')

fb_mvregler_Kp_scle = tk.Scale(fb_lblframe_mvregler, orient=tk.HORIZONTAL, from_=0.0, to= 50.0, length=200, resolution=0.1)
fb_mvregler_Ki_scle = tk.Scale(fb_lblframe_mvregler, orient=tk.HORIZONTAL, from_=0.0, to= 50.0, length=200, resolution=0.1)
fb_mvregler_AP_scle = tk.Scale(fb_lblframe_mvregler, orient=tk.HORIZONTAL, from_=0.0, to=100.0, length=200, resolution=0.1)

fb_mvregler_Kp_lbl.grid(column=0, row=0, padx=PD, sticky=tk.W )
fb_mvregler_Ki_lbl.grid(column=0, row=1, padx=PD, sticky=tk.W )
fb_mvregler_AP_lbl.grid(column=0, row=2, padx=PD, sticky=tk.W )
fb_mvregler_Kp_entry.grid(column=1, row=0, padx=PD )
fb_mvregler_Ki_entry.grid(column=1, row=1, padx=PD )
fb_mvregler_AP_entry.grid(column=1, row=2, padx=PD )
fb_mvregler_KpUnit_lbl.grid(column=2, row=0, padx=PD, sticky=tk.W )
fb_mvregler_KiUnit_lbl.grid(column=2, row=1, padx=PD, sticky=tk.W )
fb_mvregler_APUnit_lbl.grid(column=2, row=2, padx=PD, sticky=tk.W )
fb_mvregler_Kp_scle.grid(column=3, row=0, padx=PD )
fb_mvregler_Ki_scle.grid(column=3, row=1, padx=PD )
fb_mvregler_AP_scle.grid(column=3, row=2, padx=PD )

fb_mvregler_ReadBttn = tk.Button(fb_lblframe_mvregler, text='Lesen')
fb_mvregler_ChangeBttn = tk.Button(fb_lblframe_mvregler, text='Schreiben')
fb_mvregler_ReadBttn.grid(column=2, row=3, padx=PD, pady=PD )
fb_mvregler_ChangeBttn.grid(column=3, row=3, padx=PD, pady=PD )

def SetEntryVal_Kp(event):
    s = str(fb_mvregler_Kp_scle.get())[0:6]
    fb_mvregler_Kp_entry.delete(0,tk.END)
    fb_mvregler_Kp_entry.insert(0, s)

def SetEntryVal_Ki(event):
    s = str(fb_mvregler_Ki_scle.get())[0:6]
    fb_mvregler_Ki_entry.delete(0,tk.END)
    fb_mvregler_Ki_entry.insert(0, s)

def SetEntryVal_AP(event):
    s = str(fb_mvregler_AP_scle.get())[0:6]
    fb_mvregler_AP_entry.delete(0,tk.END)
    fb_mvregler_AP_entry.insert(0, s)

def SetScleVal_Kp(event):
    s = fb_mvregler_Kp_entry.get()
    fb_mvregler_Kp_scle.set(s)

def SetScleVal_Ki(event):
    s = fb_mvregler_Ki_entry.get()
    fb_mvregler_Ki_scle.set(s)

def SetScleVal_AP(event):
    s = fb_mvregler_AP_entry.get()
    fb_mvregler_AP_scle.set(s)
    
fb_mvregler_Kp_scle.bind('<ButtonRelease-1>', SetEntryVal_Kp)
fb_mvregler_Ki_scle.bind('<ButtonRelease-1>', SetEntryVal_Ki)
fb_mvregler_AP_scle.bind('<ButtonRelease-1>', SetEntryVal_AP)
fb_mvregler_Kp_entry.bind('<Return>', SetScleVal_Kp)
fb_mvregler_Ki_entry.bind('<Return>', SetScleVal_Ki)
fb_mvregler_AP_entry.bind('<Return>', SetScleVal_AP)

def fb_schreibe_mvregler_parameter():
    command_str = "put vfb 23 "+str(fb_mvregler_Kp_scle.get())[0:6] # Kp schreiben todo
    tn.write(command_str.encode('utf-8'))
    command_str = "put vfb 23 "+str(fb_mvregler_Ki_scle.get())[0:6] # Ki schreiben todo
    tn.write(command_str.encode('utf-8')) 
    command_str = "put vfb 23 "+str(fb_mvregler_AP_scle.get())[0:6] # Ki schreiben todo
    tn.write(command_str.encode('utf-8'))
    
fb_mvregler_ChangeBttn.config(command=fb_schreibe_mvregler_parameter)

def fb_lese_mvregler_parameter():
    a = 0 # todo

fb_mvregler_ReadBttn.config(command=fb_lese_mvregler_parameter)


#-------- GUI für Heizkörperheizung -----------
# todo

hk_handin_state_tkbl = tk.BooleanVar()
hk_handin_chkbttn = ttk.Checkbutton(page_HK, text='Prozesseingabe auf Handbetrieb',
                                    variable=hk_handin_state_tkbl)
hk_handin_chkbttn.grid(row=2, column=0, padx=PD, pady=PD, sticky=tk.W)

def hk_in_handauto():
    if (hk_handin_state_tkbl.get() == True):
        tn.write(b'hand inhk')
    else:
        tn.write(b'auto inhk')
    time.sleep(1)

#-------- Störungsmeldungen -------------
IO_FARBE  = 'green'
NIO_FARBE = 'red'
err_BSM_lbl = tk.Label( page_ERR, width=32, bg=IO_FARBE, relief='sunken',
                        font=SCHRIFT, text='Brennerstörung' )
err_TSENS_lbl = tk.Label( page_ERR, width=32, bg=IO_FARBE, relief='sunken',
                          font=SCHRIFT, text='Temperatursensor Störung' )
err_STBFB_lbl = tk.Label( page_ERR, width=32, bg=IO_FARBE, relief='sunken',
                          font=SCHRIFT, text='STB Fußbodenheizung' )
err_BSM_lbl.pack(padx=PD, pady=PD)
err_TSENS_lbl.pack(padx=PD, pady=PD)
err_STBFB_lbl.pack(padx=PD, pady=PD)

err_update_bttn = tk.Button(page_ERR, text='Aktualisieren')
err_update_bttn.pack(padx=PD, pady=PD)

def err_update():
    lines = getValues(b'get DI')
    for l in lines:
        if ( l.startswith('KES_SSM') ):
            if( l.split('=')[1].find('NORMAL') > 0 ):
                err_BSM_lbl.config( bg=IO_FARBE )
            else:
                err_BSM_lbl.config( bg=NIO_FARBE )
        elif ( l.startswith('FB_SEK_TW') ):
            if( l.split('=')[1].find('NORMAL') > 0 ):
                err_STBFB_lbl.config( bg=IO_FARBE )
            else:
                err_STBFB_lbl.config( bg=NIO_FARBE )
                
err_update_bttn.config(command=err_update)

#--- Zeitprogrammeditor
'''
tp_main = tk.Canvas(page_ZEIT, bg='blue', width=1220, height=650)
tp_main.pack(fill=tk.BOTH)
'''
#tp_main.create_rectangle


#-------- Connect mit Server ------------

def connect():
    HOST = server_entry.get()
    PORT = port_entry.get()
    tn.open(HOST, PORT)
    tn.read_very_eager()

    all_update_bttn.config(command=leseWerte  )
    fb_hand_chkbttn.config(command=fb_handauto)
    fb_handin_chkbttn.config(command=fb_in_handauto)
    hk_handin_chkbttn.config(command=hk_in_handauto)

    leseWerte()
        
#------------- Hauptprogramm mit Mainloop() -----------
    
connect_bttn.config( command=connect )

tn = telnetlib.Telnet()
root.mainloop()

tn.close()


        
