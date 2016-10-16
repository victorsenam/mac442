#!/usr/bin/env python
import subprocess
import sys

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

for pis_tam, pis_nome in pista:
    for cic_qtd, cic_nome in ciclistas:
        print "Teste com pista " + pis_nome + " e quantidade " + cic_nome + " de ciclistas."
        sys.stdout.flush()

        with open(str(pis_tam) + '_' + str(cic_qtd) + '.log', 'w') as log:
            proc = subprocess.Popen("/usr/bin/time -v ../../ep2 " + str(pis_tam) + " " + str(cic_qtd) + " v", shell=True, stderr=subprocess.PIPE, stdout=log)

            for line in proc.stderr.readlines():
                print line.rstrip()

        sys.stdout.flush()

