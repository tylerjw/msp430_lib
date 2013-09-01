#
# Makefile for msp430
#
# 'make' builds everything
# 'make clean' deletes everything except source files and Makefile
# You need to set TARGET, MCU and SOURCES for your project.
# TARGET is the name of the executable file to be produced 
# 
TARGET     = gpio_test
MCU        = msp430g2553
# List all the source files here
# eg if you have a source file foo.c then list it here
SOURCES = gpio_test.c
# Include are located in the Include directory
INCLUDES = .
# Add or subtract whatever MSPGCC flags you want. There are plenty more
#######################################################################################
CFLAGS   = -mmcu=$(MCU) -Os -I$(INCLUDES)
ASFLAGS  = -mmcu=$(MCU) -Os -I$(INCLUDES)
LDFLAGS  = -mmcu=$(MCU) -Os -I$(INCLUDES)
########################################################################################
CC       = msp430-gcc
LD       = msp430-ld
AR       = msp430-ar
AS       = msp430-gcc
GASP     = msp430-gasp
NM       = msp430-nm
OBJCOPY  = msp430-objcopy
OBJDUMP  = msp430-objdump
RANLIB   = msp430-ranlib
STRIP    = msp430-strip
SIZE     = msp430-size
READELF  = msp430-readelf
MAKETXT  = srec_cat
CP       = cp -p
RM       = rm -f
MV       = mv
########################################################################################
# all the object files
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET).elf

$(TARGET).elf: $(TARGET).o
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $(TARGET).elf
	$(OBJDUMP) -z -EL -D -W $(TARGET).elf >$(TARGET).lss
	$(SIZE) $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

install: all
	mspdebug --force-reset rf2500 "prog $(TARGET).elf"

cycle_count: all
	naken430util -disasm $(TARGET).hex > $(TARGET)_cc.txt

debug: all
	clear
	@echo -e "--------------------------------------------------------------------------------"
	@echo -e "-- Make sure you are running mspdebug in another window                       --"
	@echo -e "--------------------------------------------------------------------------------"
	@echo -e "$$ # you can start it like this:"
	@echo -e "$$ mspdebug rf2500 gdb\n"
	msp430-gdb --command=$(TARGET).gdb $(TARGET).elf

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).lss $(TARGET).map $(TARGET).hex $(TARGET)_cc.txt
