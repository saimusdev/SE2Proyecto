PROJECT = se2proy

# Toolchain and binaries used
PREFIX := /usr/bin/arm-linux-gnueabihf-
CC := $(PREFIX)gcc
LD := $(PREFIX)gcc

# Search directory for source code
vpath %.c $(CURDIR)/src

# Dependencies
INCLUDEDIR := $(CURDIR)/include
DEPS := $(wildcard $(INCLUDEDIR)/*.h)

# Compiler object files 
OBJDIR := $(CURDIR)/obj
OBJS := \
	$(OBJDIR)/computos.o \
	$(OBJDIR)/servidores.o \
	$(OBJDIR)/comun.o

# Libraries
LIBS = -lrt -lpthread

# Compiler options
CFLAGS = -Wall

# Includes
IFLAGS	= \
	-I/usr/arm-linux-gnueabihf/include \
	-I. \
	-I$(INCLUDEDIR)

# Linker options
LDFLAGS	= \
	-static \
	-L/usr/arm-linux-gnueabihf/lib 

# Random stuff
MSG_EMPTYLINE = "" 
MSG_COMPILING = ---COMPILE--- 
MSG_LINKING = ---LINK--- 
MSG_CLEANING = ---CLEAN--- 
MSG_SUCCESS = ---SUCCESS--- 
RM = rm -f

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
	@echo $(MSG_COMPILING) $<
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# Clean
clean:
	@echo $(MSG_CLEANING)
	$(RM) $(OBJDIR)/*.o
	$(RM) $(PROJECT)
