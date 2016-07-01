/******************************************************************************
 * This file is part of PCPSolver.                                            *
 *                                                                            *
 * Written by Marcel Lippmann <marcel.lippmann@tu-dresden.de>.                *
 * Copyright (c) 2016 by Marcel Lippmann.  All rights reserved.               *
 *                                                                            *
 ******************************************************************************/
#ifndef PCPXMLREADER_H_
#define PCPXMLREADER_H_

#include <string>
#include <memory>

#include "PCPInstance.h"


namespace pcpsolver {

/**
 * This function reads a PCP instance from an XML file using LibXML.
 * 
 * @param filepath The file path of the XML file.
 * @returns The obtained PCP instance.
 * @throws Exception if the file cannot be found or parsed correctly.
 */
std::unique_ptr<PCPInstance> read_pcp_instance_from_xml_file(std::string const& filepath);


} // namespace pcpsolver


#endif // PCPXMLREADER_H_
