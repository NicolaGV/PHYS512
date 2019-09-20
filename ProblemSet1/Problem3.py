# Problem 3:
import numpy as np
import matplotlib.pyplot as plt

ncall = 3 # Number of integration calls
ncall_saved = 0 # Number of call saved instead of doing lazy integration

def var_step_siz_integrate(fun, a, b, tol): # manager

    x_mid = (a+b)/2.0
    f, err = integrator(fun, a, x_mid, b, fun(a), fun(x_mid), fun(b), tol)
    # print(f, err, ncall)
    return f, err

def integrator(fun, x0, x2, x4, y0, y2, y4, tol):
    global ncall
    global ncall_saved
    
    x_range = x4 - x0
    
    # Non-limit points, x2 given
    x1 = x0 + x_range/4.0
    x3 = x4 - x_range/4.0
    y1 = fun(x1)
    y3 = fun(x3)
    
    ncall += 2
    ncall_saved += 3
    
    f1 = (y0 + 4*y2 + y4)*(x_range)/6.0 # Simpson's: O(dx^5f^4)
    f2 = (y0 + 4*y1 + 2*y2 + 4*y3 + y4)*(x_range)/12.0 # Simpsons's: O(dx^7f^6)
    err = np.abs(f2 - f1)
    
    if (err<tol):
        return f2, err
    
    else:
        l_integral, l_err = integrator(fun, x0, x1, x2, y0, y1, y2, tol/2.0)
        r_integral, r_err = integrator(fun, x2, x3, x4, y2, y3, y4, tol/2.0)
        
        integral = l_integral + r_integral
        err = l_err + r_err
        return integral, err

# test functions
def fun1(x):
    return 1.0/(1.0+x**2)

def fun2(x):
    return np.sin(x)

def fun3(x): # example that fails
    return np.sin(1.0/x)

fun1_val, fun1_err = var_step_siz_integrate(fun1, -1, 1, 10e-6)
fun1_ncall = ncall
fun1_ncall_saved = ncall_saved

fun2_val, fun2_err = var_step_siz_integrate(fun2, -1, 1, 10e-6)
fun2_ncall = ncall
fun2_ncall_saved = ncall_saved

print('f(x)=1/(1+x^2), -1<x<1:\n')
print('Value: ' + str(fun1_val) + ' , Error: ' + str(fun1_err) + '\n')
print('Number of calls: ' + str(fun1_ncall) + ', Number of calls saved from the lazy integration: ' + str(fun1_ncall_saved) + '\n\n')

print('f(x)=sin(x), -1<x<1:\n')
print('Value: ' + str(fun2_val) + ' , Error: ' + str(fun2_err) + '\n')
print('Number of calls: ' + str(fun2_ncall) + ', Number of calls saved from the lazy integration: ' + str(fun2_ncall_saved) + '\n\n')
