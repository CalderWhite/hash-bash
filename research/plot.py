from matplotlib import pyplot as plt
import sys
import os

def parse(r):
    return [[float(j) for j in i.split(', ')] for i in r[:-1].split("\n")]

t = "crackstation"
a = parse(open(t + "_1000.csv").read())
b = parse(open(t + "_bad_control_1000.csv").read())

plt.title(t + " naive vs sophisticated approach")
plt.xlabel("% of total possible combinations tried")
plt.ylabel("% of real passwords guessed")

plt.plot(*zip(*a), label="Sophisticated approach")
plt.plot(*zip(*b), label="Naive approach")

plt.grid(True)
plt.legend()
plt.savefig(t + "_comparison.svg")

os.system("eog %s_comparison.svg &" % t)

"""
args = sys.argv[1:]
r = open(args[0]).read()
x = [[float(j) for j in i.split(', ')] for i in r[:-1].split("\n")]

plt.title(args[2])
plt.plot(*zip(*x))
plt.grid(True)
plt.savefig(args[1])
plt.show()
"""
