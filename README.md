📡 ESP32 Fake "Hacked" WiFi Portal (Prank Project)
This project turns your ESP32 into a fake “Hacked” WiFi access point, complete with a full-screen captive portal simulating a system infection, error popups, BSOD, fake permission requests, and terminal-style code animation. It's perfect for pranks — harmless, visually convincing, and totally self-contained.
🧰 Features
- Creates a WiFi AP with a custom SSID (default: Free_WiFi_Here)
- Redirects all DNS requests to ESP32’s IP (captive portal)
- Serves a spooky HTML+JS page simulating:
•	  Fake “SYSTEM INFECTED” alert
•	  Terminal-style fake logs
•	  Blinking ASCII art
•	  Fake permission popup for camera/microphone
•	  Animated progress bar
•	  Fake error messages
•	  Countdown to fake BSOD
•	  Audible beeps for added tension
•	  Locked screen (no back, zoom, scroll, context menu)
🔧 Getting Started
1. Clone or download this repository
   git clone https://github.com/your-username/esp32-hacked-wifi-prank.git
   Or download the ZIP and extract it.
2. Libraries
   ✅ All required libraries are included in the folder named libraries. Just copy this folder into your Arduino libraries/ directory OR use PlatformIO which automatically includes local libraries.
•	   Included libraries:
•	   ESPAsyncWebServer
•	   AsyncTCP
•	   ESPAsyncDNSServer
3. Hardware Requirements
•	   ESP32 board (e.g., DevKit v1)
•	   Micro USB cable
•	   Power source (USB or battery)
4. Flashing the Code
•	   Open the .ino file using Arduino IDE.
•	   Select your board under Tools > Board > ESP32 Dev Module.
•	   Select the correct COM port.
•	   Hit Upload.
5. Run
•	   Open Serial Monitor at 115200 baud.
•	   The ESP32 will:
•	     Start a WiFi AP named Free_WiFi_Here
•	      Log connected devices
•	      Serve the prank page at http://192.168.4.1
⚠️ Disclaimer
This is a prank for educational and entertainment purposes only.
It does not actually harm, spy on, or infect devices.
Do not use it on people without their consent, especially in public places.
