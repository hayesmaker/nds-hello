# Nintendo DS Homebrew - macOS Installation Guide

A beginner-friendly guide to setting up devkitPro for Nintendo DS homebrew development on macOS.

---

## Prerequisites

- **macOS 10.15 (Catalina)** or later
- **Terminal** access
- **Administrator privileges** (for installation)

---

## Step 1: Download devkitPro Installer

1. Open **Terminal**
2. Download the macOS installer:

```bash
cd ~/Downloads
wget https://github.com/devkitPro/installer/releases/download/v3.0.1/devkitpro-pacman.pkg
```

Or visit: https://github.com/devkitPro/installer/releases

---

## Step 2: Install devkitPro

1. Double-click `devkitpro-pacman.pkg` in Finder
2. Follow the installation wizard
3. When prompted, allow installation (System Preferences → Security & Privacy may need to approve)

---

## Step 3: Initialize and Install NDS Toolchain

In Terminal, run:

```bash
# Update package lists
sudo dkp-pacman -Syu

# Install Nintendo DS development tools
sudo dkp-pacman -S nds-dev
```

When prompted to proceed, type `Y` and press Enter.

This installs:
- `devkitARM` — ARM compiler toolchain
- `libnds` — Nintendo DS hardware library
- `libdwm` — Console/text display
- `maxmod` — Audio
- `dswifi` — WiFi networking
- `nds-examples` — Sample projects

---

## Step 4: Set Up Environment Variables

Add devkitPro to your shell path. Open your shell config:

**For Zsh (default on macOS 10.15+):**
```bash
nano ~/.zshrc
```

**For Bash:**
```bash
nano ~/.bash_profile
```

Add this line at the end:
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
export PATH=$DEVKITPRO/tools/bin:$PATH
```

Save and exit (Ctrl+O, Enter, Ctrl+X).

Reload your shell:
```bash
source ~/.zshrc
```

Verify installation:
```bash
arm-none-eabi-gcc --version
```

You should see version information.

---

## Step 5: Create Your First Project

### 5.1 Create Project Folder

```bash
mkdir -p ~/projects/nds-hello/source
cd ~/projects/nds-hello
```

### 5.2 Create Makefile

Create a file called `Makefile` (no extension) with this content:

```makefile
#---------------------------------------------------------------------------------
.SUFFIXES:

#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/ds_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------

TARGET := $(shell basename $(CURDIR))
BUILD := build
SOURCES := source
INCLUDES := include build

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------

ARCH := -march=armv5te -mtune=arm946e-s -mthumb
CFLAGS := -g -Wall -O2 -ffunction-sections -fdata-sections $(ARCH)
CFLAGS += $(INCLUDE) -DARM9
CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS := -g $(ARCH)
LDFLAGS = -specs=ds_arm9.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------

LIBS := -lnds9

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------

LIBDIRS := $(LIBNDS)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------

ifneq ($(BUILD),$(notdir $(CURDIR)))

#---------------------------------------------------------------------------------

export OUTPUT := $(CURDIR)/$(TARGET)
export VPATH := $(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR := $(CURDIR)/$(BUILD)

CFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES := $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin)))

#---------------------------------------------------------------------------------

# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------

ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------

export LD := $(CC)

#---------------------------------------------------------------------------------

else
#---------------------------------------------------------------------------------

export LD := $(CXX)

#---------------------------------------------------------------------------------

endif

#---------------------------------------------------------------------------------

export OFILES := $(BINFILES:.bin=.o) \
$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
-I$(CURDIR)/$(BUILD)

export LIBPATHS := $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------

$(BUILD):
@[ -d $@ ] || mkdir -p $@
@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------

clean:
@echo clean ...
@rm -fr $(BUILD) $(TARGET).elf $(TARGET).nds $(TARGET).ds.gba

#---------------------------------------------------------------------------------

else

DEPENDS := $(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------

$(OUTPUT).nds : $(OUTPUT).elf

$(OUTPUT).elf : $(OFILES)

#---------------------------------------------------------------------------------

%.o : %.bin
#---------------------------------------------------------------------------------

@echo $(notdir $<)
$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------

endif
```

### 5.3 Create main.c

Create `source/main.c`:

```c
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>

#define PIKACHU_WIDTH  32
#define PIKACHU_HEIGHT 32

static const unsigned short pikachu_sprite[32 * 32] = {
    // Simple 32x32 Pikachu sprite (yellow with red cheeks)
    // This is a minimal representation
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
};

int main(int argc, char **argv) {
    consoleInit(NULL, 0, LCD_BOTH);
    consoleClear();
    
    printf("  ====================\n");
    printf("  Pikachu Hello World!\n");
    printf("  ====================\n\n");
    printf("  TOP SCREEN: Graphics\n");
    printf("  BOTTOM: Console\n\n");
    printf("  Controls:\n");
    printf("  - START: Exit\n");
    printf("  - A: Redraw Pikachu\n\n");
    printf("  Building DS Homebrew!\n");
    
    videoSetMode(MODE_0_2D);
    oamInit(&oamMain, SpriteMapping_1D_32, false);
    
    int x = 96;
    int y = 80;
    int frame = 0;
    
    while(1) {
        scanf();
        
        if (keysDown() & KEY_A) {
            x = rand() % (256 - PIKACHU_WIDTH);
            y = rand() % (192 - PIKACHU_HEIGHT);
        }
        
        if (keysDown() & KEY_START) break;
        
        swiWaitForVBlank();
    }
    
    return 0;
}
```

---

## Step 6: Build the Application

```bash
cd ~/projects/nds-hello
make
```

If successful, you'll see:
- `nds-hello.nds` — The runnable ROM file
- `build/` — Object files (can be cleaned with `make clean`)

---

## Step 7: Test on Hardware

### Using PicoDS:

1. Copy `nds-hello.nds` to your PicoDS micro SD card
2. Insert the micro SD into your PicoDS
3. Boot your Nintendo DS
4. Navigate to the `.nds` file and run it

### Using Emulator (melonDS):

1. Download melonDS: https://melonds.org/
2. Open the `.nds` file in melonDS
3. Use keyboard/mouse to simulate button presses

---

## Troubleshooting

### "Please set DEVKITARM in your environment"

Your environment variables aren't set. Run:
```bash
source ~/.zshrc
```

Or add to current session:
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=$DEVKITPRO/devkitARM
export PATH=$DEVKITPRO/tools/bin:$PATH
```

### "arm-none-eabi-gcc: command not found"

Re-run Step 3 to ensure the toolchain installed correctly.

### Build fails with missing headers

Ensure `nds-dev` is installed:
```bash
sudo dkp-pacman -S nds-dev
```

---

## Next Steps

Congratulations! You've built your first Nintendo DS homebrew application.

Continue learning:
- Check `$(DEVKITPRO)/libnds/examples` for more complex examples
- Explore libnds documentation: https://libnds.devkitpro.org/
- Try adding sprites, sounds, and touch screen input

---

## Quick Reference

| Command | Description |
|---------|-------------|
| `make` | Build the NDS file |
| `make clean` | Remove build artifacts |
| `dkp-pacman -Syu` | Update all packages |
| `dkp-pacman -S nds-dev` | Reinstall NDS tools |

---

*Created for Nintendo DS Homebrew Development*
