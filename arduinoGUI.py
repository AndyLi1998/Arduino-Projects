from tkinter import *
from arduinoComms import *
import atexit

def exit_handler():
    print ('My application is ending!')
    closeSerial()

atexit.register(exit_handler)

# global variables for this module
xStatus = 0
yStatus = 0
zStatus = 0

tkArd = Tk()
tkArd.minsize(width=320, height=170)
tkArd.config(bg = 'yellow')
tkArd.title("XYZ Axis Demo")

def setupView():
	global masterframe
	masterframe = Frame(bg = "yellow")
	masterframe.pack()

	selectPort()

def runProgram():
	tkArd.mainloop()

def selectPort():
	global masterframe, radioVar
	for child in masterframe.winfo_children():
		child.destroy()
	radioVar = StringVar()

	lst = listSerialPorts()

	l1= Label(masterframe, width = 5, height = 2, bg = "yellow")
	l1.pack()

	if len(lst) > 0:
		for n in lst:
			r1 = Radiobutton(masterframe, text=n, variable=radioVar, value=n, bg = "yellow")
			r1.config(command = radioPress)
			r1.pack(anchor=W)
	else:
		l2 = Label(masterframe, text = "No Serial Port Found")
		l2.pack()


def mainScreen():
    global masterframe
    for child in masterframe.winfo_children():
    	child.destroy()

    #labelA = Label(masterframe, width = 5, height = 2, bg = "yellow")
    labelA = Label(masterframe, width = 5, bg = "yellow")

    labelB = Label(masterframe, width = 5, bg = "yellow")

    labelC = Label(masterframe, width = 5, bg = "yellow")

    xAxisButton = Button(masterframe, text="x-Axis", fg="white", bg="black")
    xAxisButton.config(command = lambda: xAxis(xAxisButton))

    yAxisButton = Button(masterframe, text="y-Axis", fg="white", bg="black")
    yAxisButton.config(command = lambda: yAxis(yAxisButton))

    zAxisButton = Button(masterframe, text="z-Axis", fg="white", bg="black")
    zAxisButton.config(command = lambda: zAxis(zAxisButton))

    #slider = Scale(masterframe, from_=10, to=170, orient=HORIZONTAL)
    #slider.config(command = slide)

    labelA.grid(row = 0)
    xAxisButton.grid(row = 2
    )
    labelB.grid(row = 1, column = 2)
    yAxisButton.grid(row = 1, column = 3)
    labelC.grid(row = 1, column = 4)
    zAxisButton.grid(row = 1, column = 5)

def xAxis(btn):
    global xStatus, yStatus, zStatus

    if xStatus == 0:
        xStatus = 1
        btn.config(bg="black", fg="white")
    else:
        xStatus = 0
        btn.config(fg="white", bg="black")

    valToArduino(xStatus, yStatus, zStatus)

def yAxis(btn):
    global xStatus, yStatus, zStatus

    if yStatus == 0:
        yStatus = 1
        btn.config(fg="black", bg="white")
    else:
        yStatus = 0
        btn.config(fg="white", bg="black")

    valToArduino(xStatus, yStatus, zStatus)

def zAxis(btn):
    global xStatus, yStatus, zStatus

    if zStatus == 0:
        zStatus = 1
        btn.config(fg="black", bg="white")
    else:
        zStatus = 0
        btn.config(fg="white", bg="black")

    valToArduino(xStatus, yStatus, zStatus)


#def slide(sval):
#	global ledAstatus, ledBstatus, servoPos
#
#	servoPos = sval
#	valToArduino(ledAstatus, ledBstatus, servoPos)

def radioPress():
	global radioVar
	setupSerial(radioVar.get())
	mainScreen()

setupView()
tkArd.mainloop()
