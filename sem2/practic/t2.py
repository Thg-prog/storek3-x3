from tkinter import *

root = Tk()

root.bg = '#fafafa'
root.title( "YES" )
root.geometry( '500x500' )

canvas = Canvas( root, height=300, width=250)
canvas.pack()

frame = Frame( root, bg='red' )
frame.place( relx=0.15, rely=0.15, relwidth=1, relheight=0.7 )

title = Label( frame, text="УРА ROBLAX", bg='gray', font=40)
title.pack()
btn = Button( frame, text="btn", bg='yellow' )
btn.pack()

root.mainloop()