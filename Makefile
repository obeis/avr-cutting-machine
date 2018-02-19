PROJECT = main

MCU = atmega32

FREQ = 16000000UL

CC = avr-gcc

OBJCOPY = avr-objcopy

SOURCE = $(wildcard *.c)

OBJECT = $(SOURCE:.c=.o)

RM = rm -f

main :
	$(CC) -g -Os -DF_CPU=$(FREQ) -mmcu=$(MCU) -c $(SOURCE)
	$(CC) -g -DF_CPU=$(FREQ) -mmcu=$(MCU) -o $(PROJECT).elf $(OBJECT)
	$(OBJCOPY) -j .text -j .data -O ihex $(PROJECT).elf $(PROJECT).hex
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex main.elf main.eep

upload :
	avrdude -c usbasp -p m32 -U flash:w:main.hex:i -U eeprom:w:main.eep:i

clean :
	$(RM) $(OBJECT) $(PROJECT).elf $(PROJECT).hex $(PROJECT).eep
