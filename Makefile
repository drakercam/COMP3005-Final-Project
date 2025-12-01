# ////////////////////////////
# Makefile for the Gym Management App
# ////////////////////////////

TARGET = GymApp

# Object files
OBJS = main.o psql_admin.o psql_app.o psql_member.o psql_trainer.o

# Compiler + Flags
CC = gcc
CFLAGS = -Wall -Wextra -I/usr/include
LDFLAGS = -L/usr/lib64 -lpq

# Build the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile each C file individually
main.o: app/main.c app/psql_app.h app/psql_member.h app/psql_trainer.h app/psql_admin.h
	$(CC) $(CFLAGS) -c app/main.c -o main.o

psql_admin.o: app/psql_admin.c app/psql_admin.h
	$(CC) $(CFLAGS) -c app/psql_admin.c -o psql_admin.o

psql_app.o: app/psql_app.c app/psql_app.h
	$(CC) $(CFLAGS) -c app/psql_app.c -o psql_app.o

psql_member.o: app/psql_member.c app/psql_member.h
	$(CC) $(CFLAGS) -c app/psql_member.c -o psql_member.o

psql_trainer.o: app/psql_trainer.c app/psql_trainer.h
	$(CC) $(CFLAGS) -c app/psql_trainer.c -o psql_trainer.o

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program as postgres
run: $(TARGET)
	sudo -u postgres ./GymApp