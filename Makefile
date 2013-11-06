CXX = g++
TARGET = hmm
SRCS := $(wildcard *.cc)
HDRS := $(wildcard *.hh)
OBJS = $(SRCS:.cc=.o)
DEPS = $(OBJS:.o=.d)
RM = rm -fv
DEBUG = -ggdb
CXXFLAGS = -O3 -pthread -Wall -Wextra -Wpedantic -MMD
MODE = release

.PHONY:all
all: information $(TARGET) 

information:
ifneq ($(MODE),release)
ifneq ($(MODE),debug)
	@echo "Invalid build mode." 
	@echo "Please use 'make MODE=release' or 'make MODE=debug'"
	@exit 1
endif
endif
	@echo "Building $(TARGET) on "$(MODE)" MODE"
	@echo "............................."

$(TARGET): touch $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o:%.cc
ifeq ($(MODE),release)
	$(CXX) -c $(CXXFLAGS) -o $@ $<
else
	$(CXX) -c $(CXXFLAGS) $(DEBUG) -o $@ $<
endif

.PHONY:touch
touch:
ifeq ($(MODE),debug)
	@touch $(SRCS) $(HDRS)
endif

-include $(DEPS)

.PHONY:debug d
debug d:
	-@make MODE=debug

.PHONY:clean c
clean c:
	@$(RM) $(TARGET) $(OBJS) $(DEPS) .*.swp .*.swo *~
