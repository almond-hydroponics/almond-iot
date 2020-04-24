#ifndef ALMOND_HW_SRC_LOGGER_H
#define ALMOND_HW_SRC_LOGGER_H

#include <ESP8266WiFi.h>

#include "timer_override.h"

typedef void (*LoggerFatalHook)(const char *error_line);

class Logger
{
public:
	enum class Status
	{
		BOOTING, RUNNING, ERROR
	};
	enum class Level
	{
		DEBUG, INFO, WARNING, ERROR, FATAL
	};

	static const int max_lines = 16;
	static const int max_line_len = 80;

	Logger();

	void setup_serial(const char *hostname, int baudrate = 9600);
	void setup_led(int _led_pin);
	void setup_fatal_hook(LoggerFatalHook hook);

	Logger::Status get_status();
	static void set_status(Logger::Status status);

	void log(Logger::Level level, const __FlashStringHelper *format, ...);

	/// @returns pointer to the given line or NULL if not that many lines
	const char *get_log_line(int line_number);

	void loop();

private:
	TimerOverride led_timer;
	LoggerFatalHook fatal_hook;
	int line_loop;
	int serial_baudrate;
	int led_pin;
	bool led_state{};
	Logger::Status status;
	char buffer[max_lines * max_line_len]{};
	char format[max_line_len]{};
};

struct InfoUptime
{
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
};

// void get_uptime(InfoUptime *uptime);

extern Logger LOG;

#define LOG_INFO(format, ...) LOG.log( Logger::Level::INFO, F(format) , ## __VA_ARGS__ )
#define LOG_WARN(format, ...) LOG.log( Logger::Level::WARNING, F(format), ## __VA_ARGS__ )
#define LOG_ERROR(format, ...) LOG.log( Logger::Level::ERROR, F(format), ## __VA_ARGS__ )
#define LOG_FATAL(format, ...) LOG.log( Logger::Level::FATAL, F(format), ## __VA_ARGS__ )

#endif //ALMOND_HW_SRC_LOGGER_H
