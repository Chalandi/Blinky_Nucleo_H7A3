#include "Leds.h"

class shape
{
public:
  virtual ~shape() = default;

protected:
  shape() = default;
};

class circle : public shape
{
  circle() = default;
  ~circle() override = default;
};
