#include "factory.h"
#include <cassert>

struct SomeType
{
  using Uptr = factory::Uptr<SomeType>;
  explicit SomeType(int i) : field_(i) {}
  int field_ = 0;
};

int main()
{
  AllocatorTypeUptr allocator = std::make_unique<AllocatorType>(512);

  auto object = factory::Create<SomeType>(allocator, 42);
  assert(object->field_ == 42);

  return 0;
}