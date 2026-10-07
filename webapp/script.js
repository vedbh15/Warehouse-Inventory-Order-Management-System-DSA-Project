/* 
 * Warehouse Management System - JavaScript Simulation (Part 2)
 * This script mirrors the manual C++ implementation exactly for demonstration.
 */

// ==========================================
// 1. LINKED LIST (Parts Inventory)
// ==========================================
let head = null;

function insertPart(id, name, qty, price) {
    const newNode = { id, name, quantity: qty, price, next: null };
    if (head === null) {
        head = newNode;
        return;
    }
    let temp = head;
    while (temp.next !== null) {
        temp = temp.next;
    }
    temp.next = newNode;
}

function deletePart(id) {
    if (head === null) {
        alert("Inventory is empty, nothing to delete");
        return;
    }
    if (head.id === id) {
        head = head.next;
        return;
    }
    let temp = head;
    while (temp.next !== null && temp.next.id !== id) {
        temp = temp.next;
    }
    if (temp.next === null) {
        alert("Part with ID " + id + " not found.");
        return;
    }
    temp.next = temp.next.next;
}

function searchPart(id) {
    let temp = head;
    while (temp !== null) {
        if (temp.id === id) return temp;
        temp = temp.next;
    }
    return null;
}


// ==========================================
// 2. QUEUE (Order Processing)
// ==========================================
const MAX_SIZE = 20;
let orderQueue = new Array(MAX_SIZE);
let front = -1;
let rear = -1;

function isQueueFull() {
    return (rear === MAX_SIZE - 1);
}

function isQueueEmpty() {
    return (front === -1 || front > rear);
}

function enqueueOrder(orderId, partId, qtyRequested) {
    if (isQueueFull()) {
        alert("Queue Overflow: Order queue is full");
        return;
    }
    if (front === -1) {
        front = 0;
    }
    rear++;
    orderQueue[rear] = { orderId, partId, qtyRequested };
}

function dequeueOrder() {
    if (isQueueEmpty()) {
        alert("Queue Underflow: No orders to process");
        return null;
    }
    let temp = orderQueue[front];
    front++;
    if (front > rear) {
        front = -1;
        rear = -1;
    }
    return temp;
}


// ==========================================
// 3. STACK (Order History / Undo)
// ==========================================
const STACK_MAX = 20;
let historyStack = new Array(STACK_MAX);
let topIndex = -1;

function isStackFull() {
    return (topIndex === STACK_MAX - 1);
}

function isStackEmpty() {
    return (topIndex === -1);
}

function pushAction(orderId, partId, qtyFulfilled) {
    if (isStackFull()) {
        alert("Stack Overflow: History is full");
        return;
    }
    topIndex++;
    historyStack[topIndex] = { orderId, partId, qtyFulfilled };
}

function popAction() {
    if (isStackEmpty()) {
        alert("Stack Underflow: No action to undo");
        return null;
    }
    let temp = historyStack[topIndex];
    topIndex--;
    return temp;
}



// ==========================================
// UI INTEGRATION LOGIC & RENDERERS
// ==========================================

function renderInventory() {
    const container = document.getElementById("inventory-list");
    container.innerHTML = "";
    if (head === null) {
        container.innerHTML = "<p>Inventory is empty.</p>";
        return;
    }
    let temp = head;
    let html = "<ul>";
    while (temp !== null) {
        html += `<li>ID: ${temp.id} | Name: ${temp.name} | Qty: ${temp.quantity} | Price: $${temp.price}</li>`;
        temp = temp.next;
    }
    html += "</ul>";
    container.innerHTML = html;
}

function renderQueue() {
    const container = document.getElementById("order-queue");
    container.innerHTML = "";
    if (isQueueEmpty()) {
        container.innerHTML = "<p>Order queue is empty.</p>";
        return;
    }
    let html = "<ol>";
    for (let i = front; i <= rear; i++) {
        html += `<li>Order ID: ${orderQueue[i].orderId} | Part ID: ${orderQueue[i].partId} | Qty: ${orderQueue[i].qtyRequested}</li>`;
    }
    html += "</ol>";
    container.innerHTML = html;
}

function renderStack() {
    const container = document.getElementById("history-stack");
    container.innerHTML = "";
    if (isStackEmpty()) {
        container.innerHTML = "<p>History stack is empty.</p>";
        return;
    }
    let html = "<ul>";
    for (let i = topIndex; i >= 0; i--) {
        html += `<li>Order ID: ${historyStack[i].orderId} | Part ID: ${historyStack[i].partId} | Qty: ${historyStack[i].qtyFulfilled}</li>`;
    }
    html += "</ul>";
    container.innerHTML = html;
}

function renderAll() {
    renderInventory();
    renderQueue();
    renderStack();
}

// UI Handlers
function uiAddPart() {
    let id = parseInt(document.getElementById("part-id").value);
    let name = document.getElementById("part-name").value;
    let qty = parseInt(document.getElementById("part-qty").value);
    let price = parseFloat(document.getElementById("part-price").value);
    
    if (isNaN(id) || !name || isNaN(qty) || isNaN(price)) {
        alert("Please fill all part fields correctly.");
        return;
    }
    insertPart(id, name, qty, price);
    renderAll();
}

function uiDeletePart() {
    let id = parseInt(document.getElementById("del-part-id").value);
    if (isNaN(id)) {
        alert("Please enter a valid Part ID to delete.");
        return;
    }
    deletePart(id);
    renderAll();
}

function uiPlaceOrder() {
    let id = parseInt(document.getElementById("order-id").value);
    let partId = parseInt(document.getElementById("order-part-id").value);
    let qty = parseInt(document.getElementById("order-qty").value);
    
    if (isNaN(id) || isNaN(partId) || isNaN(qty)) {
        alert("Please fill all order fields correctly.");
        return;
    }
    enqueueOrder(id, partId, qty);
    renderAll();
}

function uiProcessOrder() {
    // INTEGRATION LOGIC: Process Next Order
    let o = dequeueOrder();
    if (!o) return; // Underflow occurred
    
    let part = searchPart(o.partId);
    if (!part) {
        alert("Error: Part ID " + o.partId + " not found in inventory. Order failed.");
        renderAll();
        return;
    }
    if (part.quantity < o.qtyRequested) {
        alert("Error: Insufficient stock for Part ID " + o.partId + ". Order failed.");
        renderAll();
        return;
    }
    
    // Reduce quantity
    part.quantity -= o.qtyRequested;
    
    // Push to history stack
    pushAction(o.orderId, o.partId, o.qtyRequested);
    
    
    renderAll();
}

function uiUndoOrder() {
    // INTEGRATION LOGIC: Undo Last Order
    let a = popAction();
    if (!a) return; // Underflow occurred
    
    let part = searchPart(a.partId);
    if (part) {
        part.quantity += a.qtyFulfilled;
    } else {
        alert("Error: Part ID " + a.partId + " no longer in inventory. Cannot restore stock.");
    }
    renderAll();
}



// Initialize rendering on load
window.onload = function() {
    // Populate some initial dummy data to demonstrate functionality
    insertPart(101, "Gearbox", 50, 120.00);
    insertPart(102, "Bearing", 200, 15.50);
    insertPart(103, "Axle", 30, 45.00);
    renderAll();
};
