Now we want to generalize the previous model to include possibly a nonlinear damping term $f(u')$, a possibly nonlinear spring (or restoring force) $s(u)$ and some external excitation $F(t)$:
$$mu'' + f(u') + s(u) = F(t), \;\;\;u(0) = I, \;u'(0) = V,\; t\in(0, T]$$
- We also have included a possibly nonzero initial value of $u'(0)$. 

There are two main types of damping (friction) forces:
- **Linear**: $f(u') = bu$. Usually encountered in spring systems.
- **Quadratic**: $f(u') = bu'|u'|$. Commonly found in air resistance.

Spring forces are often linear
$$s(u) = cu$$
but nonlinear versions are also common, the most famous being the gravity force on a pendulum that acts as a spring with $s(u) \sim \sin(u)$.


# 🔵 A centered difference scheme for linear damping 
Sampling the ODE at a mesh point $t_n$, replacing $u''(t_n)$ by $[D_tD_tu]^n$ and $u'(t_n)$ by $[D_{2t}u]^n$ results in the discretization
$$\big[mD_tD_tu + f(D_{2t}u) + s(u) = F\big]^n$$
which written out means
![[Pasted image 20240319210902.png|500]]
- Where $F^n$, as usual, means $F(t)$ evaluated at $t = t_n$.

Now we must solve the equation above for $u^{n+1}$. But the $u^{n+1}$ inside the $f$ function makes the equation *nonlinear*, unless $f(u')$ is a linear function. Now, for this problem, consider $f(u') = bu'$, then:
![[Pasted image 20240319211138.png|500]]
which gives an explicit formula for $u^{n+1}$:
	$$u^{n+1} = \left(2mu^n + \left(\frac{b}{2}\Delta t - m\right)u^{n-1} + \Delta t^2\left(F^n - s(u^n)\right)\right)\left(m+\frac{b}{2}\Delta t\right)^{-1}$$
For the first time step we must discretize $u'(0) = V$ as $[D_{2t}u  = V]^0$ and combine with the equation above for $n=0$. The discretized initial condition gives?
$$\displaylines{[D_{2t}u = V]^0 = \frac{u^1 - u^{-1}}{2\Delta t} = V\\
u^{-1} = u^{1} - 2\Delta t V}$$
Now inserting in the equation for $u^{n+1}$ for $n=0$:
![[Pasted image 20240319212323.png|400]]








