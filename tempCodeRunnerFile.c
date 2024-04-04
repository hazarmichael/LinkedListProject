#include <stdio.h>
#include <stdlib.h>

struct node {
    int number;
    int sign;
    struct node *prev;
    struct node *next;
};
struct node *read_number(FILE *fp) {
    struct node *head = NULL;
    struct node *tail = NULL;
    int sign = 1;  // default sign is positive

    char c;
    while ((c = fgetc(fp)) != '\n' && c != EOF) {
        if (c == '-') {
            sign = -1;
            continue;  // skip to next character
        } else if (c == '+') {
            sign = 1;
            continue;  // skip to next character
        }

        int digit = c - '0'; // convert character to integer digit
        struct node *new_node = malloc(sizeof(struct node));
        new_node->number = digit;
        new_node->sign = sign;
        new_node->prev = tail;
        new_node->next = NULL;
        if (tail == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return head;
}

void print_number(struct node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
   
    // print the sign if the number is negative
    if (head->sign == -1) {
        printf("-");
    }
    // print the digits of the number
    while (head != NULL) {
        printf("%d", head->number);
        head = head->next;
    }
    printf("\n");
}


// Reverse a linked list
struct node * reverseList(struct node * head) {
    struct node *prev = NULL;
    struct node *curr = head;
    while (curr != NULL) {
        struct node *next = curr->next;
        curr->next = prev;
        curr->prev = next;
        prev = curr;
        curr = next;
    }
    return prev;
}

// Add two numbers represented as linked lists
struct node *addTwoNumbers(struct node *l1, struct node *l2) {
    // Reverse the input lists
    l1 = reverseList(l1);
    l2 = reverseList(l2);

    // Initialize variables
    int carry = 0;
   struct node *head = NULL;
   struct node *tail = NULL;

    // Iterate over both lists
    while (l1 != NULL || l2 != NULL || carry != 0) {
        // Calculate the sum of the current nodes and the carry
        int sum = carry;
        if (l1 != NULL) {
            sum += l1->number;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->number;
            l2 = l2->next;
        }
        
        // Calculate the new carry and digit
        carry = sum / 10;
        int digit = sum % 10;
        
        // Create a new node with the digit
        struct node *node = (struct node *)malloc(sizeof(struct node *));
        node->number = digit;
        node->prev = tail;
        node->next = NULL;
        
        // Append the new node to the list
        if (head == NULL) {
            head = node;
        }
        if (tail != NULL) {
            tail->next = node;
        }
        tail = node;
    }
    
    // Reverse the result list
    head = reverseList(head);

    // Return the head of the new list
    return head;
}


int main() {

    int operation;
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open input file\n");
        return 1;
    }

    struct node *num1 = read_number(fp);
    struct node *num2 = read_number(fp);
    struct node *res = NULL; 

    fclose(fp);

    printf("Number 1: ");
    print_number(num1);

    printf("Number 2: ");
    print_number(num2);
    printf("Result: ");
    res = addTwoNumbers(num1,num2);
    print_number(res);
   
    return 0;
}
