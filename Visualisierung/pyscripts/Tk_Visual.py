VERSION = "0.2.1"

import tkinter as tk
import tkinter.ttk as ttk
import telnetlib
import time

#------- GUI aufbauen --------

def cllbck(event): # Callback zur Ermittlung der Koordinaten, auf denen die Labels gesetzt werden müssen
    print('Mouse clicked at ', main.canvasx(event.x), main.canvasy(event.y) )

root = tk.Tk()
root.title( "Ruderclub Aschaffenburg Heizungsanlagenvisualisierung  Version: "+VERSION )

vbar = ttk.Scrollbar( root, orient=tk.VERTICAL)
hbar = ttk.Scrollbar( root, orient=tk.HORIZONTAL)

main = tk.Canvas(root, bg='white', scrollregion=(0,0,2000,2000),
                       yscrollcommand=vbar.set, xscrollcommand=hbar.set, width=1024, height=600)
main.bind('<Button-1>', cllbck)
bgpic = tk.PhotoImage(file='Visualisierung.gif')
main.create_image(1000,1000, image=bgpic)
                             
vbar.grid(row=0, column=1, sticky=tk.NS)
hbar.grid(row=1, column=0, sticky=tk.EW)
main.grid(row=0, column=0, sticky=tk.NSEW)

vbar.config(command=main.yview)
hbar.config(command=main.xview)

bttn_frame = tk.LabelFrame( root, text='Verbindung mit Server' )
bttn_frame.grid(row=2, column=0, padx=10, pady=10, sticky=tk.EW)

server_lbl = tk.Label(bttn_frame, text='Server: ')
server_entry = tk.Entry(bttn_frame, width=30, bg='LightGoldenrod1')
port_lbl = tk.Label(bttn_frame, text='Port: ')
port_entry = tk.Entry(bttn_frame, width=6, bg='LightGoldenrod1')

PD = 5
server_lbl.pack(padx=PD, pady=PD, side=tk.LEFT)
server_entry.pack(padx=PD, pady=PD, side=tk.LEFT)
port_lbl.pack(padx=PD, pady=PD, side=tk.LEFT)
port_entry.pack(padx=PD, pady=PD, side=tk.LEFT)

connect_bttn = tk.Button( bttn_frame, text='Verbinden' )
update_bttn = tk.Button( bttn_frame, text='Aktualisieren' )
# disconnect_bttn = tk.Button( bttn_frame, text='Trennen' )
connect_bttn.pack(padx=PD, pady=PD, side=tk.LEFT)
# disconnect_bttn.pack(padx=PD, pady=PD, side=tk.LEFT)
update_bttn.pack(padx=PD, pady=PD, side=tk.RIGHT)

'''
Widgets in Canvas plazieren:
1. Widget Objekt erzeugen auf Canvas (main)
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
    temp_lbl[t_name] = tk.Label( main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---.-°C' )

PU_NAMES = { "WW_HZG_PU_SB", "HK_PU_SB", "WW_ZIRK_PU_SB", "HK_PU_SB", "FB_SEK_PU_SB", "FB_PRIM_PU_SB",
             "KES_PU_SP1_SB", "KES_PU_SP2_SB", "SOL_PU_SB" }
pu_lbl = dict()
for pu_name in PU_NAMES:
    pu_lbl[pu_name] = tk.Label( main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---' )

MV_NAMES = { "WW_HZG_MV_Y", "FB_PRIM_MV_Y", "HK_MV_Y", "WW_HZG_VV_Y" }
mv_lbl = dict()
for mv_name in MV_NAMES:
    mv_lbl[mv_name] = tk.Label( main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---%' )

CNT_NAMES = { "WW_WZ_MW" }
cnt_lbl = dict()
cnt_lbl["WW_WZ_MW"] = tk.Label( main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='-.---' )

AV_NAMES = { "SOL_SP1_AV_SB", "SOL_SP2_AV_SB" }
av_lbl = dict()
for av_name in AV_NAMES:
    av_lbl[av_name] = tk.Label( main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---' )

DI_NAMES = { "ALL_PARTY", "WW_PARTY" }
di_lbl = dict()
for di_name in DI_NAMES:
    di_lbl[di_name] = tk.Label( main, width=L, bg=HFARBE, relief='sunken', font=SCHRIFT, text='---' )
    
##
main.create_window(370, 441, window=temp_lbl["SOL_KOLL_T_MW"])
main.create_window(560, 476, window=temp_lbl["WW_Tww_MW"])
main.create_window(560, 812, window=temp_lbl["WW_HZG_Tvl_MW"])
main.create_window(658, 812, window=temp_lbl["WW_HZG_Trl_MW"])
main.create_window(1002, 555, window=temp_lbl["FB_SEK_Tvl_MW"])
main.create_window(1101, 813, window=temp_lbl["FB_PRIM_Trl_MW"])
main.create_window(483, 968, window=temp_lbl["SOL_SP1_To_MW"])
main.create_window(483, 1155, window=temp_lbl["SOL_SP1_Tu_MW"])
main.create_window(483, 1460, window=temp_lbl["SOL_SP2_To_MW"])
main.create_window(483, 1647, window=temp_lbl["SOL_SP2_Tu_MW"])
main.create_window(781, 812, window=temp_lbl["HK_Tvl_MW"])
main.create_window(879, 812, window=temp_lbl["HK_Trl_MW"])
main.create_window(1403, 1168, window=temp_lbl["KES_Tvl_MW"])
main.create_window(1403, 1355, window=temp_lbl["KES_Trl_MW"])
main.create_window(1742, 978, window=temp_lbl["ALL_Tau_MW"])
##
main.create_window(759, 755, window=pu_lbl["HK_PU_SB"])
main.create_window(980, 487, window=pu_lbl["FB_SEK_PU_SB"])
main.create_window(980, 756, window=pu_lbl["FB_PRIM_PU_SB"])
main.create_window(538, 756, window=pu_lbl["WW_HZG_PU_SB"])
main.create_window(861, 425, window=pu_lbl["WW_ZIRK_PU_SB"])
main.create_window(1289, 1157, window=pu_lbl["KES_PU_SP1_SB"])
main.create_window(1289, 1240, window=pu_lbl["KES_PU_SP2_SB"])
main.create_window(257, 996, window=pu_lbl["SOL_PU_SB"])
##    
# main.create_window(657, 427, window=cnt_lbl["WW_WZ_MW"])
##
main.create_window(550, 855, window=mv_lbl["WW_HZG_MV_Y"])
main.create_window(772, 855, window=mv_lbl["FB_PRIM_MV_Y"])
main.create_window(993, 855, window=mv_lbl["HK_MV_Y"])
main.create_window(750, 1071, window=mv_lbl["WW_HZG_VV_Y"])
##
main.create_window(403, 1252, window=av_lbl["SOL_SP1_AV_SB"])
main.create_window(335, 1714, window=av_lbl["SOL_SP2_AV_SB"])
##
main.create_window(1742, 1008, window=di_lbl["ALL_PARTY"])
main.create_window(1742, 1038, window=di_lbl["WW_PARTY"])

#-------- Eigentliche Anwendung --------

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
                
def connect():
    HOST = server_entry.get()
    PORT = port_entry.get()
    tn.open(HOST, PORT)
    tn.read_very_eager()
    update_bttn.config( command=leseWerte )
    leseWerte()
        
#-------------
    
connect_bttn.config( command=connect )

tn = telnetlib.Telnet()
root.mainloop()

tn.close()


        
