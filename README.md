# In-Memory File Indexing & Search Engine (SDA)

An in-memory file indexing and retrieval system implemented in C. The system processes file metadata, keywords, and search queries using advanced hierarchical data structures and priority queues.

## Key Features & Data Structures
- **Multi-Way Retrieval Tree (Trie):** Indexes file keywords character-by-character. Supports exact keyword lookups (`FIND`), prefix autocomplete searches (`PREFIX` bonus), and automated recursive pruning of dead nodes upon keyword deletion (`DELKW`).
- **Max-Heap Priority Queue:** Implements relevance ranking for `TOPK` queries, sorting files by relevance score (descending) with lexicographical tie-breaking by file ID.
- **Doubly Linked List:** Manages the primary collection of files, supporting efficient insertion (`ADD`) and complete metadata clean-up (`DEL`).
- **Memory Safety:** Designed with strict manual memory allocation and zero memory leaks, validated via **Valgrind**.

## Tech Stack
- **Language:** C
- **Tools:** GCC, Make, Valgrind, Linux (WSL)
- **Core Algorithms:** Trie Traversal, Max-Heapify, Subtree DFS for Prefix Matching, Recursive Pruning.

## Build & Run
To compile the project, run:
make build