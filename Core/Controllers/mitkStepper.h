#ifndef STEPPER_H_HEADER_INCLUDED_C1E77191
#define STEPPER_H_HEADER_INCLUDED_C1E77191

#include "mitkCommon.h"
#include "mitkVector.h"
#include <itkObject.h>
#include <itkObjectFactory.h>

namespace mitk {

//##ModelId=3DF8BF9A005D
//##Documentation
//## @brief Helper class to step through a list
//## @ingroup NavigationControl
//## A helper class to step through a list. Does not contain the list, just the
//## position in the list (between 0 and GetSteps()). Provides methods like
//## First (go to the first element), Next (go to the next one), etc.
class Stepper : public itk::Object
{
public:
  mitkClassMacro(Stepper, itk::Object);
  itkNewMacro(Self);

  itkGetMacro(Pos, unsigned int);
  itkSetClampMacro(Pos, unsigned int, 0, m_Steps);

  itkGetMacro(Steps, unsigned int);
  itkSetMacro(Steps, unsigned int);

  itkGetMacro(StepSize, unsigned int);
  itkSetClampMacro(StepSize, unsigned int, 0, m_Steps);

  itkGetMacro(StepToUnitFactor, mitk::ScalarType);
  itkSetMacro(StepToUnitFactor, mitk::ScalarType);

  itkGetStringMacro(UnitName);
  itkSetStringMacro(UnitName);

  //##ModelId=3DF8B9410142
  void Previous();

  //##ModelId=3DF8B92F01DF
  void Last();

  //##ModelId=3DF8B91502F8
  void First();

  //##ModelId=3DF8B92703A4
  void Next();
protected:
  //##ModelId=3DD524BD00DC
  unsigned int m_Pos;
  //##ModelId=3DF8F73C0076
  unsigned int m_Steps;
  //##ModelId=3DF8F74101AE
  unsigned int m_StepSize;

  mitk::ScalarType m_StepToUnitFactor;

  std::string m_UnitName;

private:

};

} // namespace mitk



#endif /* STEPPER_H_HEADER_INCLUDED_C1E77191 */
