#!/usr/bin/env python
import subprocess
import sys
import math
import time

jump = int(input())
n = 30

pista = [
    [250, 'pequena'], 
    [500, 'media'],
    [1000,'grande']
]
ciclistas = [
    [5, 'pequena'],
    [20, 'normal'],
    [50,'grande']
]

ok = ""

f = open('logs/run_' + str(time.time()) + '.log', 'w');

print "["
for cic_qtd, cic_nome in ciclistas:
    for pis_tam, pis_nome in pista:

        if (jump):
            jump -= 1
            continue

        times = []
        mems = []

        time_mean = 0
        time_int = 0
        mem_mean = 0
        mem_int = 0

        for rep in range(n):
            curr_time = 0
            curr_mem = 0

            with open('logs/' + str(pis_nome) + '_' + str(cic_nome) + '_' + str(rep) + '.log', 'w') as log:
                proc = subprocess.Popen("/usr/bin/time -v ../../ep2 " + str(pis_tam) + " " + str(cic_qtd) + " v", shell=True, stderr=subprocess.PIPE, stdout=log)

                i = 0
                for line in proc.stderr.readlines():
                    i+=1

                    log.write(line)
                    line = line.rstrip()
                    if (i == 5):
                        line = line[46:].split(":")

                        curr_time = float(line[0]) * 60. + float(line[1])

                    if (i == 10):
                        curr_mem = float(line[37:])

            times.append(curr_time)
            time_mean += curr_time

            mems.append(curr_mem)
            mem_mean += curr_mem

            f.write(pis_nome + " " + cic_nome + " " + str(rep) + ": " + str(curr_time) + "ms " + str(curr_mem) + "kb\n")
            f.flush()

        time_mean /= n
        mem_mean /= n

        for rep in range(n):
            time_int += (time_mean - times[rep]) ** 2
            mem_int += (mem_mean - mems[rep]) ** 2

        time_int = 1.96 * math.sqrt(time_int/n)
        mem_int = 1.96 * math.sqrt(mem_int/n)

        print ok + "[ [\"" + cic_nome + "\", \"" + pis_nome + "\"], [" + str(time_mean) + ", " + str(time_int) + "], [" + str(mem_mean) + ", " + str(mem_int) + "] ]"
        ok = ","
        sys.stdout.flush()

print "]"
sys.stdout.flush()
f.close()
