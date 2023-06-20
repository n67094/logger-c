#include <stdio.h>

#include "logger.h"

int main(int argc, char *argv[]) {
  LoggerInit();

  printf("\nERROR, WARNING, SUCCESS LOGS\n");
  printf("========\n");

  LoggerSetLevel(LOGGER_LEVEL_ERROR | LOGGER_LEVEL_WARNING |
                 LOGGER_LEVEL_SUCCESS);

  LoggerError("Error one : %d two : %f three : %s", 1, 2.0, "three");
  LoggerWarning("warning one : %d two : %f three : %s", 1, 2.0, "three");
  LoggerSuccess("success one : %d two : %f three : %s", 1, 2.0, "three");
  LoggerInfo("Info one : %d two : %f three : %s", 1, 2.0, "three");
  LoggerDebug("Debug one : %d two : %f three : %s", 1, 2.0, "three");

  printf("\nALL LOGS\n");
  printf("========\n");

  LoggerSetLevel(LOGGER_LEVEL_ALL);

  LoggerError("assets path not found %s", "../assets/image.png");
  LoggerWarning("retry fetch, network error");
  LoggerSuccess("data fetched %dms", 230);
  LoggerInfo("init queue");
  LoggerDebug("user email is : %s", "user@test.test");

  LoggerClose();

  return 0;
}
