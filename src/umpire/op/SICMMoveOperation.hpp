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
#ifndef UMPIRE_SICMMoveOperation_HPP
#define UMPIRE_SICMMoveOperation_HPP

#include "umpire/op/MemoryOperation.hpp"

extern "C" {
#include <sicm_low.h>
}

namespace umpire {
namespace op {

/*!
 * \brief Move data in CPU memory.
 */
class SICMMoveOperation :
  public MemoryOperation {
 public:
  ~SICMMoveOperation();

  /*!
   * \copybrief MemoryOperation::transform
   *
   * Uses sicm_realloc to reallocate memory.
   *
   * \copydetails MemoryOperation::transform
   */
  void transform(
      void* src_ptr,
      void** dst_ptr,
      util::AllocationRecord *src_allocation,
      util::AllocationRecord *dst_allocation,
      size_t length);

 private:
      static sicm_device_list m_devices;
};

} // end of namespace op
} // end of namespace umpire

#endif // UMPIRE_SICMMoveOperation_HPP