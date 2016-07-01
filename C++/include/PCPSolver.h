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
#include <tuple>
#include <vector>

#include <experimental/optional>

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
   * This function checks whether a given list of indices extended by a given
   * index is a solution to the given PCP instance.
   *
   * @param indices The list of indices.
   * @parem index the extension to the given list of indices.
   * @param wordpair The (truncated) word pair associated to the given list of
   *   indices.
   * @returns If a solution is found, it returns an optional object that does not
   *   contain a value.  Otherwise it returns an optional object containing a
   *   tuple with the following components: indices extended by index, all
   *   possible extensions, the truncated word pair associated to the extended
   *   list of indices.  Note that the list of extensions may be empty.
   */
  std::experimental::optional<std::tuple<indices_t, indices_t, wordpair_t>> check_indices(indices_t const& indices,
                                                                                          index_t const& index,
                                                                                          wordpair_t const& wordpair) const;

  /**
   * This function is used to traverse the search tree using BFS.
   *
   * Note that this function does not necessarily return if there is no solution.
   *
   * @param canditates A list of candidates for a solution consisting of: a
   *   sequence of indices that was checked before, a list of indices to check
   *   if the extend the given indices, and the prefix word pair obtained for
   *   the given indices.
   * @returns If a solution is found, it returns an optional object that contains
   *    it.  Otherwise it returns an optional object without a value.
   */
  std::experimental::optional<indices_t> traverse_search_space(std::vector<std::tuple<indices_t, indices_t, wordpair_t>> const& candidates) const;

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
