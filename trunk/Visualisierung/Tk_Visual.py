import tkinter as tk
import tkinter.ttk as ttk

def cllbck(event):
    print('Mouse clicked at ', main.canvasx(event.x), main.canvasy(event.y) )

root = tk.Tk()
bgpic = tk.PhotoImage(file='Visualisierung.gif')

vbar = ttk.Scrollbar( root, orient=tk.VERTICAL)
hbar = ttk.Scrollbar( root, orient=tk.HORIZONTAL)
main = tk.Canvas(root, bg='white', scrollregion=(0,0,2000,2000),
                       yscrollcommand=vbar.set, xscrollcommand=hbar.set, width=800, height=600)

main.bind('<Button-1>', cllbck)
main.create_image(1000,1000, image=bgpic)
                             
vbar.grid(row=0, column=1, sticky=tk.NS)
hbar.grid(row=1, column=0, sticky=tk.EW)
main.grid(row=0, column=0, sticky=tk.NSEW)

vbar.config(command=main.yview)
hbar.config(command=main.xview)

main.lbl_SOL_KOLL_T_MW = tk.Button( main, text='--.-', width=10, bg='darkgreen' )
main.lbl_SOL_KOLL_T_MW.place( x=329, y=429 )

root.mainloop()

        
