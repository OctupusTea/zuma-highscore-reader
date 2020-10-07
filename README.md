# Zuma Deluxe Highscore Reader
An highscore file reader for the beloved sphere-matching game Zuma Deluxe

# Build
## Dependicies
- GNU C++11
- Makefile

## Building steps
```bash
cd zuma-highscore-reader
make                 # for regular bulid
make DGLAGS=-DDEBUG  # for debugging output
```

# Execution & Usage
- Linux: `./bin/reader`
- Windows: `bin\reader`

## Command line argument
- File path(s): Path to the desired `highscore.dat` files(s) to read
- `-h`: Display help

# Future Works
- Modded game support
- `levels.xml` support