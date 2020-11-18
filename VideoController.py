import os


def videoSelector():
    
    pathPrincipal = "/home/nicolas/Desktop/Repo/ProyectoCanecas/Videos"
    videoList = os.listdir(pathPrincipal)
    for i in videoList:
        print(pathPrincipal+i)
        os.system("omxplayer -n -1 "+pathPrincipal+i)

while True:
	videoSelector()