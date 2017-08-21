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

// semantic relations module
#include "mitkControlPointManager.h"
#include "mitkDICOMHelper.h"
#include "mitkUIDGeneratorBoost.h"

// mitk core
#include <mitkPropertyNameHelper.h>

// c++
#include <ctime>

SemanticTypes::ControlPoint ControlPointManager::GenerateControlPoint(const std::vector<mitk::DataNode::Pointer>& dataOfControlPoint)
{
  SemanticTypes::ControlPoint controlPoint;
  SemanticTypes::Date startPoint = GetStartPoint(dataOfControlPoint);
  SemanticTypes::Date endPoint = GetEndPoint(dataOfControlPoint);

  // set the values of the control point
  controlPoint.UID = UIDGeneratorBoost::GenerateUID();
  controlPoint.startPoint = startPoint;
  controlPoint.endPoint = endPoint;

  return controlPoint;
}

SemanticTypes::ControlPoint ControlPointManager::GenerateControlPoint(const mitk::DataNode* datanode)
{
  SemanticTypes::ControlPoint controlPoint;
  SemanticTypes::Date date = DICOMHelper::GetDateFromDataNode(datanode);

  return GenerateControlPoint(date);
}

SemanticTypes::ControlPoint ControlPointManager::GenerateControlPoint(const SemanticTypes::Date& date)
{
  SemanticTypes::ControlPoint controlPoint;

  // set the values of the control point
  controlPoint.UID = UIDGeneratorBoost::GenerateUID();
  controlPoint.startPoint = date;
  controlPoint.endPoint = date;
  // create new UID so that the start point and the end point have a different UID
  controlPoint.endPoint.UID = UIDGeneratorBoost::GenerateUID();

  return controlPoint;
}

SemanticTypes::Date ControlPointManager::GetStartPoint(const std::vector<mitk::DataNode::Pointer>& dataOfControlPoint)
{
  SemanticTypes::Date startPoint;
  for (const auto& dataNode : dataOfControlPoint)
  {
    SemanticTypes::Date currentStartPoint = DICOMHelper::GetDateFromDataNode(dataNode);
    if (startPoint.year == 0 || currentStartPoint < startPoint)
    {
      // set the new, earlier start point
      startPoint = currentStartPoint;
    }
  }

  return startPoint;
}

SemanticTypes::Date ControlPointManager::GetEndPoint(const std::vector<mitk::DataNode::Pointer>& dataOfControlPoint)
{
  SemanticTypes::Date endPoint;
  for (const auto& dataNode : dataOfControlPoint)
  {
    SemanticTypes::Date currentEndPoint = DICOMHelper::GetDateFromDataNode(dataNode);
    if (currentEndPoint > endPoint)
    {
      // set the new, later end point
      endPoint = currentEndPoint;
    }
  }

  return endPoint;
}

std::string ControlPointManager::GetControlPointAsString(const SemanticTypes::ControlPoint& controlPoint)
{
  std::stringstream dateAsString;

  SemanticTypes::Date startPoint = controlPoint.startPoint;
  SemanticTypes::Date endPoint = controlPoint.endPoint;

  dateAsString << std::to_string(controlPoint.startPoint.year) << "-"
    << std::setfill('0') << std::setw(2) << std::to_string(startPoint.month) << "-"
    << std::setfill('0') << std::setw(2) << std::to_string(startPoint.day);
  if (startPoint != endPoint)
  {
    dateAsString << " to \n " << std::to_string(endPoint.year) << "-"
      << std::setfill('0') << std::setw(2) << std::to_string(endPoint.month) << "-"
      << std::setfill('0') << std::setw(2) << std::to_string(endPoint.day);
  }

  return dateAsString.str();
}

bool ControlPointManager::InsideControlPoint(const mitk::DataNode* dataNode, const SemanticTypes::ControlPoint& controlPoint)
{
  SemanticTypes::Date date = DICOMHelper::GetDateFromDataNode(dataNode);
  if (date >= controlPoint.startPoint && date <= controlPoint.endPoint && !controlPoint.UID.empty())
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool ControlPointManager::InsideControlPoint(const SemanticTypes::ControlPoint& containedControlPoint, const SemanticTypes::ControlPoint& containingControlPoint)
{
  if (containedControlPoint.startPoint >= containingControlPoint.startPoint && containedControlPoint.endPoint <= containingControlPoint.endPoint)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool ControlPointManager::InsideControlPoint(const SemanticTypes::Date& date, const SemanticTypes::ControlPoint& controlPoint)
{
  if (date >= controlPoint.startPoint && date <= controlPoint.endPoint)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool ControlPointManager::CheckForOverlap(const SemanticTypes::ControlPoint& controlPoint, const SemanticTypes::ControlPoint& neighboringControlPoint)
{
  if (controlPoint.startPoint >= neighboringControlPoint.endPoint || controlPoint.endPoint <= neighboringControlPoint.startPoint)
  {
    return false;
  }
  else
  {
    return true;
  }
}

SemanticTypes::ControlPoint ControlPointManager::FindFittingControlPoint(const mitk::DataNode* dataNode, std::vector<SemanticTypes::ControlPoint>& allControlPoints)
{
  SemanticTypes::Date dateFromDataNode = DICOMHelper::GetDateFromDataNode(dataNode);
  if (0 == dateFromDataNode.year)
  {
    MITK_INFO << "Could not deduce a valid date from the given data node.";
    return SemanticTypes::ControlPoint();
  }

  return FindFittingControlPoint(dateFromDataNode, allControlPoints);
}

SemanticTypes::ControlPoint ControlPointManager::FindFittingControlPoint(const SemanticTypes::Date& date, std::vector<SemanticTypes::ControlPoint>& allControlPoints)
{
  // check if the date of the data node fits into an existing control point interval
  for (const auto& controlPoint : allControlPoints)
  {
    if (ControlPointManager::InsideControlPoint(date, controlPoint))
    {
      // return the fitting control point that contains the date from the given data node
      return controlPoint;
    }
  }

  return SemanticTypes::ControlPoint();
}

SemanticTypes::ControlPoint ControlPointManager::ExtendClosestControlPoint(const mitk::DataNode* dataNode, std::vector<SemanticTypes::ControlPoint>& allControlPoints)
{
  SemanticTypes::Date dateFromDataNode = DICOMHelper::GetDateFromDataNode(dataNode);
  if (0 == dateFromDataNode.year)
  {
    MITK_INFO << "Could not deduce a valid date from the given data node.";
    return SemanticTypes::ControlPoint();
  }

  return ExtendClosestControlPoint(dateFromDataNode, allControlPoints);
}

SemanticTypes::ControlPoint ControlPointManager::ExtendClosestControlPoint(const SemanticTypes::Date& date, std::vector<SemanticTypes::ControlPoint>& allControlPoints)
{
  // sort the vector of control points for easier lookup
  std::sort(allControlPoints.begin(), allControlPoints.end());
  // new date does not fit into an existing control point
  // check if the date of the data node is close to an already existing control point
  std::vector<SemanticTypes::ControlPoint>::const_iterator it;
  for (it = allControlPoints.begin(); it != allControlPoints.end(); ++it)
  {
    if (date < it->startPoint)
    {
      break; // cannot be inside this control point; therefore has to be greater ("newer") than 'it->endPoint'
    }
  }

  SemanticTypes::ControlPoint nextControlPoint;
  SemanticTypes::ControlPoint previousControlPoint;
  SemanticTypes::Date nextDate;
  SemanticTypes::Date previousDate;
  if (it == allControlPoints.begin())
  {
    // new date is smaller ("older") than the smallest already existing control point
    nextControlPoint = *it;
    nextDate = it->startPoint;
  }
  else if (it != allControlPoints.end())
  {
    // new date is greater ("newer") than the smallest already existing control point,
    // but smaller ("older") than the greatest already existing control point
    nextControlPoint = *it;
    nextDate = nextControlPoint.startPoint;
    previousControlPoint = *(--it);
    previousDate = previousControlPoint.endPoint;
  }
  else
  {
    // new date is greater ("newer") than the greatest already existing control point
    previousControlPoint = *(--it);
    previousDate = previousControlPoint.endPoint;
  }

  // test distance to next and previous time period
  double distanceToNextTimePeriod = CalculateDistanceInDays(nextDate, date);
  double distanceToPreviousTimePeriod = CalculateDistanceInDays(previousDate, date);

  SemanticTypes::ControlPoint closestControlPoint;
  double closestDistanceInDays;
  if (distanceToNextTimePeriod < distanceToPreviousTimePeriod)
  {
    // date is closer to the next control point
    closestControlPoint = nextControlPoint;
    closestDistanceInDays = distanceToNextTimePeriod;
  }
  else
  {
    // date is closer to the previous control point
    closestControlPoint = previousControlPoint;
    closestDistanceInDays = distanceToPreviousTimePeriod;
  }

  // extend the control point or create a control point
  // TODO: threshold distance
  double THRESHOLD_DISTANCE_IN_DAYS = 30;
  if (std::abs(closestDistanceInDays) < THRESHOLD_DISTANCE_IN_DAYS)
  {
    // extend the closest control point
    ExtendControlPoint(closestControlPoint, date);
    return closestControlPoint;
  }
  else
  {
    return SemanticTypes::ControlPoint();
  }
}

void ControlPointManager::ExtendControlPoint(SemanticTypes::ControlPoint& controlPoint, SemanticTypes::Date date)
{
  if (controlPoint.startPoint > date)
  {
    // date has to extend the older start point of the control point (move start point to the earlier date)
    controlPoint.startPoint.year = date.year;
    controlPoint.startPoint.month = date.month;
    controlPoint.startPoint.day = date.day;
  }
  else if (controlPoint.endPoint < date)
  {
    // date has to extend the newer end point of the control point (move end point to the later date)
    controlPoint.endPoint.year = date.year;
    controlPoint.endPoint.month = date.month;
    controlPoint.endPoint.day = date.day;
  }
  // else: date is inside the control point
}

double ControlPointManager::CalculateDistanceInDays(SemanticTypes::Date neighboringDicomDate, SemanticTypes::Date newDicomDate)
{
  // compute distance here
  std::tm neighboringTimeStructure = { 0, 0, 0, neighboringDicomDate.day, neighboringDicomDate.month - 1, neighboringDicomDate.year - 1900 };
  std::tm newTimeStructure = { 0, 0, 0, newDicomDate.day,         newDicomDate.month - 1,         newDicomDate.year - 1900 };

  time_t neighboringTime = mktime(&neighboringTimeStructure);
  time_t newTime = mktime(&newTimeStructure);

  if (neighboringTime == -1 || newTime == -1)
  {
    // date is not initialized, no difference can be computed
    return std::numeric_limits<double>::max();
  }

  double secondsPerDay = 60 * 60 * 24;
  double timeDifferenceInDays = std::difftime(neighboringTime, newTime) / secondsPerDay;

  return timeDifferenceInDays;
}
