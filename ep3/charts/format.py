#!/usr/bin/env python
import math

algs_memoria = [
  "First Fit",
  "Next Fit",
  "Best Fit",
  "Worst Fit"
]

algs_pagina = [
  "Optimal",
  "Second Chance",
  "Clock",
  "LRU"
]

print "var data = ["

ok = 0

for memoria in algs_memoria:
  for pagina in algs_pagina:
    raw_input()

    if (ok):
      print ","
    ok = 1
    print "{ nomes: ['"+ memoria + "', '" + pagina + "'],"

    faults = []
    faults_mean = 0
    faults_int = 0

    times = []
    times_mean = 0
    times_int = 0

    for rep in range(30):
      inp_read = raw_input().split(" ")

      faults.append(inp_read[0])
      faults_mean += int(inp_read[0])

      times.append(inp_read[1])
      times_mean += float(inp_read[1])

    faults_mean /= 30.
    times_mean /= 30.

    print "media: [" + str(times_mean) + ", " + str(faults_mean) + "],"

    for i in range(30):
      faults_int += (faults_mean - int(faults[i])) ** 2
      times_int += (times_mean - float(times[i])) ** 2

    faults_int = 1.96 * math.sqrt(faults_int/30.)
    times_int = 1.96 * math.sqrt(times_int/30.)

    print "interv: [" + str(times_int) + ", " + str(faults_int) + "]}"

print "]"
