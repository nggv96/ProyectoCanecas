
import random
from datetime import datetime
import time

def saveLog(dataSensors):
    date = datetime.now()
    logTxt = open("log.txt","a+")
    data = [str(date),"|",dataSensors[0],"|",dataSensors[1],"|",dataSensors[2],"|",dataSensors[3],"|","\n"]
    logTxt.writelines(data)
    logTxt.close()
    return

def extractLog(logDate):
    logTxt = open("log.txt","a+")
    logInfo = logTxt.readlines()
    requiredInformation = []
    for j in range(len(logInfo)):
        if logInfo[j].count(logDate) >= 1:
            requiredInformation.append(logInfo[j])   
    return requiredInformation


#for i in range(10):
 #   data = [str(random.random()*1.5), str(random.random()*1.5), str(random.random()*1.5), str(random.random()*1.5)]
  #  saveLog(data)
   # time.sleep(0.5)
  
