SRCDIR = src
OBJDIR = obj
BINDIR = bin
APP = main

MKDIR_P = mkdir -p
RM_RF = rm -rf

CC = g++

LFLAGS = -Wall
CFLAGS = -Wall -c -O0 --std=c++11 -g
SDL_LFLAGS = -lSDL2 -lSDL2_image
COMPILE = $(CC) $(CFLAGS)
LINK = $(CC) $(LFLAGS)

SRCS := $(wildcard $(SRCDIR)/*.cc)
OBJS := $(patsubst $(SRCDIR)/%.cc, $(OBJDIR)/%.o, $(SRCS))

$(APP): $(OBJS) | $(BINDIR)
	$(LINK) $^ $(SDL_LFLAGS) -o $(BINDIR)/$@

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

OBJ_APP = $(OBJDIR)/$(APP).o
OBJS_TESTING = $(filter-out $(OBJ_APP), $(OBJS))

SRCDIR_TEST = test
OBJDIR_TEST = testobj
BINDIR_TEST = testbin

TCFLAGS = -Wall -c -Isrc -lgmock -lgmock_main -lpthread
TLFLAGS = -Wall -lgmock -lgmock_main -lpthread
COMPILE_TEST = $(CC) $(TCFLAGS)
LINK_TEST = $(CC) $(TLFLAGS)

SRCS_TEST := $(wildcard $(SRCDIR_TEST)/*.cc)
OBJS_TEST := $(patsubst $(SRCDIR_TEST)/%.cc, $(OBJDIR_TEST)/%.o, $(SRCS_TEST))

test: $(OBJS) $(OBJDIR_TEST)/$(COMPONENT)_test.o | $(BINDIR_TEST)
	$(CC) $(OBJS_TESTING) $(OBJDIR_TEST)/$(COMPONENT)_test.o -o $(BINDIR_TEST)/$(COMPONENT)_test $(TLFLAGS)

$(OBJDIR_TEST)/%.o: $(SRCDIR_TEST)/%.cc
	$(COMPILE_TEST) $< -o $@

$(OBJS_TEST): | $(OBJDIR_TEST)

$(OBJDIR_TEST):
	$(MKDIR_P) $(OBJDIR_TEST)

$(BINDIR_TEST):
	$(MKDIR_P) $(BINDIR_TEST)
