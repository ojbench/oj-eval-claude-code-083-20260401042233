#include <iostream>
using namespace std;

// Node structure for circular singly linked list
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Circular singly linked list class
class CircularLinkedList {
private:
    Node* head;
    int size;

public:
    CircularLinkedList() : head(nullptr), size(0) {}

    ~CircularLinkedList() {
        if (head == nullptr) return;

        Node* current = head;
        Node* nextNode;

        // Break the circular link first
        Node* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        tail->next = nullptr;

        // Now delete all nodes
        while (current != nullptr) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // Build circular linked list with n nodes (1 to n)
    void build(int n) {
        if (n <= 0) return;

        head = new Node(1);
        Node* current = head;

        for (int i = 2; i <= n; i++) {
            current->next = new Node(i);
            current = current->next;
        }

        // Make it circular
        current->next = head;
        size = n;
    }

    // Simulate Josephus problem
    void josephus(int m) {
        if (head == nullptr || m <= 0) return;

        Node* current = head;
        Node* prev = nullptr;

        // Find the last node (will be prev for the first deletion)
        Node* tail = head;
        while (tail->next != head) {
            tail = tail->next;
        }
        prev = tail;

        while (size > 0) {
            // Count m-1 steps (because we count the current node as 1)
            for (int i = 1; i < m; i++) {
                prev = current;
                current = current->next;
            }

            // Output the node to be deleted
            cout << current->data << endl;

            // Delete the current node
            Node* toDelete = current;

            if (size == 1) {
                // Last node
                head = nullptr;
            } else {
                // Move to next node
                prev->next = current->next;
                current = current->next;

                // If we deleted the head, update head
                if (toDelete == head) {
                    head = current;
                }
            }

            delete toDelete;
            size--;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    CircularLinkedList list;
    list.build(n);
    list.josephus(m);

    return 0;
}
