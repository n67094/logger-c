#ifndef LOGGER_CONFIG_H
#define LOGGER_CONFIG_H

#ifndef LOGGER_WITH_COLOR
#  define LOGGER_WITH_COLOR 1
#endif

#ifndef LOGGER_RESET_STYLE
#  define LOGGER_RESET_STYLE "\x1B[0m"
#endif

/* Color code */
#ifndef LOGGER_RED
#  define LOGGER_RED "\x1B[31m"
#endif
#ifndef LOGGER_YELLOW
#  define LOGGER_YELLOW "\x1B[33m"
#endif
#ifndef LOGGER_GREEN
#  define LOGGER_GREEN "\x1B[32m"
#endif
#ifndef LOGGER_BLUE
#  define LOGGER_BLUE "\x1B[34m"
#endif
#ifndef LOGGER_MAGENTA
#  define LOGGER_MAGENTA "\x1B[35m"
#endif

/* Style code */
#ifndef LOGGER_FAINT
#  define LOGGER_FAINT "\x1B[2m"
#endif

#ifndef LOGGER_INIT_MSG
#  define LOGGER_INIT_MSG "logger.c initialization"
#endif
#ifndef LOGGER_CLOSE_MSG
#  define LOGGER_CLOSE_MSG "logger.c close"
#endif

#ifndef LOGGER_ERROR_PREFIX
#  define LOGGER_ERROR_PREFIX " - [ERROR] --- "
#endif
#ifndef LOGGER_WARRNING_PREFIX
#  define LOGGER_WARNING_PREFIX " - [WARNING] - "
#endif
#ifndef LOGGER_SUCCESS_PREFIX
#  define LOGGER_SUCCESS_PREFIX " - [SUCCESS] - "
#endif
#ifndef LOGGER_INFO_PREFIX
#  define LOGGER_INFO_PREFIX " - [INFO] ---- "
#endif
#ifndef LOGGER_DEBUG_PREFIX
#  define LOGGER_DEBUG_PREFIX " - [DEBUG] --- "
#endif

#ifndef LOGGER_NO_TIME_PREFIX
#  define LOGGER_NO_TIME_PREFIX "Error on time()"
#endif

#ifndef LOGGER_IN_FILE
#  define LOGGER_IN_FILE 1
#endif
#ifndef LOGGER_IN_CONSOLE
#  define LOGGER_IN_CONSOLE 1
#endif

#ifndef LOGGER_FILENAME
#  define LOGGER_FILENAME "log"
#endif

#endif
