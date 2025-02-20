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

ListNode *reverseBetween(ListNode *head, int left, int right) {
    // 因为头节点有可能发生变化，使用虚拟头节点可以避免复杂的分类讨论
    ListNode *dummyNode = new ListNode(-1);
    dummyNode->next = head;

    ListNode *pre = dummyNode;
    // 第 1 步：从虚拟头节点走 left - 1 步，来到 left 节点的前一个节点
    // 建议写在 for 循环里，语义清晰
    for (int i = 0; i < left - 1; i++) {
        pre = pre->next;
    }

    // 第 2 步：从 pre 再走 right - left + 1 步，来到 right 节点
    ListNode *rightNode = pre;
    for (int i = 0; i < right - left + 1; i++) {
        rightNode = rightNode->next;
    }

    // 第 3 步：切断出一个子链表（截取链表）
    ListNode *leftNode = pre->next;
    ListNode *curr = rightNode->next;

    // 注意：切断链接
    pre->next = nullptr;
    rightNode->next = nullptr;

    // 第 4 步：同第 206 题，反转链表的子区间
    reverseList(leftNode);

    // 第 5 步：接回到原来的链表中
    pre->next = rightNode;
    leftNode->next = curr;
    return dummyNode->next;
}

ListNode *reverseGroup(ListNode *head, int k) {
    int len = 0;
    ListNode *tmp = head;
    while (tmp != nullptr) {
        tmp = tmp->next;
        len++;
    }
    cout << len << endl;
    for (int i = 0; i < len / k * k; i+=k) {
        head = reverseBetween( head, i+1, i+k);
    }
    return head;
}

int main() {
    ListNode* head = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, nullptr)))));
    printList(head);
    //head = reverseBetween(head,1,3);
    head = reverseGroup(head, 2);
    printList(head);
    return 0;
}