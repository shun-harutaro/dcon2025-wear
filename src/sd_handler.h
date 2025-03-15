#ifndef SD_HANDLER_H
#define SD_HANDLER_H

#include "SD.h"

bool initializeSD();
void readFileFromSD(const char* filename);

#endif