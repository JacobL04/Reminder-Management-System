EXEC = reminder
OBJS = interact.o linked_list.o reminder.o

all: $(EXEC) run

$(EXEC): $(OBJS)
	gcc -o $(EXEC) $(OBJS)

interact.o: interact.c interact.h
	gcc -c interact.c

linked_list.o: linked_list.c linked_list.h
	gcc -c linked_list.c

reminder.o: reminder.c reminder.h
	gcc -c reminder.c

run:
	@echo "To run the reminder program please type: ./"$(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)