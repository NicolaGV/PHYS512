# Problem 1:
import numpy as np
import matplotlib.pyplot as plt

def fourptsderiv(x, dx, fun):
    return (8*(fun(x+dx)-fun(x-dx))-(fun(x+2*dx)-fun(x-2*dx)))/(12*dx) # + O(dx^4f^(4)(x))

# Test functions with true derivatives
f1 = np.exp
df1 = np.exp
def f2(x):
    return np.exp(0.01*x)
def df2(x):
    return 0.01*np.exp(0.01*x)

def derivative_err_dx(x, fun, dfun): # Derivative error as a function of dx
    num_tests = 1000
    err_list = np.zeros(num_tests)
    dx_list = np.linspace(1, 10e-16, num_tests)
    for n in range (len(dx_list)):
        err_list[n] = np.abs(x - fourptsderiv(x, dx_list[n], dfun))
    
    return dx_list, err_list


plt.clf()
plt.figure()

dx_list, err_list = derivative_err_dx(1, f1, df1)
plt.subplot(221)
plt.plot(dx_list, err_list)
plt.xlabel('dx')
plt.ylabel('error')
plt.xlim(left=0, right=1)
plt.title('f=exp(x) derivative error')

plt.subplot(222)
plt.plot(dx_list, err_list)
plt.xlabel('dx')
plt.ylabel('error')
plt.xlim(left=0, right=0.005)
plt.title('f=exp(x) floating point error')

dx_list, err_list = derivative_err_dx(1, f2, df2)
plt.subplot(223)
plt.plot(dx_list, err_list)
plt.xlabel('dx')
plt.ylabel('error')
plt.xlim(left=0, right=1)
plt.title('f=exp(0.01x) derivative error')

plt.subplot(224)
plt.plot(dx_list, err_list)
plt.xlabel('dx')
plt.ylabel('error')
plt.xlim(left=0, right=0.005)
plt.title('f=exp(0.01x) floating point error')

plt.tight_layout()

plt.savefig("images\Derivative_Error.png")
plt.show()