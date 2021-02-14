# Research Track I - First Assignment

In this repository you will find all the package required for the construction of a 2D robot whose goal is to achieve a target. Let me explain all the 
directory which are in this repository

### my_srv
In this package you will find 
- A subfolder /srv cointains Server1.srv -> it contains all the paramaters that the Server1 required and the parameters that are returned.
- A subfolder /src contains random_server.cpp -> the scope of this code is to provide a random position in a specific interval [-6.6]. Tha random position is given as input and the code returns it to /robot _ controller node

### robot
In this package you will find
- A subfolder /src contains robot_controller.cpp -> it manages the motion of the robot and asks to the server a new target when the previous one is reached 

## How the nodes communicate to each other

In the documentation folder you can find the graph which shows how the nodes communicates to each other

## How to run the code:
- As first step it is necessary to run a command to create the master 
```
roscore & 
```
- As second step run the simulation space with
```
rosrun stage_ros stageros $(rospack find assignment1)/world/exercise.world
```
- As third step in another shell use the command to run the server
```
rosrun my_srv random_server
```
- As last step, in another shell, use the command to run the robot_controller
```
rosrun roboy robot_controller
```

