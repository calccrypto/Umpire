//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018, Lawrence Livermore National Security, LLC.
// Produced at the Lawrence Livermore National Laboratory
//
// Created by David Beckingsale, david@llnl.gov
// LLNL-CODE-747640
//
// All rights reserved.
//
// This file is part of Umpire.
//
// For details, see https://github.com/LLNL/Umpire
// Please also see the LICENSE file for MIT license.
//////////////////////////////////////////////////////////////////////////////
#ifndef UMPIRE_DeviceAllocator_INL
#define UMPIRE_DeviceAllocator_INL

#include "umpire/util/Macros.hpp"

namespace umpire {

__host__
DeviceAllocator::DeviceAllocator(Allocator allocator, size_t size) :
  m_allocator(allocator),
  m_ptr(m_allocator.allocate(size)),
  m_size(size)
{
  auto& rm = umpire::ResourceManager::getInstance();
  auto device_alloc = rm.getAllocator(umpire::resource::Device);

  m_counter = device_alloc.allocate(sizeof(size_t));
  rm.memset(m_counter, 0);
}

__host__
DeviceAllocator::~DeviceAllocator()
{
  auto& rm = umpire::ResourceManager::getInstance();
  rm.deallocate(m_counter);

  m_allocator.deallocate(m_ptr);
}

__device__
void*
DeviceAllocator::allocate(size_t size)
{
  return m_ptr + atomicAdd(m_counter, size);
}

} // end of namespace umpire

#endif // UMPIRE_DeviceAllocator_INL