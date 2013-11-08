CXX = g++
TARGET = hmm
SRCS = $(wildcard *.cc)
OBJS = $(SRCS:.cc=.o)
DEPS = $(OBJS:.o=.d)
RM = rm -fv
CXXFLAGS = -Wall -Wextra -MMD
MODE = release
ifeq ($(MODE),debug)
	CXXFLAGS += -ggdb
else
ifeq ($(MODE),profile)
	CXXFLAGS += -pg
endif
endif

.PHONY:all
all: information $(TARGET) 

information:
ifneq ($(MODE),release)
ifneq ($(MODE),debug)
ifneq ($(MODE),profile)
	@echo "Invalid build mode." 
	@echo "Please use 'make MODE=release' or 'make MODE=debug'"
	@exit 1
endif
endif
endif
	@echo "Building $(TARGET) on "$(MODE)" MODE"
	@echo "............................."

$(TARGET): $(OBJS) Makefile
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

-include $(DEPS)
%.o:%.cc Makefile
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.SILENT:debug profile clean d prof p c
debug d:
	$(MAKE) MODE=debug   --always-make --no-print-directory
profile prof p:
	$(MAKE) MODE=profile --always-make --no-print-directory
clean c:
	$(RM) $(TARGET) $(OBJS) $(DEPS) .*.swp .*.swo *~
