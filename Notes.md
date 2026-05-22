## Video 3: Kconfig
- Each directory must have a .conf file where `=Y` and `=N` configurations are
- menuconfig and guiconfig can be used with Zephyr like Embedded Linux to configure Kconfig
    - This occurs with `west build`
- Kconfig syntax uses all Caps and start with CONFIG
- BSPs will have custom Kconfig symbols that are used
    - a **.config** file in the zephyr folder of build has all the configurations; including the ones not being used
    - `p -always` deletes the .config file so use `-auto` or save it as a file somewhere
- Kconfig manages software, DT manages hardware
- With Kconfig custom symbols Zephyr will not know what to do with it so create another folder
- `west build` can have the `DEXTRA_CONF_FILE` that will be used additionally to prj.conf

### Create Custom Kconfig Settings For Libraries
- Zephyr has documenation for such
1) To create a symbol use the `config` keyword
    - EX: `config SAY_HELLO`
2) Set a type of the symbol
    - EX: `bool "Basic print test to console`
3) Set the default
    - EX: `default n`, set to NO
4) **OPTIONAL**: Set dependencies
    - EX: `depends on <fill in>`
5) **OPTIONAL**: Help information
    - EX: `help Adds ...`

- Use Cmake to build the appropriate Kconfig libraries using if-statements
    - Use `zephyr_include_directories(.)`
    - Add source file: `zephyr_library_sources(say_hello.c)`

### Create a Zephyr Module
- Inside your library directory use a "zephyr" folder with a "module.yaml" file within that folder
- spacelift.io has yaml blog post
- To set the module name use `name:`
    - EX: `name: say_hello`
- You also need to put paths for the cmake.txt and the kconfig file
- Once the module has been created you can just call the header files
- Define Zephyr modules in the cmake.txt above the `find_package(...)`
- Doing this adds a config to menuconfig

## Video 4: Devicetree
- Maps pins to keep driver code free from that abstraction
- Syntax and structure in the zephyr docs help you create the different DT values
- **phandle**: Refers to other nodes using & defined somewhere else
- Add devices to a protocol like i2c using subnodes

- **chosen**: node keyword used to set properties for a specific node
- **aliases**: node keyword for shortcuts to a specific label
    - Prevents hardcoding and you can just use the alias to reference the node making it portable

- A node without a label means the full path is required to label it

- **dtsi** (Devicetree Source Include): common include between dts files
- **dts**: devicetree for specific nodes

- Binding yaml files match the compatible property name in nodes
- Use overlay files to override information in the dtsi file
    - Application specific 
- The include folder insidefe zephyr has all the Macros needed for the different peripherals needed to interact with the devicetree
- `DT_ALIAS` macro used to get alias device node
- Underscores (_) are used to device labels, but then aliases use dashes (-) instead
- dt-named functions used the devicetree to get properties to instantitate peripherals

## Video 5: Devicetree Bindings
- Bindings are unique to Zephyr, not used in Linux
- Zephyr starts with base 1 so adc1 in the manual is actually acd0 in the DT
- `reg` has the starting address and the bytes occupied to the right of it
    - `<0x4000, 4>`, address-cell and size-cell
- yaml `,` are underscores in c, used in file names
- Just like Linux, the goal of the Zephyr driver is to implement function overwrites like f_ops for Linux
- **Steps to use bindings**:
    1) Create aliases for the hardware being used from the DT (overlay)
    2) Set the properties of the nodes being used (overlay)
    3) In driver use the zephyr includes which will call the board functions for us
    4) Look at the functions found in the appropriate .h files
    5) Create a cmake.txt to get the build functionality
    6) Add the appropriate Kconfig values to allow the driver to work (look at zephyr main Cmake.txt to look for configs)

- Get node identifier using `DT_ALIAS` macro
- Get device struct using `DEVICE_DT_GET` which uses `DT_ALIAS`
- Each peripheral type should have a DT macro to get the CH reference
- `DT_PROP` macro lets us get a device node property from the DT
- Seq structs are stored in the .h for the peripheral
- interrupt.memfault.com zephyr

## Video 6: Device Driver
- Follow naming conventions for the driver code and the bindings to that of the zephyr source tree
    - Shawn says after `dts/bindings/` it shouldn't matter
- yaml file name doesn't matter, the **compatible** property does
- For the zephyr "module" create the "zephyr" folder followed by the module.yaml file
- The Zephyr struct device is found at /workdir/zephyr/include/zephyr/device.h
    - "config" is the configuration data at build time
    - "data" is what's modified at runtime
    - "api" is the function implementing subsystem API
- `sensor.h` is found at zephyr/include/zephyr/drivers/sensor.h
- `k_work` is a a workqueue kernel structure
- Fetch/Get APIs are bound to be depricated. Use read/decode instead since 3.6.
    - Read/Decode is asynch and uses Real-Time I/O
    - Aynch means the hardware completes the data collection without the CPU so that the CPU can visit when available.
- Have the data and config structs in .h with macros. Apis and everything else in .c
- The driver only uses the functions in the .c file so no reason to put forward declarations in .h file