#ifndef _DEBUG_H
#define _DEBUG_H

/* variable parameter */
typedef char * va_list_t;
#define _INTSIZEOF(n) ((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1) )
#define va_start(ap,v) ( ap = (va_list_t)&v + _INTSIZEOF(v) )
#define va_arg(ap,t) ( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap) ( ap = (va_list_t)0 ) //clear va_list

extern void log_trace(char * fmt, ...);
/* define trace */
#define TRACE_LEVEL TRACE_LEVEL_DEBUG
#define TRACE_PRINTF log_trace

/* Trace level definitions */
#define TRACE_LEVEL_OFF      0
#define TRACE_LEVEL_FATAL    1
#define TRACE_LEVEL_ERROR    2
#define TRACE_LEVEL_WARNING  3
#define TRACE_LEVEL_INFO     4
#define TRACE_LEVEL_DEBUG    5

/* Default trace level */
#ifndef TRACE_LEVEL
   #define TRACE_LEVEL TRACE_LEVEL_DEBUG
#endif

/* Trace output redirection */
#ifndef TRACE_PRINTF
   #define TRACE_PRINTF(...)
#endif

/* Debugging macros */
#if (TRACE_LEVEL >= TRACE_LEVEL_FATAL)
   #define TRACE_FATAL(...) TRACE_PRINTF("[F] "__VA_ARGS__)
#else
   #define TRACE_FATAL(...)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_ERROR)
   #define TRACE_ERROR(...) TRACE_PRINTF("[E] "__VA_ARGS__)
#else
   #define TRACE_ERROR(...)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_WARNING)
   #define TRACE_WARNING(...) TRACE_PRINTF("[W] "__VA_ARGS__)
#else
   #define TRACE_WARNING(...)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_INFO)
   #define TRACE_INFO(...) TRACE_PRINTF("[I] "__VA_ARGS__)
#else
   #define TRACE_INFO(...)
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
   #define TRACE_DEBUG(...) TRACE_PRINTF("[D] "__VA_ARGS__)
#else
   #define TRACE_DEBUG(...)
#endif

/* define log level function */
#define log_fatal TRACE_FATAL
#define log_error TRACE_ERROR
#define log_warning TRACE_WARNING
#define log_info TRACE_INFO
#define log_debug TRACE_DEBUG


/* Deprecated definitions */
#define TRACE_LEVEL_NO_TRACE TRACE_LEVEL_OFF

#endif
