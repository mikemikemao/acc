//
// Created by maochaoqun on 2025/2/17.
//

#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {
    }

    ListNode(int x) : val(x), next(nullptr) {
    }

    ListNode(int x, ListNode *next) : val(x), next(next) {
    }
};
void printList(ListNode* head) {
    while (head != nullptr) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}


ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    while (head) {
        ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* leftNode = nullptr;
    ListNode* rightNode = nullptr;
    for (int i = 0; i < left; i++) {
        head = head->next;
    }
    leftNode = head;
    for (int i = 0; i < right; i++) {
        head = head->next;
    }
    rightNode = head;
    ListNode* prev = rightNode;
    while (leftNode) {
        ListNode* next = leftNode->next;
        leftNode->next = prev;
        prev = leftNode;
        leftNode = next;
    }
    return prev;
}

int main() {
    ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, nullptr)))));
    printList(head);
    head = reverseBetween(head,2,4);
    printList(head);
    return 0;
}