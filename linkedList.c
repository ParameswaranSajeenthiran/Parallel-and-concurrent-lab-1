//
// Created by sajeenthiran on 2025-08-31.
//

#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>

struct Node
{
    int  data;
    struct Node* next;

};

int Member(int value, struct Node* head)
{
    struct Node* current = head;
    // printf("Searching for value: %d\n", value);
    while (current != NULL && current->data < value) {
        // printf("Visiting node with value: %d\n", current->data);
        current = current->next;
    }
    if (current == NULL || current->data > value) {
        // printf("Value %d not found in list.\n", value);
        return 0;
    }
    // printf("Value %d found in list.\n", value);
    return 1;
}

int Insert(int value, struct Node** head)
{
    struct Node* current = *head;
    struct Node* previous = NULL;
    struct Node* temp = NULL;

    // printf("Attempting to insert value: %d\n", value);

    while (current != NULL && current->data < value)
    {
        // printf("Visiting node with value: %d\n", current->data);
        previous = current;
        current = current->next;
    }

    if (current == NULL || current->data > value)
    {
        temp = (struct Node*) malloc(sizeof(struct Node));
        temp->data = value;
        temp->next = current;

        if (previous == NULL)
        {
            // printf("Inserting at head.\n");
            *head = temp;
        }
        else
        {
            // printf("Inserting after node with value: %d\n", previous->data);
            previous->next = temp;
        }
        // printf("Value %d inserted successfully.\n", value);
        return 1;
    }
    // printf("Value %d already exists. Insert failed.\n", value);
    return 0;
}
int Delete (int value , struct Node** head )
{
    struct  Node *current = *head ;
    struct Node* previous = NULL;
    while (current != NULL && current->data < value)
    {
        previous = current;
        current = current->next;
    }
    if (current != NULL && current->data == value)
    {
        if (previous == NULL) // Deleting the head node
        {
            *head = current->next;
            free(current);
            return 1;
        }
        previous->next = current->next;
        free(current);
        return 1;
    }
    // value not found
    return 0;

}

