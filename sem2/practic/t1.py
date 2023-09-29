from tkinter import *

from tkinter import filedialog as fd
from tkinter import messagebox as mb
from tkcalendar import DateEntry

from matplotlib.backends.backend_tkagg import ( FigureCanvasTkAgg, NavigationToolbar2Tk )
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure
from matplotlib.widgets import CheckButtons
import matplotlib.dates as mdates
import matplotlib.pyplot as plt

from datetime import date, datetime, time, timedelta
import datedelta

import csv
import json

class MainWindow():
    def __init__( self ):
        self.file = False
        self.build_widgets()

    def build_widgets( self ):
        self.mainmenu = Menu( main_window )
        main_window.config( menu = self.mainmenu )
        self.mainmenu.add_command( label = "Open file", command = self.open_file )

    def remove_figures( self ):
        for item in self.figures:
            self.figure.delaxes( item )
            self.figures.remove( item )
        
        self.canvas.draw()

    def create_figure( self ):
        self.remove_figures()
        with open ( self.file, "r", encoding='cp1251' ) as f_obj:
            a = self.figure.add_subplot( 1, 1, 1 )
            for i in self.listb.curselection():
                f_obj.seek( 0 )
                arr_x = []
                arr_y = []
                col = self.listb.get( i )
                
                if self.file.lower().endswith( ".txt" ):
                    data = json.loads( f_obj.readline() )
                    x = 0
                    nx = self.average.get() >= 3 and self.start.get_date().day or 0

                    mx = 0
                    mn = 0

                    mxd = []
                    mnd = []

                    for key in self.data:
                        datet = date.fromisoformat( key[ :-9 ] )
                        
                        mx = max( mx, float( self.data[ key ][ col ] ) )
                        mn = min( mn, float( self.data[ key ][ col ] ) )
                        if nx == datet.day:
                            mxd.insert( nx, mx )
                            mnd.insert( nx, mn )
                    
                    
                    nx = self.average.get() >= 3 and self.start.get_date().day or 0
                    for key in self.data:
                        datet = date.fromisoformat( key[ :-9 ] )
                        timet = time.fromisoformat( key[ -8: ] )
                        datet_t = datetime.strptime( key, "%Y-%m-%d %H:%M:%S" )
                        if ( self.start.get_date() <= datet and datet <= self.end.get_date() ) and ( self.average.get() == 0 and nx >= 0 or self.average.get() > 0 and nx == timet.hour or self.average.get() == 3 and nx == datet.day or self.average.get() == 4 and ( nx == datet.day and ( float( self.data[ key ][ col ] ) == mnd[ nx ] or float( self.data[ key ][ col ] ) == mxd[ nx ] ) ) ):
                            y = float( self.data[ key ][ col ] )
                            arr_x.append( datet_t )
                            
                            if self.istemp.get() == 1 and col == "BME280_humidity":
                                h = float( self.data[ key ][ col ] )
                                arr_y.append( y - 0.4*( y - 10 ) * ( 1 - h/100 ) )
                            else:
                                arr_y.append( y )

                            if self.average.get() == 1:
                                nx = ( datet_t + timedelta( hours=1 ) ).hour
                            elif self.average.get() == 2:
                                nx = ( datet_t + timedelta( hours=3 ) ).hour
                            elif self.average.get() >= 3:
                                nx = ( datet_t + datedelta.datedelta( days=1 ) ).day
                            else:
                                nx += 1

                elif self.file.lower().endswith( ".csv" ):
                    line = f_obj.readline()
                    reader = csv.DictReader( f_obj, delimiter=';' )
                    x = 0
                    nx = self.average.get() >= 3 and self.start.get_date().day or 0
                    
                    mx = 0
                    mn = 0

                    mxd = []
                    mnd = []

                    for line in reader:
                        datet = date.fromisoformat( line[ "Date" ][ :-9 ] )

                        try:
                            mx = max( mx, float( line[ col ] ) )
                            mn = min( mn, float( line[ col ] ) )
                        except ValueError:
                            return
                            
                        if nx == datet.day:
                            mxd.insert( nx, mx )
                            mnd.insert( nx, mn )

                    f_obj.seek( 0 )
                    line = f_obj.readline()
                    reader = csv.DictReader( f_obj, delimiter=';' )
                    nx = self.average.get() >= 3 and self.start.get_date().day or 0
                    for line in reader:
                        datet = date.fromisoformat( line[ "Date" ][ :-9 ] )
                        timet = time.fromisoformat( line[ "Date" ][ -8: ] )
                        datet_t = datetime.strptime( line[ "Date" ], "%Y-%m-%d %H:%M:%S" )
                        if ( self.start.get_date() <= datet and datet <= self.end.get_date() ) and ( self.average.get() == 0 and nx >= 0 or self.average.get() > 0 and nx == timet.hour or self.average.get() == 3 and nx == datet.day or self.average.get() == 4 and ( nx == datet.day and ( float( line[ col ] ) == mnd[ nx ] or float( line[ col ] ) == mxd[ nx ] ) ) ):
                            y = float( line[ col ] )
                            arr_x.append( datet_t )

                            if self.istemp.get() == 1:
                                h = float( line[ "BME280_humidity" ] )
                                arr_y.append( y - 0.4*( y - 10 ) * ( 1 - h/100 ) )
                            else:
                                arr_y.append( y )

                            if self.average.get() == 1:
                                nx = ( datet_t + timedelta( hours=1 ) ).hour
                            elif self.average.get() == 2:
                                nx = ( datet_t + timedelta( hours=3 ) ).hour
                            elif self.average.get() >= 3:
                                nx = ( datet_t + datedelta.datedelta( days=1 ) ).day
                            else:
                                nx += 1
                
                a.xaxis.set_major_formatter( mdates.DateFormatter( '%m/%d/%Y' ) )
                a.xaxis.set_major_locator( mdates.DayLocator() )

                if self.var.get() == 0:
                    a.plot( arr_x, arr_y )
                elif self.var.get() == 1:
                    a.bar( arr_x, arr_y )
                elif self.var.get() == 2:
                    a.scatter( arr_x, arr_y )
                else:
                    a.plot( arr_x, arr_y )
                
                self.figure.autofmt_xdate()

            self.figures.append( a )
            self.canvas.draw()

    

    def onselect( self, event ):
        if self.lista.curselection():
            sel_c = self.lista.get( self.lista.curselection()[ 0 ] )
            with open( self.file, "r", encoding='utf-8' ) as f:
                line = f.readline()
                data = json.loads( line )

                self.listb.delete( 0, self.listb.size() )
                
                self.data = {}
                added = {}
                
                banned = [ "version", "serial", "ip", "rssi", "mac" ]

                for x in data:
                    for y in data[ x ]:
                        if y == "uName":
                            if data[ x ][ y ] + " (" + data[ x ][ "serial" ] + ")" == sel_c:
                                for z in data[ x ][ "data" ]:
                                    self.data.update( { data[ x ][ "Date" ] : data[ x ][ "data" ] } )

                                    if ( z not in added ):
                                        st = z[ 7: ].lower()
                                        if ( st not in banned ):
                                            self.listb.insert( END, z )
                                            added.update( { z : True } )

                                    
    def open_file( self ):
        try:
            if self.file:
                for child in main_window.winfo_children():
                    child.destroy()
                self.file = None
                self.open_file()
                self.build_widgets()
            else:
                self.file = fd.askopenfilename( filetypes = [ ( "CSV file", "*.csv" ), ( "TXT file", "*txt" ) ] )
                if self.file.lower().endswith( ".csv" ):
                    leftp = Frame( main_window )
                    leftp.pack( side=LEFT )

                    self.listb = Listbox( leftp, selectmode=MULTIPLE )
                    
                    with open( self.file, "r", encoding='cp1251' ) as f:
                        if self.file.lower().endswith( ".csv" ):
                            line = f.readline()
                            reader = csv.DictReader( f, delimiter=';' )
                            
                            for x in reader:
                                start_date = x[ "Date" ]
                                for i in x:
                                    if i.lower().find( "date" ) != False:
                                        self.listb.insert( END, i )
                                break

                            for x in reader:
                                pass
                            end_date = x[ "Date" ]
                    
                    self.listb.pack()

                    self.graphs = 3

                    self.inonegraph = 0

                    l_start = Label( leftp, text="Start time" )
                    l_start.pack()

                    start_date = datetime.fromisoformat( start_date )
                    self.start = DateEntry( leftp, selectmode='day', date_pattern='dd MM yyyy' )
                    self.start.set_date( start_date )
                    self.start.pack()

                    l_end = Label( leftp, text="End time" )
                    l_end.pack()

                    end_date = datetime.fromisoformat( end_date )
                    self.end = DateEntry( leftp, selectmode='day', date_pattern='dd MM yyyy' )
                    self.end.set_date( end_date )
                    self.end.pack()

                    self.var = IntVar()
                    self.var.set( 0 )
                    rad0 = Radiobutton( leftp, text="Graphs", variable=self.var, value=0 )
                    rad1 = Radiobutton( leftp, text="Bars", variable=self.var, value=1 )
                    rad2 = Radiobutton( leftp, text="Circles", variable=self.var, value=2 )
                    
                    rad0.pack()
                    rad1.pack()
                    rad2.pack()

                    self.average = IntVar()
                    self.average.set( 0 )
                    radi0 = Radiobutton( leftp, text="Данные как есть", variable=self.average, value=0 )
                    radi1 = Radiobutton( leftp, text="Осреднить за час", variable=self.average, value=1 )
                    radi2 = Radiobutton( leftp, text="Осреднить за каждые 3 часа", variable=self.average, value=2 )
                    radi3 = Radiobutton( leftp, text="Осреднить за сутки", variable=self.average, value=3 )
                    radi4 = Radiobutton( leftp, text="Макс. и мин. парам. за сутки", variable=self.average, value=4 )
                    
                    radi0.pack()
                    radi1.pack()
                    radi2.pack()
                    radi3.pack()
                    radi4.pack()

                    self.istemp = IntVar()
                    c1 = Checkbutton( leftp, text='График ЭТ (только для BMP280)',variable=self.istemp, onvalue=1, offvalue=0 )
                    c1.pack()

                    self.figure = Figure( figsize=( 3, 3 ), dpi=100 )
                
                    self.canvas = FigureCanvasTkAgg( self.figure, master=main_window )
                    self.canvas.get_tk_widget().pack( side=TOP, fill=BOTH, expand=1 )
                    
                    toolbar = NavigationToolbar2Tk( self.canvas, main_window )
                    toolbar.update()
                    self.canvas.get_tk_widget().pack( side=TOP, fill=BOTH, expand=1 )

                    self.figures = []
                    btn = Button( main_window, text="Create figure", command = self.create_figure )
                    btn.pack()

                    btn = Button( main_window, text="Remove figures", command = self.remove_figures )
                    btn.pack()
                elif self.file.lower().endswith( ".txt" ):
                    startdate = ""
                    leftp = Frame( main_window )
                    leftp.pack( side=LEFT )

                    self.lista = Listbox( leftp, selectmode=SINGLE )
                    self.listb = Listbox( leftp, selectmode=MULTIPLE )
                    
                    with open( self.file, "r", encoding='utf-8' ) as f:
                        if self.file.lower().endswith( ".txt" ):
                            line = f.readline()
                            data = json.loads( line )

                            added = {}
                            data_min = 0
                            for x in data:
                                for i in data[ x ]:
                                    if i == "uName":
                                        if ( data[ x ][ i ] + " (" + data[ x ][ "serial" ] + ")" not in added ):
                                            self.lista.insert( END, data[ x ][ i ] + " (" + data[ x ][ "serial" ] + ")" )
                                            added.update( { data[ x ][ i ] + " (" + data[ x ][ "serial" ] + ")" : True } )
                                    if data_min == 0:
                                        start_date = data[ x ][ "Date" ]
                                        data_min = 1

                            data = json.loads( line )
                            for x in data:
                                for i in data[ x ]:
                                    pass
                                    end_date = data[ x ][ "Date" ]
                                
                    self.lista.pack()
                    self.lista.bind("<<ListboxSelect>>", self.onselect)
                    self.listb.pack()

                    self.graphs = 3

                    self.inonegraph = 0

                    l_start = Label( leftp, text="Start time" )
                    l_start.pack()

                    start_date = datetime.fromisoformat( start_date )
                    self.start = DateEntry( leftp, selectmode='day', date_pattern='dd MM yyyy' )
                    self.start.set_date( start_date )
                    self.start.pack()

                    l_end = Label( leftp, text="End time" )
                    l_end.pack()

                    end_date = datetime.fromisoformat( end_date )
                    self.end = DateEntry( leftp, selectmode='day', date_pattern='dd MM yyyy' )
                    self.end.set_date( end_date )
                    self.end.pack()

                    self.var = IntVar()
                    self.var.set( 0 )
                    rad0 = Radiobutton( leftp, text="Graphs", variable=self.var, value=0 )
                    rad1 = Radiobutton( leftp, text="Bars", variable=self.var, value=1 )
                    rad2 = Radiobutton( leftp, text="Circles", variable=self.var, value=2 )
                    
                    rad0.pack()
                    rad1.pack()
                    rad2.pack()

                    self.average = IntVar()
                    self.average.set( 0 )
                    radi0 = Radiobutton( leftp, text="Данные как есть", variable=self.average, value=0 )
                    radi1 = Radiobutton( leftp, text="Осреднить за час", variable=self.average, value=1 )
                    radi2 = Radiobutton( leftp, text="Осреднить за каждые 3 часа", variable=self.average, value=2 )
                    radi3 = Radiobutton( leftp, text="Осреднить за сутки", variable=self.average, value=3 )
                    radi4 = Radiobutton( leftp, text="Макс. и мин. парам. за сутки", variable=self.average, value=4 )
                    
                    radi0.pack()
                    radi1.pack()
                    radi2.pack()
                    radi3.pack()
                    radi4.pack()

                    self.istemp = IntVar()
                    c1 = Checkbutton( leftp, text='График ЭТ (только для BMP280)',variable=self.istemp, onvalue=1, offvalue=0 )
                    c1.pack()

                    self.figure = Figure( figsize=( 3, 3 ), dpi=100 )
                
                    self.canvas = FigureCanvasTkAgg( self.figure, master=main_window )
                    self.canvas.get_tk_widget().pack( side=TOP, fill=BOTH, expand=1 )
                    
                    toolbar = NavigationToolbar2Tk( self.canvas, main_window )
                    toolbar.update()
                    self.canvas.get_tk_widget().pack( side=TOP, fill=BOTH, expand=1 )

                    self.figures = []
                    btn = Button( main_window, text="Create figure", command = self.create_figure )
                    btn.pack()

                    btn = Button( main_window, text="Remove figures", command = self.remove_figures )
                    btn.pack()

        except FileNotFoundError:
            mb.showinfo( "Error", "File not found" )

main_window = Tk()
main_window.title( 'PyPractic' )
main_window.geometry( '500x500' )
window = MainWindow()
main_window.mainloop()