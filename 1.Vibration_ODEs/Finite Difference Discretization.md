The very simple ODE
$$u'' + u = 0$$
captures many of the problem we'll face when dealing with finite difference methods for oscillatory ODEs and PDEs, thus it is chosen as our starting point. 


## 🔷 Basic Model for Vibrations
The simplest model for a vibrating mechanism has the following form:
$$u''(t) + \omega^2 u(t) = 0, \;\;u(0) = I, \;u'(0) = 0, \; t \in (0, T]$$
Which the exact solution is
$$u(t) = I\cos(\omega t)$$
- The period of oscillations, that is, the time between two neighboring peaks in the cosine function, is $P = 2\pi/\omega$ 
	- The distance between two neighboring peaks divided by the "speed" in which you go through it ($[\omega] = rad/s$)
- The number of periods per second, that is, the frequency is $f = \omega/2\pi = 1/P$ 
	- That is, one second divided by the number of periods. 


## 🔷 A centered finite difference scheme
Here we'll give a series of steps to follow in order to build a finite difference scheme:

### 🔹 1. Discretizing the Domain
The domain is discretized by introducing a uniformly partitioned time mesh. The points in the mesh are
$$t_n = n\Delta t \;\;\;\; n=0, 1, ..., N_t$$
Where 
$$\Delta t = T/N_t \;\;\;\; \text{where}\;\;\; t \in (0, T]$$
We introduce a mesh function $u^n = u(t_n)$ ($n = 0, 1, N_t$) which approximates the exact solution at the mesh points. 
- Since $n=0$ is the known initial condition, $u^n$ is identical to the mathematical $u$ at this point.

### 🔹 2. Fulfilling the equation at discrete time points
The ODE is to be satisfied at each mesh point where the solution must be found:
$$u''(t_n) + \omega^2u(t_n) = 0 \;\;\; n=1, ..., N_t$$

### 🔹 3. Replacing derivatives by finite differences
Utilizing the second-order central difference approximation for the second order derivative:
$$u''(t_n) \approx \frac{u^{n+1} - 2u^n + u^{n-1}}{\Delta t^2}$$
Inserting this approximation in the ODE we get
$$\frac{u^{n+1} - 2u^n + u^{n-1}}{\Delta t^2} = -\omega^2u^n$$
We also need to replace the derivative in the initial condition by a finite difference. The central difference approximation for $u'(t)$ is:
$$u'(t_n) \approx \frac{u^{t+1} - u^{t-1}}{2\Delta t}$$
Substituting in the initial condition
$$u'(0) = \frac{u^1 - u^{-1}}{2\Delta t} = 0$$

### 🔹 4. Formulating the recursive algorithm
To formulate the algorithm we assume that we've already computed $u^{n-1}$ and $u^n$, such that $u^{n+1}$ is the unknown value to be solved for
$$u^{n+1} = 2u^n - u^{n-1} - \Delta t^2 \omega^2 u^n$$
The computational algorithm is simply to apply the above equation for $n=1, 2, ..., N_t-1$.
- This is sometimes referred to as the **Störmer's method**. 


### 🔹 5. Computing the first step
the recursive algorithm we've created cannot be used for $n=0$ since the computation of $u^1$ requires the unknown value $u^{-1}$. To solve this we must utilize the discretization of the initial condition:
$$\displaylines{\frac{u^1 - u^{-1}}{2\Delta t} = 0\\
\boxed{u^1 = u^{-1}}}$$
This relation can be combined with the recursive form for $n=0$ to get the value of $u^1$:
$$\displaylines{u^1 = 2u^0 - u^1 - \Delta t^2\omega^2u^0\\
u^1 = u^0 - \frac{\Delta t^2 \omega^2 u^0}{2}}$$

## 🔷 The computational algorithm
Following the steps above we have the pseudocode:
$$\displaylines{u^0 = I\\
\text{Compute } u^1 \text{ from } u^1 = u^0 - \frac{\Delta t^2 \omega^2 1u^0}{2}\\
\text{for } n=1, 2, ..., N_{t-1}: \text{ compute } u^{n+1} \text{ from }u^{n+1} = 2u^n - u^{n-1} - \Delta t^2 \omega^2 u^n}$$

## 🔷 Operator Notation
We may write a finite difference scheme for a differential equation utilizing a compact difference notation:
![[Pasted image 20240319131827.png|500]]
This way we write the differential equation in finite difference scheme as
$$[D_tD_tu + \omega^2u = 0]^n$$
- The upper index indicates the step (n is for all steps)

As we can see in the table above, $D_tD_t$ means applying the central difference scheme twice:
$$[D_tD_tu]^n = \frac{u^{n+1} - 2u^n + u^{n-1}}{2\Delta t}$$
The initial conditions can also be expressed in this notation:
$$[u=I]^0 \;\;\; [D_{2t}u = 0]^0$$
Where $D_{2t}$ is the central difference scheme for a single derivative.