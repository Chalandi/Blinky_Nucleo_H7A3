#include <cstddef>

class shape
{
public:
  virtual ~shape() noexcept = default;

  virtual auto draw() noexcept -> void = 0;

protected:
  shape() noexcept = default;
};

class circle : public shape
{
public:
  circle() noexcept
  {
    #if defined(__GNUC__)
    asm volatile("nop");
    #endif
  }

  ~circle() noexcept override = default;

  auto draw() noexcept -> void override
  {
    #if defined(__GNUC__)
    asm volatile("nop");
    #endif
  }
};

circle shapes_circle_instance;

extern "C"
{
  auto shapes_draw_circle(void) -> void;

  auto shapes_draw_circle(void) -> void
  {
    shapes_circle_instance.draw();
  }
}
