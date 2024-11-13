# Finite Differences Algorithms
This repository stores a different set of finite differences algorithms I have developed during my graduation. More specifically, for a class on high processing computing (HPC). 

Finite difference is a numerical method used to approximate derivatives by calculating differences between function values at discrete points. It is commonly applied in physics and engineering to solve differential equations that describe systems and processes, such as heat conduction, wave propagation, and fluid flow. By transforming continuous equations into discrete forms, finite difference methods allow complex physical problems to be solved on computers, providing approximate solutions for systems where analytical solutions are difficult or impossible to obtain. This approach is also widely used in finance, biology, and other fields for modeling dynamic systems.

## 2D Wave Equation Simulation
Most of my effort was spent on the 2D wave equation problem. Since it presents a time dependency, it's a harder problem to face (compared to other common applications), specially in the context of HPC. 

### Solutions
Many simulations for different initial conditions can be observed in the following graphs.
![2D_wave_equation](https://github.com/user-attachments/assets/d7ab4f82-af61-4399-831a-e4de074fed72)
![seismic](https://github.com/user-attachments/assets/e60eea0b-079c-43e5-85d1-f0b0cc18e1f2)
![flare](https://github.com/user-attachments/assets/78bb8ab3-0871-4e81-9bfa-acc3a7edc99c)

### Parallelization
A shared memory parallelization was implemented in the 2D wave equation algorithm, via OpenMP. One of the many analyses made is shown below, where a scalability study is promoted in order to identify size conditions where the paralization is worth.
![benchmark_grid_no_flags](https://github.com/user-attachments/assets/b95a9782-14e2-4b88-97c6-cd4369d994b2)
The curve above illustrates the difficulty in parallelizing a time-dependent problem, for small grid sizes there's almost no difference. And in some scenarios, it is even worse. On the other hand, the parallelization effectiveness increases as the problem size increases, which shows a piece of important information about such systems. 
