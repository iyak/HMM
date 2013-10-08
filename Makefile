CC = g++
TARGET = hmm
SRCS := $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)
RM = rm -fv
DEBUG = -g

#Compiler flags
#if mode variable is empty, setting release build mode
ifeq ($(mode),debug)
	CFLAGS = -Wall $(DEBUG)
else
	mode = release
	CFLAGS = -Wall
endif

.PHONY:all
all: information $(TARGET) 

information:
ifneq ($(mode),release)
ifneq ($(mode),debug)
	@echo "Invalid build mode." 
	@echo "Please use 'make mode=release' or 'make mode=debug'"
	@exit 1
endif
endif
	@echo "Building $(TARGET) on "$(mode)" mode"
	@echo ".........................."

$(TARGET): touch $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o : %.cc
	$(CC) -c $(CFLAGS) -o $@ $<

.PHONY:touch
touch:
ifeq ($(mode),debug)
	@touch $(SRCS)
endif

%.dep:%.c
	$(SHELL) -c '$(CC) -MM $< > $@'

-include $(DEPS)

.PHONY:d
d:
	-@make mode=debug

.PHONY:clean
clean c:
	@$(RM) $(TARGET) $(OBJS) .*.swp .*.swo *~
