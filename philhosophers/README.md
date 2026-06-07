*This project has been created as part of the 42 curriculum by mlucena-.*

# Philosophers

## Description

Philosophers is a C project based on the classic Dining Philosophers problem.

The goal is to simulate a group of philosophers sitting around a table. Each philosopher alternates between eating, sleeping, and thinking. To eat, a philosopher must take two forks. Since each fork can only be used by one philosopher at a time, forks are represented by mutexes.

The project focuses on concurrent programming, thread synchronization, mutex protection, race condition prevention, deadlock avoidance, starvation handling, and safe cleanup of shared resources.

The simulation stops when a philosopher dies or, if the optional argument is provided, when every philosopher has eaten at least the required number of times.

## Instructions

### Compilation

Compile the project with:

```bash
make
```

This creates the executable:

```bash
./philo
```

Clean object files:

```bash
make clean
```

Clean object files and the executable:

```bash
make fclean
```

Rebuild the project:

```bash
make re
```

### Execution

Run the program with:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

* `number_of_philosophers`: number of philosophers and forks.
* `time_to_die`: time in milliseconds before a philosopher dies if they do not start eating.
* `time_to_eat`: time in milliseconds a philosopher spends eating.
* `time_to_sleep`: time in milliseconds a philosopher spends sleeping.
* `number_of_times_each_philosopher_must_eat`: optional argument. If provided, the simulation stops when all philosophers have eaten at least this many times.

### Examples

```bash
./philo 4 800 200 200
```

```bash
./philo 4 800 200 200 3
```

```bash
./philo 1 800 200 200
```

Expected behavior for one philosopher:

```text
0 1 has taken a fork
800 1 died
```

The exact timestamp may vary slightly depending on scheduling, but the death message must be printed within the required time margin.

## Output Format

Each action is printed in the following format:

```text
timestamp_in_ms philosopher_id action
```

Possible actions are:

```text
has taken a fork
is eating
is sleeping
is thinking
died
```

Example:

```text
200 2 is eating
```

All prints are protected by a print mutex to avoid overlapping messages.

## How it works

The program creates one thread for each philosopher and one additional monitor thread.

Each fork is represented by a `pthread_mutex_t`. A philosopher must lock two fork mutexes before eating and unlock them after finishing the meal.

To avoid a circular deadlock, philosophers do not all take forks in the same order. Odd philosophers take the left fork first and then the right fork, while even philosophers take the right fork first and then the left fork. This asymmetry breaks the classic situation where every philosopher holds one fork and waits forever for the next one.

For odd numbers of philosophers, an additional timing strategy is used to reduce starvation. Even philosophers start with a small delay, and philosophers in odd-sized tables wait briefly after thinking before trying to take forks again. This gives other philosophers a fairer chance to eat and prevents one philosopher from being repeatedly delayed until death in valid no-death scenarios.

A monitor thread continuously checks each philosopher's `last_meal` timestamp. If the time since the last meal reaches `time_to_die`, the monitor stops the simulation and prints the death message.

Shared data is protected with mutexes:

* `print_mutex` protects output;
* `stop_mutex` protects the simulation stop flag;
* each philosopher has a `meal_mutex` to protect `last_meal` and `meals_eaten`;
* each fork is protected by its own mutex.

The program also handles the special case of one philosopher separately. Since one philosopher has only one fork available, they take one fork and die after `time_to_die`.

## Technical Details

The implementation handles:

* argument parsing and validation;
* positive numbers with an optional leading `+`;
* invalid and negative arguments;
* overflow protection during conversion;
* dynamic allocation of philosophers and forks;
* mutex initialization and destruction;
* partial cleanup if initialization fails;
* thread creation and joining;
* partial joining if thread creation fails;
* death monitoring;
* optional meal count termination;
* prevention of overlapping output;
* cleanup without memory leaks.

## Testing

Manual tests used during development:

```bash
./philo 1 800 200 200
./philo 4 310 200 100
./philo 4 200 205 200
./philo 5 800 200 200 7
./philo 4 410 200 200 10
timeout 10 ./philo 5 800 200 200
timeout 10 ./philo 5 600 150 150
timeout 10 ./philo 100 800 200 200
timeout 10 ./philo 200 800 200 200
```

Memory checks:

```bash
valgrind --leak-check=full --show-leak-kinds=all ./philo 4 800 200 200 3
valgrind --leak-check=full --show-leak-kinds=all ./philo 1 800 200 200
```

Thread checks:

```bash
valgrind --tool=helgrind ./philo 4 800 200 200 3
valgrind --tool=drd ./philo 4 800 200 200 3
```


## Resources

The following resources were used to understand the concepts required for this project:

* `man pthread_create`
* `man pthread_join`
* `man pthread_mutex_init`
* `man pthread_mutex_lock`
* `man pthread_mutex_unlock`
* `man pthread_mutex_destroy`
* `man gettimeofday`
* `man usleep`
* POSIX Threads documentation
* Linux manual pages
* Dining Philosophers problem explanations and diagrams
* 42 Philosophers subject
* Valgrind Memcheck documentation
* Valgrind Helgrind documentation
* Valgrind DRD documentation

### AI Usage

AI assistance was used during the development process as a learning, debugging, and review tool.

It was used for:

* understanding mutex protection and data races;
* reviewing thread lifecycle management;
* discussing deadlock prevention;
* identifying starvation issues with odd numbers of philosophers;
* designing manual test cases;

AI was not used as a replacement for testing or understanding the code. All suggestions were manually reviewed, adapted, compiled, tested, and debugged before being integrated into the project.

The final implementation was validated with manual tests, Lazy Philosophers Tester, Valgrind Memcheck, Helgrind, and DRD.
