#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

using namespace std;

#define MAX_SIZE 20

// Order structure
struct Order {
  int orderId;
  int partId;
  int qtyRequested;
};

// Global Array-based Queue
Order orderQueue[MAX_SIZE];
int front = -1;
int rear = -1;

// Check if the queue is full
bool isFull() { return (rear == MAX_SIZE - 1); }

// Check if the queue is empty
bool isEmpty() { return (front == -1 || front > rear); }

// Add an order to the rear of the queue
void enqueueOrder(Order order) {
  if (isFull()) {
    cout << "Queue Overflow: Order queue is full\n";
    return;
  }
  if (front == -1) {
    front = 0;
  }
  rear++;
  orderQueue[rear] = order;
  cout << "Order added to queue.\n";
}

// Remove and return an order from the front of the queue
Order dequeueOrder() {
  Order emptyOrder = {-1, -1, -1}; // Return this if empty

  if (isEmpty()) {
    cout << "Queue Underflow: No orders to process\n";
    return emptyOrder;
  }

  Order temp = orderQueue[front];
  front++;

  // Reset queue if all items are dequeued
  if (front > rear) {
    front = -1;
    rear = -1;
  }

  return temp;
}

// View the order at the front without removing it
Order peekFront() {
  Order emptyOrder = {-1, -1, -1};
  if (isEmpty()) {
    cout << "Queue is empty.\n";
    return emptyOrder;
  }
  return orderQueue[front];
}

// Display all orders in the queue
void displayQueue() {
  if (isEmpty()) {
    cout << "Order queue is empty.\n";
    return;
  }
  cout << "\n--- Order Processing Line ---\n";
  for (int i = front; i <= rear; i++) {
    cout << "Order ID: " << orderQueue[i].orderId
         << " | Part ID: " << orderQueue[i].partId
         << " | Qty: " << orderQueue[i].qtyRequested << "\n";
  }
  cout << "-----------------------------\n";
}

#endif
