# Makefile EBSy P0 – GNU Arm Embedded Toolchain
#   make        Projekt uebersetzen (build/p0.elf, build/p0.map)
#   make run    im Simulator QEMU starten und auf den Debugger warten
#   make pre    Praeprozessor-Ausgabe erzeugen (build/*.i)
#   make asm    Assembler-Listing erzeugen (build/p0.lst)
#   make size   Speicherbedarf der Sektionen anzeigen
#   make clean  Build-Verzeichnis loeschen

PREFIX  = arm-none-eabi-
CC      = $(PREFIX)gcc
OBJDUMP = $(PREFIX)objdump
SIZE    = $(PREFIX)size
NM      = $(PREFIX)nm

BUILD   = build
TARGET  = $(BUILD)/p0

CPUFLAGS = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS   = $(CPUFLAGS) -std=c99 -O0 -g3 -Wall -Wextra -ffunction-sections -fdata-sections
ASFLAGS  = $(CPUFLAGS) -g
LDFLAGS  = $(CPUFLAGS) -T stm32f405_qemu.ld -Wl,-Map=$(TARGET).map -Wl,--gc-sections \
           --specs=nano.specs --specs=nosys.specs

# Ab binutils 2.39 warnt ld vor RWX-Segmenten (bei Mikrocontrollern harmlos).
# Aeltere Linker kennen die Option nicht, deshalb nur setzen, wenn ld sie unterstuetzt.
ifneq ($(shell $(PREFIX)ld --help 2>/dev/null | grep -c no-warn-rwx-segments),0)
LDFLAGS += -Wl,--no-warn-rwx-segments
endif

# Diese Datei wird absichtlich mit Optimierung uebersetzt (Aufgabe volatile)
OPT_O2   = $(BUILD)/p0_volatile.o

CSRC = $(wildcard src/*.c)
SSRC = $(wildcard src/*.s)
OBJS = $(patsubst src/%.c,$(BUILD)/%.o,$(CSRC)) $(patsubst src/%.s,$(BUILD)/%.o,$(SSRC))

all: $(TARGET).elf size

$(BUILD):
	mkdir -p $(BUILD)

$(OPT_O2): CFLAGS := $(subst -O0,-O2,$(CFLAGS))

$(BUILD)/%.o: src/%.c src/*.h | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: src/%.s | $(BUILD)
	$(CC) $(ASFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJS) stm32f405_qemu.ld
	$(CC) $(LDFLAGS) $(OBJS) -o $@

size: $(TARGET).elf
	$(SIZE) $<

asm: $(TARGET).elf
	$(OBJDUMP) -d -S $< > $(TARGET).lst
	@echo "Listing: $(TARGET).lst"

pre: | $(BUILD)
	for f in $(CSRC); do $(CC) $(CFLAGS) -E -P $$f -o $(BUILD)/$$(basename $$f .c).i; done
	@echo "Praeprozessor-Ausgabe: $(BUILD)/*.i"

symbols: $(TARGET).elf
	$(NM) -n -S $<

run: $(TARGET).elf
	qemu-system-arm -M netduinoplus2 -nographic -kernel $< -S -gdb tcp::1234

clean:
	rm -rf $(BUILD)

.PHONY: all size asm pre symbols run clean
