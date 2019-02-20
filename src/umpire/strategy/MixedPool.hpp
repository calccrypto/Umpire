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
#ifndef UMPIRE_MixedPool_HPP
#define UMPIRE_MixedPool_HPP

#include <memory>
#include <array>

#include "umpire/strategy/AllocationStrategy.hpp"

#include "umpire/strategy/DynamicPool.hpp"
#include "umpire/strategy/FixedPool.hpp"

#include "umpire/Allocator.hpp"

namespace umpire {
namespace strategy {

/**
 * \brief A faster pool that pulls from a series of pools
 *
 * Pool implementation using a series of FixedPools for small sizes,
 * and a DynamicPool for sizes larger than (1 << LastFixed) bytes.
 */
template<int FirstFixed = 8, int Increment = 1, int LastFixed = 22>
class MixedPoolImpl :
  public AllocationStrategy
{
  public:
    MixedPoolImpl(
        const std::string& name,
        int id,
        Allocator allocator) noexcept;

    void* allocate(size_t bytes) override;

    void deallocate(void* ptr) override;

    void release() override;

    long getCurrentSize() const noexcept override;
    long getActualSize() const noexcept override;
    long getHighWatermark() const noexcept override;

    Platform getPlatform() noexcept override;

  private:
    static size_t nextPower2(unsigned int n);

    enum { NUM_FIXED_POOLS = LastFixed - FirstFixed + 1 };
    using StrategyPtr = std::shared_ptr<umpire::strategy::AllocationStrategy>;
    using FixedPoolArray = std::array<StrategyPtr, NUM_FIXED_POOLS>;

    FixedPoolArray m_fixed_pool;
    StrategyPtr m_dynamic_pool;
    StrategyPtr m_allocator;
};

using MixedPool = MixedPoolImpl<>;

} // end of namespace strategy
} // end namespace umpire

#include "umpire/strategy/MixedPool.inl"

#endif // UMPIRE_MixedPool_HPP