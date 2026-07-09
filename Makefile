.SUFFIXES:
.SECONDARY:

PORT         := /dev/ttyUSB0
GCC_MCU      := atmega328p
AVRDUDE_MCU  := m328p
AVRDUDE_STK  := stk500v1
AVRDUDE_BAUD := 57600

# datasheet says 8 but that fucks UART, or maybe i'm just blind
CLOCKSPEED   := 16000000L

CFLAGS :=                    \
	-Wall -Wextra -Wpedantic \
	-Os                      \
	-static                  \
	-mmcu=$(GCC_MCU)         \
	-D F_CPU=$(CLOCKSPEED)   \

$(shell mkdir -p bld)

all: test

%: bld/%.hex
	avrdude -v -V          \
		-c $(AVRDUDE_STK)  \
		-p $(AVRDUDE_MCU)  \
		-b $(AVRDUDE_BAUD) \
		-P $(PORT)         \
		-U flash:w:$<:i

bld/%.hex: bld/%.bin
	avr-objcopy -O ihex $< $@

bld/%.bin: raw/%.c
	avr-gcc $(CFLAGS) $< -o $@

clean:
	rm -rf bld
