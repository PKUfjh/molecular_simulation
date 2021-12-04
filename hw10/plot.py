import matplotlib.pyplot as plt
import numpy as np

temlist= []
temlist2= []
x = np.linspace(0,10,101)
y = np.linspace(0,10,101)
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
plt.ylabel("MSD")
plt.savefig("MSD change")
