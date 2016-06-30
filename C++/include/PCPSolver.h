/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#ifndef PCPSOLVER_H
#define PCPSOLVER_H

#include <string>
#include <experimental/optional>
#include <vector>

#include "PCPInstance.h"


namespace pcpsolver {


/**
 * This class describes the PCP solver.
 */
class PCPSolver {

private:

  /**
   * The PCP instance that the solver was initialised with.
   */
  PCPInstance const instance_;

  /**
   * This function checks whether a given list of indices is a solution to the
   * given PCP instance.
   *
   * @param indices The list of indices to check.
   * @returns If a solution is found, it returns an optional object that does not
   *   contain a value. Otherwise it returns an optional object containing a list
   *   of list of indices that need to be checked for a solution.  This list may
   *   be empty.
   */
  std::experimental::optional<std::vector<indices_t>> check_indices(indices_t const& indices) const;

  /**
   * This function is used to traverse the search tree using BFS.
   *
   * Note that this function does not necessarily return if there is no solution.
   *
   * @param roots A list of sequences of indices to check.
   * @returns If a solution is found, it returns an optional object that contains
   *    it.  Otherwise it returns an optional object without a value.
   */
  std::experimental::optional<indices_t> traverse_search_space(std::vector<indices_t>& roots) const;

public:

  /**
   * This constructor initialises the PCP solver with a given PCP instance.
   *
   * @param instance The PCP instance.
   */
  PCPSolver(PCPInstance const& instance);

  /**
   * The standard destructor.
   */
  ~PCPSolver();

  /**
   * This function `solves' the given PCP instance using BFS.
   *
   * Note that the function does not necessarily return if there is no solution.
   *
   * @returns If a solution is found, it returns an optional object that contains
   *   it.  If there is no solution, it returns an optional object without a value.
   */
  std::experimental::optional<indices_t> solve() const;
};

} // namespace pcpsolver


#endif // PCPSOLVER_H
