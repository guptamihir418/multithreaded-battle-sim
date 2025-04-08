# multithreaded-battle-sim

🏴‍☠️ Combat Simulation in C: Pirate Battles with Hare & Tortoise

This project simulates a multi-threaded battle scenario between a hero (either a Tortoise or a Hare) and a group of Pirates. It explores how different configurations and weapons affect the outcomes of battles over multiple randomized runs. Heroes engage pirates from both ends of a deque (double-ended queue), using threads and synchronization primitives (semaphores) to manage combat.

🔧 Features
Simulates 3 battle scenarios with different hero configurations
Heroes: 🐢 Tortoise and 🐇 Hare, with optional sword bonuses
Pirates have randomized strength, armor, and health
Uses POSIX threads for concurrent battles
Employs semaphores for thread-safe deque access
Includes stats tracking and outcome reporting
Fully modularized C code with header and implementation separation
Memory-safe with valgrind support

make
./fp [number_of_runs]  # Optional: Defaults to 100


make
valgrind --leak-check=full --show-leak-kinds=all -s ./fp

make clean
