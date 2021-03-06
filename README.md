# IoT Super Friday

This workshop involves programming ESP32 modules to take on different responsibilities as part of a larger network. We use  [PlatformIO](https://platformio.org) as the development environment.

We assume you're using a Mac lappy with Brew installed.

You (or your pair) will need:

* An ESP32 module 
* A laptop with a regular USB-A port (or USB-A dongle)
* Appropriate jumper cables and hardware for your project

## Getting Started with PlatformIO

Install [CP210x drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) for the ESP32 modules.

For the next steps, feel free to use either [Visual Studio Code](#using-platformio-with-visual-studio-code) or [CLion](#using-platformio-with-clion).

### Using PlatformIO with Visual Studio Code

1. Install VS Code (if you don't already have it)
    ```bash
    brew cask install visual-studio-code
    ```
2. Install PlatformIO IDE (or search for the extension in VS Code)
    ```bash
    code --install-extension platformio.platformio-ide
    ```
3. Follow the [PlatformIO VS Code Quick Start](https://docs.platformio.org/en/latest/ide/vscode.html#quick-start) guide. When setting up a new project, use the following info:
   * Board: **Espressif ESP32 Dev Module**  
   * Framework: **Arduino**
4. Once you have completed the steps in the Quick Start Guide, delete the contents of the file `src/main.cpp` and replace it with the code from our [Hello World](hello-world.cpp) example.
5. Build the code with the `✓` icon and upload the code with the `➡` icon (both in the footer menu bar). You should now see a blue LED blinking on the ESP32 module.

## Projects

Once you have the ESP32 module drivers installed and PlatformIO set up and ready, you can start with one of these projects.

* [Motion Sensor](motion-sensor/)
* [Build Monitor](build-monitor/)
* [Glowing Eyes](glowing-eyes/)
* [Glowing Eyes Connected](glowing-eyes-connected/)
* [Remote toggle](remote-toggle/)