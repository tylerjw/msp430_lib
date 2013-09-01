
TARGET		= gpio_test
mmcu		= msp430g2553
OBJECTS 	= gpio_test.o gpio_api.o
#######################################################################################
CFLAGS   = -mmcu=$(MCU) -Os
ASFLAGS  = -mmcu=$(MCU) -Os
LDFLAGS  = -mmcu=$(MCU) -Os
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
$(TARGET).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET).elf
	$(OBJDUMP) -z -EL -D -W $(TARGET).elf >$(TARGET).lss
	$(SIZE) $(TARGET).elf
	$(OBJCOPY) -O ihex $(TARGET).elf $(TARGET).hex

gpio_test.o: msp430_lib.h
gpio_api.o: gpio_api.h

install: all
	mspdebug --force-reset rf2500 "prog $(TARGET).elf"

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