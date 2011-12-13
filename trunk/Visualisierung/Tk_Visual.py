import tkinter as tk
import tkinter.ttk as ttk


CNT_NAMES = { "WW_WZ_MW" }

cnt_lbl = dict()
mv_lbl = dict()

def cllbck(event):
    print('Mouse clicked at ', main.canvasx(event.x), main.canvasy(event.y) )

root = tk.Tk()
bgpic = tk.PhotoImage(file='Visualisierung.gif')

vbar = ttk.Scrollbar( root, orient=tk.VERTICAL)
hbar = ttk.Scrollbar( root, orient=tk.HORIZONTAL)
main = tk.Canvas(root, bg='white', scrollregion=(0,0,2000,2000),
                       yscrollcommand=vbar.set, xscrollcommand=hbar.set, width=1024, height=768)

main.bind('<Button-1>', cllbck)
main.create_image(1000,1000, image=bgpic)
                             
vbar.grid(row=0, column=1, sticky=tk.NS)
hbar.grid(row=1, column=0, sticky=tk.EW)
main.grid(row=0, column=0, sticky=tk.NSEW)

vbar.config(command=main.yview)
hbar.config(command=main.xview)

'''
Widgets in Canvas plazieren:
1. Widget Objekt erzeugen auf Canvas (main)
2. Mit .create_window() Methode auf Canvas platzieren. Der Parameter window benennt das Widget Objekt
'''

TEMP_NAMES = { "ALL_Tau_MW", "SOL_KOLL_T_MW", "SOL_SP1_To_MW", "SOL_SP1_Tu_MW", "SOL_SP2_To_MW",
              "SOL_SP2_Tu_MW", "KES_Tvl_MW", "KES_Trl_MW", "HK_Tvl_MW", "HK_Trl_MW",
              "FB_PRIM_Trl_MW", "FB_SEK_Tvl_MW", "WW_HZG_Tvl_MW", "WW_HZG_Trl_MW", "WW_Tww_MW",
              "Tau_1h_mittel", "Tau_36h_mittel" }        
temp_lbl = dict()
for t_name in TEMP_NAMES:
    temp_lbl[t_name] = tk.Label( main, width=8, bg='yellow', relief='sunken', font=('arial', 12), text='---.-°C' )

PU_NAMES = { "WW_HZG_PU_SB", "HK_PU_SB", "WW_ZIRK_PU_SB", "HK_PU_SB", "FB_SEK_PU_SB", "FB_PRIM_PU_SB" }
pu_lbl = dict()
for pu_name in PU_NAMES:
    pu_lbl[pu_name] = tk.Label( main, width=8, bg='yellow', relief='sunken', font=('arial', 12), text='---' )

MV_NAMES = { "WW_HZG_MV_Y", "FB_PRIM_MV_Y", "HK_MV_Y", "WW_HZG_VV_Y" }
for mv_name in MV_NAMES:
    mv_lbl[mv_name] = tk.Label( main, width=8, bg='yellow', relief='sunken', font=('arial', 12), text='---%' )

cnt_lbl["WW_WZ_MW"] = tk.Label( main, width=8, bg='yellow', relief='sunken', font=('arial', 12), text='-.---' )

main.create_window(370, 441, window=temp_lbl["SOL_KOLL_T_MW"])
main.create_window(560, 476, window=temp_lbl["WW_Tww_MW"])
main.create_window(560, 812, window=temp_lbl["WW_HZG_Tvl_MW"])
main.create_window(658, 812, window=temp_lbl["WW_HZG_Trl_MW"])
main.create_window(1002, 556, window=temp_lbl["FB_SEK_Tvl_MW"])
main.create_window(1101, 813, window=temp_lbl["FB_PRIM_Trl_MW"])
main.create_window(483, 968, window=temp_lbl["SOL_SP1_To_MW"])
main.create_window(483, 1155, window=temp_lbl["SOL_SP1_Tu_MW"])
main.create_window(483, 1460, window=temp_lbl["SOL_SP2_To_MW"])
main.create_window(483, 1647, window=temp_lbl["SOL_SP2_Tu_MW"])
main.create_window(781, 812, window=temp_lbl["HK_Tvl_MW"])
main.create_window(879, 812, window=temp_lbl["HK_Trl_MW"])

main.create_window(759, 755, window=pu_lbl["HK_PU_SB"])
main.create_window(980, 487, window=pu_lbl["FB_SEK_PU_SB"])
main.create_window(980, 754, window=pu_lbl["FB_PRIM_PU_SB"])
main.create_window(538, 756, window=pu_lbl["WW_HZG_PU_SB"])
main.create_window(861, 425, window=pu_lbl["WW_ZIRK_PU_SB"])

main.create_window(657, 427, window=cnt_lbl["WW_WZ_MW"])

main.create_window(550, 855, window=mv_lbl["WW_HZG_MV_Y"])
main.create_window(772, 855, window=mv_lbl["FB_PRIM_MV_Y"])
main.create_window(993, 855, window=mv_lbl["HK_MV_Y"])
main.create_window(750, 1071, window=mv_lbl["WW_HZG_VV_Y"])

root.mainloop()

        
