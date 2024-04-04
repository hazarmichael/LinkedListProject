#include <stdio.h>
#include <stdlib.h>

struct node {
    int number; //To holdd the digits of the number 
    int sign; // -1 for negative, 1 for positive 
    struct node *prev;
    struct node *next;
};


struct node *createNode(int number, int sign) { // this function creates the new node 
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->number = number;
    newNode->sign = sign;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
struct node *read_number(FILE *fp) {
    struct node *head = NULL;
    struct node *tail = NULL;
    int sign = 1;  // the default sign is positive


    char c;
    while ((c = fgetc(fp)) != '\n' && c != EOF) {

        if (c == '-') {
            sign = -1;
            continue;  // skip to the next character
        }

        int digit = c - '0'; // convert character to integer digit
        struct node *new_node = malloc(sizeof(struct node));
        new_node->number = digit;
        new_node->sign = sign;
        new_node->prev = tail;
        new_node->next = NULL;
        if (tail == NULL) { // to see if the list is empty 
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node; // Set the next pointer of the current tail to the new node
            tail = new_node;  // Update the tail pointer to the new node
        }
    }
    return head;
}

void print_number(struct node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
   
   
    if (head->sign == -1) { // will print the negative sign if the number is negative 
        printf("-");
    }
    while (head != NULL) { // print the digits of the number 
        printf("%d", head->number);
        head = head->next;
    }
    printf("\n"); 
}


struct node *copyList(struct node *head) { /*this function is used to create a copy of a linked list, 
                                            to make sure the original linked lists are not changed */
    struct node *newHead = NULL; // head and tail pointers 
    struct node *newTail = NULL;


    while (head != NULL) { // to create a new node for each element
     
     // the following lines are to create the node 
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        newNode->number = head->number; // Copy the number from the original node 
        newNode->sign = head->sign;  // Copy the sign from the original node
        newNode->prev = NULL;
        newNode->next = NULL;

        if (newHead == NULL) { // make the new node as the head and tail
            newHead = newNode;
            newTail = newNode;
        } else {
            newTail->next = newNode;
            newNode->prev = newTail; // Set the previous pointer of the new node to the current tail
            newTail = newNode;
        }

 
        head = head->next; // Move to the next node in the original list
    }
    return newHead; // return the copied list. 
}


struct node * reverseList(struct node * head) { // this function to reverse the order of the doubly linked list
    struct node *prev = NULL;
    struct node *original = head;
    while (original != NULL) {
        struct node *next = original->next; // to store the next node

        original->next = prev; //to reverse the next and previous pointers of the original node
        original->prev = next;

        prev = original;
        original = next;
    }
    return prev; // return a pointer to the reversed list
}

void print_result_to_file(struct node *result, FILE *fout) { //to print the results to the output file when needed 

    // Print the digits of the number
    while (result != NULL) {
        fprintf(fout, "%d", result->number);
        result = result->next;
    }

    fprintf(fout, "\n");
}

struct node* addTwoNumbers(struct node* l1, struct node* l2) {
    // create copies of the input lists to make sure the original lists are not modified
    struct node* tempL1 = copyList(l1);
    struct node* tempL2 = copyList(l2);

    // reverse the temporary lists because addition starts with the last node 
    tempL1 = reverseList(tempL1);
    tempL2 = reverseList(tempL2);

   
    int carry = 0; // to hold the carry 
    struct node* head = NULL;
    struct node* tail = NULL;


    while (tempL1 != NULL || tempL2 != NULL || carry != 0) {    // iterate over both lists

        // Calculate the sum of the current nodes and the carry
        int sum = carry;
        if (tempL1 != NULL) {
            sum += tempL1->number;
            tempL1 = tempL1->next;
        }
        if (tempL2 != NULL) {
            sum += tempL2->number;
            tempL2 = tempL2->next;
        }

        // calculate the new carry and digit
        carry = sum / 10;
        int digit = sum % 10;

        // create a new node with the digit we obtained 
        struct node* node = (struct node*)malloc(sizeof(struct node));
        node->number = digit;
        node->prev = tail;
        node->next = NULL;

        // append the new node to the list
        if (head == NULL) {
            head = node;
        }
        if (tail != NULL) {
            tail->next = node;
        }
        tail = node;
    }

    head = reverseList(head); // to print the result in the right direction 

    return head;
}


int getLength(struct node *head) { // I wrote this function to do the signs but i didn't reach because of the time 
    int length = 0; // to determine which linked list is taller
    struct node *list = head;

    while (list != NULL) {
        length++;
        list = list->next;
    }
    return length;
}

struct node* subtractTwoLists(struct node* l1, struct node* l2) {
    // Create copies of the input lists
    struct node* copiedL1 = copyList(l1);
    struct node* copiedL2 = copyList(l2);

    // Reverse the copied lists
    struct node* reversedL1 = reverseList(copiedL1);
    struct node* reversedL2 = reverseList(copiedL2);

    // Initialize variables
    int borrow = 0;
    struct node* head = NULL;
    struct node* tail = NULL;

    // Iterate over both lists
    while (reversedL1 != NULL || reversedL2 != NULL) {
        // Calculate the difference of the current nodes and the borrow
        int diff = borrow;
        if (reversedL1 != NULL) {
            diff += reversedL1->number;
            reversedL1 = reversedL1->next;
        }
        if (reversedL2 != NULL) {
            diff -= reversedL2->number;
            reversedL2 = reversedL2->next;
        }

        // Calculate the new borrow and digit
        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        // Create a new node with the digit
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->number = diff;
        newNode->prev = tail;
        newNode->next = NULL;

        // Append the new node to the list
        if (head == NULL) {
            head = newNode;
        }
        if (tail != NULL) {
            tail->next = newNode;
        }
        tail = newNode;
    }

    // Reverse the result list
    head = reverseList(head);


    return head;
}

struct node* multiplyTwoLists(struct node* first, struct node* second) {
    long long N = 1000000007;
    long long num1 = 0, num2 = 0, product = 0;
    struct node* result = NULL;




    // Create copies of the input lists
    struct node* tempFirst = copyList(first);
    struct node* tempSecond = copyList(second);




    while (tempFirst || tempSecond) {
        if (tempFirst) {
            num1 = ((num1)*10) % N + tempFirst->number;
            tempFirst = tempFirst->next;
        }
 
        if (tempSecond) {
            num2 = ((num2)*10) % N + tempSecond->number;
            tempSecond = tempSecond->next;
        }
    }
    product = ((num1 % N) * (num2 % N)) % N;
    // Create a new node for each digit in the product
    while (product > 0) {
        int digit = product % 10;
        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        newNode->number = digit;
        newNode->next = result;
        result = newNode;
        product /= 10;
    }

    // If the product is zero, create a single node with value zero
    if (!result) {
        struct node* newNode = (struct node*) malloc(sizeof(struct node));
        newNode->number = 0;
        newNode->next = NULL;
        result = newNode;
    }

    return result;
}

struct node* divideTwoNumbers(struct node* dividend, struct node* divisor) {

 if (divisor == NULL || divisor->number == 0) {
        printf("Error: Division by zero\n");
        return NULL;
}
}

int main() {

    struct node *result_of_adding  = (struct node*) malloc(sizeof(struct node));
    struct node *result_of_subtraction = (struct node*) malloc(sizeof(struct node));
    struct node *result_of_multiplication= (struct node*) malloc(sizeof(struct node));
    struct node *result_of_division = (struct node*) malloc(sizeof(struct node));
    
     FILE *fp = fopen("input.txt", "r");
         if (fp == NULL) {
        fprintf(stderr, "Failed to open input file\n");
        return 1;
        }   
    
    struct node *num1 = read_number(fp);
    struct node *num2 = read_number(fp);

    fclose(fp);
    result_of_adding -> next = NULL;
    result_of_subtraction -> next = NULL;
    result_of_multiplication -> next = NULL;
    result_of_division -> next = NULL;  

     int operation = 0;
    char out;
    int flag = 0; 

    while (operation != 6) {
        printf(">>>> Menu <<<<\nWhich operation would you like to perform on these numbers?\n");
        printf("\n1.Read from file.\n2. Addition.\n3. Subtraction.\n4. Multiplication.\n5. Division.\n6. Exit\n");
        printf("\nPlease provide the number of the operation:\n");
        scanf("%d", &operation);

        if (operation == 1){   
            printf("Number 1: ");
            print_number(num1);

             printf("Number 2: ");   
             print_number(num2);
            flag = 1; // this flag is for the reading from a file, no operation will work unstil reading the numbers from the file 
        }


        else if (operation == 2) {

            if(flag == 0){
                printf("You have to read numbers from file first.\n");
            }
             else {
           
            printf("would you like to print the result to the input file? y = yes, anything else = no \n");
            scanf("%s", &out );
            if (out == 'y'){
            FILE *fout = fopen("output.txt", "a");
            result_of_adding = addTwoNumbers(num1,num2); 
            printf("Result of ADDITION these two linked lists is displayed now in the output.txt file.\n\n");
            print_result_to_file(result_of_adding, fout);
            fclose(fout);
            }
            result_of_adding = NULL;
        }

        } else if (operation == 3) {

            if(flag == 0){
                printf("You have to read numbers from file first.\n");
            }
             else {

            printf("would you like to print the result to the output file? y = yes, anything else = no \n");
            scanf("%s", &out );
            if (out == 'y'){
            FILE *fout = fopen("output.txt", "a");
            result_of_subtraction = subtractTwoLists(num1, num2);
            printf("Result of SUBTRACTING linked list 2 from linekd list 1 is displayed now in the output.txt file.\n\n");
            print_result_to_file(result_of_subtraction, fout);
             fclose(fout);
            }
            result_of_subtraction = NULL;

        }
        }

         else if (operation == 4) {
             if(flag == 0){
                printf("You have to read numbers from file first.\n");
            }
             else {
            printf("would you like to print the result to the output file? y = yes, anything else = no \n");
            scanf("%s", &out );
            if (out == 'y'){
            FILE *fout = fopen("output.txt", "a");
            result_of_multiplication = multiplyTwoLists(num1,num2);
            printf("Result of MULTIPLICATION these two linked lists is displayed now in the output.txt file.\n\n");
            print_result_to_file(result_of_multiplication, fout);
             fclose(fout);


            }

        }
            result_of_multiplication = NULL;
    }
    else if (operation == 5 ){
         if(flag == 0){
                printf("You have to read numbers from file first.\n");
            }
            else {
           printf("would you like to print the result to the output file? y = yes, anything else = no \n");
            scanf("%s", &out );
            if (out == 'y'){
            FILE *fout = fopen("output.txt", "a");
            result_of_division = divideTwoNumbers(num1,num2);
            printf("Result of DIVISION these two linked lists is displayed now in the output.txt file.\n\n");
            print_result_to_file(result_of_division, fout);
             fclose(fout);


            }
        }

            result_of_multiplication = NULL;

    }

    else if (operation != 1 && operation != 2 && operation != 3 &&operation != 4 && operation != 5 && operation != 6 ) {
        printf("Invalid operator, please try again.\n");
    }


    }

    if(operation==6)
     printf("Program exit, Thank you for using. \n");


    return 0;
   
}