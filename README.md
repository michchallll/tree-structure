# ctree - Command Line Tree Structure Manager

A simple command-line application written in C++ for creating and managing hierarchical tree structures.

This project was originally created as a programming certification assignment. I decided to revisit it afterwards, clean up the code structure, add documentation, testing files, and prepare it as a standalone GitHub project.

## Features

The program allows users to build a tree structure using commands read from standard input (`stdin`) and prints results to standard output (`stdout`).

Implemented functionality:

- Create new nodes with unique identifiers
- Attach nodes into a hierarchical tree structure
- Maintain a single root node
- Prevent invalid tree states and cycles
- Print information about individual nodes
- Print complete tree structures
- Handle invalid commands and identifiers

## Tree Structure

Each node contains:

- Unique identifier (`id`)
- Reference to its parent node
- List of child nodes

The tree follows these rules:

- The structure contains at most one root node
- Every node except the root has exactly one parent
- A node can have any number of children
- Nodes without children are leaf nodes

Example:

```
-[root]
    -[a]
        -[aa]
        -[ab]
    -[b]
        -[ba]
        -[bb]
```

## Commands

### Create a node

```
create node <id>
```

Example:

```
create node root
create node child
```

Output:

```
New node root
New node child
```

---

### Attach a node

```
attach node <id> under <parent_id>
```

Example:

```
attach node child under root
```

Output:

```
Node child is child of node root
```

---

### Print node information

```
print node <id>
```

Example:

```
print node root
```

Output:

```
Node root with 2 children child1,child2
```

---

### Print root node

```
print root
```

Prints information about the current root node.

---

### Print tree

Print the whole tree:

```
print tree
```

or print a subtree:

```
print tree under <id>
```

Example output:

```
-[root]
    -[a]
        -[aa]
        -[ab]
    -[b]
```

## Project Structure

```
.
├── src
│   ├── main.cpp
│   ├── Node.h
│   ├── Tree.h
│   └── Tree.cpp
│
├── tests
│   ├── input
│   │   └── basic-tree-test.in
│   │
│   ├── expected
│   │   └── basic-tree-test.out
│   │
│   └── generated
│
├── scripts
│   └── treegen.sh
│
├── Makefile
└── README.md
```

## Building

The project uses a simple Makefile.

Compile the project:

```bash
make
```

The executable will be created:

```
build/ctree
```

Clean generated files:

```bash
make clean
```

Rebuild:

```bash
make rebuild
```

## Running

Run the program:

```bash
make run
```

By default, the program waits for commands from standard input.

Example:

```text
create node root
create node child
attach node child under root
print tree
```

Input can also be redirected from a file:

```bash
./build/ctree < tests/input/basic-tree-test.in
```

## Testing

A basic test case is included:

```bash
make test
```

The repository also contains a tree generator for creating larger input files:

```bash
make generate
```

Generated stress test:

```bash
make stress-test
```

## Implementation Details

The project is implemented in modern C++ using:

- `std::unordered_map` for fast node lookup by identifier
- `std::shared_ptr` for automatic memory management
- `std::weak_ptr` for non-owning parent references
- Recursive tree traversal for printing
- Command parsing using standard C++ streams

## License

This project is licensed under the MIT License.
