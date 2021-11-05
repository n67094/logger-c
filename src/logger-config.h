#ifndef LOGGER_CONFIG_H
#define LOGGER_CONFIG_H

#define LOGGER_WITH_COLOR 1

#define LOGGER_RESET_COLOR "\x1B[0m"

#define LOGGER_RED "\x1B[31m"
#define LOGGER_YELLOW "\x1B[33m"
#define LOGGER_GREEN "\x1B[32m"
#define LOGGER_BLUE "\x1B[34m"
#define LOGGER_MAGENTA "\x1B[35m"

#define LOGGER_INIT_MSG "logger.c initialization"
#define LOGGER_CLOSE_MSG "logger.c close"

#define LOGGER_ERROR_PREFIX " - [ERROR] --- "
#define LOGGER_WARNING_PREFIX " - [WARNING] - "
#define LOGGER_SUCCESS_PREFIX " - [SUCCESS] - "
#define LOGGER_INFO_PREFIX " - [INFO] ---- "
#define LOGGER_DEBUG_PREFIX " - [DEBUG] --- "

#define LOGGER_NO_TIME_PREFIX "Error on time()"

#define LOGGER_IN_FILE 1
#define LOGGER_IN_CONSOLE 1

#define LOGGER_FILENAME "log"

#endif
