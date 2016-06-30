/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include "PCPSolver.h"

using namespace pcpsolver;


PCPSolver::PCPSolver(PCPInstance const& instance) : instance_(instance) {
}


PCPSolver::~PCPSolver() {
}


std::experimental::optional<std::vector<indices_t>> PCPSolver::check_indices(indices_t const& indices) const {

  if (!indices.empty()) {

    std::string firstW = "";
    std::string secondW = "";

    for (auto const& i : indices) {
      auto const& pair = instance_.get_pair(i);
      firstW += pair.first;
      secondW += pair.second;
    }

    // Check whether the first word is a prefix of the second word.
    bool const firstPrefixOfSecond = std::equal(std::begin(firstW), std::end(firstW), std::begin(secondW));

    // Check whether the second word is a prefix of the first word.
    bool const secondPrefixOfFirst = std::equal(std::begin(secondW), std::end(secondW), std::begin(firstW));

    if (firstPrefixOfSecond && secondPrefixOfFirst) {

      // Words are equal.
      return std::experimental::nullopt;

    } else if (!firstPrefixOfSecond && !secondPrefixOfFirst) {

      // This sequence of indices cannot be extended to a solution.
      return std::experimental::make_optional(std::vector<indices_t>());
    }
  }

  // Consider all successor nodes, since sequence of indices can possibly be
  // extended to a solution.
  std::vector<indices_t> nextIndices;
  for (auto const& i : instance_.get_list_of_indices()) {
    auto next = indices;
    next.push_back(i);
    nextIndices.push_back(next);
  }

  return std::experimental::make_optional(nextIndices);
}


std::experimental::optional<indices_t> PCPSolver::traverse_search_space(std::vector<indices_t>& roots) const {

  std::vector<indices_t> nextRoots;
  for (auto const& root : roots) {

    auto const nextIndices = check_indices(root);
    if (nextIndices) {

      // Add new indices to search space
      nextRoots.insert(std::end(nextRoots),
                       std::begin(nextIndices.value()),
                       std::end(nextIndices.value()));

    } else {

      // Solution found.
      return std::experimental::make_optional(root);
    }
  }

  // No solution found (yet), try next roots if there are any.
  if (nextRoots.empty()) {

    return std::experimental::nullopt;

  } else {

    return traverse_search_space(nextRoots);
  }
}


std::experimental::optional<indices_t> PCPSolver::solve() const {

  std::vector<indices_t> startRoots;
  indices_t start;
  startRoots.push_back(start);

  return traverse_search_space(startRoots);
}
