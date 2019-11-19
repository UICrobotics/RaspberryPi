import serial
import pygame

#Written by Brendon Brown
#Last updated March 11, 2019
#This program uses pygame to read xbox 360/PSX controller input and send serial data
#through an xbee connected to a serial port
#data is sent and read one byte at a time
#To those who end up using this code remember to test, test, test!!! This code should be functional but you have to make sure that you understand what is going on

#There is still much that should be done to get better control of the robot
#[[[Some things that could be done to get better functionality below]]] 
#Create more levels of motor function, right now there is only 5 levels but at about 15+ levels the controls should start to feel extremely fluid
#Add constant feedback to the robot so the robot knows when a disconnect has occured(THIS IS NECESSARY FOR SAFETY AND SHOULD BE DONE BEFORE NEXT COMPETITION)
#Adjust the program so that is will automatically detect whether you are using a xbox or playstation controller
#Map out and send data on every possible button/axis/hatarray (not really nessacery for robot control but nice to have done)

#This creates the Controller class
class Controller:

    def __init__(self):
        pygame.init()
        pygame.joystick.init()
        self.joystick = pygame.joystick.Joystick(0)
        self.joystick.init()
        self.hatcount = self.joystick.get_numhats()
        self.axescount = self.joystick.get_numaxes()
        self.buttcount = self.joystick.get_numbuttons()
#end of controller class
        

serxb = serial.Serial('COM6', 9600)     #assumes xbee is connected to the COM6 port this will have to be changed by checking where the xbee is connected in your system
test = Controller()                     #creates controller class under name test to the first joystick connected to pc
serxb.close()                           #makes sure the old port isn't open
serxb.open()                            #opens up port for communication

print(test.hatcount)            #for testing purposes
print(test.axescount)           #for testing purposes
print(test.buttcount)           #for testing purposes

                                                ######IMPORTANT######
#the controller you use will have different axis #s, remember to actually test the axis to see it is representing the correct axis
#right now it is set up so it will work with a plastation 4 controller

lx = test.joystick.get_axis(0) #generates the X axis of the left joystick
ly = test.joystick.get_axis(1) #generates the Y axis of the left joystick
ry = test.joystick.get_axis(3) #generates the Y axis of the right joystick
rx = test.joystick.get_axis(2) #generates the X axis of the right joystick

hatlist = [0,0]


while True:
    for event in pygame.event.get():
        if event.type == pygame.JOYAXISMOTION:

                        ###Encoding Table###
            #This needs to expanded so it includes all outputs and what they do
#Left Motor: Stop = 0, Forward = 2, Forward+ = 6, Backward = 4, Backward- = 8
#Right Motor: Stop = 1, Forward = 3, Forward+ = 7, Backward = 5, Backward- = 9
            
            if abs(lx - test.joystick.get_axis(0)) > 0.1:
                lx = test.joystick.get_axis(0)      #if the change in the axis is great enough lx becomes the X axis of the left joystick
                print(test.joystick.get_axis(0))    #testing purposes
            if abs(ly - test.joystick.get_axis(1)) > 0.05:
                ly = test.joystick.get_axis(1)      #if the change in the axis is great enough ly becomes the Y axis of the left joystick
                print('Left Y is ', test.joystick.get_axis(1))    #testing purposes
                if 0.25 >= ly >= -0.25:
                    serxb.write("0".encode())
                elif 0.75 >= ly > 0.25:
                    serxb.write("4".encode())
                elif ly > 0.75:
                    serxb.write("8".encode())
                elif -0.25 > ly >= -0.75:
                    serxb.write("2".encode())
                elif ly < -0.75:
                    serxb.write("6".encode())
            if abs(rx - test.joystick.get_axis(2)) > 0.1:
                rx = test.joystick.get_axis(2)      #if the change in the axis is great enough rx becomes the X axis of the right joystick
                print(test.joystick.get_axis(2))    #testing purposes
            if abs(ry - test.joystick.get_axis(3)) > 0.05:
                ry = test.joystick.get_axis(3)      #if the change in the axis is great enough ry becomes the Y axis of the right joystick
                print('Right Y is ', test.joystick.get_axis(3))    #testing purposes
                if 0.25 >= ry >= -0.25:
                    serxb.write("1".encode())
                elif 0.75 >= ry > 0.25:
                    serxb.write("5".encode())
                elif ry > 0.75:
                    serxb.write("9".encode())
                elif -0.25 > ry >= -0.75:
                    serxb.write("3".encode())
                elif ry < -0.75:
                    serxb.write("7".encode())


# Button to int format (Playstation buttons have not been recorded)
# A = 0 = Square
# B = 1 =
# X = 2
# Y = 3
# LB = 4
# RB = 5
# Back = 6
# Start = 7
# Left Joystick Button = 8
# Right Joystick Button = 9
            
        if event.type == pygame.JOYBUTTONDOWN:
            if test.joystick.get_button(0):
                print("0 has been activated")
            if test.joystick.get_button(1):
                print("1 has been activated")
                serxb.write("A".encode())
            if test.joystick.get_button(2):
                print("2 has been activated")
                serxb.write("B".encode())
            if test.joystick.get_button(3):
                print("3 has been activated")
            if test.joystick.get_button(4):
                print("4 has been activated")
            if test.joystick.get_button(5):
                print("5 has been activated")
            if test.joystick.get_button(6):
                print("6 has been activated")
            if test.joystick.get_button(7):
                print("7 has been activated")
            if test.joystick.get_button(8):
                print("8 has been activated")
            if test.joystick.get_button(9):
                print("9 has been activated")

        if event.type == pygame.JOYHATMOTION:
            hatlist = test.joystick.get_hat(0)
            if(hatlist[0] == 1):
                serxb.write("R".encode())
                print("right")
            if(hatlist[0] == -1):
                serxb.write("L".encode())
                print("left")
            if(hatlist[0] == 0):
                serxb.write("X".encode())
                print("null x-axis")
            if(hatlist[1] == 1):
                serxb.write("U".encode())
                print("up")
            if(hatlist[1] == -1):
                serxb.write("D".encode())
                print("down")
            if(hatlist[1] == 0):
                serxb.write("Y".encode())
                print("null y-axis")

            
