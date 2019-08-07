SRCDIR = src
_OBJDIR = obj
OBJDIR := $(_OBJDIR)
APP = main

MKDIR_P = mkdir -p
RM_RF = rm -rf

LFLAGS = -Wall
CFLAGS = -Wall -c -O0 --std=c++11 -g -Iinclude
CC = g++
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(LFLAGS)

_OBJS = $(APP).o game.o
OBJS = $(patsubst %, $(OBJDIR)/%,$(_OBJS))

$(APP): $(OBJS)
	$(LINK) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(OBJDST)
	$(COMPILE) -o $@ $<

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

.PHONY: clean

clean:
	$(RM_RF) $(_OBJDIR) $(APP)
Debug: $(APP)
