from __future__ import print_function
import sys
import subprocess
import threading
import time

"""docstring for VisionModule"""
class VisionModule():
	
	def __init__(self, arg):
		super(VisionModule, self).__init__()
		self.arg = arg
		self.getBalloonLocation(arg)
	
	"""docstring for getBalloonLocation method"""
	def getBalloonLocation(self, color):
		if color == "red":
			#print(subprocess.Popen("./Vision r", shell=True, stdout=subprocess.PIPE).stdout.read())
			subprocess.Popen("./Vision b", shell=True)
		elif color == "blue":
			subprocess.Popen("./Vision b", shell=True)
		else:
			sys.exit("ERROR 1: invalid input int method \"getBalloonLocation\", \"" + color + "\" not recognised. exiting!")
		#readFile BUFFER
		#print("<text>", file=<file>)
		#OR writelines(<iterable(list)>)

if len(sys.argv) == 2:
	vision = VisionModule(sys.argv[1])
else:
	sys.exit("Invalid number of arguments.")