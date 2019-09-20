num_x = 99
x_vals = np.linspace(0, R+1, num_x)
f_vals = np.zeros(num_x)

for i in range (len(x_vals)):
    z = x_vals[i]
    f1, f2 = integrate.quad(fun_toIntegrate, l_bound, u_bound)
    f_vals[i] = f1
    
plt.plot(x_vals, f_vals, 'bo', markersize=2)
plt.title('Electric field of a uniformly charged sphere using scipy.integrate.quad', y=1.1)
plt.xlabel('Distance from Center')
plt.ylabel('Electric Field')

plt.savefig('images\ElectrifieldSphereScipyQuad', bbox_inches="tight")
plt.tight_layout()
plt.show()