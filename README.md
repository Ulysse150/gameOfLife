
# Conway's Game of Life

This is project is an implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life), in console only for the moment.

# How to use it

To compile it, you will need to have installed ``` g++ ```, and then use the Makefile : 

- ``` make evolution ``` will simply compile the files and create a ```launch``` file
- ``` make all ``` will compile and execute the file but without the options

# Execution options

There are 3 ways to execute the file
 
| Parameters | Effect | Example | 
 | :---:   | :---:   | :---:   |
 | No parameters | Launch the simulation with a 20*20 grid with a square of 256 alive cells | ./launch
| File Name | Launch the simulation using the file as a layout (0 for dead cell 1 for alive) | ./launch file.txt
|Three Ints w h p|Launch the simulation with w*h grid size, and with a square of alive cells the size of w*(p/100) | ./launch 15 15 70 
