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
#ifndef UMPIRE_NumaMemoryResource_HPP
#define UMPIRE_NumaMemoryResource_HPP

#include "umpire/resource/MemoryResource.hpp"

#include "umpire/strategy/mixins/Inspector.hpp"

namespace umpire {
namespace resource {

class NumaMemoryResource :
    public MemoryResource,
    private umpire::strategy::mixins::Inspector
{
public:
  NumaMemoryResource(const std::string& name, int id, MemoryResourceTraits traits);

  void* allocate(size_t bytes);
  void deallocate(void* ptr);

  long getCurrentSize() const noexcept;
  long getHighWatermark() const noexcept;

  Platform getPlatform() noexcept;

protected:
  Platform m_platform;
};

} // end of namespace resource
} // end of namespace umpire

#endif // UMPIRE_NumaMemoryResource_HPP