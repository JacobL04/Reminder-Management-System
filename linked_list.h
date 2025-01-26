#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_STR_LEN 100
#define REMINDER_FILE "reminders.txt"

struct Node{
    int day;
    char reminder_str[MAX_STR_LEN];
    struct Node *next;
};

extern struct Node *head;

void insert_to_calendar(int day, const char *value);
void remove_from_calendar(int day, int index);
void save_reminders(const char *filename);
void load_reminders(const char *filename);

#endif