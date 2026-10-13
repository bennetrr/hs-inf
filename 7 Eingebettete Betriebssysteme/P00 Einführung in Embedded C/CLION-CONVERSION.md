# Converting a VS Code project (Cortex-Debug + QEMU) to CLion

How to move the build tasks and Cortex-Debug launch configs from `.vscode/` into CLion run configurations. P00 is the reference project, so copy the
files from there.

## 0. Dev container

Add the locale variables to `.devcontainer/devcontainer.json` so the tools in the container run with UTF-8 (e.g. for umlauts in paths), then rebuild the container:

```jsonc
"containerEnv": {
  "LANG": "C.UTF-8",
  "LC_ALL": "C.UTF-8"
}
```

## 1. Copy the files

From P00 into the new project root:

```
.gdbinit                          # loads .idea/gdb-stop.py
.idea/qemu-start.sh               # starts QEMU in the background (chmod +x)
.idea/gdb-stop.py                 # stops at main / Reset_Handler after connecting
.idea/runConfigurations/*.xml     # make, make clean, QEMU starten (2x), P0 debuggen (2x)
```

```bash
SRC=$(echo /IdeaProjects/P00*); DST="/IdeaProjects/<new project>"
mkdir -p "$DST/.idea/runConfigurations"
cp $SRC/.gdbinit "$DST/"
cp $SRC/.idea/qemu-start.sh $SRC/.idea/gdb-stop.py "$DST/.idea/"
cp $SRC/.idea/runConfigurations/*.xml "$DST/.idea/runConfigurations/"
chmod +x "$DST/.idea/qemu-start.sh"
```

## 2. Adapt to the new project

Compare against the new project's `.vscode/launch.json`, `.vscode/tasks.json` and `GNUmakefile`:

| launch.json / Makefile                      | Where to change it                                              |
| ------------------------------------------- | --------------------------------------------------------------- |
| `executable` (e.g. `build/p1.elf`)          | `qemu-start.sh` (`-kernel`), `P0_debuggen_*.xml` (`symbolFile`) |
| `machine`, extra QEMU args                  | `qemu-start.sh`                                                 |
| `runToEntryPoint` (e.g. `main`)             | `gdb-stop.py` (`tbreak main`)                                   |
| Reset handler name                          | `gdb-stop.py` (`tbreak *Reset_Handler`)                         |
| Makefile name (`Makefile` vs `GNUmakefile`) | `make.xml`, `make_clean.xml` (`filename`)                       |
| Config name (e.g. "P1 debuggen")            | `name="..."` in `P0_debuggen_*.xml`                             |
| Extra tasks in tasks.json                   | copy `make.xml`, change `name` and `target`                     |

The QEMU config names are referenced from the debug configs (`run_configuration_name`), so rename them in both places.

## 3. Allow GDB to load the project's `.gdbinit`

Add one line per project to `~/.gdbinit`:

```bash
echo "add-auto-load-safe-path $(cd "$DST" && pwd -P)/.gdbinit" >> ~/.gdbinit
```

Use `pwd -P` rather than typing the path. Folder names with umlauts may be stored in decomposed form ("u" + combining mark), and a typed path won't
match. Without this line, debugging still works but doesn't stop at main or Reset. `~/.gdbinit` is lost when the dev container is rebuilt, so put this
line in `postCreateCommand` if you want it to survive.

## 4. Load and test in CLion

- CLion picks up **new** files in `.idea/runConfigurations/` automatically. It does **not** reliably reload **edited** ones. If you change a file
  after CLion has loaded it, move it out of the folder, wait a few seconds, then move it back (or rename the config).
- Test: run `make clean` then `make`, then debug both configs. "ab main" should stop in `main`, and "ab Reset" in `Reset_Handler`.

## 5. Clean up old files

Remove the old Makefile tasks from CLion, and remove the VS Code configuration files. 

## 6. Format the code

Run these commands on the host, not in the devcontainer:

```bash
mise exec npm:oxfmt -- oxfmt --config ~/projects-bennetrr/licium-player/.oxfmtrc.json
/opt/homebrew/opt/llvm/bin/clang-format "--style=file:../../7 Computergrafik 1/.clang-format" -i **/*.h **/*.c
```

## Why it's built this way

- **No "Embedded GDB Server" config.** It fails on Makefile projects with "Build target is not supported". Use "Remote Debug" (`CLion_Remote`) with
  before-launch tasks instead.
- **QEMU is daemonized** (`-daemonize`, `-display none -serial null -monitor none`). A before-launch task has to finish before GDB starts, so a
  foreground QEMU would block it.
- **`pkill -x qemu-system-arm`**, not `pkill -f …`. The `-f` pattern also matches the script itself, which then gets killed (exit 143).
- **Bundled GDB.** CLion ignores a custom GDB path in the Remote Debug config, so the stop logic lives in `.gdbinit`, which runs in any GDB.
- **"ab main"**: QEMU starts halted (`-S`), and a `tbreak main` is set on connect.
- **"ab Reset"**: QEMU starts _running_, and on connect GDB runs `monitor system_reset`, flushes its register cache and sets `tbreak *Reset_Handler`.
  A breakpoint at the PC GDB is already halted on would be skipped, and running `stepi` during connect makes CLion abort the session.
- QEMU keeps running after a debug session ends; the next launch kills it first.
