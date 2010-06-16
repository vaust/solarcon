#!/usr/bin/python3
# -*- coding: utf-8 -*-

import telnetlib
import datetime
import time

FRMSTR = "; {0:5.1f}; {1:5.1f}; {2:5.1f}; {3:5.1f}; {4:5.1f}; {5:5.1f}; {6:5.1f}; {7:5.1f}; {8:5.1f}; {9:5.1f}; \
{10:5.1f}; {11:5.1f}; {12:5.1f}; {13:5.1f}; {14:5.1f}; {15:6.2f}; {16:6.2f};"
    
#Anzahl der Messreihen
MAX_N = 100

# HOST = "192.168.3.33"
HOST = "localhost"

tn = telnetlib.Telnet()
tn.open(HOST, 1969)

# lese Ueberschriftenblock
tn.read_very_eager()

fd = open( "Temperaturen.csv", "w" )
fd.write( "Zeit; ALL_Tau_MW; SOL_KOLL_T_MW; SOL_SP1_To_MW; SOL_SP1_Tu_MW; SOL_SP2_To_MW; SOL_SP2_Tu_MW; \
KES_Tvl_MW; KES_Trl_MW; HK_Tvl_MW; HK_Trl_MW; FB_PRIM_Trl_MW; FB_SEK_Tvl_MW; WW_HZG_Tvl_MW; WW_HZG_Trl_MW;\
WW_Tww_MW; Tau_1h_mittel_f; Tau_36h_mittel_f;\n" )

for n in range(MAX_N):
    tn.write(b"GET T\n")
    time.sleep(1)
    buffer = tn.read_very_eager()
    bufdecode = buffer.decode('utf8')
    lines = bufdecode.splitlines()

    # alle Temperaturen auf unplausible Werte initialisieren
    all_tau_mw = -100.0
    sol_koll_t_mw = -100.0
    sol_sp1_to_mw = -100.0
    sol_sp1_tu_mw = -100.0
    sol_sp2_to_mw = -100.0
    sol_sp2_tu_mw = -100.0
    kes_tvl_mw = -100.0
    kes_trl_mw = -100.0
    hk_tvl_mw = -100.0
    hk_trl_mw = -100.0
    fb_prim_trl_mw = -100.0
    fb_sek_tvl_mw = -100.0
    ww_hzg_tvl_mw = -100.0
    ww_hzg_trl_mw = -100.0
    ww_tww_mw = -100.0
    tau_1h_mittel_f = -100.0
    tau_36h_mittel_f = -100.0
    
    for line in lines:
        if   (line.startswith( "ALL_Tau_MW" )):
            all_tau_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "SOL_KOLL_T_MW" )):
            sol_koll_t_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "SOL_SP1_To_MW" )):
            sol_sp1_to_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "SOL_SP1_Tu_MW" )):
            sol_sp1_tu_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "SOL_SP2_To_MW" )):
            sol_sp2_to_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "SOL_SP2_Tu_MW" )):
            sol_sp2_tu_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "KES_Tvl_MW" )):
            kes_tvl_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "KES_Trl_MW" )):
            kes_trl_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "HK_Tvl_MW" )):
            hk_tvl_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "HK_Trl_MW" )):
            hk_trl_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "FB_PRIM_Trl_MW" )):
            fb_prim_trl_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "FB_SEK_Tvl_MW" )):
            fb_sek_tvl_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "WW_HZG_Tvl_MW" )):
            ww_hzg_tvl_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "WW_HZG_Trl_MW" )):
            ww_hzg_trl_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "WW_Tww_MW" )):
            ww_tww_mw = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "Tau_1h_mittel_f" )):
            tau_1h_mittel_f = float(line.split('=')[1].split('°')[0])
        elif (line.startswith( "Tau_36h_mittel_f" )):
            tau_36h_mittel_f = float(line.split('=')[1].split('°')[0])


    now = datetime.datetime.now()
    # Mikrosekundenteil auf 0 setzen, damit Excel den ISO Zeitstring versteht
    now = datetime.datetime( now.year, now.month, now.day, now.hour, now.minute, now.second )
    csvstr = now.isoformat(' ') + FRMSTR.format( 	all_tau_mw, sol_koll_t_mw,
													sol_sp1_to_mw, sol_sp1_tu_mw,
													sol_sp2_to_mw, sol_sp2_tu_mw,
													kes_tvl_mw, kes_trl_mw,
													hk_tvl_mw, hk_trl_mw,
													fb_prim_trl_mw, fb_sek_tvl_mw,
													ww_hzg_tvl_mw, ww_hzg_trl_mw,
													ww_tww_mw,
													tau_1h_mittel_f, tau_36h_mittel_f
												)
	fd.write( csvstr + "\n" ) 
    print( csvstr )
    n += 1
    
tn.close()
fd.close()



