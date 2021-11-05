#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logger-config.h"
#include "logger.h"

FILE* file = NULL;

int loggerLevel = LOGGER_LEVEL_ALL;

void static LoggerOpenFile()
{
	file = fopen(LOGGER_FILENAME, "a+");

	if (file == NULL) {
		printf("log.c error opening file %s", LOGGER_FILENAME);
		exit(0);
	}
};

int static LoggerCloseFile()
{
	return fclose(file);
}

/*
 * Since va_copy is only available in c99 I use two va_list, va_list are invalidated by vprintf and vfprintf so it cannot be used twice
 */
void static Logger(char* color, char* msg, char* prefix, va_list vList1, va_list vList2)
{
	time_t currentDate = time(NULL);

	char* date = NULL;

	int dateLength = 0;
	int msgLength = strlen(msg);
	int prefixLength = strlen(prefix);

	if (currentDate == (time_t)(-1)) {
		dateLength = strlen(LOGGER_NO_TIME_PREFIX);

		date = LOGGER_NO_TIME_PREFIX;
	} else {
		date = asctime(gmtime(&currentDate));

		/* remove \n of asctime() */
		char* newline = strchr(date, '\n');
		if (newline != NULL)
			*newline = '\0';

		dateLength = strlen(date);
	}

	if (LOGGER_IN_FILE) {
		/* + 1 for \n added below*/
		char* fullMsg = malloc(sizeof(char) * (dateLength + prefixLength + msgLength + 1));
		*fullMsg = '\0';

		strcat(fullMsg, date);
		strcat(fullMsg, prefix);
		strcat(fullMsg, msg);
		strcat(fullMsg, "\n");

		vfprintf(file, fullMsg, vList1);

		free(fullMsg);
		fullMsg = NULL;
	}

	if (LOGGER_IN_CONSOLE) {

		char* fullMsg = NULL;

		if (LOGGER_WITH_COLOR == 1) {
			int colorLength = strlen(color);

			/* + 1 for \n added below*/
			fullMsg = malloc(sizeof(char) * (colorLength + dateLength + prefixLength + msgLength + 1));
			*fullMsg = '\0';

			strcat(fullMsg, color);
		} else {
			/* + 1 for \n added below*/
			fullMsg = malloc(sizeof(char) * (dateLength + prefixLength + msgLength + 1));
			*fullMsg = '\0';
		}

		strcat(fullMsg, date);
		strcat(fullMsg, prefix);
		strcat(fullMsg, msg);
		strcat(fullMsg, "\n");

		vprintf(fullMsg, vList2);

		if (LOGGER_WITH_COLOR)
			printf("%s", LOGGER_RESET_COLOR);

		free(fullMsg);
		fullMsg = NULL;
	}
};

void LoggerInit()
{
	LoggerOpenFile();
	LoggerInfo(LOGGER_INIT_MSG);
}

void LoggerSetLevel(int flags)
{
	loggerLevel = flags;
}

void LoggerInfo(char* msg, ...)
{
	if (loggerLevel & LOGGER_LEVEL_INFO) {
		va_list vlist1;
		va_list vlist2;
		va_start(vlist1, msg);
		va_start(vlist2, msg);

		Logger(LOGGER_BLUE, msg, LOGGER_INFO_PREFIX, vlist1, vlist2);

		va_end(vlist1);
		va_end(vlist2);
	}
};

void LoggerDebug(char* msg, ...)
{
	if (loggerLevel & LOGGER_LEVEL_DEBUG) {
		va_list vlist1;
		va_list vlist2;
		va_start(vlist1, msg);
		va_start(vlist2, msg);

		Logger(LOGGER_MAGENTA, msg, LOGGER_DEBUG_PREFIX, vlist1, vlist2);

		va_end(vlist1);
		va_end(vlist2);
	}
};

void LoggerSuccess(char* msg, ...)
{
	if (loggerLevel & LOGGER_LEVEL_SUCCESS) {
		va_list vlist1;
		va_list vlist2;
		va_start(vlist1, msg);
		va_start(vlist2, msg);

		Logger(LOGGER_GREEN, msg, LOGGER_SUCCESS_PREFIX, vlist1, vlist2);

		va_end(vlist1);
		va_end(vlist2);
	}
};

void LoggerWarning(char* msg, ...)
{
	if (loggerLevel & LOGGER_LEVEL_WARNING) {
		va_list vlist1;
		va_list vlist2;
		va_start(vlist1, msg);
		va_start(vlist2, msg);

		Logger(LOGGER_YELLOW, msg, LOGGER_WARNING_PREFIX, vlist1, vlist2);

		va_end(vlist1);
		va_end(vlist2);
	}
};

void LoggerError(char* msg, ...)
{
	if (loggerLevel & LOGGER_LEVEL_ERROR) {
		va_list vlist1;
		va_list vlist2;
		va_start(vlist1, msg);
		va_start(vlist2, msg);

		Logger(LOGGER_RED, msg, LOGGER_ERROR_PREFIX, vlist1, vlist2);

		va_end(vlist1);
		va_end(vlist2);
	}
};

int LoggerClose()
{
	LoggerInfo(LOGGER_CLOSE_MSG);
	return LoggerCloseFile();
}
