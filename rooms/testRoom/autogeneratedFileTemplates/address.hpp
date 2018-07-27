{header}

#ifndef ADDRESS_H_ 
#define ADDRESS_H_
                
#include <stdint.h>
                
typedef uint8_t Address_t;

typedef enum : Address_t {{
{addressEnum}
}} Address_e;


#define PACKET_TERMINATOR {packetTerminator}

#define UART_BAUDRATE {uartBaudrate}
#define UART_TIMEOUT {uartTimeout}

typedef uint8_t I2C_address_t;
#define I2C_BAUDRATE {i2cBaudrate}
#define I2C_TIMEOUT {i2cTimeout}


I2C_address_t I2C_TABLE[{i2cAddressesN}] = {{
{i2cTable}
}};
{footer}
#endif
