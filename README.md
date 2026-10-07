# Warehouse-Inventory-Order-Management-System-DSA-Project
This is a college minor-project for Data Structures & Algorithms (DSA), building a warehouse management system using plain C++ arrays and pointers (no STL containers).

## Part 1: Core ADT Implementations

The foundational data structures are built from scratch:
- **Parts Inventory (Linked List)**: A singly linked list to store warehouse parts.
- **Order Processing (Queue)**: A fixed-size array-based queue to handle incoming orders.
- **Order History (Stack)**: A fixed-size array-based stack for keeping track of processed orders for an undo feature.

## Part 2: Full Integration & Webapp Simulation

The final version (Part 2) integrates these structures together into a cohesive system:
- Placing an order places it in the Order Queue.
- Processing an order checks the inventory linked list, deducts stock, pushes the fulfillment record onto the Order History Stack, and adds a waypoint to the Robot Route Queue.
- Undoing an order pops the latest fulfillment from the Stack and restores the stock to the inventory linked list.

### Compiling and Running C++ Version
Ensure you have `g++` installed. From the `cpp` directory, run:
```bash
g++ main.cpp -o warehouse
./warehouse
```

### Webapp Simulation
A static webapp (HTML/CSS/vanilla JS) is provided in the `/webapp` directory. It perfectly mirrors the C++ logic using basic JavaScript arrays and objects. 
To run it, simply open `/webapp/index.html` in your web browser. There is no server or build process required.
