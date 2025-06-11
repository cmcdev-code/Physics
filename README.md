
This is a particle simulation that I created during my sophomore year of university.

I am not proud of this code now, largely due to the inaccurate way I applied the kinematic equations. I used a 'step' for time and simply added acceleration to velocity and then velocity to position, instead of numerically solving the integral.

If I were to do this now, I would use a method more akin to Monte Carlo integration and research some numerical analysis techniques to achieve a tolerable error, $\epsilon$.

Nonetheless, this was part of my programming journey, so I will leave it up.
![example](./example/particles_test1.gif)
