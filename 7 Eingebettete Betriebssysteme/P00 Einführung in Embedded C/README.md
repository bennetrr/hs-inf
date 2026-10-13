# EBSy – Projekt P0: Übungsprojekt (GNU-Toolchain + QEMU)

Übungsprojekt zur Anleitung „EBSy – P0 – Einführung in die C-Programmierung (GNU, online)“.

- Zielsystem: ARM Cortex-M4F (STM32F405, QEMU-Board `netduinoplus2`)
- Compiler: GNU Arm Embedded Toolchain (`arm-none-eabi-gcc`)
- Debugger: GDB (`gdb-multiarch`) mit der VS-Code-Erweiterung Cortex-Debug

## Start im Browser (GitHub Codespaces, keine Installation)

1. Repository auf GitHub öffnen → **Code** → **Codespaces** → **Create codespace**.
2. Warten, bis die Umgebung eingerichtet ist (beim ersten Start einige Minuten, das Projekt wird dabei automatisch einmal übersetzt).
3. Links **Run and Debug** (Strg+Umschalt+D) → „P0 debuggen (ab main)“ → **F5**.

## Lokal (optional)

- Mit Docker: VS Code + Erweiterung „Dev Containers“ → „Reopen in Container“.
- Ohne Docker (Linux/WSL): `sudo apt install make gcc-arm-none-eabi libnewlib-arm-none-eabi qemu-system-arm gdb-multiarch`

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
