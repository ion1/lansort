# lansort

This is an entry to a humorous competition that occurred at a small LAN party.

The objective was to implement a sorting algorithm for integers in an unusual way.

Some other notable entries were:

* A program that emailed people attending the party asking questions like "is **a** greater than **b**?", parsed responses in natural language and finally emailed the list sorted according to the responses to the participants.
* A program that used a physics engine and a 3D graphics engine to shoot spheres with a force proportional to the numbers in the list and then ran a horizontal beam through them at a constant velocity to determine the sorted order by beam-sphere intersections.

This program:

1. ([`measure.cpp`](measure.cpp)) Samples random integers from the input list, adds Gaussian noise to each (with a standard deviation of 1.0). Given the input list `0, 0, 2, 3, 4, 4, 4, 8` (in any order), a histogram of the output of this part looks like:
   ![Histogram of the sampled input list](https://raw.githubusercontent.com/ion1/lansort/master/example_output/measurements.svg?sanitize=true)
1. ([`estimate.cpp`](estimate.cpp)) Generates a complete array of all the possible ordered lists of integers given a list length (such as 8) and an integer range (such as 0–9).
1. Given a sample from the first part, computes the probability for each candidate list generating the sample and updates a total probability associated with each candidate.
1. Selects a candidate as the result when its total probability is a million times higher than the probability of the next best candidate, or repeats with a fresh sample from the first part otherwise.
1. As the candidates were generated as ordered lists, the sorting problem has been solved.

[The output from a run of the program can be seen here](example_output/lansort.out). It shows the program receiving samples from the first part, selecting the best candidate list at each iteration and computing how happy it is with it (its log probability minus the log probability of the next best candidate) until it makes a final selection.

There are some small problems with this approach, such as sorting a list of five arbitrary 64-bit integers requiring more bits of memory than there are atoms in the universe, but in general it works well.
