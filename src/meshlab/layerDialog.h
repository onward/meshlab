/****************************************************************************
* MeshLab                                                           o o     *
* An extendible mesh processor                                    o     o   *
*                                                                _   O  _   *
* Copyright(C) 2005, 2006                                          \/)\/    *
* Visual Computing Lab                                            /\/|      *
* ISTI - Italian National Research Council                           |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/


#ifndef LAYER_DIALOG_H
#define LAYER_DIALOG_H

#include <QTreeWidgetItem>
#include <QDockWidget>
#include <QTabWidget>
#include <QGroupBox>
#include <QCheckBox>
#include <common/filterparameter.h>
#include <common/ml_shared_data_context.h>
#include "ml_render_gui.h"



class MainWindow;
class QTreeWidget;
class GLLogStream;
class MeshModel;
class RasterModel;
class MeshDocument;
class MeshDecorateInterface;
class StdParFrame;
class QGridLayout;
class QToolBar;

#include <QDialog>

namespace Ui
{
    class layerDialog;
}


class MeshTreeWidgetItem : public QTreeWidgetItem
{ 
public:
    MeshTreeWidgetItem(MeshModel* meshmodel,QTreeWidget* tree,MLRenderingToolbar* rendertoolbar);
    ~MeshTreeWidgetItem();
    void updateVisibilityIcon(bool isvisible);

    MLRenderingToolbar* _rendertoolbar;
    int _meshid;
};

class RasterTreeWidgetItem : public QTreeWidgetItem
{
public:
    RasterTreeWidgetItem(RasterModel *);
    void updateVisibilityIcon( bool isvisible );
    //RasterModel *r;
    int _rasterid;
};

class DecoratorParamItem : public QTreeWidgetItem
{
public:
    DecoratorParamItem(QAction* );

    QAction* act;
};

class DecoratorParamsTreeWidget : public QFrame
{
    Q_OBJECT
public:
    DecoratorParamsTreeWidget(QAction* act,MainWindow *mw,QWidget* parent);
    ~DecoratorParamsTreeWidget();

public slots:
    void save();
    void reset();
    void apply();
    void load();

private:
    float osDependentButtonHeightScaleFactor();
    MainWindow* mainWin;
    StdParFrame* frame;
    RichParameterSet tmpSet;
    QPushButton* savebut;
    QPushButton* resetbut;
    QPushButton* loadbut;
    QGridLayout* dialoglayout;
};

class LayerDialog : public QDockWidget
{
    Q_OBJECT
public:
    LayerDialog(QWidget *parent = 0);
    ~LayerDialog();
	void updateLog(GLLogStream &Log);
    void updateDecoratorParsView();
    void updateRenderingParametersTab(int meshid,const MLRenderingData& dt);
    void reset();
    MLRenderingParametersTab* createRenderingParametersTab();
public slots:
    void keyPressEvent ( QKeyEvent * event );
    void updateTable(const MLSceneGLSharedDataContext::PerMeshRenderingDataMap& dtf);
    void rasterItemClicked(QTreeWidgetItem * , int );
    void meshItemClicked(QTreeWidgetItem * , int );
    void showEvent ( QShowEvent * event );
    void showContextMenu(const QPoint& pos);
    void adaptLayout(QTreeWidgetItem * item);
    void updateRenderingDataAccordingToActions(int meshid,const QList<MLRenderingAction*>&);
    void updateRenderingDataAccordingToAction(int meshid,MLRenderingAction*);
    void actionActivated(MLRenderingAction* ract);

private slots:
	/*WARNING!!! ADDED just to avoid usual mac strange behavior. Please, avoid to use it if it's not absolutely necessary*/
	void updateTable();

private:
    Ui::layerDialog* ui;
    MainWindow *mw;

    QMenu *rasterMenu;
    QAction* addNewRasterAct;
    QAction* removeCurrentRasterAct;
    //It stores if the treeWidgetItems are expanded or not
    QMap< QPair<int ,int> ,  bool> expandedMap;
    
    //QList<QToolBar*> tobedel;
    void addDefaultNotes(QTreeWidgetItem * parent, MeshModel *meshModel);
    void updateColumnNumber(const QTreeWidgetItem * item);
    //QVector<QTreeWidgetItem*> tobedeleted;
    void updateExpandedMap(int meshId, int tagId, bool expanded);
    void updatePerMeshItemSelectionStatus();
    void updatePerRasterItemSelectionStatus();
    void updatePerMeshItemVisibility();
    void updatePerRasterItemVisibility();

    void updateProjectName(const QString& name);

    QTreeWidgetItem* _docitem;
	MLRenderingSideToolbar* _globaldoctool;
    int _previd;
	QGroupBox* _renderingtabcontainer;
	QCheckBox* _applytovis;
public:
	MLRenderingParametersTab* _tabw;
signals:
    void removeDecoratorRequested(QAction* );
    void toBeShow();
};


#endif
