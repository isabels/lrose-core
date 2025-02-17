// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// ** Copyright UCAR (c) 1990 - 2016                                         
// ** University Corporation for Atmospheric Research (UCAR)                 
// ** National Center for Atmospheric Research (NCAR)                        
// ** Boulder, Colorado, USA                                                 
// ** BSD licence applies - redistribution and use in source and binary      
// ** forms, with or without modification, are permitted provided that       
// ** the following conditions are met:                                      
// ** 1) If the software is modified to produce derivative works,            
// ** such modified software should be clearly marked, so as not             
// ** to confuse it with the version available from UCAR.                    
// ** 2) Redistributions of source code must retain the above copyright      
// ** notice, this list of conditions and the following disclaimer.          
// ** 3) Redistributions in binary form must reproduce the above copyright   
// ** notice, this list of conditions and the following disclaimer in the    
// ** documentation and/or other materials provided with the distribution.   
// ** 4) Neither the name of UCAR nor the names of its contributors,         
// ** if any, may be used to endorse or promote products derived from        
// ** this software without specific prior written permission.               
// ** DISCLAIMER: THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS  
// ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      
// ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
#include <assert.h>
#include <cmath>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <toolsa/toolsa_macros.h>
#include <toolsa/uusleep.h>
#include <toolsa/LogStream.hh>

#include <QTimer>
#include <QBrush>
#include <QPalette>
#include <QPaintEngine>
#include <QPen>
#include <QResizeEvent>
#include <QStylePainter>
#include <QToolTip>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QErrorMessage>

#include "ParameterColorView.hh"
#include "DisplayFieldModel.hh"
#include "FieldColorController.hh"
#include "PolarWidget.hh"
#include "PolarManager.hh"
#include "SpreadSheetView.hh"
#include "SpreadSheetController.hh"
#include "BoundaryPointEditor.hh"

using namespace std;


const double PolarWidget::SIN_45 = sin(45.0 * DEG_TO_RAD);
const double PolarWidget::SIN_30 = sin(30.0 * DEG_TO_RAD);
const double PolarWidget::COS_30 = cos(30.0 * DEG_TO_RAD);

PolarWidget::PolarWidget(QWidget* parent,
                         const PolarManager &manager,
                         const RadxPlatform &platform,
			 DisplayFieldController *displayFieldController,
			 //                         const vector<DisplayField *> &fields,
                         bool haveFilteredFields) :
        QWidget(parent),
        _parent(parent),
        _manager(manager),
        _platform(platform),
        //_fields(fields),
	      displayFieldController(displayFieldController),
        _haveFilteredFields(haveFilteredFields),
        // _selectedField(0),
        _ringsEnabled(false),
        _gridsEnabled(false),
        _angleLinesEnabled(false),
        _scaledLabel(ScaledLabel::DistanceEng),
        _rubberBand(0),
        _ringSpacing(10.0)

{

  _params = ParamFile::Instance();
  string color = _params->backgroundColor;
  _backgroundBrush = QColor(color.c_str());
  _gridRingsColor = _params->gridColor.c_str();

  // mode

  _archiveMode = _params->begin_in_archive_mode;

  // Set up the background color

  QPalette new_palette = palette();
  new_palette.setColor(QPalette::Dark, _backgroundBrush.color());
  setPalette(new_palette);
  
  setBackgroundRole(QPalette::Dark);
  setAutoFillBackground(true);
  setAttribute(Qt::WA_OpaquePaintEvent);

  // Allow the widget to get focus

  setFocusPolicy(Qt::StrongFocus);

  // create the rubber band

  _rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

  // Allow the size_t type to be passed to slots

  qRegisterMetaType<size_t>("size_t");


  // create the field renderers
  _fieldRendererController = new FieldRendererController();
  /*
  size_t nFields = displayFieldController->getNFields();
  for (size_t ii = 0; ii < nFields; ii++) {
    DisplayField *displayField = displayFieldController->getField(ii);
    FieldRenderer *fieldRenderer =
      new FieldRenderer(displayField->getName()); // *_fields[ii]);
    fieldRenderer->createImage(width(), height());
    _fieldRendererController->addFieldRenderer(fieldRenderer);
  }
*/



  // init other values

  _worldPressX = 0.0;
  _worldPressY = 0.0;
  _worldReleaseX = 0.0;
  _worldReleaseY = 0.0;
  _pointClicked = false;
  _mousePressX = 0;
  _mousePressY = 0;
  _mouseReleaseX = 0;
  _mouseReleaseY = 0;
  _zoomCornerX = 0;
  _zoomCornerY = 0;
  
}


/*************************************************************************
 * Destructor
 */

PolarWidget::~PolarWidget()
{

  
  // Delete all of the field renderers
  //delete _fieldRendererController;
  /*
  for (size_t i = 0; i < _fieldRenderers.size(); ++i) {
    delete _fieldRenderers[i];
  }
  _fieldRenderers.clear();
  */
}


/*************************************************************************
 * configure the axes
 */

/*************************************************************************
 * set archive mode
 */

void PolarWidget::setArchiveMode(bool archive_mode)
{
  _archiveMode = archive_mode;
}

/*************************************************************************
 * unzoom the view
 */

void PolarWidget::unzoomView()
{
  LOG(DEBUG) << "enter";
  _zoomWorld = _fullWorld;
  _isZoomed = false;
  _setTransform(_zoomWorld.getTransform());
  _setGridSpacing();
  _dirty = true;
  _refreshImages();
  update();
  LOG(DEBUG) << "exit";
}


/*************************************************************************
 * setRings()
 */

void PolarWidget::setRings(const bool enabled)
{
  _ringsEnabled = enabled;
  update();
}


/*************************************************************************
 * setGrids()
 */

void PolarWidget::setGrids(const bool enabled)
{
  _gridsEnabled = enabled;
  update();
}


/*************************************************************************
 * setAngleLines()
 */

void PolarWidget::setAngleLines(const bool enabled)
{
  _angleLinesEnabled = enabled;
  update();
}



// TODO: this should be a slot?
// TODO: sort out new fields in PolarManager
// Who needs to know about the new fields?
// Beams, FieldRenderers, DisplayFieldController 
void PolarWidget::addNewFields(vector<DisplayField *> &newFields) 
//void PolarWidget::addField(string &fieldName) 
{
  LOG(DEBUG) << "enter";

  //FieldRendererView *fieldRenderer =
  //    new FieldRenderer(_params, fieldIdx, *newFields[ii]);
  //fieldRenderer->createImage(width(), height());


  // add to the field renderers any new fields in the volume
  // for each field in the volume
  /*
  LOG(DEBUG) << "all fields in _vol ... ";
  vector<RadxField *> allFields = vol->getFields();
  vector<RadxField *>::iterator it;
  for (it = allFields.begin(); it != allFields.end(); it++) {
    LOG(DEBUG) << *it;
  }
  */
/*
  //LOG(DEBUG) << "fieldRenderers ...";
  for (size_t ii = 0; ii < newFields.size(); ii++) {

    //    displayFieldController->addField(newFields[ii]);

    int fieldIdx = newFields[ii]->getButtonRow() - 1; // TODO: fix HACK!
    //LOG(DEBUG) << "_fieldRenderers.size() before insert = " << lastFieldIdx;
    // HERE ... 
    // Q: What is fieldIndex?  
    FieldRenderer *fieldRenderer =
      new FieldRenderer(_params, fieldIdx, *newFields[ii]);
    fieldRenderer->createImage(width(), height());
    _fieldRendererController->addFieldRenderer(fieldRenderer);
//    _fieldRenderers.push_back(fieldRenderer);

    //LOG(DEBUG) << "_fieldRenderers.size() after insert = " << _fieldRenderers.size(); 

  }
*/
  // TODO: this may be handled by addBeam, or fillColor?
  //_ppiBeamController->addFieldsToEachBeam(needRay, newFields);    


  // activateArchiveRendering();
  LOG(DEBUG) << "exit";
}


/*
// TODO: this should be a slot?
// TODO: sort out new fields in PolarManager
// Who needs to know about the new fields?
// Beams, FieldRenderers, DisplayFieldController 
void PolarWidget::updateField(size_t fieldIdx) 
{
  LOG(DEBUG) << "enter";

  _fieldRendererController->updateImage(fieldIdx, width(), height());
      //    fieldRenderer->createImage(width(), height());

  LOG(DEBUG) << "exit";
}
*/

/*************************************************************************
 * turn on archive-style rendering - all fields
 */

void PolarWidget::activateArchiveRendering()
{
  LOG(DEBUG) << "enter";
  //_fieldRendererController->activateArchiveRendering();
  //_fieldRendererController->performRendering(0); 
  /*
  LOG(DEBUG) << "_fieldRenderers.size()  = " << _fieldRenderers.size(); 
  for (size_t ii = 0; ii < _fieldRenderers.size(); ii++) {
    _fieldRenderers[ii]->setBackgroundRenderingOn();
  }
  */
  LOG(DEBUG) << "exit";
}


/*************************************************************************
 * displayImage()
 */

void PolarWidget::displayImage(string currentFieldName, double currentSweepAngle,
  RayLocationController *rayLocationController, ColorMap &colorMap,
  QColor backgroundColor)
{
  try {

    // If we weren't rendering the current field, do nothing
    //if (field_num != selectedField) {
    //  return;
    //}
    //update();

    _image = _fieldRendererController->renderImage(width(), height(), 
      currentFieldName, _zoomTransform, currentSweepAngle,
      rayLocationController, colorMap, backgroundColor);


/*
  _fieldRendererController->refreshImages(width(), height(), size(),
            _backgroundBrush.color().rgb(),
            _zoomTransform, 
            selectedField, 
            _ppiBeams);
            */

    update();
  } catch (std::range_error &ex) {
    LOG(ERROR) << ex.what();
    //QMessageBox::warning(NULL, "Error changing field (displayImage):", ex.what());
  }
}


/*************************************************************************
 * backgroundColor()
 */

void PolarWidget::backgroundColor(const QColor &color)
{
  _backgroundBrush.setColor(color);
  QPalette new_palette = palette();
  new_palette.setColor(QPalette::Dark, _backgroundBrush.color());
  setPalette(new_palette);
  _dirty = true;
  _refreshImages();
}


/*************************************************************************
 * gridRingsColor()
 */

void PolarWidget::gridRingsColor(const QColor &color)
{
  LOG(DEBUG) << "enter " << color.name().toStdString();
  _gridRingsColor = color;
  update();
  LOG(DEBUG) << "exit";
}

/*************************************************************************
 * ColorScaleLegend()
 */

void PolarWidget::colorScaleLegend()
{
  LOG(DEBUG) << "enter " ;
  update();
  LOG(DEBUG) << "exit";
}


/*************************************************************************
 * getImage()
 */

QImage* PolarWidget::getImage()
{
  QPixmap pixmap = QPixmap::grabWidget(this);
  QImage* image = new QImage(pixmap.toImage());
  return image;
}


/*************************************************************************
 * getPixmap()
 */

QPixmap* PolarWidget::getPixmap()
{
  QPixmap* pixmap = new QPixmap(QPixmap::grabWidget(this));
  return pixmap;
}


/*************************************************************************
 * Slots
 *************************************************************************/

/*************************************************************************
 * mousePressEvent()
 */

void PolarWidget::mousePressEvent(QMouseEvent *e)
{


  if (e->button() == Qt::RightButton) {

    //-------

      QPointF clickPos(e->pos());

      _mousePressX = e->x();
      _mousePressY = e->y();

      _worldPressX = _zoomWorld.getXWorld(_mousePressX);
      _worldPressY = _zoomWorld.getYWorld(_mousePressY);

      emit customContextMenuRequested(clickPos.toPoint()); // , closestRay);

  } else {


  _rubberBand->setGeometry(QRect(e->pos(), QSize()));
  _rubberBand->show();

  _mousePressX = e->x();
  _mousePressY = e->y();

  _worldPressX = _zoomWorld.getXWorld(_mousePressX);
  _worldPressY = _zoomWorld.getYWorld(_mousePressY);
  }
}


/*************************************************************************
 * mouseMoveEvent(), mouse button is down and mouse is moving
 */

void PolarWidget::mouseMoveEvent(QMouseEvent * e)
{
  int worldX = (int)_zoomWorld.getXWorld(e->pos().x());
  int worldY = (int)_zoomWorld.getYWorld(e->pos().y());

  // ---- insert here ---

  if (_manager._boundaryEditorDialog->isVisible()) {

    BoundaryToolType tool = BoundaryPointEditor::Instance()->getCurrentTool();
    
    if (tool == BoundaryToolType::polygon && 
        BoundaryPointEditor::Instance()->isAClosedPolygon() && 
        BoundaryPointEditor::Instance()->isOverAnyPoint(worldX, worldY)) {
      BoundaryPointEditor::Instance()->moveNearestPointTo(worldX, worldY);
    } else if (tool == BoundaryToolType::brush) {
      BoundaryPointEditor::Instance()->addToBrushShape(worldX, worldY);
    }
    //_dirty = true;
    update();
    return;
  }

  /* ---- cut here --- 
  if (_manager._boundaryEditorDialog->isVisible() && BoundaryPointEditor::Instance()->isPolygonFinished() && BoundaryPointEditor::Instance()->isOverAnyPoint(worldX, worldY))
  {
	BoundaryPointEditor::Instance()->moveNearestPointTo(worldX, worldY);
	update();
	return;
  }
  // ----- cut here ----
  */

  // Zooming with the mouse

  int x = e->x();
  int y = e->y();
  int deltaX = x - _mousePressX;
  int deltaY = y - _mousePressY;

  // Make the rubberband aspect ratio match that
  // of the window

  double dx = fabs(deltaY * _aspectRatio);
  double dy = fabs(dx / _aspectRatio);

  // Preserve the signs

  dx *= fabs(deltaX)/deltaX;
  dy *= fabs(deltaY)/deltaY;

  int moveX = (int) floor(dx + 0.5);
  int moveY = (int) floor(dy + 0.5);
  QRect newRect = QRect(_mousePressX, _mousePressY, moveX, moveY);

  _zoomCornerX = _mousePressX + moveX;
  _zoomCornerY = _mousePressY + moveY;

  newRect = newRect.normalized();
  _rubberBand->setGeometry(newRect);

}


/*************************************************************************
 * mouseReleaseEvent()
 */

void PolarWidget::mouseReleaseEvent(QMouseEvent *e)
{

  _pointClicked = false;

  if (e->button() == Qt::RightButton) {

      QPointF clickPos(e->pos());

      _mousePressX = e->x();
      _mousePressY = e->y();

      emit customContextMenuRequested(clickPos.toPoint()); // , closestRay);

  } else {

  QRect rgeom = _rubberBand->geometry();

  // If the mouse hasn't moved much, assume we are clicking rather than
  // zooming

  QPointF clickPos(e->pos());
  
  _mouseReleaseX = clickPos.x();
  _mouseReleaseY = clickPos.y();

  // get click location in world coords

  if (rgeom.width() <= 20) {
    
    // Emit a signal to indicate that the click location has changed
    
    _worldReleaseX = _zoomWorld.getXWorld(_mouseReleaseX);
    _worldReleaseY = _zoomWorld.getYWorld(_mouseReleaseY);

    double x_km = _worldReleaseX;
    double y_km = _worldReleaseY;
    _pointClicked = true;


    /***** testing ******
    // QToolTip::showText(mapToGlobal(QPoint(_mouseReleaseX, _mouseReleaseY)), "louigi")  
    QToolTip::showText(QPoint(0,0), "louigi");

    smartBrush(_mouseReleaseX, _mouseReleaseY);

    // ***** end testing ****/

    // get ray closest to click point

    const RadxRay *closestRay = _getClosestRay(x_km, y_km);

    // emit signal

    emit locationClicked(x_km, y_km, closestRay);
  
  } else {

    // mouse moved more than 20 pixels, so a zoom occurred
    
    _worldPressX = _zoomWorld.getXWorld(_mousePressX);
    _worldPressY = _zoomWorld.getYWorld(_mousePressY);

    _worldReleaseX = _zoomWorld.getXWorld(_zoomCornerX);
    _worldReleaseY = _zoomWorld.getYWorld(_zoomCornerY);

    _zoomWorld.set(_worldPressX, _worldPressY, _worldReleaseX, _worldReleaseY);

    _setTransform(_zoomWorld.getTransform());

    _setGridSpacing();

    // enable unzoom button
    
    _manager.enableZoomButton();
    
    // Update the window in the renderers
    
    _dirty = true;
    _refreshImages();

  }
    
  // hide the rubber band

  _rubberBand->hide();
  update();
  }
}

/**************   testing *****
void PolarWidget::smartBrush(int xPixel, int yPixel) {
  //int xp = _ppi->_zoomWorld.getIxPixel(xkm);
  //int yp = _ppi->_zoomWorld.getIyPixel(ykm);

  QImage qImage;
  qImage.load("/h/eol/brenda/octopus.jpg");
  // get the Image from somewhere ...   
  //qImage->convertToFormat(QImage::Format_RGB32);
  //qImage->invertPixels();
  QPainter painter(this);
  painter.drawImage(0, 0, qImage);
  _drawOverlays(painter);

}

*/

void PolarWidget::imageReady(QImage *image) {
//  _image = image;  // TODO: make sure this isn't a copy!  just assign a pointer
//  update();
}

/*************************************************************************
 * paintEvent()
 */

void PolarWidget::paintEvent(QPaintEvent *event)
{
  LOG(DEBUG) << "enter";
  try {
    _refreshImages();
    showSelectedField();
    /*
    string selectedField = displayFieldController->getSelectedFieldName();
    _image = _fieldRendererController->getImage(selectedField);
  //update(); 
  QPainter painter(this);
  //size_t selectedField = displayFieldController->getSelectedFieldNum();

  //FieldRenderer *fieldRenderer = _fieldRendererController->get(selectedField);

  //QImage *image = _fieldRendererController->getImage(selectedField, selectedSweep);
  //painter.drawImage(0, 0, *(displayFieldController->getSelectedFieldImage()));
  //painter.(0, 0, *(fieldRenderer->getImage()));
  //  painter.drawImage(0, 0, *(_fieldRenderers[_selectedField]->getImage()));

  // _image should already be set by previous slot imageReady
  if (_image != NULL) {
    painter.drawImage(0, 0, *_image);
        //painter.drawImage(100, 300, *_image);
  }

  _drawOverlays(painter);

  BoundaryPointEditor::Instance()->draw(_zoomWorld, painter);  //if there are no points, this does nothing
   */
  } catch (const std::out_of_range& ex) {
    LOG(DEBUG) << ex.what();
  } catch (std::range_error &ex) {
      LOG(ERROR) << ex.what();
      //QMessageBox::warning(NULL, "Error changing field (_changeField):", ex.what());
  }
  LOG(DEBUG) << "exit";
}

void PolarWidget::showSelectedField()
{
  LOG(DEBUG) << "enter";
  try {
    string selectedField = displayFieldController->getSelectedFieldName();
    _image = _fieldRendererController->getImage(selectedField);
  //update(); 
  QPainter painter(this);
  //size_t selectedField = displayFieldController->getSelectedFieldNum();

  //FieldRenderer *fieldRenderer = _fieldRendererController->get(selectedField);

  //QImage *image = _fieldRendererController->getImage(selectedField, selectedSweep);
  //painter.drawImage(0, 0, *(displayFieldController->getSelectedFieldImage()));
  //painter.(0, 0, *(fieldRenderer->getImage()));
  //  painter.drawImage(0, 0, *(_fieldRenderers[_selectedField]->getImage()));

  // _image should already be set by previous slot imageReady
  if (_image != NULL) {
    painter.drawImage(0, 0, *_image);
        //painter.drawImage(100, 300, *_image);
  }

  _drawOverlays(painter);

  BoundaryPointEditor::Instance()->draw(_zoomWorld, painter);  //if there are no points, this does nothing
  } catch (const std::out_of_range& ex) {
    LOG(DEBUG) << ex.what();
  } catch (std::range_error &ex) {
      LOG(ERROR) << ex.what();
      //QMessageBox::warning(NULL, "Error changing field (_changeField):", ex.what());
  }
  LOG(DEBUG) << "exit";
}


/*************************************************************************
 * resizeEvent()
 */

void PolarWidget::resizeEvent(QResizeEvent * e)
{ 
  LOG(DEBUG) << "enter";
  _resetWorld(width(), height());
  LOG(DEBUG) << "exit";
}


/*************************************************************************
 * resize()
 */

void PolarWidget::resize(const int width, const int height)
{

  LOG(DEBUG) << "enter";
  // Set the geometry based on the aspect ratio that we need for this display.
  // The setGeometry() method will fire off the resizeEvent() so we leave the
  // updating of the display to that event.
  
  int sizeNeeded = (int) ((width - _colorScaleWidth) / _aspectRatio + 0.5);
  if (height < sizeNeeded) {
    sizeNeeded = height;
  }
  // setGeometry triggers a resizeEvent
  setGeometry(0, 0, 
              (int) (sizeNeeded * _aspectRatio + 0.5) + _colorScaleWidth,
              sizeNeeded);
  LOG(DEBUG) << "exit";
}

//////////////////////////////////////////////////////////////
// reset the pixel size of the world view

void PolarWidget::_resetWorld(int width, int height)

{

  _fullWorld.resize(width, height);
  _zoomWorld = _fullWorld;
  _setTransform(_fullWorld.getTransform());
  _setGridSpacing();
  _dirty = true;
}


/*************************************************************************
 * Protected methods
 *************************************************************************/

////////////////////
// set the transform

void PolarWidget::_setTransform(const QTransform &transform)
{
  
  _fullTransform = transform;
  _zoomTransform = transform;
  
}
  
/*************************************************************************
 * perform the rendering
 */

void PolarWidget::_performRendering()
{
  LOG(DEBUG) << "enter";
  /*
  try {
    size_t selectedField = displayFieldController->getSelectedFieldNum();
    _fieldRendererController->performRendering(selectedField);
    update();
  } catch (std::range_error &ex) {
      LOG(ERROR) << ex.what();
      // QMessageBox::warning(NULL, "Error changing color map", ex.what());
  }
  */
  LOG(DEBUG) << "exit";
}

void PolarWidget::informationMessage()
{
  // QMessageBox::StandardButton reply;
  // QLabel *informationLabel;

  // reply = QMessageBox::information(this, "QMessageBox::information()", "Not implemented");
  QMessageBox::information(this, "QMessageBox::information()", "Not implemented");
  //  if (reply == QMessageBox::Ok)
  //  informationLabel->setText("OK");
  //else
  //  informationLabel->setText("Escape");

}

void PolarWidget::notImplemented()
{
  cerr << "inside notImplemented() ... " << endl;

  QErrorMessage *errorMessageDialog = new QErrorMessage(_parent);
  // QLabel *informationLabel = new QLabel();

  errorMessageDialog->showMessage("This option is not implemented yet.");
  QLabel errorLabel;
  int frameStyle = QFrame::Sunken | QFrame::Panel;
  errorLabel.setFrameStyle(frameStyle);
  errorLabel.setText("If the box is unchecked, the message "
		     "won't appear again.");

  cerr << "exiting notImplemented() " << endl;

}


// slots for context editing; create and show the associated modeless dialog and return                                   

void PolarWidget::contextMenuCancel()
{
  //  informationMessage();

  //notImplemented();                                                                                                     
}

void PolarWidget::contextMenuParameterColors()
{

  informationMessage();
   
}

void PolarWidget::contextMenuView()
{
  informationMessage();
  //  notImplemented();                                                                                                   
}

void PolarWidget::contextMenuEditor()
{
  informationMessage();
  //  notImplemented();                                                                                                   
}


void PolarWidget::contextMenuExamine()         
{
  informationMessage();                                                                                                 

}

void PolarWidget::contextMenuDataWidget()
{
  informationMessage();

  //  notImplemented();                                                                                                   
}

void PolarWidget::contextMenuHistogram()
{
  informationMessage();
  //  notImplemented();                                                                                                   
}


void PolarWidget::ExamineEdit(const RadxRay *closestRay) 
{
  notImplemented();
}

void PolarWidget::ShowContextMenu(const QPoint &pos, RadxVol *vol) 
{  
  notImplemented();
}

