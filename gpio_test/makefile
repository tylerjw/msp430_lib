
TARGET		= gpio_test
MCU 		= msp430g2553
OBJECTS 	= gpio_test.o gpio_api.o
#######################################################################################
# compile - debug symbols (g), optomize for size (Os)
CFLAGS   = -mmcu=$(MCU) -g -Os
ASFLAGS  = -mmcu=$(MCU)
# link - all warnings (Wall)
LDFLAGS  = -mmcu=$(MCU) -Wall
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
CP       = cp -p
RM       = rm -f
MV       = mv
########################################################################################
$(TARGET).elf: $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(TARGET).elf
	$(OBJDUMP) -z -EL -D -W $(TARGET).elf > $(TARGET).lss
	$(SIZE) $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

gpio_test.o: msp430_lib.h defines.h
gpio_api.o: gpio_api.h defines.h

install: $(TARGET).elf
	mspdebug --force-reset rf2500 "prog $(TARGET).elf"

debug: $(TARGET).elf
	clear
	@echo -e "--------------------------------------------------------------------------------"
	@echo -e "-- Make sure you are running mspdebug in another window                       --"
	@echo -e "--------------------------------------------------------------------------------"
	@echo -e "$$ # you can start it like this:"
	@echo -e "$$ mspdebug rf2500 gdb\n"
	msp430-gdb --command=commands.gdb $(TARGET).elf

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).lss $(TARGET).map $(TARGET).hex