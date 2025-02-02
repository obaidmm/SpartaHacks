import sounddevice as sd

print("Available audio input devices:")
print(sd.query_devices())
