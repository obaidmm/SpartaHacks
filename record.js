// Step 1: Record 5 seconds of audio
recordSound("my_audio.wav", 5000);

// Step 2: Enable streaming
setAudioSettings({
  stream: true,
  fft: true,
  mic: true
});

// Step 3: Detect loud sounds
if (getMicLevel() > 80) {
  console.log("Loud sound detected!");
}

// Step 4: Play back the recorded audio
setTimeout(() => {
  playSound("my_audio.wav");
}, 6000); // Delay playback to ensure recording is finished
