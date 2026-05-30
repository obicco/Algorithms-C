# Algorithms & Programming in C

C exercises on algorithms and advanced data structures, developed as part of the **Algorithms and Programming (AP)** course at Politecnico di Torino.

**Author:** Oskar Bich (s226421)  
**Language:** C  
**Period:** 2020 – 2022

---

## Repository Structure

```
.
├── Lab00 – Lab13        # Lab sessions with PDF assignments and C solutions
├── Exams/               # Past exam solutions (2014 – 2022)
├── Teoria Scritto/      # Reference implementations for written exams
├── AP_Algoritmi_e_Programmazione_in_Pratica/   # Standard ADT examples
├── AP_Ricorsione_e_Calcolo_Combinatorio/       # Recursion & combinatorics
└── DalProblemaAlProgramma/                     # Introductory problem-solving exercises
```

Each `Lab##` folder contains:
- A PDF with the problem statement
- An annotated PDF with full commentary (`Commento completo`)
- Input files used during testing
- A `Soluzione/` directory with the C source code

---

## Lab Sessions

### Lab00 — Arrays and Matrices
| Exercise | Description |
|----------|-------------|
| es1 | Find maximum-length contiguous non-zero sub-arrays |
| es2 | Count vowels per word in a text file using sub-arrays |
| es3 | Rotate a vector left or right by P positions |
| es4 | Find and print the maximum-sum D×D sub-matrix |

### Lab01 — Matrices, Files, and Structs
| Exercise | Description |
|----------|-------------|
| es1 | Read a matrix from file and print column maximums |
| es2 | Phone book with codename/phonetic lookup from file |
| es3 | Rotate rows and columns of a matrix read from file |

### Lab02 — Structs, File I/O, and Sorting
| Exercise | Description |
|----------|-------------|
| es1 | Identify rectangular regions in a 2D integer matrix |
| es2 | Flight log management with date/time structs and commands |
| es3 | Concordance index: map keywords to line positions in a text file |
| es4 | Selection sort with step-by-step comparison and swap counters |

### Lab03 — Advanced Arrays and Memory Representation
| Exercise | Description |
|----------|-------------|
| es1 | Identify rectangular regions (refined approach with pointers) |
| es2 | Endianness detection and IEEE 754 binary encoding of floats |

### Lab04 — Recursion and Divide & Conquer
| Exercise | Description |
|----------|-------------|
| es1 | Recursive GCD using binary (Stein's) algorithm |
| es2 | Find the majority element in an array using divide & conquer |
| es3 | Simple regular expression matching with `.` wildcard |
| es4 | Flight log with multi-key sorting (merge sort / insertion sort) |
| es5 | Flight log extended with quick sort variant |

### Lab05 — (Problem statement PDF only)

### Lab06 — Dynamic Memory and Backtracking
| Exercise | Description |
|----------|-------------|
| es1 | Friends & songs: find sets of songs known by all friends (backtracking) |
| es2 | Read a matrix with dynamic allocation; separate black/white elements |
| es3 | Flight log with dynamic allocation and full sort/filter command set |

### Lab07 — Dynamic Data Structures
| Exercise | Description |
|----------|-------------|
| es1 | Read a graph (edge list) from file using dynamic arrays of structs |
| es2 | Employee registry with dynamic linked list and CRUD operations |

### Lab08 — Backtracking
| Exercise | Description |
|----------|-------------|
| es1 | Gems/jewels selection with repetition via backtracking |
| es2 | Gems selection without repetition, constraint-based backtracking |
| es3 | RPG character + inventory management with equipment optimization |

### Lab09 — Backtracking and Combinatorial Problems
| Exercise | Description |
|----------|-------------|
| es1 | Activity selection problem solved with backtracking |
| es2 | Domino tile placement on a board (backtracking) |
| es3 | RPG character management with linked list and array-based inventory |

### Lab10 — Dynamic Programming
| Exercise | Description |
|----------|-------------|
| es1 | Activity selection with dynamic programming (memoization + merge sort) |
| es2 | Gems selection with 4D DP table |
| es3 | RPG management refactored with linked list for characters and array for inventory |

### Lab11 — Dynamic Programming and Greedy Algorithms
| Exercise | Description |
|----------|-------------|
| es1 | Gymnastics sequence composition via DP (subsequence with direction/difficulty constraints) |
| es2 | Same problem solved with a greedy approach (multiple ordering criteria) |

### Lab12 — Abstract Data Types (BST / Symbol Table)
| Exercise | Description |
|----------|-------------|
| es1 | Stock exchange simulator: read and query financial data using BST-backed ADTs for `Exchange`, `Index`, `Stock`, `Quote`, and `Date` |

### Lab13 — Graphs and Topological Sort
| Exercise | Description |
|----------|-------------|
| es1 | Directed graph with topological sort using a Symbol Table (ST) and adjacency-list Graph ADT |

---

## Theory Reference (`Teoria Scritto/`)

Compact, exam-ready implementations of core algorithms:

| File | Algorithms |
|------|-----------|
| `01_Iterativi_ordinamento_interno.c` | Insertion Sort, Exchange (Bubble) Sort, Selection Sort |
| `02_ricorsivi_ordinamento_interno.c` | Merge Sort, Quick Sort |
| `03_Heap&PQ.c` | Heapify, Heap Sort, Priority Queue operations |

---

## Past Exam Solutions (`Exams/`)

Solutions to official AP written exams. The suffix `_18pt` denotes the 18-point (ADT/data structure) portion of the exam.

| Exam | Topics |
|------|--------|
| AP_Exam012014 | Linked list, struct management |
| AP_Exam012015 | Array/matrix processing |
| AP_Exam012016 | Array problems |
| AP_Exam012016_18pt | Symbol Table (ST) ADT |
| AP_Exam012017 | Recursion / divide & conquer |
| AP_Exam012018 | Dynamic programming |
| AP_Exam012018_18pt | Symbol Table (ST) ADT |
| AP_Exam012019 | Backtracking |
| AP_Exam012019_18pt | Graph + Symbol Table ADTs |
| AP_Exam012021 | Mixed algorithms |
| AP_Exam012022 | Binary Tree ADT |
| AP_Exam022018 | Mixed algorithms |
| AP_Exam022022 | Mixed algorithms |
| AP_Exam032016 | Array processing |
| AP_Exam032017 | Recursion |
| AP_Exam032017_18pt | Symbol Table (ST) ADT |
| AP_Exam032018 | Dynamic programming |
| AP_Exam032019 | Backtracking |
| AP_Exam032021 | Linked list ADT |
| AP_Exam032022 | Mixed algorithms |
| AP_Exam032022_18pt | Graph + Symbol Table ADTs |
| AP_Exam042016 | Array processing |
| AP_Exam042017 | Recursion |
| AP_Exam042018 | Dynamic programming |
| AP_Exam042021 | Mixed algorithms |
| AP_Exam042022_18pt | Graph ADT |

---

## Additional Modules

| Folder | Description |
|--------|-------------|
| `AP_Algoritmi_e_Programmazione_in_Pratica/` | Standard Queue ADT implementation with `Item`, `Queue`, and a menu-driven driver |
| `AP_Ricorsione_e_Calcolo_Combinatorio/` | Recursive enumeration and combinatorics (restaurant menu, permutations) |
| `DalProblemaAlProgramma/` | Introductory exercises: variable swaps, array/matrix access, basic I/O |

---

## Building

Each exercise is a standalone C program. Compile with:

```bash
gcc -o program main.c -lm
```

For multi-file exercises (e.g. Lab12, Lab13):

```bash
gcc -o program main.c *.c -lm
```

> **Note:** Some exercises expect input files (e.g. `mat.txt`, `brani.txt`) to be present in the working directory. These are provided in each lab's `input files/` folder.
