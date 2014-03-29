# This is board dependent.
# Move to separate file
# arduino.cc/en/uploads/Main/boards.txt
ARDUINO = mega2560
MCU = atmega2560
PROTOCOL = stk500v2
FORMAT = ihex
UPLOAD_RATE = 115200

# This depends on with usb port the arduino is connected.
# Detect (how?) or move out of here
PORT = /dev/ttyACM0

CXX = avr-g++
SIZE = avr-size
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CXXFLAGS = -mmcu=$(MCU) -std=c++11 -Iarduino -include board-$(ARDUINO).hpp -Wall -Wextra -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
LDFLAGS = -mrelax
PFLAGS = -F -p $(MCU) -P $(PORT) -c $(PROTOCOL) -b $(UPLOAD_RATE) -D

build: main.S main.o main.elf main.hex
	$(SIZE) main.elf

%.S: %.cpp $(wildcard arduino/*.hpp)
	$(CXX) -S $(CXXFLAGS) $< -o $@
	
%.o: %.cpp $(wildcard arduino/*.hpp)
	$(CXX) -c $(CXXFLAGS) $< -o $@
	
%.elf: %.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

%.hex: %.elf
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

upload: main.hex
	$(AVRDUDE) $(PFLAGS) -U flash:w:$<

clean:
	 rm -f *.elf *.hex *.o *.S *~

.PHONY: build upload clean
