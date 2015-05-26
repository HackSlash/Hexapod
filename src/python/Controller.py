class Controller(object):
	__foregroundModules = [];
	__backgroundModules = [];
	
	__currentForegroundModule = "";
	
	def __init__(self):
		pass
	
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

controller = Controller();
