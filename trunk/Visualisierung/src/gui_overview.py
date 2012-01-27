'''
Created on 23.01.2012

@author: stegmv
'''
# -*- coding: utf-8 -*-

import tkinter as tk
import tkinter.ttk as ttk

import signals

class GuiOverview(tk.Frame):
    '''
    classdocs
    '''
    def __init__(self, master=None):
        '''
        Constructor
        '''
        self.SCHRIFT = ('Arial', 12, 'bold')
#        self.SCHRIFT = ('Arial', 11)

        self.L       = 8
        self.HFARBE  = 'LightGoldenrod1'

        tk.Frame.__init__(self, master)
        self.draw()
        self.drawLabels()
        
    def cllbck(self, event): 
        print('Mouse clicked at ', self.main.canvasx(event.x), self.main.canvasy(event.y) )
    
    def draw(self):
        self.vbar = ttk.Scrollbar( self, orient=tk.VERTICAL)
        self.hbar = ttk.Scrollbar( self, orient=tk.HORIZONTAL)

        self.main = tk.Canvas(self, bg='white', scrollregion=(0,0,2000,2000),
                       yscrollcommand=self.vbar.set, xscrollcommand=self.hbar.set, width=1220, height=560)
        self.main.bind('<Button-1>', self.cllbck)
        self.bgpic = tk.PhotoImage(file='Visualisierung.gif')
        
        self.main.create_image(1000,1000, image=self.bgpic)
                             
        self.vbar.grid(row=0, column=1, sticky=tk.NS)
        self.hbar.grid(row=1, column=0, sticky=tk.EW)
        self.main.grid(row=0, column=0, sticky=tk.NSEW)

        self.vbar.config(command=self.main.yview)
        self.hbar.config(command=self.main.xview)

    def drawLabels(self):
        self.temp_lbl = dict()
        for t_name in signals.TEMP_NAMES:
            self.temp_lbl[t_name] = tk.Label( self, width=self.L, bg=self.HFARBE, relief='sunken', font=self.SCHRIFT, text='---.-°C' )
        
        self.pu_lbl = dict()
        for pu_name in signals.PU_NAMES:
            self.pu_lbl[pu_name] = tk.Label( self, width=self.L, bg=self.HFARBE, relief='sunken', font=self.SCHRIFT, text='---' )

        self.mv_lbl = dict()
        for mv_name in signals.MV_NAMES:
            self.mv_lbl[mv_name] = tk.Label( self, width=self.L, bg=self.HFARBE, relief='sunken', font=self.SCHRIFT, text='---%' )

        self.cnt_lbl = dict()
        self.cnt_lbl["WW_WZ_MW"] = tk.Label( self, width=self.L, bg=self.HFARBE, relief='sunken', font=self.SCHRIFT, text='-.---' )

        self.av_lbl = dict()
        for av_name in signals.AV_NAMES:
            self.av_lbl[av_name] = tk.Label( self, width=self.L, bg=self.HFARBE, relief='sunken', font=self.SCHRIFT, text='---' )

        self.di_lbl = dict()
        for di_name in signals.DI_NAMES:
            self.di_lbl[di_name] = tk.Label( self, width=self.L, bg=self.HFARBE, relief='sunken', font=self.SCHRIFT, text='---' )

        self.main.create_window( 370,  441, window=self.temp_lbl["SOL_KOLL_T_MW"])
        self.main.create_window( 560,  476, window=self.temp_lbl["WW_Tww_MW"])
        self.main.create_window( 560,  812, window=self.temp_lbl["WW_HZG_Tvl_MW"])
        self.main.create_window( 658,  812, window=self.temp_lbl["WW_HZG_Trl_MW"])
        self.main.create_window(1002,  555, window=self.temp_lbl["FB_SEK_Tvl_MW"])
        self.main.create_window(1101,  813, window=self.temp_lbl["FB_PRIM_Trl_MW"])
        self.main.create_window( 483,  968, window=self.temp_lbl["SOL_SP1_To_MW"])
        self.main.create_window( 483, 1155, window=self.temp_lbl["SOL_SP1_Tu_MW"])
        self.main.create_window( 483, 1460, window=self.temp_lbl["SOL_SP2_To_MW"])
        self.main.create_window( 483, 1647, window=self.temp_lbl["SOL_SP2_Tu_MW"])
        self.main.create_window( 781,  812, window=self.temp_lbl["HK_Tvl_MW"])
        self.main.create_window( 879,  812, window=self.temp_lbl["HK_Trl_MW"])
        self.main.create_window(1403, 1168, window=self.temp_lbl["KES_Tvl_MW"])
        self.main.create_window(1403, 1355, window=self.temp_lbl["KES_Trl_MW"])
        self.main.create_window(1742,  978, window=self.temp_lbl["ALL_Tau_MW"])
        ##
        self.main.create_window( 759,  755, window=self.pu_lbl["HK_PU_SB"])
        self.main.create_window( 980,  487, window=self.pu_lbl["FB_SEK_PU_SB"])
        self.main.create_window( 980,  756, window=self.pu_lbl["FB_PRIM_PU_SB"])
        self.main.create_window( 538,  756, window=self.pu_lbl["WW_HZG_PU_SB"])
        self.main.create_window( 861,  425, window=self.pu_lbl["WW_ZIRK_PU_SB"])
        self.main.create_window(1289, 1157, window=self.pu_lbl["KES_PU_SP1_SB"])
        self.main.create_window(1289, 1240, window=self.pu_lbl["KES_PU_SP2_SB"])
        self.main.create_window( 257,  996, window=self.pu_lbl["SOL_PU_SB"])
        ##    
        self.main.create_window( 657,  427, window=self.cnt_lbl["WW_WZ_MW"])
        ##
        self.main.create_window( 550,  855, window=self.mv_lbl["WW_HZG_MV_Y"])
        self.main.create_window( 772,  855, window=self.mv_lbl["FB_PRIM_MV_Y"])
        self.main.create_window( 993,  855, window=self.mv_lbl["HK_MV_Y"])
        self.main.create_window( 750, 1071, window=self.mv_lbl["WW_HZG_VV_Y"])
        ##
        self.main.create_window( 403, 1252, window=self.av_lbl["SOL_SP1_AV_SB"])
        self.main.create_window( 335, 1714, window=self.av_lbl["SOL_SP2_AV_SB"])
        ##
        self.main.create_window(1742, 1008, window=self.di_lbl["ALL_PARTY"])
        self.main.create_window(1742, 1038, window=self.di_lbl["WW_PARTY"])
 
    def updateLabels(self, t_dict, pu_dict, mv_dict, di_dict, cnt_dict, av_dict):
        for t_name in signals.TEMP_NAMES:
            self.temp_lbl[t_name].config( text=str(t_dict[t_name])+' °C' )
        
        for pu_name in signals.PU_NAMES:
            self.pu_lbl[pu_name].config( text=str(pu_dict[pu_name]) )

        for mv_name in signals.MV_NAMES:
            self.mv_lbl[mv_name].config( text=str(mv_dict[mv_name])+' %' )

        self.cnt_lbl["WW_WZ_MW"].config( text=str(cnt_dict["WW_WZ_MW"]) )

        for av_name in signals.AV_NAMES:
            self.av_lbl[av_name].config( text=str(av_dict[av_name]) )

        for di_name in signals.DI_NAMES:
            self.di_lbl[di_name].config( text=str(di_dict[di_name]) )

#--------------------------------------------------
   
if __name__ == "__main__":
    root=tk.Tk()
    gui = GuiOverview(root)
    gui.pack()
    root.mainloop()
    





        
