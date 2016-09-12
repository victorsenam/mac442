#!/usr/bin/env python
import subprocess

scheduler = 1

while scheduler <= 3 :
    for curr_type in [ 'small', 'medium', 'large' ]:
        cnt = 0

        outfile = 'output/' + str(scheduler) + '_' + str(curr_type) + '.out'

        subprocess.call('echo "" > ' + outfile, shell=True)
        
        while cnt < 5 :
            subprocess.call('./testing/gen ' + str(cnt) + ' < testing/' + str(curr_type) + '.in > tmp_input', shell=True)
            subprocess.call('./ep1 ' + str(scheduler) + ' tmp_input out >> ' + outfile, shell=True)
            print(str(scheduler) + ' ' + str(curr_type) + ' ' + str(cnt))

            cnt += 1

        subprocess.call('cat ' + outfile, shell=True)
    scheduler += 1

