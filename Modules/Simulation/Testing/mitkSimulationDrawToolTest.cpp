/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include <mitkNodePredicateDataType.h>
#include <mitkRenderingTestHelper.h>
#include <mitkSimulation.h>
#include <mitkSimulationObjectFactory.h>
#include <mitkTestingMacros.h>
#include <sofa/simulation/common/UpdateContextVisitor.h>

using namespace mitk;

int mitkSimulationDrawToolTest(int argc, char* argv[])
{
  MITK_TEST_BEGIN("mitkSimulationDrawToolTest")

  MITK_TEST_CONDITION_REQUIRED(argc == 4, "Check if command line has correct number of arguments.")

  MITK_TEST_OUTPUT(<< "Register SimulationObjectFactory.")
  RegisterSimulationObjectFactory();

  MITK_TEST_OUTPUT(<< "Create RenderingTestHelper.")
  mitkRenderingTestHelper renderingTestHelper(1024, 768, argc, argv);
  renderingTestHelper.SetMapperIDToRender3D();

  DataNode* simulationNode = renderingTestHelper.GetDataStorage()->GetNode(NodePredicateDataType::New("Simulation"));
  MITK_TEST_CONDITION_REQUIRED(simulationNode != NULL, "Check if simulation scene was loaded correctly.");

  MITK_TEST_OUTPUT(<< "Initialize simulation.")
  Simulation::Pointer simulation = dynamic_cast<Simulation*>(simulationNode->GetData());
  simulation->SetAsActiveSimulation();
  simulation->GetRootNode()->execute<sofa::simulation::UpdateContextVisitor>(sofa::core::ExecParams::defaultInstance());

  MITK_TEST_OUTPUT(<< "Set camera.")
  renderingTestHelper.SetViewDirection(mitk::SliceNavigationController::Frontal);
  renderingTestHelper.GetVtkRenderer()->ResetCamera();

  simulationNode->SetBoolProperty("Simulation.Visual.Visual Models", false);
  simulationNode->SetBoolProperty("Simulation.Behavior.Behavior Models", true);

  // renderingTestHelper.SaveReferenceScreenShot(".../CMakeExternals/Source/MITK-Data/Simulation/drawTool1024x768REF.png");
  MITK_TEST_CONDITION(renderingTestHelper.CompareRenderWindowAgainstReference(argc, argv) == true, "Compare behavior models with reference image.")

  simulationNode->SetBoolProperty("Simulation.Behavior.Behavior Models", false);
  simulationNode->SetBoolProperty("Simulation.Behavior.Force Fields", true);

  // renderingTestHelper.SaveReferenceScreenShot(".../CMakeExternals/Source/MITK-Data/Simulation/drawTool1024x768REF_1.png");
  MITK_TEST_CONDITION(renderingTestHelper.CompareRenderWindowAgainstReference(argc, argv) == true, "Compare force fields with reference image.")

  simulationNode->SetBoolProperty("Simulation.Behavior.Force Fields", false);
  simulationNode->SetBoolProperty("Simulation.Collision.Collision Models", true);

  // renderingTestHelper.SaveReferenceScreenShot(".../CMakeExternals/Source/MITK-Data/Simulation/drawTool1024x768REF_2.png");
  MITK_TEST_CONDITION(renderingTestHelper.CompareRenderWindowAgainstReference(argc, argv) == true, "Compare collision models with reference image.")

  simulationNode->SetBoolProperty("Simulation.Options.Wire Frame", true);

  // renderingTestHelper.SaveReferenceScreenShot(".../CMakeExternals/Source/MITK-Data/Simulation/drawTool1024x768REF_3.png");
  MITK_TEST_CONDITION(renderingTestHelper.CompareRenderWindowAgainstReference(argc, argv) == true, "Compare collision models (wire frame) with reference image.")

  simulationNode->SetBoolProperty("Simulation.Collision.Collision Models", false);
  simulationNode->SetBoolProperty("Simulation.Mapping.Visual Mappings", true);
  simulationNode->SetBoolProperty("Simulation.Options.Wire Frame", false);

  // renderingTestHelper.SaveReferenceScreenShot(".../CMakeExternals/Source/MITK-Data/Simulation/drawTool1024x768REF_4.png");
  MITK_TEST_CONDITION(renderingTestHelper.CompareRenderWindowAgainstReference(argc, argv) == true, "Compare visual mappings with reference image.")

  MITK_TEST_END()
}
