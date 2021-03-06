/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef MITK_UID_GENERATOR_INDCLUDED_FASAWE
#define MITK_UID_GENERATOR_INDCLUDED_FASAWE

#include <MitkCoreExports.h>
#include <iostream>
#include <random>
#include <string>

namespace mitk
{
  /*!
    \brief Generated unique IDs

    Creates unique IDs from a given prefix, the current date/time and a random part. Be aware that, a length of one or
    two might not be sufficient.

    The prefix is given to the constructor, together with the desired
    length of the random part.

    The current implementation uses the time in seconds in combination with an a random part.
  */
  class MITKCORE_EXPORT UIDGenerator
  {
  public:
    UIDGenerator(const char *prefix = "UID_", unsigned int lengthOfRandomPart = 8);

    /** @return Returns a unique ID as string. You will get another unique ID each time you call GetUID. */
    std::string GetUID();

  private:
    std::string m_Prefix;
    unsigned int m_LengthOfRandomPart;
    std::uniform_int_distribution<unsigned long int> m_Distribution;
  };
} // namespace mitk

#endif
