#ifndef DEBUG_INFO_H
#define DEBUG_INFO_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

typedef enum
{
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR,
    LGO_GL

} LogLevel;

typedef struct
{
    FILE *logfile;
    bool isConsoleEnabled;
    bool isFileEnabled;
    bool isTimeEnabled;
} DebugS;

DebugS DebugInit(const char *pathLogfile, bool toConsole, bool toFile);
void EndDebugMode(DebugS *debug);
void DebugLog(DebugS *debug, LogLevel lvl, const char *fmt, ...);
DebugS DebugInit(const char *pathLogfile, bool toConsole, bool toFile)
{
    DebugS debug = {0};
    debug.isConsoleEnabled = toConsole;
    debug.isFileEnabled = toFile;
    debug.isTimeEnabled = true;

    if (toFile == true)
    {
        debug.logfile = fopen(pathLogfile, "w");
        if (!debug.logfile)
        {
            fprintf(stderr, "Failed to open logfile [%s]", pathLogfile);
            debug.isFileEnabled = false;
        }
    }

    return debug;
}

void EndDebugMode(DebugS *debug)
{
    if (!debug)
    {
        return;
    }
    if (debug->logfile)
    {
        fclose(debug->logfile);
        debug->logfile = NULL;
        return;
    }
}

void DebugLog(DebugS *debug, LogLevel lvl, const char *fmt, ...)
{

    const char *debugLvl[] = {"INFO", "WARN", "ERROR", "GL"};
    char buffer[1024];

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    char final[2048];
    snprintf(final, sizeof(final), "[%s]: %s \n", debugLvl[lvl], buffer);

    if (debug->isConsoleEnabled)
    {
        fprintf(stderr, "%s", final);
    }
    if (debug->logfile)
    {
        if (debug->isFileEnabled)
        {
            fprintf(debug->logfile, "%s", final);
            fflush(debug->logfile);
        }
    }
}

#endif