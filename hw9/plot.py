import matplotlib.pyplot as plt
import numpy as np

temlist= []
x = np.linspace(0,5,251)
file_object = open('temperature.log','r')
try: 
    for line in file_object:
        temlist.append(np.double(line))
finally:
     file_object.close()

plt.plot(x,temlist)
plt.axhline(200, c = 'r',linestyle='--')
plt.xlabel("t(ps)")
plt.ylabel("T(K)")
plt.savefig("temperature change")
