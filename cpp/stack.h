#ifndef STACK_H
#define STACK_H

#include <iostream>

using namespace std;

// Assuming MAX_SIZE is 20 for history stack as well
#define STACK_MAX 20

// We reuse the Order struct for stack history, keeping track of what was fulfilled
// Struct definition is in queue.h, so we will include it in main.cpp before stack.h, 
// or define a lightweight Action struct here. Let's define an Action struct for clarity.
struct Action {
    int orderId;
    int partId;
    int qtyFulfilled;
};

// Global Array-based Stack
Action historyStack[STACK_MAX];
int topIndex = -1;

// Check if stack is full
bool isStackFull() {
    return (topIndex == STACK_MAX - 1);
}

// Check if stack is empty
bool isStackEmpty() {
    return (topIndex == -1);
}

// Push an action onto the history stack
void pushAction(Action action) {
    if (isStackFull()) {
        cout << "Stack Overflow: History is full\n";
        return;
    }
    topIndex++;
    historyStack[topIndex] = action;
}

// Pop an action from the history stack to undo it
Action popAction() {
    Action emptyAction = {-1, -1, -1}; // Return if empty
    
    if (isStackEmpty()) {
        cout << "Stack Underflow: No action to undo\n";
        return emptyAction;
    }
    
    Action temp = historyStack[topIndex];
    topIndex--;
    return temp;
}

// View the top action on the stack without removing it
Action peekTop() {
    Action emptyAction = {-1, -1, -1};
    if (isStackEmpty()) {
        cout << "Stack is empty.\n";
        return emptyAction;
    }
    return historyStack[topIndex];
}

// Display all actions in the history stack
void displayStack() {
    if (isStackEmpty()) {
        cout << "History stack is empty.\n";
        return;
    }
    
    cout << "\n--- Order History (Top to Bottom) ---\n";
    for (int i = topIndex; i >= 0; i--) {
        cout << "Order ID: " << historyStack[i].orderId 
             << " | Part ID: " << historyStack[i].partId 
             << " | Qty: " << historyStack[i].qtyFulfilled << "\n";
    }
    cout << "-------------------------------------\n";
}

#endif
