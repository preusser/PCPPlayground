/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#include <cstdlib>
#include <iostream>
#include <string>

#include "PCPInstance.h"
#include "PCPSolver.h"
#include "PCPXmlReader.h"

using namespace pcpsolver;


void print_usage(std::string const& prgName, std::string const& errorMsg) {

  std::cout << "Usage: "   << prgName  << " [filepath]" << std::endl
            << "  Error: " << errorMsg << std::endl;
}


int main(int argc, char* argv[]) {

  std::string prgName = argv[0];

  if (argc != 2) {
    print_usage(prgName, "Please specify exactly one file path.");
    return EXIT_FAILURE;
  }

  std::string xmlFilepath = argv[1];

  try {

    auto pcpInstance = read_pcp_instance_from_xml_file(xmlFilepath);

    auto solution = solve(*pcpInstance);

    std::cout << "Found solution of length " << solution.size() << ": ";

    bool first = true;
    for (auto const& i : solution) {

      if (first) {
        first = false;
      } else {
        std::cout << ", ";
      }

      std::cout << i;
    }

    std::cout << std::endl;

  } catch (std::exception const& e) {

    print_usage(prgName, e.what());
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
