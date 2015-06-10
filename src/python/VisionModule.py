import sys
import subprocess
import time

###################################################
###################################################
######## This program is not fully tested #########
###################################################
###################################################

"""docstring for VisionModule"""
class VisionModule():
	statusRed = False
	statusBlue = False
	file0 = ["0\n", "\n", "\n", ""]
	file1 = ["2\n", "\n", "\n", ""]

	balloonValues = []
	
	"""Constructor"""
	def __init__(self, arg):
		super(VisionModule, self).__init__()
		self.arg = arg
		self.main(arg)

	"""docstring for sendFile method"""
	def sendFile(self, array):
		with open("test.txt") as fw:
			fw.writelines(array)

	"""Reads all lines out of a file, and returns them as a list"""
	def readFile(self):
		with open("test.txt") as fr:
			lines = fr.read().splitlines()
		return lines
	
	"""Starts the Vision program, with the right kind of balloon"""
	def startVision(self, color):
		if color == "red":
			subprocess.Popen("./Vision r", shell=True)
		elif color == "blue":
			subprocess.Popen("./Vision b", shell=True)
		else:
			sys.exit("ERROR 1: invalid input int method \"startVision\", \"" + color + "\" not recognised. exiting!")

	"""main method"""
	def main(arg):
		sendFile()
		self.startVision(arg)
		
		while 1:
			lijst = self.readFile()
			if lijst[1] == 0:
				time.sleep(1)
			elif lijst[0] == 1:
				sendFile(file0)
				self.balloonValues = lijst
				#TODO: Pass on the values to movement module.
			else:
				sendFile(file1)
				sys.exit("Program exited with code 0 (no problems).")
				#return 0
		
"""Original call of class"""
if len(sys.argv) == 2:
	vision = VisionModule(sys.argv[1])
else:
	sys.exit("Invalid number of arguments.")




"""...Old Code..."""
#print(subprocess.Popen("./Vision r", shell=True, stdout=subprocess.PIPE).stdout.read())
