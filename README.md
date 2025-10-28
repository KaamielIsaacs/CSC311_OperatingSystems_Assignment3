# Thread Synchronization with Mutexes (Critical Section Guard)

This project demonstrates the use of **POSIX Threads (pthreads) mutexes** for synchronizing access to a shared global variable among multiple threads. This technique prevents race conditions and ensures that concurrent operations on the shared data are performed safely and predictably.

## Project Overview 🔒

The goal is to show how a mutex creates a **critical section** around the code that modifies a shared variable (`global_value`). Four separate threads are created, each attempting to perform a different arithmetic operation on the same variable.

Without the mutex (`lock_guard`), the concurrent access to `global_value` would lead to unpredictable results due to **race conditions**. By using `pthread_mutex_lock()` and `pthread_mutex_unlock()`, we guarantee that only one thread can modify `global_value` at any given time, thus preserving data integrity.

### Shared Resource and Operations

| Component | Initial Value |
| :--- | :--- |
| **`global_value`** (float) | **`64.0`** |

| Thread Function | Operation | Intended Effect on **`global_value`** |
| :--- | :--- | :--- |
| `increment` | `global_value += 1.0` | $64.0 \rightarrow 65.0$ |
| `decrement` | `global_value -= 1.0` | $65.0 \rightarrow 64.0$ |
| `multiply_by_two` | `global_value *= 2.0` | $64.0 \rightarrow 128.0$ |
| `divide_by_two` | `global_value /= 2.0` | $128.0 \rightarrow 64.0$ |

### Expected Final Result

If the operations execute sequentially (which the mutex forces, despite the threads running concurrently), the intended sequence of values would be:

$$64.0 \rightarrow 65.0 \rightarrow 64.0 \rightarrow 128.0 \rightarrow 64.0$$

The net effect of the four operations (one increment, one decrement, one multiplication by 2, and one division by 2) on the initial value of $64.0$ is:

$$\text{Final Value} = (((64.0 + 1.0) - 1.0) \times 2.0) / 2.0 = \mathbf{64.0}$$

**The `pthread_mutex_t lock_guard` ensures that the final printed value is consistently $\mathbf{64.0}$.**

-----

## Technical Details

| Function/Variable | Description |
| :--- | :--- |
| **`global_value`** | The shared `float` variable accessed by all threads. |
| **`lock_guard`** | The **mutex** variable used for synchronization. It must be initialized with `pthread_mutex_init`. |
| **`pthread_mutex_lock()`** | Acquires the lock. If the mutex is already locked, the thread blocks (waits) until the lock is released. |
| **`pthread_mutex_unlock()`** | Releases the lock, allowing one of the waiting threads (if any) to acquire it. |
| **`pthread_mutex_destroy()`** | Releases resources associated with the mutex at the end of the program. |
| **`pthread_join()`** | Used in `main` to wait for all worker threads to complete before printing the final result and exiting. |

-----

## How to Compile and Run

The pthreads library must be linked when compiling the C code.

### Prerequisites

You need a C compiler (like GCC) installed on your system.

### Compilation

Use the `-pthread` flag to ensure the pthreads library is correctly included.

```bash
# Assuming the C code is saved as 'mutex_safety.c'
gcc -o mutex_app mutex_safety.c -pthread
```

### Execution

Run the compiled executable.

```bash
./mutex_app
```

### Expected Console Output

The order of the intermediate output lines may vary due to thread scheduling, but the content of the lines and the **final value** should be consistent.

```
Initial float variable: 64.00
[... intermediate output lines will appear here in a non-deterministic order ...]
Final value: 64.00
```

-----

Would you like to explore what happens if you **remove the mutex** from the code to see a race condition in action, or would you like a detailed explanation of the **critical section** concept?
