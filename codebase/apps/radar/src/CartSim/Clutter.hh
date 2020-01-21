// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
// � University Corporation for Atmospheric Research (UCAR) 2009-2010. 
// All rights reserved.  The Government's right to use this data and/or 
// software (the "Work") is restricted, per the terms of Cooperative 
// Agreement (ATM (AGS)-0753581 10/1/08) between UCAR and the National 
// Science Foundation, to a "nonexclusive, nontransferable, irrevocable, 
// royalty-free license to exercise or have exercised for or on behalf of 
// the U.S. throughout the world all the exclusive rights provided by 
// copyrights.  Such license, however, does not include the right to sell 
// copies or phonorecords of the copyrighted works to the public."   The 
// Work is provided "AS IS" and without warranty of any kind.  UCAR 
// EXPRESSLY DISCLAIMS ALL OTHER WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// ANY IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE.  
//  
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
#include <toolsa/copyright.h>
/**
 * @file  Clutter.hh
 * @brief  Sphere with clutter inside
 * @class  Clutter
 * @brief  Sphere with clutter inside
 */

# ifndef    CLUTTER_H
# define    CLUTTER_H

#include "Params.hh"
#include "Thing.hh"
#include "Xyz.hh"
class Data;

//----------------------------------------------------------------
class Clutter : public Thing
{
public:

  /**
   * Default constructor
   */
  Clutter(const Params &P, const Params::ClutterRegion_t &mP);
  
  /**
   * Destructor
   */
  virtual ~Clutter(void);

protected:

  virtual void _addToData(const Xyz &loc, Data &data) const;

private:  

  double _theta;  /**< Center azimuth (degrees math) */
  double _phi;    /**< Center elevation (degrees) */
  double _r;      /**< Center radius meters */
  double _dtheta; /**< width of speck azimuthally degrees */
  double _dphi;   /**< Width of speck elevations (degrees) */
  double _dr;     /**< Width of speck radially meters */

  double _dbz;
  double _vel;
  bool _valuesRandom;
  double _clutter;
  double _percent;
  double _percentCorrect;
};

# endif 
