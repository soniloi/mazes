SRCDIR = src
OBJDIR = obj
BINDIR = bin
APP = main

MKDIR_P = mkdir -p
RM_RF = rm -rf

LFLAGS = -Wall
CFLAGS = -Wall -c -O0 --std=c++11 -g
CC = g++
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
	$(RM_RF) $(OBJDIR) $(BINDIR)
Debug: $(APP)
