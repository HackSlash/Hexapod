class UserControlerModule(Module):
	def __init__(self, ident):
		super(Module, self).__init__(ident, 3, loopFunction=self.loop);
	
	def loop(self):
		print("Module loop");
		super().loop();
	
	controller.addForegroundModule(UserControlModule("User controle module"));
