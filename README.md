# csci-473-global-sum-with-mpi

The project contains a command-line program that calculates the nth sum in parallel using the OpenMPI library. The codebase is entirely
written in the C programming language and requires the OpenMPI module version 4.1.1 to be both installed and loaded on the machine 
employed for execution. 

The algorithm responsible for the functionality of this project is variation of global summation where running processes are partitioned into groups and 
the summation is calculated over a series of phases. If the group number of a process is even, then it communicates with a processes that is conceptually to the right.
Conversely, if the group number of the process is odd, then it communicates with another processes that is to the left of the given process. From these requirements, 
we can view the concept of targetting processes by direction based on a given process's group number. The distance traveled in this direction is a base-2 function 
that utilizes the current phase number as the exponent (I.E. 2^phase_number). In each phase, each process will multiply the direction by the distance to find the target 
process for communication in that face. The communication is simply an exchange of values and at the end of all the phases, each processes will have the same sum
that was formed from the values of its neighbors. 


### Important Note
This project was created for an assignment and is no longer under active development. 
