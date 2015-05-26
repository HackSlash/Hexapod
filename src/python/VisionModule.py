class VisionModule(Module):
	"""docstring for VisionModule"""
	def __init__(self, arg):
		super(VisionModule, self).__init__()
		self.arg = arg
		
	def getBalloonLocation(self, color):
		locX = 0
		locY = 0

		if color == "red":
			#Vision Code
		elif color == "blue":
			#Vision Code
		else:
			print("ERROR 1: invalid input int method \"getBalloonLocation\", " + color + " not recognised.")


		return [locX, locY]