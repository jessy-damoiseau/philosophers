# philosophers

<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg"  width="30" height="30" />

 ## Overview
 - create a software that simulates Dijkstra's dining philosophers problem
 - learn the concepts of concurrent and parallel execution between threads
 - manipulates threads and mutex
 - leaks, deadlocks, datarace or thread starvation are stricly forbidden
## Problem specifications
 - One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table.
 - The philosophers alternatively eat, think, or sleep.
    - While they are eating, they are not thinking nor sleeping;
    - while thinking, they are not eating nor sleeping;
    - and, of course, while sleeping, they are not eating nor thinking.
 - There are also forks on the table. There are as many forks as philosophers.
 - Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand.
 - When a philosopher has finished eating, they put their forks back on the table and start sleeping. Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation.
 - Every philosopher needs to eat and should never starve.
 - Philosophers don’t speak with each other.
 - Philosophers don’t know if another philosopher is about to die.
 - No need to say that philosophers should avoid dying!
## Warning
As this project manipulates threads and mutex this project might not work well or even not work work at all depending on the OS you use.
