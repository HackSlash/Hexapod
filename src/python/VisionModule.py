import sys
import os
import subprocess
import time
from movementModule import movementModule

"""docstring for VisionModule"""
class VisionModule():
	
	"""Constructor"""
	def __init__(self, arg):
		super(VisionModule, self).__init__()
		self.arg = arg
		if arg == "red":
			self.startColor = "red"
		elif arg == "blue":
			self.startColor = "blue"
		else:
			sys.exit("Invalid color in argument!")
		movement = movementModule()
	
	"""Starts the Vision program, with the right kind of balloon"""
	def startVision(self, color):
		if color == "red":
			path = "./Vision r"
		else:
			path = "./Vision b"
		cProgram = subprocess.Popen(path, stdout=PIPE, stderr=STDOUT, shell=True, preexec_fn=os.setsid)
		for cFeedback in cProgram.stdout:
			pFeedback = cFeedback.decode("utf-8").replace('\n', '')
			movement.moveOnBalloon(pFeedback)
		
	"""main method"""
	def main(self):
		if self.startColor == "red":
			self.startVision("red")
			self.startVision("blue")
		else:
			self.startVision("blue")
			self.startVision("red")
		
		
	"""
	if len(sys.argv) == 2:
		vision = VisionModule(sys.argv[1])
	else:
		sys.exit("Invalid number of arguments.")
	"""