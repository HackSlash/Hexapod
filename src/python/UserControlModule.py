import sys

"""docstring for UserControlModule"""
class UserControlModule(object):
	def __init__(self, arg):
		super(UserControlModule, self).__init__()
		self.arg = arg
		

	def main(arg):
		#main code

usercontrol=new UserControlModule(sys.arg)


if __name__== "__main__":
	usercontrol.main(sys.arg[1])