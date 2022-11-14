#include "SignalLight.h"
#include "Component.h"

SignalLight::SignalLight(uint8_t i, uint8_t o)
{
  pinIn = i;
  pinOut = o;
}

void SignalLight::on()
{
  digitalWrite(pinOut, HIGH);
}

void SignalLight::off()
{
  digitalWrite(pinOut, LOW);
}

bool SignalLight::isOn()
{
  return digitalRead(pinIn) == LOW;
}

bool SignalLight::isOff()
{
  return digitalRead(pinIn) == HIGH;
}

unsigned long SignalLight::send(uint8_t n)
{
  unsigned long d = (n + 1) * SIGNAL_UNIT;
  on();
  delay(d);
  off();
  return d;
}

uint8_t SignalLight::receive()
{
  unsigned long r;
  do {
    while(isOff());
    unsigned long m = millis();
    while(isOn());
    r = (millis() - m + (SIGNAL_UNIT >> 1)) / SIGNAL_UNIT;
  }
  while(r == 0);
  return r - 1;
}
