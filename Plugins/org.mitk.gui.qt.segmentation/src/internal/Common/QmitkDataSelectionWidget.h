/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/

#ifndef QmitkDataSelectionWidget_h
#define QmitkDataSelectionWidget_h

#include <ui_QmitkDataSelectionWidgetControls.h>
#include <mitkDataNode.h>
#include <mitkDataStorage.h>
#include <vector>

namespace mitk
{
  class NodePredicateBase;
}

class QmitkSingleNodeSelectionWidget;

class QmitkDataSelectionWidget : public QWidget
{
  Q_OBJECT

public:
  enum Predicate
  {
    ImagePredicate,
    SegmentationPredicate,
    SurfacePredicate,
    ImageAndSegmentationPredicate,
    ContourModelPredicate
  };

  explicit QmitkDataSelectionWidget(QWidget* parent = nullptr);
  ~QmitkDataSelectionWidget() override;

  unsigned int AddDataStorageComboBox(Predicate predicate);
  unsigned int AddDataStorageComboBox(mitk::NodePredicateBase* predicate = nullptr);
  unsigned int AddDataStorageComboBox(const QString &labelText, const QString &info, const QString &popupTitel, const QString &popupHint, Predicate predicate);
  unsigned int AddDataStorageComboBox(const QString &labelText, const QString &info, const QString &popupTitel, const QString &popupHint, mitk::NodePredicateBase* predicate = nullptr);

  mitk::DataStorage::Pointer GetDataStorage() const;
  mitk::DataNode::Pointer GetSelection(unsigned int index);
  void SetPredicate(unsigned int index, Predicate predicate);
  void SetPredicate(unsigned int index, mitk::NodePredicateBase* predicate);
  void SetHelpText(const QString& text);

signals:
  void SelectionChanged(unsigned int index, const mitk::DataNode* selection);

private slots:
  void OnSelectionChanged(QList<mitk::DataNode::Pointer> selection);

private:
  Ui::QmitkDataSelectionWidgetControls m_Controls;
  std::vector<QmitkSingleNodeSelectionWidget*> m_NodeSelectionWidgets;
};

#endif
