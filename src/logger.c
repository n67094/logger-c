#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logger-config.h"
#include "logger.h"

FILE* file = NULL;

int loggerLevel = LOGGER_LEVEL_ALL;

/* used to know if we can write in file, set to 1 if the file can't be opened */
int loggerFileError = 0;

static void LoggerReplaceSpace(char* pointer, char character)
{
	while (*pointer) {
		if (*pointer == ' ')
			*pointer = character;

		pointer++;
	}
}

/* returned pointer should be freed*/
static char* LoggerGetTime()
{
	char* date = NULL;
	time_t currentDate = time(NULL);

	if (currentDate == (time_t)(-1)) {
		date = malloc(sizeof(char) * strlen(LOGGER_NO_TIME_PREFIX));
		strcpy(date, LOGGER_NO_TIME_PREFIX);
	} else {
		int dateLength = sizeof(char) * 20;
		date = malloc(dateLength);

		strftime(date, dateLength, "%Y-%m-%d %H:%M:%S", gmtime(&currentDate));

		char* newline = strchr(date, '\n');
		if (newline != NULL)
			*newline = '\0';
	}

	return date;
}

static int LoggerOpenFile()
{
	char* date = LoggerGetTime();

	int filenameLength = strlen(LOGGER_FILENAME);
	int dateLength = strlen(date);

	/* + 1 for the - between filename and date */
	char* fullFilename = malloc(sizeof(char) * (filenameLength + dateLength + 1));

	strcat(fullFilename, LOGGER_FILENAME);
	strcat(fullFilename, "-");
	strcat(fullFilename, date);

	LoggerReplaceSpace(fullFilename, '_');

	file = fopen(fullFilename, "a+");

	if (file == NULL) {
		printf("log.c error opening file %s", fullFilename);
		loggerFileError = 1;
		return 1;
	}

	free(fullFilename);
	fullFilename = NULL;

	return 0;
};

static int LoggerCloseFile()
{
	return fclose(file);
}

static void LoggerInFile(int msgLength, char* date, char* prefix, char* msg, va_list args)
{
	/* + 1 for \n added below*/
	char* fullMsg = malloc(sizeof(char) * (msgLength + 1));
	*fullMsg = '\0';

	strcat(fullMsg, date);
	strcat(fullMsg, prefix);
	strcat(fullMsg, msg);
	strcat(fullMsg, "\n");

	vfprintf(file, fullMsg, args);

	free(fullMsg);
	fullMsg = NULL;
}

static void LoggerInConsole(int msgLength, char* date, char* color, char* prefix, char* msg, va_list args)
{
	char* fullMsg = fullMsg = malloc(sizeof(char) * (msgLength + 1));
	*fullMsg = '\0';

	if (LOGGER_WITH_COLOR)
		strcat(fullMsg, LOGGER_FAINT);

	strcat(fullMsg, date);

	if (LOGGER_WITH_COLOR)
		strcat(fullMsg, LOGGER_RESET_STYLE);

	if (LOGGER_WITH_COLOR)
		strcat(fullMsg, color);

	strcat(fullMsg, prefix);

	if (LOGGER_WITH_COLOR)
		strcat(fullMsg, LOGGER_RESET_STYLE);

	strcat(fullMsg, msg);
	strcat(fullMsg, "\n");

	vprintf(fullMsg, args);

	free(fullMsg);
	fullMsg = NULL;
}

/*
 * Since va_copy is only available in c99 I use two va_list, va_list are invalidated by vprintf and vfprintf so it cannot be used twice
 */
static void Logger(char* color, char* msg, char* prefix, va_list vList1, va_list vList2)
{
	int msgLength = strlen(msg);
	int prefixLength = strlen(prefix);

	char* date = LoggerGetTime();
	int dateLength = strlen(date);

	if (LOGGER_IN_FILE && loggerFileError != 1) {
		int fullMsgLength = dateLength + prefixLength + msgLength;

		LoggerInFile(fullMsgLength, date, prefix, msg, vList1);
	}

	if (LOGGER_IN_CONSOLE) {
		int fullMsgLength = 0;

		if (LOGGER_WITH_COLOR == 1) {
			int faintStyleLength = strlen(LOGGER_FAINT);
			int colorLength = strlen(color);
			int resetStyleLength = strlen(LOGGER_RESET_STYLE);

			fullMsgLength = faintStyleLength + dateLength + resetStyleLength + colorLength + prefixLength + resetStyleLength + msgLength;
		} else {
			fullMsgLength = dateLength + prefixLength + msgLength;
		}

		LoggerInConsole(fullMsgLength, date, color, prefix, msg, vList2);
	}

	free(date);
	date = NULL;
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
