# MVC Pattern

MVC Pattern stands for Model-View-Controller Pattern. This pattern is used to separate application's concerns.
- Model - Model represents an object or JAVA POJO carrying data. It can also have logic to update controller if its data changes.
- View - View represents the visualization of the data that model contains.
- Controller - Controller acts on both Model and view. It controls the data flow into model object and updates the view whenever data changes. It keeps View and Model separate.

## Active Model MVC Pattern:

In Active Model within three components of MVC Pattern the Model is in action. The main difference with Passive Model implementation is, in Active Model implementation the Model notifies the View when the Model is changed by Controller. The pictorial representation will clear it more.

## Passive Model MVC Pattern:

But in Passive Model implementation, Model is inactive. It is not in action. It does not notify View when it is changes by Controller. The notification task is done by Controller. That’s the major difference between the two.

# REF

http://www.tutorialspoint.com/design_pattern/mvc_pattern.htm  
http://www.codeproject.com/Articles/674959/MVC-Patterns-Active-and-Passive-Model-and-its  
