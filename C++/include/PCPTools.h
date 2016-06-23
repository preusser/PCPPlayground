/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#ifndef PCPTOOLS_H
#define PCPTOOLS_H

#include <string>
#include <vector>

#include "PCPInstance.h"


namespace pcpsolver {


/**
 * This type decribes a three-valued truth value.
 */
typedef enum {
  SOLUTION,
  EXTENSION_POSSIBLE,
  NOT_SOLUTION
} solution_t;


/**
 * This function checks whether a given list of indices is a solution to a
 * given PCP instance.
 *
 * @param instance The PCP instance.
 * @param indices The proposed solution.
 * @returns SOLUTION if the list of indices is a solution,
 *          EXTENSION_POSSIBLE if the list of indices can possibly be extended
 *            to a solution, and
 *          NOT_SOLUTION otherwise.
 */
solution_t check(const PCPInstance &instance, const std::vector<std::string> &indices);

/**
 * This function `solves' a given PCP instance using iterative DFS.
 *
 * Note that the function does not return if there is no solution.
 *
 * @param instance The PCP instance.
 * @returns The solution, which is a list of indices.
 */
std::vector<std::string> solve(const PCPInstance &instance);


} // namespace pcpsolver


#endif // PCPTOOLS_H
