/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/


#ifndef __DOSE_NODE_HELPER_H
#define __DOSE_NODE_HELPER_H

#include "mitkIsoDoseLevelCollections.h"
#include "mitkDataNode.h"
#include "MitkDicomRTExports.h"

namespace mitk
{
  /**Helper that ensures that all properties of a dose node are set correctly to visualize the node properly.*/
  void MITKDICOMRT_EXPORT ConfigureNodeAsDoseNode(mitk::DataNode* doseNode,
    const mitk::IsoDoseLevelSet* colorPreset,
    mitk::DoseValueAbs referenceDose,
    bool showColorWashGlobal = true);

  void MITKDICOMRT_EXPORT ConfigureNodeAsIsoLineNode(mitk::DataNode* doseOutlineNode,
    const mitk::IsoDoseLevelSet* colorPreset,
    mitk::DoseValueAbs referenceDose,
    bool showIsolinesGlobal = true);


}

#endif
