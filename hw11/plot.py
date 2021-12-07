import matplotlib.pyplot as plt
import numpy as np
from numpy import polyfit
from scipy import optimize as op

temlist= []
temlist2= []
temlist3 = []
temlist4 = []
x = np.linspace(0,10,51)
y = np.linspace(0,10,101)
z = np.linspace(0,8.5,85)
w = np.linspace(0.005,8.495,850)

def f_1(x, A):
    return A * x

# file_object = open('temperature.log','r')
# file2_object = open('diffusion.txt','r')
file3_object = open('rdf.txt','r')
file4_object = open('ref_rdf.txt','r')
# try: 
#     for line in file_object:
#         temlist.append(np.double(line))
# finally:
#      file_object.close()

# try: 
#     for line in file2_object:
#         temlist2.append(np.double(line))
# finally:
#      file2_object.close()

try: 
    for line in file3_object:
        temlist3.append(np.double(line.split("\t")[1]))
finally:
     file3_object.close()

try: 
    for line in file4_object:
        temlist4.append(np.double(line.split(" ")[1]))
finally:
     file4_object.close()

# plt.plot(x,temlist)
# plt.xlabel("t(ps)")
# plt.ylabel("T(K)")
# plt.savefig("temperature change")

# plt.plot(y,temlist2)
# plt.xlabel("t(ps)")
# plt.ylabel("MSD ($\AA ^ 2$)")
# plt.savefig("MSD change")

# A = op.curve_fit(f_1, y, temlist2)[0][0]
# D = A/6*0.0001
# print(A)

# plt.plot(y,A*y)
# plt.annotate("D = %e $cm^2/s$" %D,xy=(1,60), xytext=(1, 60))

# plt.savefig("MSD fit")

plt.plot(z,temlist3,color = 'blue')
plt.plot(w,temlist4,color = 'red',linestyle = "dashed")
plt.xlabel("r")
plt.ylabel("g(r)")
plt.legend(["my MD","ref"])
plt.savefig("radial distribution function")