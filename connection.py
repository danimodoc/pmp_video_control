import serial 
import time 
import pyautogui

ArduinoSerial = serial.Serial('com3',9600) 
time.sleep(2) #asteptare pentru stabilire conexiune

while 1:
    incoming = str (ArduinoSerial.readline()) #citire valori transmise serial
    print incoming
    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)
        #pyautogui.hotkey('ctrl', 'q')

    if 'Rewind' in incoming:
        pyautogui.hotkey('ctrl', 'left')  

    if 'Forward' in incoming:
        pyautogui.hotkey('ctrl', 'right') 

    if 'Vup' in incoming:
        #pyautogui.hotkey('ctrl', 'down')
        #pyautogui.press('f2')
        pyautogui.press('volumeup')

    if 'Vdown' in incoming:
        #pyautogui.hotkey('ctrl', 'up')
        #pyautogui.press('f3')
        pyautogui.press('volumedown')
