"""Sends movement commands to the communication interface"""
class MovementModule(object):

	"""constructor"""
	def __init__(self, arg):
		super(MovementModule, self).__init__()
		self.arg = arg
		self.isIdle = false

	"""Sends a command to the arduino to move a specific servo into a specific angle"""
	def moveServo(self, id, angle):
		#code to move a single servo

	"""Sends commands to the arduino to move dead ahead"""
	def moveForward(self, length):
		#code to move forward

	"""Sends commands to the arduino to move in reverse"""
	def moveBackward(self, length):
		#code to move backward

	"""Sends commands to the arduino to rotate to the left"""
	def rotateLeft(self, angle):
		#code to rotate left

	"""Sends commands to the arduino to rotate to the right"""
	def rotateRight(self, angle):
		#code to rotate right

	"""Sends commands to the arduino to strafe to the left"""
	def strafeLeft(self, length):
		#code to strafe left

	"""Sends commands to the arduino to strafe to the right"""
	def strafeRight(self, length):
		#code to strafe right

	def main(self, arg):
		#main code

movementModule = new MovementModule()

if __name__== "__main__":
	movementModule.main(sys.arg[1])
