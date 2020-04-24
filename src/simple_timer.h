#ifndef ARDUINO_TIMER_SRC_SIMPLE_TIMER_H
#define ARDUINO_TIMER_SRC_SIMPLE_TIMER_H

class SimpleTimer {
public:
  SimpleTimer();
  // Use all time
  void reset();
  // User @param timeout_ms amount of time.
  void reset_with_carry(unsigned long timeout_ms);
  // Check if @param timeout_ms milliseconds has passed since the last reset.
  bool check(unsigned long timeout_ms);

protected:
  unsigned long reset_ms;
};

#endif //ARDUINO_TIMER_SRC_SIMPLE_TIMER_H
