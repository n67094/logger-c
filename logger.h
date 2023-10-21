#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "logger_config.h"

#define LOGGER_LEVEL_INFO 0b00001
#define LOGGER_LEVEL_DEBUG 0b00010
#define LOGGER_LEVEL_SUCCESS 0b00100
#define LOGGER_LEVEL_WARNING 0b01000
#define LOGGER_LEVEL_ERROR 0b10000
#define LOGGER_LEVEL_ALL 0b11111

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static void LoggerInit();
static int LoggerClose();

static void LoggerSetLevel(int flags);
static void LoggerInfo(const char *msg, ...);
static void LoggerDebug(const char *msg, ...);
static void LoggerSuccess(const char *msg, ...);
static void LoggerWarning(const char *masg, ...);
static void LoggerError(const char *msg, ...);

static FILE *logger_file = NULL;

static int logger_level = LOGGER_LEVEL_ALL;

/*
 * used to know if we can write in file, set to 1 if the file can't be
 * opened
 */
static int logger_file_error = 0;

static void LoggerReplaceSpace(char *pointer, const char character) {
  while (*pointer) {
    if (*pointer == ' ')
      *pointer = character;

    pointer++;
  }
}

/* returned pointer should be freed */
static char *LoggerGetTime() {
  char *date = NULL;
  time_t current_date = time(NULL);

  if (current_date == (time_t)(-1)) {
    date = (char *)malloc(sizeof(char) * strlen(LOGGER_NO_TIME_PREFIX) + 1);
    strcpy(date, LOGGER_NO_TIME_PREFIX);
  } else {
    int date_length = sizeof(char) * 20;
    date = (char *)malloc(date_length);

    strftime(date, date_length, "%Y-%m-%d %H:%M:%S", gmtime(&current_date));

    char *newline = strchr(date, '\n');
    if (newline != NULL)
      *newline = '\0';
  }

  return date;
}

static int LoggerOpenFile() {
  char *date = LoggerGetTime();

  int filename_length = strlen(LOGGER_FILENAME);
  int date_length = strlen(date);

  /* + 1 for the - between filename and date and + 1 for /0 */
  char *full_filename =
      (char *)malloc(sizeof(char) * (filename_length + date_length + 2));
  *full_filename = '\0';

  strcat(full_filename, LOGGER_FILENAME);
  strcat(full_filename, "-");
  strcat(full_filename, date);
  strcat(full_filename, "\0");

  LoggerReplaceSpace(full_filename, '_');

  logger_file = fopen(full_filename, "a+");

  if (logger_file == NULL) {
    printf("log.c error opening file %s", full_filename);
    logger_file_error = 1;
    return 1;
  }

  free(full_filename);
  full_filename = NULL;

  free(date);
  date = NULL;

  return 0;
};

static int LoggerCloseFile() {
  if (logger_file != NULL) {
    return fclose(logger_file);
  }

  return 0;
}

static void LoggerInFile(int msg_length, const char *date, const char *prefix,
                         const char *msg, va_list args) {

  assert(logger_file != NULL && "no file opened");

  /* + 2 for \n and \0 added below */
  char *full_msg = (char *)malloc(sizeof(char) * (msg_length + 2));
  *full_msg = '\0';

  strcat(full_msg, date);
  strcat(full_msg, prefix);
  strcat(full_msg, msg);
  strcat(full_msg, "\n");
  strcat(full_msg, "\0");

  vfprintf(logger_file, full_msg, args);

  free(full_msg);
  full_msg = NULL;
}

static void LoggerInConsole(int msg_length, const char *date, const char *color,
                            const char *prefix, const char *msg, va_list args) {
  /* + 2 for \n and \0 added below */
  char *full_msg = (char *)malloc(sizeof(char) * (msg_length + 2));
  *full_msg = '\0';

  if (LOGGER_WITH_COLOR)
    strcat(full_msg, LOGGER_FAINT);

  strcat(full_msg, date);

  if (LOGGER_WITH_COLOR)
    strcat(full_msg, LOGGER_RESET_STYLE);

  if (LOGGER_WITH_COLOR)
    strcat(full_msg, color);

  strcat(full_msg, prefix);

  if (LOGGER_WITH_COLOR)
    strcat(full_msg, LOGGER_RESET_STYLE);

  strcat(full_msg, msg);
  strcat(full_msg, "\n");
  strcat(full_msg, "\0");

  vprintf(full_msg, args);

  free(full_msg);
  full_msg = NULL;
}

/*
 * Since va_copy is only available in c99 I use two va_list, va_list are
 * invalidated by vprintf and vfprintf so it cannot be used twice
 */
static void Logger(const char *color, const char *msg, const char *prefix,
                   va_list v_list_1, va_list v_list_2) {
  int msg_length = strlen(msg);
  int prefix_length = strlen(prefix);

  char *date = LoggerGetTime();
  int date_length = strlen(date);

  if (LOGGER_IN_FILE && logger_file_error != 1) {
    int full_msg_length = date_length + prefix_length + msg_length;

    LoggerInFile(full_msg_length, date, prefix, msg, v_list_1);
  }

  if (LOGGER_IN_CONSOLE) {
    int full_msg_length = 0;

    if (LOGGER_WITH_COLOR == 1) {
      int faint_style_length = strlen(LOGGER_FAINT);
      int color_length = strlen(color);
      int reset_style_length = strlen(LOGGER_RESET_STYLE);

      full_msg_length = faint_style_length + date_length + reset_style_length +
                        color_length + prefix_length + reset_style_length +
                        msg_length;
    } else {
      full_msg_length = date_length + prefix_length + msg_length;
    }

    LoggerInConsole(full_msg_length, date, color, prefix, msg, v_list_2);
  }

  free(date);
  date = NULL;
};

void LoggerInit() {
  if (LOGGER_IN_FILE) {
    LoggerOpenFile();
  }
  LoggerInfo(LOGGER_INIT_MSG);
}

void LoggerSetLevel(int flags) { logger_level = flags; }

void LoggerInfo(const char *msg, ...) {
  if (logger_level & LOGGER_LEVEL_INFO) {
    va_list v_list_1;
    va_list v_list_2;
    va_start(v_list_1, msg);
    va_start(v_list_2, msg);

    Logger(LOGGER_BLUE, msg, LOGGER_INFO_PREFIX, v_list_1, v_list_2);

    va_end(v_list_1);
    va_end(v_list_2);
  }
};

void LoggerDebug(const char *msg, ...) {
  if (logger_level & LOGGER_LEVEL_DEBUG) {
    va_list v_list_1;
    va_list v_list_2;
    va_start(v_list_1, msg);
    va_start(v_list_2, msg);

    Logger(LOGGER_MAGENTA, msg, LOGGER_DEBUG_PREFIX, v_list_1, v_list_2);

    va_end(v_list_1);
    va_end(v_list_2);
  }
};

void LoggerSuccess(const char *msg, ...) {
  if (logger_level & LOGGER_LEVEL_SUCCESS) {
    va_list v_list_1;
    va_list v_list_2;
    va_start(v_list_1, msg);
    va_start(v_list_2, msg);

    Logger(LOGGER_GREEN, msg, LOGGER_SUCCESS_PREFIX, v_list_1, v_list_2);

    va_end(v_list_1);
    va_end(v_list_2);
  }
};

void LoggerWarning(const char *msg, ...) {
  if (logger_level & LOGGER_LEVEL_WARNING) {
    va_list v_list_1;
    va_list v_list_2;
    va_start(v_list_1, msg);
    va_start(v_list_2, msg);

    Logger(LOGGER_YELLOW, msg, LOGGER_WARNING_PREFIX, v_list_1, v_list_2);

    va_end(v_list_1);
    va_end(v_list_2);
  }
};

void LoggerError(const char *msg, ...) {
  if (logger_level & LOGGER_LEVEL_ERROR) {
    va_list v_list_1;
    va_list v_list_2;
    va_start(v_list_1, msg);
    va_start(v_list_2, msg);

    Logger(LOGGER_RED, msg, LOGGER_ERROR_PREFIX, v_list_1, v_list_2);

    va_end(v_list_1);
    va_end(v_list_2);
  }
};

int LoggerClose() {
  LoggerInfo(LOGGER_CLOSE_MSG);
  return LoggerCloseFile();
}

#ifdef __cplusplus
}
#endif

#endif
