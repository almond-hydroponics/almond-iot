#pragma once

#include <stdint.h>

#include "device.h"
#include "simple_timer.h"

/** Simple filtered input, the value will be -1 in case of fiddling input and 0/1 when input is stable (for filter_len * 2 time when changing
 */


class Device_pin_in: public Device_input
{
public:
	static const int poll_interval = 100;

	Device_pin_in(const char *name,
				  uint8_t pin,
				  uint8_t filter_len,
				  bool invert);
	virtual void setup() override;
	virtual void loop() override;

protected:
	SimpleTimer timer;
	int16_t filter_sum;
	uint8_t pin;
	uint8_t filter_len;
	bool invert;
};
