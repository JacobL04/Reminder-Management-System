#include "interact.h"
#include "reminder.h"
#include "linked_list.h"

void userInput(char *command, char *userDay, char *reminder){
    int loop = 1;
    int day = atoi(userDay);
    int index = -1;

    if(strcmp(command, "add") == 0){ // Add command
        if(day < 1 || day > currentMonth.numDays){
            printf("Invalid day\n");
            return;
        }

        insert_to_calendar(day, reminder); // Add reminder to the specified day
        printCalendar(); // Print the calendar after adding the reminder
        save_reminders(REMINDER_FILE); // Save reminders to file
    }

    else if(strcmp(command, "remove") == 0){ // Remove command
        if(strlen(reminder) == 0){
            printf("Invalid arguments\n");
            printf("Usage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");
            return;
        }

        index = atoi(reminder); // Use the reminder input as the index
        if(day < 1 || day > currentMonth.numDays){
            printf("Invalid day\n");
            return;
        }
        
        if(index < 1){ // Error handling for negative integers
            printf("Invalid index! Must be 1 or greater.\n");
            return;
        }

        remove_from_calendar(day, index); // Remove reminder from calendar
        printCalendar(); // Print the calendar after adding the reminder
        save_reminders(REMINDER_FILE); // Save reminders to file
    }

    else {
        printf("Invalid arguments\n");
        printf("Usage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");
    }
}

void signal_handler(int signal){ // Signal interupt, save file and exit
    if(signal == SIGINT){
        printf("\nProgram interupted! Saving reminders...\n");
    }

    else if(signal == SIGTERM){
        printf("\nProgram terminated! Saving reminders...\n");
    }

    else if(signal == SIGSEGV){
        printf("Program segmentation error! Saving reminders... ");
    }
    save_reminders(REMINDER_FILE);
    exit(0);
}

int main(int argc, char *argv[]){
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGSEGV, signal_handler);

    char reminder[MAX_STR_LEN] = "";

    for(int i = 3; i < argc; i++){
        strcat(reminder, argv[i]);
        if(i != argc - 1){  // Add space between words
            strcat(reminder, " ");
        }
    }

    initializeMonth();
    if(access(REMINDER_FILE, F_OK) == 0){ // Checks if reminder.txt exists
        load_reminders(REMINDER_FILE);

        if(strcmp(argv[1], "view") == 0){ // View command
            printCalendar();
            save_reminders(REMINDER_FILE);
        }

        else if(strcmp(argv[1], "today") == 0){ // Today command
            printToday();
            save_reminders(REMINDER_FILE);
        }

        else {
            userInput(argv[1], argv[2], reminder);
        }
    }
    
    else {
        userInput(argv[1], argv[2], reminder);
    }
    return 0;
}