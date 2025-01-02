# Usage
```
gcc main.c -o main
sudo ./main
```
After that, you will see the keys you have pressed in the console.

## Principe
We just parse /proc/bus/input/devices to find our keyboard event, then we can read /dev/input/[event] that actually our keyboard and resolve this bytes with keys.h.
