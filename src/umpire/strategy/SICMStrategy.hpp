//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2018-2019, Lawrence Livermore National Security, LLC.
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
#ifndef UMPIRE_SICMStrategy_HPP
#define UMPIRE_SICMStrategy_HPP

#include <vector>

#include "umpire/strategy/AllocationStrategy.hpp"

#include "umpire/Allocator.hpp"

extern "C" {
#include <sicm_low.h>
}

namespace umpire {

namespace strategy {

/*!
 * \brief Use SICM interface to locate memory to a specific SICM device.
 *
 * This AllocationStrategy provides a method of ensuring memory sits
 * on a specific SICM device. This can be used either for optimization,
 * or for moving memory between the host and devices.
 */
class SICMStrategy :
  public AllocationStrategy
{
  public:
    SICMStrategy(
        const std::string& name,
        int id,
        size_t device_index,
        size_t max_size = 0);

    ~SICMStrategy();

    void* allocate(size_t bytes);
    void deallocate(void* ptr);

    long getCurrentSize() const noexcept;
    long getHighWatermark() const noexcept;

    Platform getPlatform() noexcept;

    size_t getDeviceIndex() const noexcept;

  private:
    size_t m_index;
    size_t m_max_size;
    sicm_arena m_arena;

    static sicm_device_list m_devices;
};

} // end of namespace strategy
} // end of namespace umpire

#endif // UMPIRE_SICMStrategy_HPP