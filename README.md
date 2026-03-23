# 🍝 philo

A multithreading and synchronization project in C based on the dining philosophers problem, developed as part of the 42 curriculum.

## 📖 About

`philo` is a core project of the 42 curriculum. The goal of this project is to simulate the dining philosophers problem using threads and mutexes, while managing synchronization, timing, and shared resources correctly.

## 🧩 What’s Included

This project includes:

- philosopher thread creation and management
- mutex-based fork handling
- synchronization of shared data
- death detection and monitoring
- meal count tracking
- timing and action control
- safe message printing between threads

## 🗂️ Project Structure

```text
philo/
├── Makefile
├── README.md
├── .gitignore
├── inc/
│   └── philo.h
└── src/
    ├── philo.c
    ├── init.c
    ├── check_args.c
    ├── routine_actions.c
    ├── routine_control.c
    ├── handle_threads.c
    └── utils.c
```

## 🚀 Usage

Clone the repository and move into the project folder:

```bash
git clone https://github.com/bde-luce/philo.git
cd philo
```

Compile the project:

```bash
make
```

After compilation, the project generates the `philo` executable.

Run the program with:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:

```bash
./philo 5 800 200 200
```

## ⚙️ Makefile Rules

The Makefile supports the following commands:

- `make` or `make all` — compiles the project

- `make clean` — removes object files

- `make fclean` — removes object files and the executable

- `make re` — rebuilds everything from scratch


## 📝 Notes

This project is part of the 42 School curriculum. The repository was later reorganized for clearer structure and presentation.