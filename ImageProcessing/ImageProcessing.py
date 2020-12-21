import serial
import sys
import cv2 as cv
import numpy as np
import time
import math

fin = 0
ini = 0

def send_data(y, x, vecino):
    package_to_send = [ini,y,x,vecino,fin]
    ser.write(package_to_send)
    time.sleep(1)
    

def paint(y, x, neighbour):
    if(img[y,x]==0 and processed_pixels[y,x]==0):
        processed_pixels[y,x]=255
        send_data(y,x,neighbour)
        neighbour=0
        if img[y,x+1]==0:
            paint(y,x+1,neighbour)
        if img[y+1,x+1]==0:
            paint(y+1,x+1,neighbour)
        if img[y+1,x]==0:
            paint(y+1,x,neighbour)
        if img[y+1,x-1]==0:
            paint(y+1,x-1,neighbour)
        if img[y,x-1]==0:
            paint(y,x-1,neighbour)
        if img[y-1,x-1]==0:
            paint(y-1,x-1,neighbour)
        if img[y-1,x]==0:
            paint(y-1,x,neighbour)
        if img[y-1,x+1]==0:
            paint(y-1,x+1,neighbour)


print('Ingresar la ruta de una imagen: ')
ruta_imagen = input()
img = cv.imread(ruta_imagen,cv.IMREAD_GRAYSCALE)
if img is None:
    print("No se pudo abrir la imagen")
    exit(1)

ser = serial.Serial('/dev/ttyACM0',9600)

rows = img.shape[0]
cols = img.shape[1]

copia = np.zeros(img.shape, dtype=np.uint8)

pixeles_recorridos = np.zeros(img.shape, dtype=np.uint8)

for y in range(rows):
    for x in range(cols):
        intensity = img[y,x];
        if intensity!=255:
            paint(y,x,1)
