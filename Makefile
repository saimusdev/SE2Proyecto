PROJECT := se2proy

# Search directory for source code
vpath %.c src

# Dependencies
INCLUDEDIR := include
DEPS := $(wildcard $(INCLUDEDIR)/*.h)

# Compiler object files 
OBJDIR := obj
OBJS := \
	$(OBJDIR)/ts_util.o \
	$(OBJDIR)/calc.o \
	$(OBJDIR)/events.o \
	$(OBJDIR)/tasks.o \
	$(OBJDIR)/servers.o \
	$(OBJDIR)/main.o

# Libraries
LIBS := -lrt -lpthread

# Compiler options
CFLAGS := -Wall #-DDEBUG

# UNIX only (Windows not supported)
OS := $(shell uname -s)
ifeq ($(OS),Linux)
	DISTRO := $(shell lsb_release -si)
	ifeq ($(DISTRO),Ubuntu)
		# Linaro toolchain PATH
		PREFIX := /usr/bin/arm-linux-gnueabihf-
		# Includes
		IFLAGS := \
			-I/usr/arm-linux-gnueabihf/include \
			-I. \
			-I$(INCLUDEDIR)

		# Linker options
		LDFLAGS	= \
			-static \
			-L/usr/arm-linux-gnueabihf/lib 
	else
		# Linaro toolchain PATH
		PREFIX := /usr/local/linaro/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
		# Includes
		IFLAGS := \
			-I$(TARGET)/arm-linux-gnueabihf/libc/usr/include \
			-I. \
			-I$(INCLUDEDIR)

		# Linker options
		LDFLAGS	:= \
			-static \
			-L$(TARGET)/arm-linux-gnueabihf/libc/lib/arm-linux-gnueabihf \
			-L$(TARGET)/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf
	endif
else
	# Linaro toolchain PATH
	PREFIX := /usr/local/linaro/arm-linux-gnueabihf/bin/arm-linux-gnueabihf-
	# Includes
	IFLAGS	:= \
		-I$(TARGET)/arm-linux-gnueabihf/libc/usr/include \
		-I. \
		-I$(INCLUDEDIR)

	# Linker options
	LDFLAGS	:= \
		-static \
		-L$(TARGET)/arm-linux-gnueabihf/libc/lib/arm-linux-gnueabihf \
		-L$(TARGET)/arm-linux-gnueabihf/libc/usr/lib/arm-linux-gnueabihf
endif

# Binaries full path
CC := $(PREFIX)gcc
LD := $(PREFIX)gcc

# Random stuff
MSG_EMPTYLINE := "" 
MSG_COMPILING := ---COMPILE--- 
MSG_LINKING := ---LINK--- 
MSG_CLEANING := ---CLEAN--- 
MSG_SUCCESS := ---SUCCESS--- 
RM := rm -f
MKDIR := mkdir -p

##################################################################

all: $(PROJECT)

# Linker call
$(PROJECT): $(OBJS)
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_LINKING)
	$(LD) -o $@ $^ $(LDFLAGS) $(LIBS)
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_SUCCESS) $(PROJECT)

# Compiler call
$(OBJS): $(OBJDIR)/%.o: %.c $(DEPS)
	$(MKDIR) $(OBJDIR)
	@echo $(MSG_COMPILING) $<
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# Clean
clean:
	@echo $(MSG_CLEANING)
	$(RM) $(OBJDIR)/*.o
	$(RM) $(PROJECT)
