# minitsp
Finds approximate solutions for the travelling salesman problem

# Install
Requires:
- a C compiler and `make`
- (optional) Python with `matplotlib` for plotting solutions

1. Download repository
2. Run `make` in directory
3. A binary file `minitsp` will be created in directory

# Use
## Find solution
1. Prepare file containing the coordinates of each point (one point per line, coordinates separated by whitespace).
2. Run `./minitsp your_coordinate_file.txt`
- (optional) You can choose how many times the solution should be checked for shortcuts (default 20):
```
./minitsp your_coordinate_file.txt number_of_rounds
```

3. An approximate solution will be written to standard output. Numbers on each line represent the indices of the points listed in the order that they appear on the travelling salesman path. The indices match those in the input coordinate file. For example,
```
1
7
2
```
means that the travelling salesman goes from the point at index 1 to the point at index 7 to the point at index 2.

## Evaluate solution
Requires:
- a coordinate file for the travelling salesman problem
- a file containing the solutions for the coordinate file as described in above section

1. Running `plot_solution.py coordinates_file.txt solution.txt` will show the total round-trip distance for that solution using the Euclidean metric.
2. Running `plot_solution.py coordinates_file.txt solution.txt plot.svg` will plot the points and the travelling salesman solution  to `plot.svg`.

Example solution with 500 uniform random points
![Example travelling salesman solution](https://github.com/agentlans/minitsp/blob/master/example/Random500.svg)

# Author, license
Copyright (C) 2019 Alan Tseng

License: GNU Public License 3
