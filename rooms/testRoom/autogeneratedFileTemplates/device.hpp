{header}

#ifndef DEVICE_H_
#define DEVICE_H_

#include <stdint.h>
                
#define DEV_NAME "{name}"
#define DEV_ADDRESS {address}

typedef uint8_t Command_t;

typedef enum : Command_t {{
{commands}
}} Command_e;


typedef uint8_t ReturnCode_t;

typedef enum : ReturnCode_t {{
{returnCodes}
}} ReturnCode_e;


typedef uint8_t Component_t;

typedef enum : Component_t {{
{components}
}} Component_e;
{footer}
#endif
