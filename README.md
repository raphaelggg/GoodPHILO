*This project has been created as part of the 42 curriculum by <ragolden>.*

# Philosophers - The Dining Philosophers Problem

## Description
The **Philosophers** project is a simulation of the classic *Dining Philosophers problem*, a famous computer science puzzle that illustrates the challenges of **concurrency**, **multithreading**, and **synchronization** in operating systems.

The core goal is to create a simulation where $N$ philosophers sit around a circular table with $N$ forks. A philosopher needs two forks to eat. They alternate between three states: **eating**, **sleeping**, and **thinking**. If a philosopher doesn't start eating within a certain timeframe (`time_to_die`), they die of starvation. 

The technical challenge consists of managing shared resources (forks) using **Threads** and **Mutexes** to completely avoid **deadlocks** (where everyone holds one fork and waits forever) and **data races** (where two threads access memory simultaneously).

---

## Technical Choices
* **One Thread per Philosopher:** Each philosopher runs independently inside their own thread (`pthread_create`).
* **One Mutex per Fork:** Each fork is protected by a mutex (`pthread_mutex_t`) to ensure it can only be picked up by one philosopher at a time.
* **State Protection Mutexes:** Shared variables (like the death flag or the last meal timestamp) are carefully wrapped in mutex locks to prevent data races.
* **Asymmetric Fork Picking:** To prevent deadlocks, philosophers pick up their forks based on their ID (e.g., even IDs pick up left then right, odd IDs pick up right then left).

---

## Instructions

### Compilation
The project includes a strict `Makefile` that compiles the source files with the `-Wall -Wextra -Werror` flags.

To compile the program, run the following command in your terminal:
```bash
make