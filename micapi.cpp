#include <stdio.h>
#include "fwwsam/include/fwwasm.h"  // Make sure the correct path is used

// The following code will call the functions defined in the WebAssembly runtime
void recordSound(char * szSoundPath, int iLengthSeconds) WASM_IMPORT("recordSound");

int snprintf ( char * s, int32_t n, const char * format, ... ) __attribute__((import_module("env"))) __attribute__((import_name("snprintf")));


// Function to configure and record sound
void configureAndRecordSound() {
    // Set audio settings to stream mic data and enable plotting for microphone
   // setAudioSettings(1, 0, 1, 0, 0, 0);  // Using integer values (1 for true, 0 for false)
    
    // Specify the sound path and duration
    char soundPath[] = "/record/recorded_sound.wav";  
    int recordDuration = 2;  // Record for 10 seconds
    //char redDur[64] = "\0";
   // snprintf(redDur, sizeof(redDur), "Recording complete. Sound saved to: %s\n", soundPath); 
    //add a wait time     
    // Record the sound
    recordSound(soundPath, recordDuration);
    waitms(2000);
    
    // Print using printInt with appropriate color and data type
    //printInt(redDur, printColorGreen, printInt32, 0);
    printInt("Recording duration: %d seconds\n", printColorGreen, printInt32, recordDuration);
}

int main() {
    // Use printInt to replace printf
    printInt("Starting sound recording...\n", printColorGreen, printChar, 0);
    configureAndRecordSound();  // Configure and record the sound
    return 0;
}

