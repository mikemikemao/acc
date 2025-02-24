//
// Created by maochaoqun on 2025/2/20.
//
#include <iostream>
#include <stack>
#include <vector>
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
//比较麻烦 淘汰
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    int len1 = 0, len2 = 0;
    int jinwei = 0;
    ListNode* p1 = l1;
    ListNode* p2 = l2;
    ListNode* revp1 = nullptr;
    ListNode* revp1p2 = nullptr;
    ListNode* p1Pre =nullptr;
    while (p1 != nullptr) {
        cout << p1 << endl;
        len1++;
        p1 = p1->next;
    }
    while (p2 != nullptr) {
        len2++;
        p2 = p2->next;
    }
    //反转
    revp1 = reverseList(l1);
    revp1p2 = reverseList(l2);
    p1 = revp1;

    p2 = revp1p2;
    printList(p1);
    printList(p2);

    //按第一个链表长度遍历
    int len = len1 <= len2 ? len1 :len2;
    for (int i = 0; i < len; i++) {
        p1->val = p1->val + p2->val + jinwei;
        if(p1->val >= 10) {
            jinwei = 1;
            p1->val -= 10;
        }else {
            jinwei = 0;
        }
        cout << p1->val << endl;
        p1Pre = p1;
        p1 = p1->next;
        p2 = p2->next;
    }
    cout << "p1:" << p1 << endl;
    printList(revp1);
    //补齐最后的操作
    if(len1 == len2) {
        if(jinwei == 1) {
            p1Pre->next = new ListNode(1,nullptr);
        }
    }
    printList(revp1);
    if(len1 < len2) {
        p1->next = p2->next;
        if(jinwei == 1) {
            p1->next->val += 1;
        }
    }
    return reverseList(revp1);
}

int main() {
    // ListNode* head1 = new ListNode(7, new ListNode(2, new ListNode(4, new ListNode(3,nullptr))));
    // ListNode* head2 = new ListNode(5, new ListNode(6, new ListNode(4, nullptr)));
    ListNode* head1 = new ListNode(4, new ListNode(4, new ListNode(3, nullptr)));
    ListNode* head2 = new ListNode(5, new ListNode(6, new ListNode(4, nullptr)));
    printList(head1);
    printList(head2);
    head1 = addTwoNumbers(head1, head2);
    printList(head1);
}