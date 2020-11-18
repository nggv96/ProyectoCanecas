import serial
import random
import os
from datetime import datetime


ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=100) 
print(ser.name)   
key = True
minValue = '0.7'

#para configurar despues ser.baudrate = 9600
#para configurar despues ser.port = 'COM1
#Hay 5 sensores, los contenedores de las esquinas tienen 2 y el del centro solo 1
#El orden de las canecas aqui planteado es  Aprovechables-  Organico  -No aprovechables
#                                            sensores 0-1     sensor 2    Sensores 3-4

def audioRandom(audioPatch):
    audioList = os.listdir(audioPatch)
    audio = audioList[random.randint(0,(len(audioList))-1)]
    return audioPatch+audio

def audioSelector(sensor):
    pathPrincipal = "/home/nicolas/Desktop/Repo/ProyectoCanecas/Audios/"
    
    Organico = "Organico/"
    NoApro = "Noaprovechable/"
    Apro = "Aprovechable/"
    Reciclar = "Reciclar/"
    
    if sensor == 0:
        print("Aprovechables")
        newPatch = audioRandom(pathPrincipal+Apro)
        os.system("omxplayer "+newPatch)
    elif sensor == 1:
        print("Aprovechables")
        newPatch = audioRandom(pathPrincipal+Apro)
        os.system("omxplayer "+newPatch)
    elif sensor == 2:
        print("Organico")
        newPatch = audioRandom(pathPrincipal+Organico)
        os.system("omxplayer "+newPatch)
    elif sensor == 3:
        print("No Aprovechables")
        newPatch = audioRandom(pathPrincipal+NoApro)
        os.system("omxplayer "+newPatch)
    elif sensor == 4:
        print("No Aprovechables")
        newPatch = audioRandom(pathPrincipal+NoApro)
        os.system("omxplayer "+newPatch)
    elif sensor == 5:
        print("Reciclar Reciclar")
        newPatch = audioRandom(pathPrincipal+Reciclar)
        os.system("omxplayer "+newPatch)
  
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
			#saveLog(dataSensors)
			return dataSensors

def writeSerial(task):
    
    if task == 'data':
        print('pedir data')
        ser.write(b's')
    if task == 'open':
        print('open')
        ser.write(b'o')
    if task == 'close':
        print('close')
        ser.write(b'c')
        
def mainControl(sensorInfo):
    if sensorInfo[1] <= minValue:
        audioSelector(sensorInfo[0])
        writeSerial('open')
        audioSelector(5)
        writeSerial('close')
        
def begin():
    writeSerial(b,'b')    

os.system("python VideoController.py")
while key:
    writeSerial('data')
    dataSensors = readingSerial()
    print("Los sensores: ", dataSensors)
    sensorInfo = findSmallestMeasure(dataSensors)
    print("Caneca: ",sensorInfo)
    mainControl(sensorInfo)
 
print("fuera del while") 
ser.close()