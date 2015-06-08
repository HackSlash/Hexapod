import threading

class Module(object):
	def __init__(self, ident, updatesPerSecond, loopFunction=None, arguments=None):
		self.modId = ident;
		print("Module: "+self.modId+" started\n");
		
		function = 0;
		
		if loopFunction != None:
			fnction = self.loop;
		else:
			function = loopFunction;
		
		self.timer = threading.Timer(updatesPerSecond, function, args=arguments);
		self.on = True;
		self.timer.run();
	
	def getId(self):
		return self.modId;
	
	def loop(self):
		print("original loop function entered");
		if on:
			print("self is on");
			self.timer.run();
		else:
			print("self is off");
	
	def stop(self):
		self.on = False;
		print("Module: "+self.__id+" stopped\n");
		self.timer.cancel();
