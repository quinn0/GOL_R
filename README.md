# The Game of Life is Expensive: 
## Using C++ to help R do the heavy lifting!
This is an exercise in RCPP when row/col iteration is necessary over large datasets. It simulates [Conway's Game Of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) with wrap-around on a random state.
## Runtime
Rendering images is slow enough! Before any of that can happen, we need to check all neighboring elements of a matrix element so the vectorized optimizations in R or Python (pandas) cannot help speed things up. 
Conway's Game of Life algorithm runs in Quadratic Time (e.g. O(n^2)), meaning that running this algorithm on a 100x100 matrix compared to a 10x10 matrix doesn't take ~10 times longer, it takes ~100 times longer! Yet another reason to be writing half of this code in C++.

## Note: map, purr, progress
While we have significantly improved the runtime of the algorithm, to produce the pretty, simulated gif below (or one of your own customization), you must render the visualization of each state of this matrix (this gif uses 300 'life cycles'). There aren't too many ways of speeding this up without utilizing CUDA and your GPUs... it took me almost a week to render my simulation! using the ```purr``` library and its ```map``` method, you can benchmark an anonymous function (in our case, what is producing the image) so you at least know your program is not hung up (and who doesn't love pretty progress bars)!

## Simulation and Next Steps:
I may switch over to Python for this part (R is still my favorite child shhh), but for improvements to this simulation, especially if I want to add more features, one should/must indeed utilize their GPU. If you have a CUDA primer for me I'll add it to the reading list... but I will be relying on **[Datashader](https://datashader.org/index.html#topics)** to help me render data-driven images (and a useful tool for my current work visualizing big data!). Ultimately this is part of a longer journey to become more comfortable with D3.js

# Watch those little critters go! Can you pick out some periodic 'lifeforms'?
[Game Of Life 300 epochs, random initial state]()
