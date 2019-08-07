SRCDIR = src
OBJDIR = obj
BINDIR = bin
APP = main

MKDIR_P = mkdir -p
RM_RF = rm -rf

CC = g++

LFLAGS = -Wall
CFLAGS = -Wall -c -O0 --std=c++11 -g
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(LFLAGS)

SRCS := $(wildcard $(SRCDIR)/*.cc)
OBJS := $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRCS))

$(APP): $(OBJS) | $(BINDIR)
	$(LINK) $^ -o $(BINDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(COMPILE) $< -o $@

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

$(BINDIR):
	$(MKDIR_P) $(BINDIR)

.PHONY: clean

clean:
	$(RM_RF) $(OBJDIR) $(BINDIR) $(OBJDIR_TEST) $(BINDIR_TEST)
Debug: $(APP)

SRCDIR_TEST = test
OBJDIR_TEST = testobj
BINDIR_TEST = testbin

TCFLAGS = -Wall -c -Isrc -lgtest -lgtest_main -lpthread
TLFLAGS = -Wall -lgtest -lgtest_main -lpthread
COMPILE_TEST = $(CC) $(TCFLAGS)
LINK_TEST = $(CC) $(TLFLAGS)

SRCS_TEST := $(wildcard $(SRCDIR_TEST)/*.cc)
OBJS_TEST := $(patsubst $(SRCDIR_TEST)/%.cc, $(OBJDIR_TEST)/%.o, $(SRCS_TEST))

test: $(OBJDIR)/$(COMPONENT).o $(OBJDIR_TEST)/test_$(COMPONENT).o | $(BINDIR_TEST)
	$(CC) $(OBJDIR)/$(COMPONENT).o $(OBJDIR_TEST)/test_$(COMPONENT).o -o $(BINDIR_TEST)/test_$(COMPONENT) $(TLFLAGS)

$(OBJDIR_TEST)/%.o: $(SRCDIR_TEST)/%.cc
	$(COMPILE_TEST) $< -o $@

$(OBJS_TEST): | $(OBJDIR_TEST)

$(OBJDIR_TEST):
	$(MKDIR_P) $(OBJDIR_TEST)

$(BINDIR_TEST):
	$(MKDIR_P) $(BINDIR_TEST)
