# NDS Hello World - Pikachu Demo

A beginner-friendly "Hello World" Nintendo DS homebrew application that displays text on the console and renders a simple sprite on the top screen.

## Prerequisites

### Ubuntu Installation
See [UBUNTU_INSTALL.md](UBUNTU_INSTALL.md) for detailed Ubuntu/Linux installation instructions.

### macOS Installation
See [MACOS_INSTALL.md](MACOS_INSTALL.md) for detailed macOS installation instructions.

## Project Structure

```
nds-hello/
├── source/
│   └── main.c          # Application source code
├── Makefile            # Build configuration
├── UBUNTU_INSTALL.md   # Ubuntu installation guide
├── MACOS_INSTALL.md   # macOS installation guide
└── README.md          # This file
```

## Building

1. **Install devkitPro** first (see installation guides above)

2. **Set environment variables** (if not already set):
   ```bash
   export DEVKITPRO=/opt/devkitpro
   export DEVKITARM=$DEVKITPRO/devkitARM
   export PATH=$DEVKITPRO/tools/bin:$PATH
   ```

3. **Build the project**:
   ```bash
   cd nds-hello
   make
   ```

4. **Output**: Creates `nds-hello.nds` in the project directory

## Running

### On Hardware (PicoDS)
1. Copy `nds-hello.nds` to your PicoDS micro SD card
2. Boot your Nintendo DS
3. Navigate to the file and run it

### On Emulator
- **melonDS**: Open the `.nds` file directly
- **DeSmuME**: Open the `.nds` file directly

## Controls

| Button | Action |
|--------|--------|
| START | Exit application |

## What It Does

- Displays "Pikachu Hello World!" text on the bottom screen console
- Renders a simple 32x32 sprite on the top screen
- Shows control instructions

## Troubleshooting

### "Please set DEVKITARM in your environment"
Run: `source ~/.bashrc` (Ubuntu) or `source ~/.zshrc` (macOS)

### Build fails
Ensure devkitPro is installed: `dkp-pacman -S nds-dev`

### Sprite not showing
The sprite demo uses 16-color format. For more complex graphics, consider using converted sprite sheets with proper palette configuration.

## Next Steps

Once you've verified this works:
1. Try modifying the sprite graphics in `main.c`
2. Add button input handling
3. Explore the libnds examples in `/opt/devkitpro/libnds/examples`
4. Learn about sprite animation, audio, and touch input

## Resources

- libnds Documentation: https://libnds.devkitpro.org/
- devkitPro Wiki: https://devkitpro.org/wiki/
- GBAtemp NDS Homebrew Forum: https://gbatemp.net/forums/nds-homebrew.60/

---

*Created for Nintendo DS Homebrew Development*
