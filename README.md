*This project has been created as part of the 42 curriculum by ragolden.*

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
```

### Usage

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) at the table |
| `time_to_die` | Time in ms before a philosopher dies if they haven't started eating |
| `time_to_eat` | Time in ms a philosopher spends eating |
| `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation ends when all philosophers have eaten this many times |

### Example

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```

---

## Resources

### Documentation & References

- [POSIX Threads Programming — Lawrence Livermore National Laboratory](https://hpc-tutorials.llnl.gov/posix/) — comprehensive reference for `pthread` functions, thread lifecycle, and mutex usage.
- [The Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem) — original problem statement, history, and classic solutions.
- [pthread_create / pthread_join — Linux man pages](https://man7.org/linux/man-pages/man3/pthread_create.3.html) — official POSIX documentation for thread creation and synchronization primitives.
- [pthread_mutex_lock — Linux man pages](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html) — reference for mutex locking and unlocking behaviour.
- [Data Races and Deadlocks — GeeksforGeeks](https://www.geeksforgeeks.org/deadlock-in-os/) — accessible introduction to deadlock conditions and prevention strategies.

### AI Usage

Claude (Anthropic) was used as an assistant during this project in the following ways:

- **Debugging:** Identifying potential data races and deadlock scenarios by describing the thread logic and asking for analysis of edge cases.
- **Conceptual explanation:** Getting clearer explanations of memory model concepts (e.g., why a boolean flag must still be mutex-protected even if reads feel "atomic").
- **Code review:** Asking for feedback on the structure of the monitoring loop and the fork-picking order to validate the asymmetric strategy.