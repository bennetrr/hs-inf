# EBSy – Projekt P0: Übungsprojekt (GNU-Toolchain + QEMU)

Übungsprojekt zur Anleitung „EBSy – P0 – Einführung in die C-Programmierung (GNU, online)“.

- Zielsystem: ARM Cortex-M4F (STM32F405, QEMU-Board `netduinoplus2`)
- Compiler: GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`)
- Debugger: GDB (`gdb-multiarch`) mit der VS-Code-Erweiterung Cortex-Debug

## Projekt herunterladen

Oben rechts **Code → Download source code → zip** wählen und das Zip auf dem eigenen Rechner entpacken.

## Installation

Siehe Anleitung „P0 – Lokale Installation unter Windows (und Linux)“ in Moodle:

- **Weg A (empfohlen):** WSL + Ubuntu, Werkzeuge mit `apt`, Debuggen mit **Seer**.
- **Weg B:** WSL + Ubuntu, Werkzeuge mit `apt`, Debuggen mit **VS Code** (`code .`, dann F5 → „P0 debuggen (ab main)“).
- **Weg C:** Docker Desktop + VS Code „Dev Containers“ → „Reopen in Container“.
- **Bereits Linux (nativ oder VM):** `sudo apt install make gcc-arm-none-eabi libnewlib-arm-none-eabi qemu-system-arm gdb-multiarch`, dann wie Weg A
  oder B.

Das Makefile funktioniert auch mit älteren Toolchains (getestet: GCC 9.2 / binutils 2.34 und GCC 13.2 / binutils 2.42). Adressen im Speicher können
sich zwischen Compilerversionen leicht unterscheiden.

## Befehle

| Befehl         | Wirkung                                                     |
| -------------- | ----------------------------------------------------------- |
| `make`         | übersetzen → `build/p0.elf`, Memory Map `build/p0.map`      |
| `make asm`     | Disassembly mit Quelltext → `build/p0.lst`                  |
| `make pre`     | Ausgabe des Präprozessors → `build/*.i`                     |
| `make symbols` | Symboltabelle sortiert nach Adresse                         |
| `make run`     | QEMU starten und auf GDB an Port 1234 warten (ohne VS Code) |
| `make clean`   | Build-Verzeichnis löschen                                   |

Ohne VS Code debuggen: in einem Terminal `make run`, in einem zweiten `gdb-multiarch build/p0.elf -ex "target remote :1234"`.
