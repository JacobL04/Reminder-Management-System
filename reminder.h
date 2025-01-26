#ifndef REMINDER_H
#define REMINDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_STR_LEN 100

struct Month{
	int numDays;
	int startingDay;
    char reminder_str[31][MAX_STR_LEN]; 
    int months;
    int month_idx;
};

extern struct Month currentMonth;

void insert_to_calendar(int day, const char* value);
void initializeMonth();
void printCalendar(); // prints the calendar
void printToday(); // prints todays reminders

#endif