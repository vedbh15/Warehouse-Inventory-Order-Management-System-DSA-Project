#include <iostream>
#include <string>

#include "linkedlist.h"
#include "queue.h"
#include "stack.h"

using namespace std;

// Display the menu options
void displayMenu() {
    cout << "\n=== Warehouse Management System ===\n";
    cout << "1. Add Part to Inventory\n";
    cout << "2. Delete Part from Inventory\n";
    cout << "3. Search Part in Inventory\n";
    cout << "4. Display Inventory\n";
    cout << "5. Place Order\n";
    cout << "6. Process Next Order\n";
    cout << "7. Undo Last Order\n";
    cout << "8. Display Order Queue\n";
    cout << "9. Display Order History\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, qty;
                float price;
                string name;
                cout << "Enter Part ID: ";
                cin >> id;
                cout << "Enter Part Name: ";
                cin.ignore(); // clear newline
                getline(cin, name);
                cout << "Enter Quantity: ";
                cin >> qty;
                cout << "Enter Price: ";
                cin >> price;
                insertPart(id, name, qty, price);
                cout << "Part added successfully.\n";
                break;
            }
            case 2: {
                int id;
                cout << "Enter Part ID to delete: ";
                cin >> id;
                deletePart(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter Part ID to search: ";
                cin >> id;
                Node* found = searchPart(id);
                if (found != nullptr) {
                    cout << "Found - ID: " << found->id << " | Name: " << found->name 
                         << " | Qty: " << found->quantity << " | Price: $" << found->price << "\n";
                } else {
                    cout << "Part not found.\n";
                }
                break;
            }
            case 4:
                displayAll();
                break;
            case 5: {
                Order newOrder;
                cout << "Enter Order ID: ";
                cin >> newOrder.orderId;
                cout << "Enter Part ID: ";
                cin >> newOrder.partId;
                cout << "Enter Quantity Requested: ";
                cin >> newOrder.qtyRequested;
                enqueueOrder(newOrder);
                break;
            }
            case 6: {
                // INTEGRATION LOGIC: Process Next Order
                if (isEmpty()) {
                    cout << "Queue Underflow: No orders to process\n";
                    break;
                }

                Order o = dequeueOrder();
                cout << "Processing Order ID: " << o.orderId << "\n";
                
                // Search Linked List
                Node* part = searchPart(o.partId);
                if (part == nullptr) {
                    cout << "Error: Part ID " << o.partId << " not found in inventory. Order failed.\n";
                } else if (part->quantity < o.qtyRequested) {
                    cout << "Error: Insufficient stock for Part ID " << o.partId << ". Order failed.\n";
                } else {
                    // Reduce quantity
                    part->quantity -= o.qtyRequested;
                    cout << "Order fulfilled! Stock updated.\n";
                    
                    // Push to history stack
                    Action a = {o.orderId, o.partId, o.qtyRequested};
                    pushAction(a);
                }
                break;
            }
            case 7: {
                // INTEGRATION LOGIC: Undo Last Order
                if (isStackEmpty()) {
                    cout << "Stack Underflow: No action to undo\n";
                    break;
                }
                
                Action a = popAction();
                cout << "Undoing Order ID: " << a.orderId << "\n";
                
                // Restore quantity in Linked List
                Node* part = searchPart(a.partId);
                if (part != nullptr) {
                    part->quantity += a.qtyFulfilled;
                    cout << "Restored " << a.qtyFulfilled << " items of Part ID " << a.partId << " to inventory.\n";
                } else {
                    cout << "Error: Part ID " << a.partId << " no longer in inventory. Cannot restore stock.\n";
                }
                break;
            }
            case 8:
                displayQueue();
                break;
            case 9:
                displayStack();
                break;
            case 10:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}
