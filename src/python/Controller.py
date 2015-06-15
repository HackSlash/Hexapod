"""docstring for Controller"""
class Controller(object):
	__foregroundModules = [];
	__backgroundModules = [];
	__comunicationsInterface = object
	
	__currentForegroundModule = "";
	
	"""constructor"""
	def __init__(self, arg):
		super(Controller, self).__init__()
		self.arg = arg
	
	def getForegroundModuleIdList(self):
		returnList = [];
		
		for module in self.__foregroundModules:
			returnList.append(module.getId());
		
		return returnList;
	
	def getBackgroundModuleIdList(self):
		returnList = [];
		
		for module in self.__backgroundModules:
			returnList.apend(module.getId());
		
		return returnList;
	
	def getForegroundModuleById(self, ident):
		for module in self.__foregroundModules:
			if module.getId() == ident:
				return module
		
		return
	
	def getBackgroundModuleById(self, ident):
		for module in self.__backgroundModules:
			if module.getId() == ident:
				return module
		
		return
	
	def addForegroundModule(self, module):
		usedNames = self.getForegroundModuleIdList();
		
		if module.getId() in usedNames:
			return False;
		
		self.__foregroundModules.append(module);
		
		return True;
	
	def addBackgroundModule(self, module):
		usedNames = self.getBackgroundModuleIdList();
		
		if module.getId() in usedNames:
			return False;
		
		self.__backgroundModules.append(module);
		
		return True;

	def main(self, arg):
		#main code

controller = Controller()

if __name__== "__main__":
	controller.main()
