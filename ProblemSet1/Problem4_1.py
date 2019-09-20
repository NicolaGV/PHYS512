# Problem 4:
from scipy import integrate
import sys

e0 = 8.854e-10 # Permittivity
R = 1.0 # Sphere radius
Q = 1.0 # Total Charge
o = Q/(4.0*np.pi*R**2) # Area charge density
z = 2.0 # Sphere distance
factor = o*R/2/e0 # In front of the integral
tol = 10e-3 # Tolerance

l_bound = 0.5*np.pi
u_bound = -0.5*np.pi
def fun_toIntegrate(t):
    top = np.cos(t)*(R*np.sin(t)-z) #R*np.sin(t)-z
    bot = ((z-R*np.sin(t))**2 + (R*np.cos(t))**2)**1.5
    return factor*top/bot

def true_value(z):
        if (z>R):
            return Q/(4*np.pi*e0*z**2)
        else:
            return 0

num_x = 500
x_vals = np.linspace(10e-3, R+1, num_x)
f_vals = np.zeros(num_x)
f_errs = np.zeros(num_x)

sys.setrecursionlimit(3000)
for i in range (len(x_vals)):
    z = x_vals[i]
    val_tmp, err_tmp = var_step_siz_integrate(fun_toIntegrate, l_bound, u_bound, tol)
    f_vals[i] = val_tmp
    f_errs[i] = err_tmp

plt.clf()

ax1=plt.subplot(211)
plt.plot(x_vals, f_vals, 'ko', markersize=1)
plt.title("Electric field of a uniformly charged sphere")
plt.xlabel('Distance from Center')
plt.ylabel('Electric Field')

# True function
y_true = np.zeros(num_x)
for i in range(len(x_vals)):
    y_true[i] = true_value(x_vals[i])

plt.plot(x_vals, y_true, 'r--')


ax2=plt.subplot(212, sharex=ax1)
plt.plot(x_vals, np.abs(y_true - f_vals))
plt.title('Error between the true and integrated values')
plt.xlabel('Distance from Center')
plt.ylabel('Error')

plt.savefig('images\ElectricFieldSphere', bbox_inches="tight")
plt.tight_layout()
plt.show()