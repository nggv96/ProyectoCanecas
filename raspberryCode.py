import serial
import random
import os
from datetime import datetime
from playsound import playsound

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=300)
print(ser.name)        
key = True
i = 0

#para configurar despues ser.baudrate = 9600
#para configurar despues ser.port = 'COM1
#Hay 5 sensores, los contenedores de las esquinas tienen 2 y el del centro solo 1
#El orden de las canecas aqui planteado es  Aprovechables-  Organico  -No aprovechables
#                                            sensores 0-1     sensor 2    Sensores 3-4

def audioSelector(sensor):
    Organico = "/home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/Organico.ogg"
    NoApro = "/home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/NoApro.ogg"
    Apro = "/home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/Apro.ogg"
    Reciclar = "/home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/Reciclar.ogg"
    if sensor == 0:
        print("Aprovechables")
        os.system("omxplayer /home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/Apro.ogg")
    elif sensor == 1:
        print("Aprovechables")
        os.system("omxplayer /home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/Apro.ogg")
    elif sensor == 2:
        print("Organico")
        os.system("omxplayer /home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/Organico.ogg")
    elif sensor == 3:
        print("No Aprovechables")
        os.system("omxplayer /home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/NoApro.ogg")
    elif sensor == 4:
        print("No Aprovechables")
        os.system("omxplayer /home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/NoApro.ogg")
    elif sensor == 5:
		print("Reciclar Reciclar")
		os.system("omxplayer /home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/Reciclar.ogg")
  
def findSmallestMeasure(dataSensors):
    j = 0
    minimum = min(dataSensors)
    for i in dataSensors:
        if i == minimum:
            sensor = j
        j = j+1
    sensorInfo = [sensor,minimum]
    return sensorInfo

def saveLog(dataSensors):
    date = datetime.now()
    logTxt = open("log.txt","a+")
    data = [str(date),"|",dataSensors[0],"|",dataSensors[1],"|",dataSensors[2],"|",dataSensors[3],"|",dataSensors[4],"|","\n"]
    logTxt.writelines(data)
    logTxt.close()

def readingSerial():
	while ser.inWaiting() >= 0:
		reading = ser.readline()
		if reading.find("///") == -1:
			dataSensors = [reading[0:4],reading[5:9],reading[10:14],reading[15:19],reading[20:24]]
			saveLog(dataSensors)
			return dataSensors

def writeSerial(task):
    
    if task == 'data':
        ser.write(b's')
    if task == 'open':
        ser.write(b'o')
    if task == 'close':
        ser.write(b'c')

while key:
    writeSerial('data')
    dataSensors = readingSerial()
    print("Los sensores: ", dataSensors)
    sensorInfo = findSmallestMeasure(dataSensors)
    print("Caneca: ",sensorInfo)
    #if float(sensorInfo[1]) < 0.1:
        #audioSelector(sensorInfo[0])
        #writeSerial()
        #audioSelector(5)
    #i = i+1
    #if i >= 4:
        #key = False
 
print("fuera del while") 
ser.close()