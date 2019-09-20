# Problem 2:
import numpy as np
import matplotlib.pyplot as plt
from scipy import interpolate

diodes = np.transpose(np.loadtxt('lakeshore.txt'))

plt.clf()
plt.plot(diodes[1], diodes[0], 'ro', markersize=2, label="Lakeshore Data")
plt.xlabel('Voltage (V)')
plt.ylabel('Temperature (K)')

# Neighbours cubic spline
cubic_spline = interpolate.interp1d(diodes[1], diodes[0], kind='cubic')
x_spline = np.linspace(diodes[1,0],diodes[1,len(diodes[1])-1],1000)
y_spline = cubic_spline(x_spline)
plt.plot(x_spline, y_spline, 'g-', label="Cubic Spline")
plt.title("Lakeshore Diodes Voltage to Temperature")
plt.legend()

plt.savefig('LakeShore_Interpolated_VoltageToTemp')
plt.show()