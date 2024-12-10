You may be following the amaizing course of ROS2 mapping by Antonio Brandi, but maybe you don't have a xbox controller or any other. Here is one possible solution for you, a node which allows you to control the robot using your laptop/pc keyboard :D!.
This node works when the gazebo.launch.py and the controller.launch.py are active. Source another terminal and type
```
ros2 run bumperbot_controller teclado
```

Maintain the BlockMayus on. 
* W -> move forward
* S -> move backwards
* A -> turn left
* D -> turn right
* E -> increase speed +0.1
* R -> decrease speed -0.1
* Q -> exit

It only moves in one sence. Not linear + angular twice. In case you would.
