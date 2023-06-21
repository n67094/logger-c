# logger.c

An ANSI C (C89) header only lib for logs

![image](https://user-images.githubusercontent.com/15613425/143301975-5f01fd49-92a6-476a-a14a-d54203b58abf.png)

## Build example

```
cd example
make
```

## Configuration

c.f logger.h for options

this is how to override default configuration

```
/* configuration */
#define LOGGER_IN_FILE 0
#define LOGGER_INIT_MSG "Hello world !"

#include "logger.h"

LoggerInit();

...

LoggerClose();

```

## Notes

Feel free to report bugs and improvements

## Like this work ?

Help me create more of it.

[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/n67094)
