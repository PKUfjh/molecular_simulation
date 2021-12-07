import matplotlib.pyplot as plt
import numpy as np
from numpy import polyfit
from scipy import optimize as op

temlist= []
temlist2= []
x = np.linspace(0,10,51)
y = np.linspace(0,10,101)

def f_1(x, A):
    return A * x

file_object = open('temperature.log','r')
file2_object = open('diffusion.txt','r')
try: 
    for line in file_object:
        temlist.append(np.double(line))
finally:
     file_object.close()

try: 
    for line in file2_object:
        temlist2.append(np.double(line))
finally:
     file2_object.close()

# plt.plot(x,temlist)
# plt.xlabel("t(ps)")
# plt.ylabel("T(K)")
# plt.savefig("temperature change")

plt.plot(y,temlist2)
plt.xlabel("t(ps)")
plt.ylabel("MSD ($\AA ^ 2$)")
plt.savefig("MSD change")

A = op.curve_fit(f_1, y, temlist2)[0][0]
D = A/6*0.0001
print(A)

plt.plot(y,A*y)
plt.annotate("D = %e $cm^2/s$" %D,xy=(1,60), xytext=(1, 60))

plt.savefig("MSD fit")
