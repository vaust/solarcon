import tkinter as tk
import tkinter.ttk as ttk
def cllbck(event):
    print('Mouse clicked at ', event.x, event.y)

root = tk.Tk()
bgpic = tk.PhotoImage(file='Visualisierung.gif')
main_frame = tk.Canvas(root, bg='black', width=800, height=800, scrollregion=(-1000,-1000,1000,1000))
main_frame.bind('<Button-1>', cllbck)
main_frame.create_image(0,0, image=bgpic)

right_scrlbar = ttk.Scrollbar( root, orient=tk.VERTICAL)
bottom_scrlbar = ttk.Scrollbar( root, orient=tk.HORIZONTAL)
                             
right_scrlbar.pack(side=tk.RIGHT, fill=tk.Y)
bottom_scrlbar.pack(side=tk.BOTTOM, fill=tk.X)
main_frame.pack(side=tk.LEFT)

right_scrlbar.config(command=main_frame.yview)
bottom_scrlbar.config(command=main_frame.xview)

root.mainloop()

        
