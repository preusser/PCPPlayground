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
 * This function checks whether a given list of indices is a solution to a
 * given PCP instance.
 *
 * @param instance The PCP instance.
 * @param indices The list of indices to check.
 * @returns If a solution is found, it returns an optional object that does not
 *   contain a value. Otherwise it returns an optional object containing a list
 *   of list of indices that need to be checked for a solution.  This list may
 *   be empty.
 */
std::experimental::optional<std::vector<indices_t>> check_indices(PCPInstance const& instance,
                                                                  indices_t const& indices);


/**
 * This function `solves' a given PCP instance using BFS.
 *
 * Note that the function does not necessarily return if there is no solution.
 *
 * @param instance The PCP instance.
 * @returns The solution, which is a list of indices.
 */
indices_t solve(PCPInstance const& instance);


} // namespace pcpsolver


#endif // PCPSOLVER_H
