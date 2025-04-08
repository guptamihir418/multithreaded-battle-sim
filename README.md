# 🧵 multithreaded-battle-sim

## 🏴‍☠️ Combat Simulation in C: Pirate Battles with Hare & Tortoise

This project simulates a **multi-threaded battle scenario** between a hero (either a 🐢 Tortoise or 🐇 Hare) and a group of Pirates. It explores how different hero configurations and sword bonuses affect battle outcomes over multiple randomized runs. Heroes engage pirates from both ends of a deque (double-ended queue), using **threads** and **semaphores** to manage combat safely and concurrently.

---

## 🔧 Features

- ⚔️ Simulates **3 battle scenarios** with different hero configurations
- 🐢 Tortoise and 🐇 Hare heroes, optionally equipped with a sword
- 🏴‍☠️ Pirates have randomized strength, armor, and health
- 🧵 Uses **POSIX threads** for parallel fights
- 🔒 Thread-safe deque access using **semaphores**
- 📊 Tracks and prints battle statistics across multiple runs
- 📁 Fully modularized C codebase
- 🧼 Memory-safe with support for `valgrind`

---

## 🚀 Build & Run

### ✅ Compile the project:
```bash
make


make
./fp [number_of_runs]  # Optional: Defaults to 100


make
valgrind --leak-check=full --show-leak-kinds=all -s ./fp

make clean
```
