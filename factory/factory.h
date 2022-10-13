//
// Created by morslm
//
#pragma once
#include "allocator.h"

namespace factory
{
  template<typename T>
  class Deleter
  {
  public:
    const std::size_t SIZE = sizeof(T);
    const std::size_t ALIGN = alignof(T);
    AllocatorType* allocator_ = nullptr;

    constexpr Deleter() noexcept = default;
    explicit Deleter(const AllocatorTypeUptr& allocator) : allocator_(allocator.get()) {}

    template<typename U>
    explicit Deleter(Deleter<U>&& d) noexcept : SIZE(d.SIZE), ALIGN(d.ALIGN), allocator_(d.allocator_)
    {
      d.allocator_ = nullptr;
    }

    Deleter& operator=(Deleter&& d) noexcept
    {
      if(std::addressof(d) == this)
        return *this;

      allocator_ = d.allocator_;
      d.allocator_ = {};

      return *this;
    }

    void operator()(T* ptr) const noexcept
    {
      ptr->~T();
      allocator_->DeAllocate(ptr, SIZE, ALIGN);
    }
  };

  template<typename T>
  using Uptr = std::unique_ptr<T, Deleter<T>>;

  template<typename T, typename ...Types>
  inline auto Create(AllocatorTypeUptr& allocator, Types&& ...args)
  {
    void* p = allocator->Allocate(sizeof(T), alignof(T));
    T* ptr = new(p) T(std::forward<Types>(args)...);
    return std::unique_ptr<T, Deleter<T>>{ptr, Deleter<T>{allocator}};
  };
}
