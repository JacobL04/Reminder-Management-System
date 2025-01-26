#include "linked_list.h"

struct Node *head = NULL;

void insert_to_calendar(int day, const char *value){ // Insert reminders into calendar node
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->day = day;
    strncpy(node->reminder_str, value, MAX_STR_LEN);
    node->reminder_str[MAX_STR_LEN - 1] = '\0';
    node->next = head; // Insert to the start
    head = node;
}

void remove_from_calendar(int day, int index){ // Removes reminders from calendar node
    if(head == NULL){
        printf("No reminders to remove\n");
        return;
    }

    struct Node *currNode = head;
    struct Node *prevNode = NULL;
    int reminderIdx = 1;

    while(currNode != NULL){ // Traversing list to find reminder at the specified day and index
        if(currNode->day == day){
            if(reminderIdx == index){ // Finds a reminder for the specific day
                if(prevNode == NULL){ // Deletes first node of the list
                    head = currNode->next;
                }
                
                else {
                    prevNode->next = currNode->next;
                }

                free(currNode); // Freeing memory from reminder node
                return;
            }
            reminderIdx++;
        }

        prevNode = currNode;
        currNode = currNode->next;
    }

    printf("Reminder index %d on day %d was not found\n", index, day); // Reminder not found
}

void save_reminders(const char *filename){ // Save reminders to file
    FILE *file;
    file = fopen(filename, "w");

    if(!file){
        printf("Error, couldn't save file!\n");
        return;
    }

    struct Node *currNode = head;
    while(currNode){
        fprintf(file, "%d %s\n", currNode->day, currNode->reminder_str);
        currNode = currNode->next;
    }

    fclose(file);
}

void load_reminders(const char *filename){ // Load reminders from file
    FILE *file;
    file = fopen(filename, "r");

    if(!file){
        printf("Error, couldn't load file!\n");
        return;
    }

    int day;
    char reminder_str[MAX_STR_LEN];
    while(fscanf(file, "%d %99[^\n]\n", &day, reminder_str) == 2) {
        insert_to_calendar(day, reminder_str);
    }
    
    fclose(file);

    // Reverses the nodes to keep the reminders.txt files in orders
    struct Node *prev = NULL, *curr = head, *next = NULL;
    while(curr){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}