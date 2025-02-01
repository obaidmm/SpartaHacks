#include <stdio.h>

void setBoardLED(int led, int r, int g, int b, int duration, int mode) {
    printf("Simulating setBoardLED: LED=%d, RGB=(%d,%d,%d), Duration=%d, Mode=%d\n", led, r, g, b, duration, mode);
}

void waitms(int ms) {
    printf("Simulating waitms: %d ms\n", ms);
}
