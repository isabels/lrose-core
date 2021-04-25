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
/////////////////////////////////////////////////////////////
// WaterfallPlot.hh
//
// Plotting of spectra vs range
//
// Mike Dixon, EOL, NCAR, P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// April 2021
//
///////////////////////////////////////////////////////////////
#ifndef WaterfallPlot_HH
#define WaterfallPlot_HH

#include <string>
#include <vector>

#include <QDialog>
#include <QWidget>
#include <QResizeEvent>
#include <QImage>
#include <QTimer>
#include <QRubberBand>
#include <QPoint>
#include <QTransform>

#include "Params.hh"
#include "ScaledLabel.hh"
#include "WorldPlot.hh"
#include "ColorMap.hh"

class Beam;
class MomentsFields;

/// Waterfall plotting

class WaterfallPlot
{

public:

  ////////////////////
  // Public methods //
  ////////////////////

  /**
   * Constructor.
   */
  
  WaterfallPlot(QWidget *parent,
                const Params &params,
                int id);
  
  /**
   * @brief Destructor.
   */

  virtual ~WaterfallPlot();

  /**
   * Clear the plot
   */
  
  void clear();

  // set the window geometry
  
  void setWindowGeom(int width,
                     int height,
                     int xOffset,
                     int yOffset);

  // set the world limits

  void setWorldLimits(double xMinWorld,
                      double yMinWorld,
                      double xMaxWorld,
                      double yMaxWorld);

  // set the zoom limits, using pixel space

  void setZoomLimits(int xMin,
                     int yMin,
                     int xMax,
                     int yMax);
  
  void setZoomLimitsX(int xMin,
                      int xMax);

  void setZoomLimitsY(int yMin,
                      int yMax);

  // set the moment type

  void setPlotType(Params::waterfall_type_t val) { _plotType = val; }
  
  // zooming

  void zoom(int x1, int y1, int x2, int y2);
  void unzoom();

  // plot a beam
  
  void plotBeam(QPainter &painter,
                Beam *beam,
                double selectedRangeKm);

  // set grid lines on/off

  void setXGridLinesOn(bool val) { _xGridLinesOn = val; }
  void setYGridLinesOn(bool val) { _yGridLinesOn = val; }
  
  // get the world plot objects
  
  WorldPlot &getFullWorld() { return _fullWorld; }
  WorldPlot &getZoomWorld() { return _zoomWorld; }
  bool getIsZoomed() const { return _isZoomed; }

  // get the window geom

  int getWidth() const { return _fullWorld.getWidthPixels(); }
  int getHeight() const { return _fullWorld.getHeightPixels(); }
  int getXOffset() const { return _fullWorld.getXPixOffset(); }
  int getYOffset() const { return _fullWorld.getYPixOffset(); }
  
  // get grid lines state

  bool getXGridLinesOn() const { return _xGridLinesOn; }
  bool getYGridLinesOn() const { return _yGridLinesOn; }
  
  // get the moment type
  
  const Params::waterfall_type_t getPlotType() const { return _plotType; }
  static string getName(Params::waterfall_type_t wtype);
  static string getUnits(Params::waterfall_type_t wtype);
  
protected:

  ///////////////////////
  // Protected members //
  ///////////////////////

  QWidget *_parent;
  const Params &_params;
  int _id;

  // moment type active for plotting

  Params::waterfall_type_t _plotType;
  
  // unzoomed world

  WorldPlot _fullWorld;

  // color map

  ColorMap _cmap;

  // zoomed world

  bool _isZoomed;
  WorldPlot _zoomWorld;

  // grid lines

  bool _xGridLinesOn;
  bool _yGridLinesOn;
  
  ///////////////////////
  // Protected methods //
  ///////////////////////

  void _drawOverlays(QPainter &painter, double selectedRangeKm);
  int _readColorMap();
  
};

#endif
