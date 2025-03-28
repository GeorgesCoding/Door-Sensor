""" 
python script to convert any mp3 file into a C style hex dump that can be interpreted 
using the MP3DecoderHelix library using no dependencies other than Python itself 

instructions: place this script into the same directory as the mp3 file and run it using "python converter.py"
"""





import glob
import os

file = glob.glob('*.mp3')[0]

with open(file, "rb") as f:
    data = f.read()

hex_data = ", ".join(f"0x{byte:02X}" for byte in data)
count = hex_data.count(",") + 1

try:
    os.chdir("../include")
except FileNotFoundError:
    os.chdir("../")
    os.makedirs("include")
    os.chdir("include")

try:
    os.remove("audio.h")
except FileNotFoundError:
    pass

with open("audio.h", "w") as f:
    f.write("const unsigned char audio[] = ")
    f.write("{ " + hex_data + " };\n\n")
    f.write("const unsigned int length = " + str(count) + ";")

print("Header file created")
