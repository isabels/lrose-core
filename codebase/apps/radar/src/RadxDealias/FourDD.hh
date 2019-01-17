/*
 *   Module: FourDD.hh
 *
 *   Author: Curtis James 
 *           Packaged into a C++ class by Sue Dettling with a few mods.
 *   
 *   Date:   11/13/2001
 *
 * Copyright Information: This software was developed by the 
 * Mesoscale Group, Department of Atmospheric
 * Sciences, University of Washington, Seattle, WA, USA.
 * Access and use of this software shall impose the following obligations on
 * the user.  The user is granted the right, without any fee or cost, to use,
 * copy, modify, alter, enhance, and distribute this software, and any
 * derivative works thereof, and its supporting documentation for any purpose
 * whatsoever, except commercial sales, provided that this entire notice appears
 * in all copies of the software, derivative works, and supporting 
 * documentation. Further, the user agrees to credit the University 
 * of Washington in any publications that result from the use of this 
 * software or in any software package that includes this software.  
 * The name University of Washington, however, may not be used in 
 * any advertising or publicity to endorse or promote any products or 
 * commercial entity unless specific written permission
 * is obtained from the University of Washington.  The user also understands
 * that the University of Washington is not obligated to provide the user with
 * any support, consulting, training, or assistance of any kind with regard to
 * the use, operation, and performance of this software nor to provide the user
 * with any updates, revisions, new versions, or "bug fixes."
 *  
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY OF WASHINGTON "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MECHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OF WASHINGTON BE LIABLE FOR
 * ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER,
 * INCLUDING BUT NOT LIMITED TO CLAIMS ASSOCIATED WITH THE LOSS OF DATA OR
 * PROFITS, WHICH MAY RESULT FROM AN ACTION IN CONTRACT, NEGLIGENCE, OR OTHER
 * TORTIOUS CLAIM THAT ARISES OUT OF OR IN CONNECTION WITH THE ACCESS, USE, OR
 * PREFORMANCE OF THIS SOFTWARE.
 *
 * 
 *   UW Radial Velocity Unfolding Algorithm
 *   Four-Dimensional Dealiasing (4DD)
 *
 *   DESCRIPTION:
 *     This algorithm unfolds a volume of single Doppler radial velocity data.
 *   The algorithm uses a previously unfolded volume (or VAD if previous volume
 *   is unavailable) and a higher elevation sweep to unfold some of the bins
 *   in each sweep. Then, it completes the unfolding, assuming spatial
 *   continuity around each bin.
 *
 */


#ifndef FOURDD_HH
#define FOURDD_HH

//
// Radius of earth in kilometers. 
// 
#define A 6372.0 

#define PI 3.1415927 

#include <cstdlib>
#include <math.h>
#include <Spdb/SoundingGet.hh>
#include "Rsl.hh"
#include <toolsa/DateTime.hh>
#include <toolsa/mem.h>
#include "Params.hh"
using namespace std;

class FourDD 
{
public:
  
  FourDD(Params &parameters);

  ~FourDD();
  
  int Dealias(Volume *lastVelVol, Volume *currVelVol, Volume *currDbzVol,
	      time_t volTime);
 
  void firstGuess(Volume* soundVolume, float missingVal,short unsigned int *,time_t volTime);

  void unfoldVolume(Volume* rvVolume, Volume* soundVolume, Volume* lastVolume,
     float missingVal, unsigned short rm, unsigned short* success);

  Range window(Volume* rvVolume, int sweepIndex, int startray, int endray,
     int firstbin, int lastbin, float* std, float missingVal, unsigned 
     short* success);

  void prepVolume (Volume* DBZVolume, Volume* rvVolume, float missingVal);

  int findRay (Volume* rvVolume1, Volume* rvVolume2, int sweepIndex1, int 
	sweepIndex2, int currIndex1, float missingVal);

  float previousVal (Volume* rvVolume, Volume* lastVolume, int sweepIndex, int
	currIndex, int rangeIndex, float missingVal);

  int loadSoundingData( time_t issueTime );

private:

  Params            params;

  SoundingGet       sounding;

};

#endif // FOURDD_HH
