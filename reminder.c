#include "reminder.h"
#include "linked_list.h"

extern int months;
struct Month currentMonth;

const char *monthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; // Months
const char *weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; // Weekday name, abbreviated

void initializeMonth(void){ // Initializes the month using local time
    time_t now = time(NULL); 
    struct tm *t = localtime(&now); 
    currentMonth.month_idx = t->tm_mon; 
     
    t->tm_mday = 1; 
    mktime(t); 
    currentMonth.startingDay = t->tm_wday; 
     
    currentMonth.numDays = t->tm_mday; 
    while (t->tm_mon == currentMonth.month_idx){ 
        currentMonth.numDays = t->tm_mday; 
        t->tm_mday++;
        mktime(t); 
    } 
}

void printCalendar(){
    int days = currentMonth.numDays;
    int start = currentMonth.startingDay;
    int counter = 0; // Keeps track of each week to format it properly
    // const char *weekdays[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; // Weekday name, abbreviated

    printf("\n%s\t%s\t%s\t%s\t%s\t%s\t%s\n", weekdays[0], weekdays[1], weekdays[2], weekdays[3], weekdays[4], weekdays[5], weekdays[6]);
    for(int i = 0; i < start; i++){ // Starting day prints at the right week (Sets the position)
        printf("\t");
        counter++;
    }

    for(int i = 1; i <= days; i++){ // Print the days of the month and reminders
        struct Node *currNode = head;
        bool reminderDate = false;
        while(currNode){
            if(currNode->day == i){
                reminderDate = true;  // Reminder was found
                break;
            }
            currNode = currNode->next;
        }

        if(reminderDate){
            printf("(%d)\t", i);  // Prints day with the reminder
        }
        
        else {
            printf("%d\t", i);  // Prints day without the reminder
        }
        counter++;

        if(counter % 7 == 0){ // Newline for end of a week
            printf("\n");
        }
    }

    if(counter % 7 != 0){ // Newline if days arent filled to the end of the week
        printf("\n");
    }

    printf("\n%s reminders: \n", monthNames[currentMonth.month_idx]);
    
    for(int i = 1; i <= days; i++){
        struct Node *currNode = head;
        int numReminders = 0;

        while(currNode){ // Checks any reminders for this day
            if(currNode->day == i){
                numReminders++;
            }
            currNode = currNode->next;
        }

        if(numReminders > 0){
            // Prints the day and reminders
            printf("%s %d::", weekdays[(i + currentMonth.startingDay - 1) % 7], i);
            currNode = head;
            int reminderIdx = 1;

            while(currNode){
                if(currNode->day == i){
                    printf(" (%d) %s", reminderIdx, currNode->reminder_str);
                    reminderIdx++;
                }
                currNode = currNode->next;
            }
            printf("\n");
        }
    }
    printf("______________________________\n");
}

void printToday(){ // Prints today reminders (if any)
    time_t t = time(NULL);  // Get current time
    struct tm tm = *localtime(&t);  // Convert to local time
    int today = tm.tm_mday;  // Todays date
    int weekday = tm.tm_wday; // This Weekday

    printf("\nReminders for %s %d:\n", monthNames[currentMonth.month_idx], today);
    
    struct Node *currNode = head;
    int reminderIdx = 1;
    int remindersFound = 0;

    printf("%s %d:: ", weekdays[weekday], today);
    while(currNode){
        if(currNode->day == today){
            // Print the reminder with index
            printf("(%d) %s ", reminderIdx, currNode->reminder_str);
            reminderIdx++;
            remindersFound = 1;
        }
        currNode = currNode->next;
    }

    if(!remindersFound){
        printf("No reminders for today\n");
    }

    printf("\n______________________________\n");
}