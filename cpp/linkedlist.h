#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

using namespace std;

// Node structure to store a part in inventory
struct Node {
    int id;
    string name;
    int quantity;
    float price;
    Node* next;
};

// Global head pointer for the linked list
Node* head = nullptr;

// Insert a new part at the end of the list
void insertPart(int id, string name, int quantity, float price) {
    Node* newNode = new Node();
    newNode->id = id;
    newNode->name = name;
    newNode->quantity = quantity;
    newNode->price = price;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// Delete a part by its ID
void deletePart(int id) {
    if (head == nullptr) {
        cout << "Inventory is empty, nothing to delete\n";
        return;
    }

    // If head node is the one to delete
    if (head->id == id) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Part deleted successfully.\n";
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr && temp->next->id != id) {
        temp = temp->next;
    }

    if (temp->next == nullptr) {
        cout << "Part with ID " << id << " not found.\n";
        return;
    }

    Node* nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
    cout << "Part deleted successfully.\n";
}

// Search for a part by its ID and return the pointer
Node* searchPart(int id) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Update the quantity of an existing part
void updateQuantity(int id, int qty) {
    Node* part = searchPart(id);
    if (part != nullptr) {
        part->quantity = qty;
        cout << "Quantity updated successfully.\n";
    } else {
        cout << "Part with ID " << id << " not found.\n";
    }
}

// Display all parts in the inventory
void displayAll() {
    if (head == nullptr) {
        cout << "Inventory is empty.\n";
        return;
    }
    
    Node* temp = head;
    cout << "\n--- Parts Inventory ---\n";
    while (temp != nullptr) {
        cout << "ID: " << temp->id 
             << " | Name: " << temp->name 
             << " | Qty: " << temp->quantity 
             << " | Price: $" << temp->price << "\n";
        temp = temp->next;
    }
    cout << "-----------------------\n";
}

#endif
