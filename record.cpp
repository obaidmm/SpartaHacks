#include <iostream>
#include "freewili_api.h"  // Include the actual API header if available


void recordAudio() {
    std::string filename = "test_audio.wav";
    int duration = 5000; // 5 seconds

    std::cout << "Recording audio for " << duration / 1000 << " seconds...\n";
    
    recordSound(filename.c_str(), duration);

    std::cout << "Recording complete. Saved as " << filename << "\n";
}

void playRecordedAudio() {
    std::string filename = "test_audio.wav";
    
    std::cout << "Playing recorded audio: " << filename << "\n";
    playSound(filename.c_str());
}


int main() {
    recordAudio();           // Record for 5 seconds
    playRecordedAudio();

    return 0;
}