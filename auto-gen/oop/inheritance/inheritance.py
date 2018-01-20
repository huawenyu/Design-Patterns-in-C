class Parent:

	def v_override_who(self): # virtual and override
		pass

	def v_ancestor(self): # virtual but no-override
		pass

	def method_work(self):   # method
		pass

class Child(Parent):

	def v_override_who(self):
		pass

	def v_child_right(self):
		pass

	def method_work(self):   # method
		pass

class GrandSon(Child):

	def v_override_who(self):
		pass

class GrandGirl(Child):

	def v_override_who(self):
		pass


