# logger-c

An ANSI C (C89) header only lib for logs

![image](https://user-images.githubusercontent.com/15613425/143301975-5f01fd49-92a6-476a-a14a-d54203b58abf.png)

## Build example

```
cd example
make
```

## Configuration

c.f logger_config.h for options

this is how to override default configuration ex. custom-logger.h

```
#ifndef CUSTOM_LOGGER_HPP
#define CUSTOM_LOGGER_HPP

#define LOGGER_IN_FILE 0 // if you don't want to log an a file
#define LOGGER_INIT_MSG "Hello world !" // message printed once the logger is initialised
#define LOGGER_CLOSE_MSG "Bye world !" // message printed once the logger is closed

#include "logger.h"

#endif
```

then on your files, use your custom include (1):

```
#include "custom-logger.h

LoggerInit();

{{others code}}

LoggerError("This is an %s !", "example");

{{others code}}

LoggerClose();
```

(1) Make sure to override configuration only once, and in that case to use your custom include instead of logger.h, if you override it here and there, or mix includes, you can accounter assertions errors.

## Notes

Feel free to report bugs and improvements

## Like this work ?

Help me create more of it.

[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://www.buymeacoffee.com/n67094)
