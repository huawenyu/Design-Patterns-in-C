# OOP Sample of C

* Inheritance
* Multiple inheritance

# Class Diagram

## Inheritance Diagram

```

+----------------+
|     Parent     |
|----------------|
| v_override_who |
| v_ancestor     |
| method_work    |
+----------------+
       .          
      /_\         
       |          
       |          
       |          
       |          
       |          
+----------------+
|     Child      |
|----------------|
| v_override_who |
| v_child_right  |
| method_work    |
+----------------+
       .                                   
      /_\                                  
       |                    [ Child ]      
       |                        .          
       |                       /_\         
       |                        |          
       |                        |          
+----------------+       +----------------+
|   GrandGirl    |       |    GrandSon    |
|----------------|       |----------------|
| v_override_who |       | v_override_who |
+----------------+       +----------------+


```

## Multiple Inheritance Diagram

```

+----------+
| Employee |
|----------|
| wage     |
| level    |
+----------+
                                       
                                       
                                       
                                       
[ Employee ][ Person ]       +--------+
    .                        | Person |
   /_\                       |--------|
    |                        | name   |
    |                        | age    |
+---------+                  +--------+
| Teacher |                            
|---------|                            
| name    |                            
| age     |                            
| wage    |                            
| level   |                            
+---------+                            

```
