import subprocess
import sys
import os
import statistics as stat
from random import randint

if len(sys.argv[1:]) <= 0:
    print('test.py <executable>')
    sys.exit(1)

def run(fp, type):
    return subprocess.run([sys.argv[1], fp, type], stdout=subprocess.PIPE)


def test():
    for fp in os.listdir('.'):
        if 'cmplx_numbers' in fp:
            cmul4 = []
            cmul3 = []
            for x in range(50):
                proc = run(fp, '4')
                cmul4.append(float(proc.stdout))
                proc = run(fp, '3')
                cmul3.append(float(proc.stdout))

            print(fp, 'cmul4', stat.mean(cmul4), stat.stdev(cmul4))
            print(fp, 'cmul3', stat.mean(cmul3), stat.stdev(cmul3))


def genNum(len):
    if len < 1:
        return ''
    elif len == 1:
        return str(randint(1, 9))

    return ''.join([str(randint(1, 9))] + [str(randint(0, 9)) for _ in range(len - 1)])


def genData(len, amt=50):
    fp = 'tmpfile.txt'
    with open(fp, 'w') as tmp:
        for amount in range(amt):
            num1 = genNum(len)
            num2 = genNum(len)
            txt = ''.join(['(', num1, ', ', num2, ')']) + "\n"
            tmp.write(txt)
    return fp


for bitlen in [50]:#, 50, 60, 70, 80, 90, 100, 200]:
    cmul3 = []
    cmul4 = []

    print('Generating Data')
    for multiplies in range(1, 200):
        fp = genData(bitlen, multiplies)

        data = []
        for _ in range(3):
            data.append(float(run(fp, '3').stdout))

        cmul3.append((multiplies, sum(data)/len(data)))

        data = []
        for _ in range(3):
            data.append(float(run(fp, '4').stdout))

        cmul4.append((multiplies, sum(data)/len(data)))

    print('Graphing...')
    import matplotlib.pyplot as plt

    fig, ax = plt.subplots()

    x = [tup[0] for tup in cmul3]
    y = [tup[1] for tup in cmul3]
    plt.plot(x, y, label='cmul3')

    x = [tup[0] for tup in cmul4]
    y = [tup[1] for tup in cmul4]
    plt.plot(x, y, label='cmul4')

    ax.legend(loc='upper left')
    ax.set_title("3-Multiply vs. 4-Multiply ("+str(bitlen)+"bits)")
    ax.set_xlabel("# of multiplies")
    ax.set_ylabel("Time")

    plt.show()