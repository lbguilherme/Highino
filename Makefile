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

SERIAL_RATE = 9600

CXX = avr-g++
SIZE = avr-size
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CXXFLAGS = -mmcu=$(MCU) -std=c++11 -Iarduino/include -include arduino/board-$(ARDUINO).hpp -Wall -Wextra -Wno-unused-function -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
LDFLAGS = -mrelax
PFLAGS = -F -p $(MCU) -P $(PORT) -c $(PROTOCOL) -b $(UPLOAD_RATE) -D

EXAMPLES = $(wildcard examples/*.cpp)
EXAMPLES_ELF = $(EXAMPLES:.cpp=.elf)
EXAMPLES_S = $(EXAMPLES:.cpp=.S)
EXAMPLES_HEX = $(EXAMPLES:.cpp=.hex)

.PRECIOUS: %.o %.elf

build: main.S main.o main.elf main.hex $(EXAMPLES_HEX) $(EXAMPLES_S)
	@$(SIZE) main.elf $(EXAMPLES_ELF)

%.S: %.cpp $(wildcard arduino/*.hpp) arduino
	@echo $<" => "$@
	@$(CXX) -S $(CXXFLAGS) $< -o $@
	
%.o: %.cpp $(wildcard arduino/*.hpp) arduino
	@echo $<" => "$@
	@$(CXX) -c $(CXXFLAGS) $< -o $@
	
%.elf: %.o
	@echo $<" => "$@
	@$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

%.hex: %.elf
	@echo $<" => "$@
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

upload: main.hex
	@$(AVRDUDE) $(PFLAGS) -U flash:w:$<

run: upload
	@stty -F $(PORT) cs8 $(SERIAL_RATE) ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts eof \^d
	@cat $(PORT)

clean:
	@echo Cleaning...
	@rm -f *.elf *.hex *.o *.S *~
	@rm -f **/*.elf **/*.hex **/*.o **/*.S **/*~

.PHONY: build upload clean
