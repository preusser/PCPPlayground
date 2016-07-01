/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#ifndef PCPINSTANCE_H_
#define PCPINSTANCE_H_

#include <map>
#include <string>
#include <tuple>
#include <vector>


namespace pcpsolver {


/**
 * This type defined an index.
 */
typedef std::string index_t;

/**
 * This type defines a list of indices.
 */
typedef std::vector<index_t> indices_t;

/**
 * This type defines a word pair.
 */
typedef std::pair<std::string, std::string> wordpair_t;

/**
 * This class describes a PCP instance.
 */
class PCPInstance {

private:

  /**
   * The internal data structure for a PCP instance.
   */
  std::map<std::string, wordpair_t> instance_;

  /**
   * The list of indices of the PCP instance.
   */
  indices_t indices_;

public:

  /**
   * The standard constructor.
   */
  PCPInstance();

  /**
   * The standard destructor.
   */
  ~PCPInstance();

  /**
   * This method adds a pair to the PCP instance.
   *
   * If a word pair with the specified index is already present, it is
   * overridden.
   *
   * @param index The index name.
   * @param first The first word.
   * @param second The second word.
   */
  void add_pair(index_t const& index,
                std::string const& first,
                std::string const& second);

  /**
   * This method is used to retrieve the word pair at the specified index.
   *
   * @param index The name of the index.
   * @returns The word pair at specified index.
   * @throws Exception if there is no word pair with the specified index.
   */
  wordpair_t const& get_pair(index_t const& index) const;

  /**
   * This method returns the list of indices of the PCP instance.
   *
   * @returns List of indices.
   */
  indices_t const& get_list_of_indices() const;
};

} // namespace pcpsolver


#endif // PCPINSTANCE_H_
