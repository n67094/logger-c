#ifndef LOGGER_H
#define LOGGER_H

#define LOGGER_LEVEL_INFO 0b00001
#define LOGGER_LEVEL_DEBUG 0b00010
#define LOGGER_LEVEL_SUCCESS 0b00100
#define LOGGER_LEVEL_WARNING 0b01000
#define LOGGER_LEVEL_ERROR 0b10000
#define LOGGER_LEVEL_ALL 0b11111

void LoggerInit();
int LoggerClose();

void LoggerSetLevel(int flags);
void LoggerInfo(char* msg, ...);
void LoggerDebug(char* msg, ...);
void LoggerSuccess(char* msg, ...);
void LoggerWarning(char* masg, ...);
void LoggerError(char* msg, ...);

#endif
