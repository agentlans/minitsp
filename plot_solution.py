#!/usr/bin/python

# Python script to calculate distance and
# plot travelling salesman problem solution
# given a file containing the coordinates of points and
# a file containing the indices of points in the solution.

import sys
import numpy as np
import matplotlib.pyplot as plt
import pylab as pl
from matplotlib import collections as mc

num_arguments = len(sys.argv)
if num_arguments < 3 or num_arguments > 4:
  print("Usage: plot_solution.py coordinates_file.txt solution.txt [plot.svg]")
  exit(1)

# Parse command line arguments
coordinates_file, solution_file = sys.argv[1:3]
plot_file = ''
if num_arguments == 4:
  plot_file = sys.argv[3]

# Read the coordinates file
coord_file = open(coordinates_file, 'r')
coords = dict()
pt_i = 0
for line in coord_file:
  try:
    coords[pt_i] = tuple(map(float, line.strip().split("\t")))
    pt_i += 1
  except ValueError:
    pass # Ignore strings that can't be converted to float

coord_file.close()

# Read the solution file
soln_file = open(solution_file, 'r')
soln = []
for line in soln_file:
  soln.append(int(line.strip()))

soln_file.close()

def distance(t1, t2):
  'Returns distance between two tuples.'
  assert(len(t1) == len(t2))
  d = 0
  for i in range(len(t1)):
    d += pow(t1[i] - t2[i], 2)
  return d

# Lines to plot
num_pts = len(soln)
lines = []
tsp_dist = 0
for i in range(num_pts):
  pt1 = coords[soln[i]]
  pt2 = coords[soln[(i+1) % num_pts]]
  # Calculate total distance
  tsp_dist += distance(pt1, pt2)
  # Add line segments to plot
  if plot_file != '':
    lines.append([pt1, pt2])

# Show total distance
print("Total distance: " + str(tsp_dist))

# Make plot if necessary
if plot_file != '':
  # Dimension of point
  pt_dimension = len(coords[0])
  if pt_dimension != 2:
    print('Plot is for 2D points only.')
    exit(1)

  # Code based on https://stackoverflow.com/questions/21352580/matplotlib-plotting-numerous-disconnected-line-segments-with-different-colors
  lc = mc.LineCollection(lines)
  fig, ax = pl.subplots()
  ax.add_collection(lc)
  ax.autoscale()
  #pl.show()
  plt.savefig(plot_file)

