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

#ifndef QMITKDATANODEGLOBALREINITACTION_H
#define QMITKDATANODEGLOBALREINITACTION_H

#include <org_mitk_gui_qt_application_Export.h>

#include "QmitkAbstractDataNodeAction.h"

// qt
#include <QAction>

namespace GlobalReinitAction
{
  MITK_QT_APP void Run(berry::IWorkbenchPartSite::Pointer workbenchPartSite, mitk::DataStorage::Pointer dataStorage);
}

class MITK_QT_APP QmitkDataNodeGlobalReinitAction : public QAction, public QmitkAbstractDataNodeAction
{
  Q_OBJECT

public:

  static const QString ACTION_ID; // = "org.mitk.gui.qt.application.globalreinitaction";

  QmitkDataNodeGlobalReinitAction(QObject* parent, berry::IWorkbenchPartSite::Pointer workbenchPartSite);
  QmitkDataNodeGlobalReinitAction(QObject* parent, berry::IWorkbenchPartSite* workbenchPartSite);

  virtual ~QmitkDataNodeGlobalReinitAction() override;

private Q_SLOTS:

  void OnActionTriggered(bool);

private:

  virtual void InitializeAction() override;

};

#endif // QMITKDATANODEGLOBALREINITACTION_H
