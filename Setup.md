# Instructions to get Zephyr image working

1. Visit official docker image repo for Zephyr

    https://github.com/zephyrproject-rtos/docker-image

    - Get all 3 versions of the build base,ci, and dev **NO LONGER NEEDED**
        - This step is subject to change on Arch Linux since the docker build command has issues.
    - Go to the official build image for zephyr and download 0.26 which is LTS.

2. Perform the default build commands in ~ directory
    - $ west init 
        - $ west init -m https://github.com/zephyrproject-rtos/zephyr --mr v3.7.0 . **Command for a specific version (LTS)**
    - $ west update
        - If west init is interrupted you will have change ZEPHYR_BASE before doing the command again. Or just delete the container.
    https://docs.zephyrproject.org/latest/develop/getting_started/index.html

3. Install the nrfjprog and jlink

    - go to the nrf site and get the nrf-tools tar.gz
    - move the extracted folder with 2 inner folders to the /opt/nordic folder (create if needed)

    - After extracted point the PATH to the nrfjprog bin and the linkjarm.so for the jlink using the code below in .bashrc
        # Nordic nRF Command Line Tools
        export PATH=$PATH:/opt/nordic/nrf-command-line-tools/bin
        
        # J-Link Shared Libraries
        export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/opt/nordic/JLink_Linux_V794e_x86_64"
    - Make sure to give file permissions to both files
        $ sudo chmod +x /opt/nordic/nrf-command-line-tools/bin/*
        $ sudo chmod +x /opt/nordic/JLink_Linux_V794e_x86_64/*.so*

4. Install usbutilies
    - $ sudo apt update
      $ sudo apt install usbutils
    - Remember I'm in ubuntu in the container so use apt

5. Build project flash with west
    $ west build -p always -b nrf5340dk/cpuapp samples/basic/blinky

-- DEBUGGING

Install the cross compilier in /opt
Point the vscode launch.json to the server in the Jlink folder

Restart the container if it doesn't work the first time
