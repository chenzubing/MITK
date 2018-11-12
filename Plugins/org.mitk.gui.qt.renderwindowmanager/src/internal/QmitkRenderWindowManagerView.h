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

#ifndef QMITKRENDERWINDOWMANAGERVIEW_H
#define QMITKRENDERWINDOWMANAGERVIEW_H

// render window manager plugin
#include "ui_QmitkRenderWindowManagerControls.h"

// render window manager UI module
#include <QmitkDataStorageRenderWindowInspector.h>

// mitk gui qt application
#include <QmitkDataNodeContextMenu.h>

// mitk gui qt common plugin
#include <QmitkAbstractView.h>

/**
* @brief RenderWindowManager
*/
class QmitkRenderWindowManagerView : public QmitkAbstractView
{
  Q_OBJECT

public:

  static const std::string VIEW_ID;

protected:

  virtual void SetFocus() override;

  virtual void CreateQtPartControl(QWidget* parent) override;

private Q_SLOTS:

  /**
  * @brief Called when the user changes the render window selection in the combo box.
  *
  * @param renderWindowId   The text inside the combo box.
  */
  void OnRenderWindowSelectionChanged(const QString& renderWindowId);

private:

  void SetControlledRenderer();

  QWidget* m_Parent;
  Ui::QmitkRenderWindowManagerControls m_Controls;

  QmitkDataStorageRenderWindowInspector* m_RenderWindowInspector;
  QmitkDataNodeContextMenu* m_DataNodeContextMenu;
  QAbstractItemView* m_InspectorView;

  mitk::RenderWindowLayerUtilities::RendererVector m_ControlledRenderer;

  virtual QItemSelectionModel* GetDataNodeSelectionModel() const override;

};

#endif // QMITKRENDERWINDOWMANAGERVIEW_H
