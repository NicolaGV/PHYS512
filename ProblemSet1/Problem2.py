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
interval_num = 1000
cubic_spline = interpolate.interp1d(diodes[1], diodes[0], kind='cubic')
x_spline = np.linspace(diodes[1,len(diodes[1])-1], diodes[1,0], interval_num)
y_spline = cubic_spline(x_spline)
plt.plot(x_spline, y_spline, 'g-', label="Cubic Spline")
plt.title("Lakeshore Diodes Voltage to Temperature")
plt.legend()

plt.savefig('LakeShore_Interpolated_VoltageToTemp')
plt.show()

# Error
x_shift = np.abs(diodes[1,len(diodes[1])-1] - diodes[1,0]) / (2.0 * interval_num) # half-step shift
x_spline_shift = np.linspace(diodes[1, len(diodes[1])-1]+x_shift, diodes[1,0]-x_shift, interval_num-1) # shifted x values
y_spline_shift = cubic_spline(x_spline_shift) # interpolated value shifted
yy_spline_shift = interpolate.interp1d(x_spline_shift, y_spline_shift, kind='cubic') # interpolation of shifted interpolation

# remove first and last element to be in interpolation range
xx_diodes = np.copy(diodes[1])
xx_diodes = np.delete(xx_diodes, 0)
xx_diodes = np.delete(xx_diodes, len(xx_diodes)-1)

# interpolated y values not shifted
yy_diodes = yy_spline_shift(xx_diodes)

err = 0
for i in range (len(yy_diodes) - 1):
    err += (yy_diodes[i] - diodes[0,i+1])**2
err /= len(yy_diodes)
err = np.sqrt(err)
print('rms error: ' + str(err))