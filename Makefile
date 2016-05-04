avrType=atmega328
avrFreq=1000000
programmerDev=usb
programmerType=atmelice_isp
BIN=esfeedercontroller

CPP_FILES := $(wildcard src/*.c) 
OBJ_FILES := $(addprefix obj/, $(notdir $(CPP_FILES:.c=.o)))
CC_FLAGS=-Os -DF_CPU=$(avrFreq)UL -mmcu=$(avrType) -Wall -Werror -Isrc/ -std=c99
LFLAGS=-mmcu=$(avrType) -Wl,-u,vfprintf -lprintf_min -Wl,-u,vfscanf -lscanf_min

.PHONY: erase flash clean

$(BIN).hex: $(BIN).elf
	avr-objcopy -j .text -j .data -O ihex $< $@

obj/%.o: src/%.c
	avr-gcc $(CC_FLAGS) -c -o $@ $<

$(BIN).elf: $(OBJ_FILES) $(ARDUINO_OBJ_FILES)
	avr-gcc $(LFLAGS) -o $@ $^

clean:
	rm -f $(BIN).elf $(BIN).hex obj/*

erase:
	avrdude -c$(programmerType) -p$(avrType) -P$(programmerDev) -e

flash: $(BIN).hex
	avrdude -B4 -c$(programmerType) -p$(avrType) -P$(programmerDev) -v -U flash:w:$<

