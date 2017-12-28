#include <PWM.h>

#define PWM_PIN 3

#define FREQUENCY 55560 // carrier frequency in Hz

// all _ON/_OFF in µs
#define HELLO_ON  3980
#define HELLO_OFF 3990
#define FOO_ON     482
#define FOO_OFF   1996
#define BAR_ON     482
#define BAR_OFF    994
#define END_ON     482
#define END_OFF   8004

void cmd_poweronoff();

/**
 * Turns the device on independent of the previous state.
 * If the device was already turned on it will be turned off and on again.
 */
void power_on() {
  /* Commands are send multiple times to make sure the device receives them.
   *
   * When the device was already turned on it will naturally turn off when
   * it receives the command. When we keep sending the command it will
   * eventually turn on again.
   *
   * When the device was turned off it will turn on and would eventually turn
   * off again. However, there is a delay when turning the device on in which
   * it does not respond to commands. The delay in the body of this function
   * was choosen carefully to match the device's delay.
   */

  cmd_poweronoff();
  cmd_poweronoff();
  cmd_poweronoff();
  cmd_poweronoff();
  cmd_poweronoff();

  delay(1000);

  cmd_poweronoff();
  cmd_poweronoff();
  cmd_poweronoff();
  cmd_poweronoff();
  cmd_poweronoff();
}

void setup()
{
  Serial.begin(9600);
  InitTimersSafe();

  uint8_t timer = digitalPinToTimer(PWM_PIN);
  Serial.print("set timer ");
  Serial.println(timer);

  bool success = SetPinFrequencySafe(PWM_PIN, FREQUENCY);
  if(success) {
    Serial.println("ok");
  }
  else {
    Serial.println("error");
  }
}

void loop()
{
  if(Serial.available()) {
    power_on();
    while(Serial.available()) {
      Serial.read();
    }
  }

  delay(250);
}

inline void pwm_on_off(int onMicros, int offMicros) {
  pwmWrite(PWM_PIN, 128);
  delayMicroseconds(onMicros);
  pwmWrite(PWM_PIN, 0);
  delayMicroseconds(offMicros);
}

void signal_hello() {
  pwm_on_off(HELLO_ON, HELLO_OFF);
}

void signal_foo() {
  pwm_on_off(FOO_ON, FOO_OFF);
}

void signal_bar() {
  pwm_on_off(BAR_ON, BAR_OFF);
}

void signal_end() {
  pwm_on_off(END_ON, END_OFF);
}

void cmd_poweronoff() {
  signal_hello();
  signal_foo();
  signal_foo();
  signal_bar();
  signal_bar();
  signal_bar();
  signal_bar();
  signal_foo();
  signal_bar();
  signal_foo();
  signal_bar();
  signal_foo();
  signal_bar();
  signal_bar();
  signal_bar();
  signal_foo();
  signal_foo();
  signal_foo();
  signal_foo();
  signal_bar();
  signal_foo();
  signal_bar();
  signal_foo();
  signal_bar();
  signal_foo();
  signal_end();
}
