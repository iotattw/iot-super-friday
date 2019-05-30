# IoT Super Friday

This workshop involves programming ESP32 modules to take on different responsibilities as part of a larger network. We use [Visual Studio Code](https://code.visualstudio.com/) with the [Platform.IO](https://platformio.org) plugin.

We assume you're using a Mac lappy with Brew installed.

You (or your pair) will need:

* An ESP32 module 
* A laptop with a regular USB-A port (or USB-A dongle)
* Appropriate jumper cables and hardware for your project

## Getting Started

1. Install [CP210x drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) for the ESP32 modules
2. Install VS Code (if you don't already have it)
    ```bash
    brew cask install visual-studio-code
    ```
3. Install Platform․IO IDE (or search for the extension in VS Code)
    ```bash
    code --install-extension platformio.platformio-ide
    ```
4. Follow the [Platform.IO VS Code Quick Start](https://docs.platformio.org/en/latest/ide/vscode.html#quick-start) guide. When setting up a new project, use the following info:
   * Board: **Espressif ESP32 Dev Module**  
   * Framework: **Arduino**
5. Once you have completed the steps, delete the `main.cpp` project code and replace it with the code from our [Hello World](hello-world.cpp) example.
6. Upload the code. You should see a blue LED blinking on the ESP32 module. 