//
// Created by morslm
//
#pragma once
#include <cctype>
#include <memory_resource>

template<std::size_t SIZE = 10 * 1024, std::size_t ALIGN = 16>
class Allocator
{
public:
  using ResourceType = std::pmr::monotonic_buffer_resource;
  explicit Allocator(std::size_t initialSize) :
    begin_(initialSize > sizeof(localBuff_) ? (char*)std::malloc(initialSize) : localBuff_),
    resource_(begin_, initialSize, std::pmr::new_delete_resource())
  {
    if(!begin_)
      throw std::bad_alloc{};
  }

  ~Allocator() noexcept
  {
    if(begin_ != localBuff_)
      std::free(begin_);
  }

  Allocator(const Allocator&) = delete;
  Allocator& operator=(const Allocator&) = delete;

  void* Allocate(std::size_t size, std::size_t align)
  {
    return resource_.allocate(size,align);
  }

  void DeAllocate(void* ptr, std::size_t size, std::size_t align)
  {
    resource_.deallocate(ptr, size, align);
  }

private:
  alignas(ALIGN) char localBuff_[SIZE];
  char* const begin_;
  ResourceType resource_;
};

using AllocatorType = Allocator<>;
using AllocatorTypeUptr = std::unique_ptr<AllocatorType>;