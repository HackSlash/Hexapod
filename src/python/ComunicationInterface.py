import struct
import serial
from time import sleep

class PacketManager():
        def __init__(self, bluetoothConnenction, serialConnection):
            self.message = bytearray()
            self.bluetoothConnection = bluetoothConnenction
            self.serialConnection = serialConnection
            self.PACKET_START = 254
            self.PACKET_END = 255
            self.WALK_STRAFE = 0
            self.WALK_TURN = 1
            self.WALK_HIGH = 2
            self.WALK_FUP = 3
            self.MODE1 = 4
            self.MODE2 = 5

        def bluetoothPackageHandler(self):
            PACKET_SIZE = 5
            self.message.append(self.bluetoothConnection.read())
            if len(self.message) == PACKET_SIZE:
                if self.message[0] == self.PACKET_START and self.message[4] == self.PACKET_END:
                    self.switch(self.message[1])(self.message)
                    self.message = bytearray()
                else:
                    del self.message[0:1]

        def switch(self, function_Id):
                return {
                        self.WALK_STRAFE : lambda x: self.sendToSpider(x),
                        self.WALK_TURN : lambda x: self.sendToSpider(x),
                        self.WALK_HIGH : lambda x: self.placeHolder(x),
                        self.WALK_FUP : lambda x: self.placeHolder(x),
                        self.MODE1 : lambda x: self.placeHolder(x),
                        self.MODE2 : lambda x: self.placeHolder(x),
                        }[function_Id]

        def sendToSpider(self, packet):
            self.serialConnection.write(packet)
            print(str(packet[0]) + " " + str(packet[1]) + " " + " " + str(packet[2])
                  + " " + str(packet[3]) + " "  + str(packet[4]))
            with open("./bluetooth_debug.txt", "a") as text_file:
                text_file.write(str(packet[0]) + " " + str(packet[1]) + " " + " " + str(packet[2])
                  + " " + str(packet[3]) + " "  + str(packet[4]) + "\n")

        def placeHolder(self, parameter1):
            lol = 1
        
        
class ControllerConnection():
    def __init__(self):
        self.bluetoothSerial = serial.Serial( "/dev/rfcomm1", baudrate=9600)

    def write(self,message):
        #for value in message:
        self.bluetoothSerial.write(message)

    def read(self):
        #return bytearray(self.bluetoothSerial.readline())
        return ord(self.bluetoothSerial.read(1))
            
class SerialWrite:
    def __init__(self):
        self.ser = serial.Serial('/dev/ttyAMA0',115200,timeout=1)
        

    def write(self,message):
        self.ser.open()
        for value in message:
            self.ser.write(bytes([value]))
        self.ser.close()
        
    def read(self):
        self.ser.open()
        #response = self.ser.readline()
        #print (response)
        byte = ord(self.ser.read(1))
        print(byte)
        self.ser.close()
        return byte

controller = ControllerConnection()
spider = SerialWrite()

manager = PacketManager(controller,spider)

with open("./bluetooth_debug.txt", "a") as text_file:
    text_file.write("begin bluetooth connection!\n")

while 1:
    manager.bluetoothPackageHandler()