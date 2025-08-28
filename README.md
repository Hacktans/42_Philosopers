# Philosophers (Dining Philosophers Problem)

This project contains the implementation of the classic **Dining Philosophers Problem** simulation using C programming language with pthread library. This problem is a classic computer science problem used to teach concurrent programming, thread synchronization, and deadlock prevention concepts.

## 📋 Project Description

The Dining Philosophers Problem is defined as follows:
- N philosophers sit around a circular table
- Each philosopher has a plate of spaghetti in front of them
- There are N forks between the philosophers (one fork between every two philosophers)
- Philosophers only think, eat, and sleep
- To eat, each philosopher needs two forks (left and right)
- If a philosopher dies (doesn't eat within the specified time), the simulation ends

## 🚀 Compilation and Execution

### Compilation
```bash
make
```

### Cleaning
```bash
make clean    # Remove object files
make fclean   # Remove all compiled files
make re       # Clean and recompile
```

### Execution
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

#### Parameters:
- `number_of_philosophers`: Number of philosophers (between 1-200)
- `time_to_die`: Death time (milliseconds)
- `time_to_eat`: Eating time (milliseconds)
- `time_to_sleep`: Sleep time (milliseconds)
- `number_of_times_each_philosopher_must_eat`: (Optional) Minimum number of meals for each philosopher

## 💡 Usage Examples

```bash
# 5 philosophers, death at 800ms, 200ms eating, 200ms sleeping
./philo 5 800 200 200

# 4 philosophers, each must eat 3 times
./philo 4 410 200 200 3

# Single philosopher case (special case)
./philo 1 800 200 200
```

## ⚙️ Thread Synchronization

The project uses the following mutexes:
- **Fork Mutexes**: Separate mutex for each fork
- **Print Mutex**: Thread-safety for output printing
- **Meal Mutex**: For meal count and last meal time
- **Death Mutex**: For death status control

## ⚠️ Special Cases

- **Single Philosopher**: Handled specially (cannot eat because there's only one fork)
- **Death Control**: Death status is checked before each action
- **Meal Count**: Optional parameter for minimum meal count control

## 📊 Output Format

```
[timestamp] [philosopher_id] [action]
```

Example:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

## 📝 Notes

- This implementation is written according to 42 School standards
- Careful mutex usage is implemented to prevent race conditions
- Memory leaks are prevented and all resources are cleaned up
- The program is norminette compliant

## 👨‍💻 Developer

**Haktan Dalıcı**

---

This project aims to teach concurrent programming, thread synchronization, and resource sharing concepts in a practical way.
