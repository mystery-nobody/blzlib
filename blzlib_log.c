#include <stdio.h>
#include <stdarg.h>

#include "blzlib_log.h"

static void (*log_handler)(enum loglevel ll, const char *fmt, va_list ap);

void __attribute__ ((format (printf, 2, 3)))
blz_log_out(enum loglevel level, const char *format, ...)
{
	va_list args;

	va_start(args, format);
	if (log_handler != NULL) {
		log_handler(level, format, args);
		va_end(args);
		return;
	}

	vprintf(format, args);
	printf("\n");
	va_end(args);
}

void blz_set_log_handler(void (*cb)(enum loglevel ll, const char *fmt, va_list ap))
{
	log_handler = cb;
}
