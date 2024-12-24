import base64
import os
import sys
import subprocess

def main():
    try:
        # Read Base64-encoded input
        encoded_data = input("give here")

        # Decode the Base64 data
        # binary_data = base64.b64decode(encoded_data)

        # Run the `chal` binary and pass the decoded ELF as input
        proc = subprocess.Popen(["./chal"], stdin=subprocess.PIPE)
        proc.communicate(input=encoded_data)

    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
