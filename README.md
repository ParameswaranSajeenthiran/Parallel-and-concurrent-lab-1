# Concurrent Data Structures Project

This project implements and benchmarks concurrent data structures using:
- Serial execution
- Mutex-based locking
- Read–write locks

The goal is to compare performance across different synchronization techniques.

---

## 📦 Requirements

- Linux / macOS (tested on Ubuntu 24.04)
- GCC (with pthread support)
- `make`
- (Optional) Docker

---

## ⚙️ Build & Run (Locally)

1. Build the project:
   ```bash
   make

2. RUn the project:
   ```bash
   make run 

3. RUn the project with 4 cores:
   ```bash
   make run CORES=4

4. View the results in the `output` directory.

5. Clean the project:
   ```bash
   make clean


## ⚙️ Build & Run (Docker)

1. Build the Docker image:
   ```bash
   docker build -t lab-app .
   
2. Run the Docker container:
      ```bash
    docker run --rm -v $(pwd)/output:/usr/src/app/build/output -e NUM_CORES=4 lab-app
   

3. The results will be available in the `output` directory.
   

# Parallel-and-concurrent-lab-1
