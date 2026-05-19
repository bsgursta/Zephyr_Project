# Introductory Zephyr RTOS Project

### This contains the main project folder code inside the Docker image

###

```
i2c1_default: i2c1_default {
		group1 {
			psels = <NRF_PSEL(TWIM_SDA, 1, 2)>,
				<NRF_PSEL(TWIM_SCL, 1, 3)>;
		};
	};
```

- This code shows the port and the pin. So SDA is on port 1 pin 2. SCL is port 1 pin 3. I2c2 since i2c0 is 1
