### Using PlatformIO with CLion

If you prefer a different IDE such as Clion from Jetbrains, you can get stared like so:
1. Download Clion from Jetbrains: https://www.jetbrains.com/clion/download/
2. Install PlatformIO Core: https://docs.platformio.org/en/latest/installation.html

    or
    ```
	$ pip install -U platformio
    ```

3. Create project directory
4. Install Clion plugins: `File Watchers`
5. Setup Project defaults:
    ```
	$ platformio init --ide clion --board esp32dev
    ```
6. Delete the contents of the file `src/main.cpp` and replace it with the code from our [Hello World](hello-world.cpp) example.
7. Compile the code into a runable binary:
    ```
    $ pio run
    ```
8. Upload the runnable binary over the serial port to the device:
    ```
    $ pio run --target upload
    ```
9. Monitor the serial ouput from the device:
    ```
    $ pio device monitor
    ```

### Using PlatformIO without an IDE

If you prefer a minimalist setup, you can forgo using an IDE and opt for 
your favourite text editor (Nano, vim, Notepad++).
 
By skipping step 1 above and only installing PlatformIO core you can still create code, compile and deploy to your device.
