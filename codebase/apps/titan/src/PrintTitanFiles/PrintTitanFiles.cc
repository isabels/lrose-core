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
///////////////////////////////////////////////////////////////
// PrintTitanFiles.cc
//
// PrintTitanFiles object
//
// Mike Dixon, RAP, NCAR
// P.O.Box 3000, Boulder, CO, 80307-3000, USA
//
// Feb 2001
//
///////////////////////////////////////////////////////////////
//
// PrintTitanFiles produces ASCII output from TITAN binary files.
// Output goes to stdout.
//
///////////////////////////////////////////////////////////////

#include "PrintTitanFiles.hh"
#include "Args.hh"
#include <toolsa/file_io.h>
#include <toolsa/str.h>
#include <toolsa/Path.hh>
#include <toolsa/sincos.h>
#include <toolsa/TaXml.hh>
#include <titan/Titan2Xml.hh>
#include <cerrno>
#include <vector>
#include <map>
using namespace std;

// Constructor

PrintTitanFiles::PrintTitanFiles(int argc, char **argv)
  
{
  
  // initialize

  OK = true;
  
  // set programe name
  
  _progName = "PrintTitanFiles";

  // get command line args

  if (_args.parse(argc, argv, _progName)) {
    cerr << "ERROR: " << _progName << endl;
    cerr << "  Problem with command line args" << endl;
    OK = false;
    return;
  }

  return;

}

// destructor

PrintTitanFiles::~PrintTitanFiles()

{

}

//////////////////////////////////////////////////
// Run

int PrintTitanFiles::Run()
{

  // read the file label

  char file_label[R_FILE_LABEL_LEN];
  if (_readLabel(file_label)) {
    return -1;
  }
  
  // show info for given file type

  if (!strcmp(file_label, STORM_HEADER_FILE_TYPE)) {

    if (_args.printAsXml) {
      if (_printStormsXml()) {
        return -1;
      }
    } else {
      if (_printStormFile()) {
        return -1;
      }
    }

  } else if (!strcmp(file_label, TRACK_HEADER_FILE_TYPE)) {

    if (_args.printAsXml) {
      if (_printTracksXml()) {
        return -1;
      }
    } else {
      if (_printTrackFile()) {
        return -1;
      }
    }

  } else {

    cerr << "ERROR - " << _progName << endl;
    cerr << "Unknown file type: " << _args.path << endl;
    return -1;

  }

  return 0;

}

//////////////////////////////////////////////////
// read label

int PrintTitanFiles::_readLabel(char *label)
{

  FILE *in;

  // open file

  char path[MAX_PATH_LEN];
  STRncopy(path, _args.path.c_str(), MAX_PATH_LEN);
  if ((in = ta_fopen_uncompress(path, "r")) == NULL) {
    int errNum = errno;
    cerr << "ERROR - PrintTitanFiles::_readLabel" << endl;
    cerr << "  Cannot open file: " << _args.path << endl;
    cerr << strerror(errNum) << endl;
    return -1;
  }
  
  // read label

  if (ufread(label, sizeof(char), R_FILE_LABEL_LEN,
	     in) != R_FILE_LABEL_LEN) {
    int errNum = errno;
    cerr << "ERROR - PrintTitanFiles::_readLabel" << endl;
    cerr << "  Cannot read label from file: " << _args.path << endl;
    cerr << strerror(errNum) << endl;
    fclose(in);
    return -1;
  }

  fclose(in);

  return 0;

}


//////////////////////////////////////////////////
// printStormFile

#define BOOL_STR(a) (a == 0? "false" : "true")

int PrintTitanFiles::_printStormFile()

{

  TitanStormFile sfile;
  
  // open storm properties files
  
  if (sfile.OpenFiles("r", _args.path.c_str())) {
    cerr << "ERROR - PrintTitanFiles::_printStormFile" << endl;
    cerr << sfile.getErrStr() << endl;
    return -1;
  }

  //  read in storm properties file header

  if (sfile.ReadHeader()) {
    cerr << "ERROR - PrintTitanFiles::_printStormFile" << endl;
    cerr << sfile.getErrStr() << endl;
    return -1;
  }

  int n_scans = sfile.header().n_scans;
  const storm_file_params_t &params = sfile.header().params;
  
  // print out header
  
  fprintf(stdout, "STORM FILE\n");
  fprintf(stdout, "==========\n");
  fprintf(stdout, "Header file label : %s\n",
	  sfile.header_file_label().c_str());
  fprintf(stdout, "Data   file label : %s\n",
	  sfile.data_file_label().c_str());
  fprintf(stdout, "\n");
  
  RfPrintStormHeader(stdout, "  ", &sfile.header());

  /*
   * loop through scans
   */
  
  for (int iscan = 0; iscan < n_scans; iscan++) {

    /*
     * read in scan info
     */

    if (sfile.ReadScan(iscan)) {
      cerr << "ERROR - PrintTitanFiles::_printStormFile" << endl;
      cerr << sfile.getErrStr() << endl;
      return -1;
    }

    const storm_file_scan_header_t &scan = sfile.scan();
    
    /*
     * print out s_handle.scan info
     */

    if (_args.printSummary) {
      
      printf("Scan, time, nstorms : %4d %s %4d\n",
	     scan.scan_num, utimstr(scan.time), scan.nstorms);

    } else {
      
      RfPrintStormScan(stdout, "    ", &params, &sfile.scan());
      
      if (_args.printFull) {
	
	for (int istorm = 0; istorm < scan.nstorms; istorm++) {
	  
	  if (sfile.ReadProps(istorm)) {
	    cerr << "ERROR - PrintTitanFiles::_printStormFile" << endl;
	    cerr << sfile.getErrStr() << endl;
	    return -1;
	  }
	  
	  RfPrintStormProps(stdout, "      ", &params,
			    &sfile.scan(),
			    sfile.gprops() + istorm);
	  
	  RfPrintStormLayer(stdout, "      ", &params,
			    &sfile.scan(),
			    sfile.gprops() + istorm,
			    sfile.lprops());
	  
	  RfPrintStormHist(stdout, "      ", &params,
			   sfile.gprops() + istorm,
			   sfile.hist());
	  
	  
	  RfPrintStormRuns(stdout, "      ",
			   sfile.gprops() + istorm,
			   sfile.runs());
	  
	  RfPrintStormProjRuns(stdout, "      ",
			       sfile.gprops() + istorm,
			       sfile.proj_runs());
	  
	} // istorm

      } // f (_args.printFull)

    } // if (_args.printSummary)

  } // iscan
  
  // close files

  sfile.CloseFiles();

  return 0;

}

//////////////////////////////////////////////////
// printTrackFile

int PrintTitanFiles::_printTrackFile()

{

  // open track properties files
  
  TitanTrackFile tfile;
  if (tfile.OpenFiles("r", _args.path.c_str())) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << tfile.getErrStr() << endl;
    return -1;
  }
  
  // read in track properties file header

  if (tfile.ReadHeader()) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << tfile.getErrStr() << endl;
    return -1;
  }

  if (tfile.ReadSimplesPerComplex()) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << tfile.getErrStr() << endl;
    return -1;
  }

  // print out header
  
  if (_args.printCsvTable) {
      
    if (_args.csvTableType == 1) {
      // table type 1
      printf("%%timestep; id;  centerx;  centery; volume;"
             "  boxxmin;  boxxmax;  boxymin;  boxymax;"
             " lwpmean;  lwpmin;  lwpmax\n");
    } else if (_args.csvTableType == 2) {
      // table type 2
      printf("%%timestep; idstep1; idstep2;  weight\n");
    } else if (_args.csvTableType == 3) {
      // table type 3
      printf("%%timestep; nstorms\n");
    } else if (_args.csvTableType == 4) {
      // table type 4
      printf("%%complex_track_num; duration_in_scans; duration_in_secs\n");
    } else if (_args.csvTableType == 5) {
      // table type 5
      printf("%%complex_track_num; simple_track_num; "
             "duration_in_scans; duration_in_secs\n");
    }

  } else {
    
    printf("TRACK FILE\n");
    printf("==========\n");
    printf("Header file label : %s\n", tfile.header_file_label().c_str());
    printf("Data   file label : %s\n", tfile.data_file_label().c_str());
    printf("\n");
  
    RfPrintTrackHeader(stdout, "  ", &tfile.header());

  }

  if (_args.printFull) {
    RfPrintTrackHeaderArrays(stdout, "  ",
			     &tfile.header(),
			     tfile.complex_track_nums(),
			     tfile.complex_track_offsets(),
			     tfile.simple_track_offsets(),
			     tfile.nsimples_per_complex(),
			     tfile.simples_per_complex_offsets(),
			     (const si32 **) tfile.simples_per_complex(),
			     tfile.scan_index());
  }

  // open storm file

  Path trackPath(_args.path);
  string stormFilePath = trackPath.getDirectory();
  stormFilePath += PATH_DELIM;
  stormFilePath += tfile.header().storm_header_file_name;

  TitanStormFile sfile;
  if (sfile.OpenFiles("r", stormFilePath.c_str())) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << sfile.getErrStr() << endl;
    return -1;
  }

  // read in storm properties file header
  
  if (sfile.ReadHeader()) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << sfile.getErrStr() << endl;
    return -1;
  }

  // if full listing, print out track info
  
  if (_args.printFull) {
    if (_printTrackFull(sfile, tfile)) {
      return -1;
    }
  } else if (_args.printSummary) {
    if (_printTrackSummary(sfile, tfile)) {
      return -1;
    }
  } else if (_args.printCsvTable) {
    if (_args.csvTableType == 1) {
      if (_printCsvTableType1(sfile, tfile)) {
        return -1;
      }
    } else if (_args.csvTableType == 2) {
      if (_printCsvTableType2(sfile, tfile)) {
        return -1;
      }
    } else if (_args.csvTableType == 3) {
      if (_printCsvTableType3(sfile, tfile)) {
        return -1;
      }
    } else if (_args.csvTableType == 4) {
      if (_printCsvTableType4(sfile, tfile)) {
        return -1;
      }
    } else if (_args.csvTableType == 5) {
      if (_printCsvTableType5(sfile, tfile)) {
        return -1;
      }
    }
  }
    
  // close files

  sfile.CloseFiles();
  tfile.CloseFiles();

  return 0;

}

/////////////////////////////////////////////////////////////////////
// Print track in full

int PrintTitanFiles::_printTrackFull(TitanStormFile &sfile,
                                     TitanTrackFile &tfile)
  

{
  
  const storm_file_params_t &sparams = sfile.header().params;
  const track_file_params_t &tparams = tfile.header().params;
  const track_file_verify_t &verify = tfile.header().verify;

  /*
   * complex tracks
   */
  
  for (int icomplex = 0;
       icomplex < tfile.header().n_complex_tracks; icomplex++) {

    int complex_track_num = tfile.complex_track_nums()[icomplex];
    
    if (_args.trackNum >= 0 &&
	_args.trackNum != complex_track_num) {
      continue;
    }

    if (tfile.ReadComplexParams(complex_track_num, true)) {
      cerr << "ERROR - PrintTitanFiles::_printTrackFull" << endl;
      cerr << tfile.getErrStr() << endl;
      return -1;
    }
    
    RfPrintComplexTrackParams(stdout, "    ",
			      verify.verification_performed,
			      &tparams,
			      &tfile.complex_params(),
			      tfile.simples_per_complex()[complex_track_num]);
    
    // simple tracks in this complex track
    
    for (int isimple = 0;
	 isimple < tfile.complex_params().n_simple_tracks; isimple++) {
      
      int simple_track_num =
	tfile.simples_per_complex()[complex_track_num][isimple];

      // prepare to read in simple track

      if (tfile.RewindSimple(simple_track_num)) {
	cerr << "ERROR - PrintTitanFiles::_printTrackFull" << endl;
	cerr << tfile.getErrStr() << endl;
	return -1;
      }
      
      RfPrintSimpleTrackParams(stdout, "      ",
			       &tfile.simple_params());
      
      // loop through the track entries
      
      for (int ientry = 0;
	   ientry < tfile.simple_params().duration_in_scans; ientry++) {
	
	if (tfile.ReadEntry()) {
	  cerr << "ERROR - PrintTitanFiles::_printTrackFull" << endl;
	  cerr << tfile.getErrStr() << endl;
	  return -1;
	}
	
	const track_file_entry_t &entry = tfile.entry();
	
	// check that simple and complex track numbers are
	// correct
	
	if (entry.complex_track_num !=
	    tfile.complex_params().complex_track_num) {
	  fprintf(stderr, "\aERROR: complex track num "
		  "incorrect in entry\n");
	  fprintf(stderr, "complex_params->complex_track_num : %d\n",
		  tfile.complex_params().complex_track_num);
	  fprintf(stderr, "entry.complex_track_num : %d\n",
		  entry.complex_track_num);
	}
	
	if (entry.simple_track_num !=
	    tfile.simple_params().simple_track_num) {
	  fprintf(stderr, "\aERROR: simple track num "
		  "incorrect in entry\n");
	  fprintf(stderr, "simple_params->simple_track_num : %d\n",
		  tfile.simple_params().simple_track_num);
	  fprintf(stderr, "entry.simple_track_num : %d\n",
		  entry.simple_track_num);
	}
	
	RfPrintTrackEntry(stdout, "        ",
			  ientry, &tparams, &entry);
	
	if (_args.trackNum >= 0) {
	  
	  // read in storm props
	  
	  if (sfile.ReadScan(entry.scan_num)) {
	    cerr << "ERROR - PrintTitanFiles::_printTrackFull" << endl;
	    cerr << sfile.getErrStr() << endl;
	    return -1;
	  }

	  const storm_file_scan_header_t &scan = sfile.scan();
	  
	  // print out sfile.scan info
	  
	  RfPrintStormScan(stdout, "    ", &sparams, &scan);

	  if (sfile.ReadProps(entry.storm_num)) {
	    cerr << "ERROR - PrintTitanFiles::_printTrackFull" << endl;
	    cerr << sfile.getErrStr() << endl;
	    return -1;
	  }

	  RfPrintStormProps(stdout, "      ", &sparams, &scan,
			    sfile.gprops() + entry.storm_num);
	  
	  RfPrintStormLayer(stdout, "      ", &sparams, &scan,
			    sfile.gprops() + entry.storm_num,
			    sfile.lprops());
	  
	  RfPrintStormHist(stdout, "      ", &sparams,
			   sfile.gprops() + entry.storm_num,
			   sfile.hist());
	  
	  
	  RfPrintStormRuns(stdout, "      ",
			   sfile.gprops() + entry.storm_num,
			   sfile.runs());
	  
	  
	} // if (_args.trackNum >= 0)
	
      } // ientry
      
    } // isimple
    
    printf("\n");
    
  } // icomplex

  return 0;

}

/////////////////////////////////////////////////////////////////////
// Print track in summary

int PrintTitanFiles::_printTrackSummary(TitanStormFile &sfile,
                                        TitanTrackFile &tfile)
  

{

  const track_file_verify_t &verify = tfile.header().verify;

  // complex tracks
  
  if (tfile.header().n_complex_tracks > 0) {
    fprintf(stdout, "COMPLEX TRACKS\n\n");
  }
  
  for (int icomplex = 0; icomplex < tfile.header().n_complex_tracks;
       icomplex++) {
    
    int complex_track_num = tfile.complex_track_nums()[icomplex];
    if (_args.trackNum >= 0 && _args.trackNum != complex_track_num) {
      continue;
    }

    if (tfile.ReadComplexParams(complex_track_num, true)) {
      cerr << "ERROR - PrintTitanFiles::_printTrackSummary" << endl;
      cerr << tfile.getErrStr() << endl;
      return -1;
    }
    
    const complex_track_params_t &ct_params = tfile.complex_params();

    // continue to next track if this one is too short

    if (ct_params.duration_in_secs < _args.minDuration) {
      continue;
    }
    
    RfPrintComplexTrackParams(stdout, "    ",
			      verify.verification_performed,
			      &tfile.header().params,
			      &tfile.complex_params(),
			      tfile.simples_per_complex()[complex_track_num]);


    // loop through simple tracks in this complex track
  
    for (int isimple = 0; isimple < ct_params.n_simple_tracks; isimple++) {
    
      int complex_track_num = ct_params.complex_track_num;
      
      int simple_track_num =
	tfile.simples_per_complex()[complex_track_num][isimple];

      // prepare to read in simple track

      if (tfile.RewindSimple(simple_track_num)) {
	cerr << "ERROR - PrintTitanFiles::_printTrackSummary" << endl;
	cerr << tfile.getErrStr() << endl;
	return -1;
      }
      
      const simple_track_params_t &st_params = tfile.simple_params();

      // loop through the track entries
      
      fprintf(stdout, "\nTRACK NUMBER %d/%d\n\n",
              complex_track_num, simple_track_num);
      
      fprintf(stdout, "%4s %10s %8s %7s %7s %7s %7s %7s %7s %7s %7s\n",
              "scan", "date", "time", "refl-x", "refl-y", "refl-z", "delta-z",
              "volume", "mass", "av area", "max dbz");
      
      fprintf(stdout, "%4s %10s %8s %7s %7s %7s %7s %7s %7s %7s %7s\n",
              " ", " ", " ", "(km)", "(km)", "(km)", "(km)",
              "(km3)", "(ktons)", "(km2)", "(dbz)");
      
      for (int ientry = 0; ientry < st_params.duration_in_scans; ientry++) {
      
	if (tfile.ReadEntry()) {
	  cerr << "ERROR - PrintTitanFiles::_printTrackSummary" << endl;
	  cerr << tfile.getErrStr() << endl;
	  return -1;
	}
      
	const track_file_entry_t &entry = tfile.entry();

        // read in scan info
        
        if (sfile.ReadScan(entry.scan_num)) {
          cerr << "ERROR - PrintTitanFiles::_printTrackSummary" << endl;
          cerr << sfile.getErrStr() << endl;
          return -1;
        }
        
	if (sfile.ReadProps(entry.scan_num)) {
	  cerr << "ERROR - PrintTitanFiles::_printTrackSummary" << endl;
	  cerr << sfile.getErrStr() << endl;
	  return -1;
	}

	int istorm = entry.storm_num;
	const storm_file_global_props_t *gprops = sfile.gprops() + istorm;
	
	// print out storm data
	
	fprintf(stdout, 
		"%4d %s "
		"%7.1f %7.1f %7.1f %7.1f %7.1f"
		"%7.1f %7.1f %7.1f\n", 
		sfile.scan().scan_num,
		utimstr(sfile.scan().time),
		gprops->refl_centroid_x,
		gprops->refl_centroid_y,
		gprops->refl_centroid_z,
		gprops->refl_centroid_z - gprops->vol_centroid_z,
		gprops->volume,
		gprops->mass,
		gprops->area_mean,
		gprops->dbz_max);
	
      } // ientry

    } // isimple
	
  } // icomplex
  
  fprintf(stdout, "\n");
  
  return 0;

}

/////////////////////////////////////////////////////////////////////
// Print CSV table type 1

int PrintTitanFiles::_printCsvTableType1(TitanStormFile &sfile,
                                         TitanTrackFile &tfile)
  

{

  const storm_file_params_t &sparams = sfile.header().params;

  // loop through scans

  for (int iscan = 0; iscan < tfile.header().n_scans; iscan++) {

    // read in scan info
    
    if (sfile.ReadScan(iscan)) {
      cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
      cerr << sfile.getErrStr() << endl;
      return -1;
    }
    
    const storm_file_scan_header_t &scan = sfile.scan();
    const titan_grid_t &grid = scan.grid;
          
    // loop through complex tracks
    
    for (int icomplex = 0;
         icomplex < tfile.header().n_complex_tracks; icomplex++) {
      
      int complex_track_num = tfile.complex_track_nums()[icomplex];
      
      if (tfile.ReadComplexParams(complex_track_num, true)) {
        cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
        cerr << tfile.getErrStr() << endl;
        return -1;
      }

      // check scan limits for this complex track

      const complex_track_params_t &complexParams = tfile.complex_params();
      if (complexParams.start_scan > iscan ||
          complexParams.end_scan < iscan) {
        continue;
      }
      
      // simple tracks in this complex track
      
      for (int isimple = 0;
           isimple < tfile.complex_params().n_simple_tracks; isimple++) {
        
        int simple_track_num =
          tfile.simples_per_complex()[complex_track_num][isimple];
        
        // prepare to read in simple track
        
        if (tfile.RewindSimple(simple_track_num)) {
          cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
          cerr << tfile.getErrStr() << endl;
          return -1;
        }
        
        // check scan limits for this simple track
        
        const simple_track_params_t &simpleParams = tfile.simple_params();
        if (simpleParams.start_scan > iscan ||
            simpleParams.end_scan < iscan) {
          continue;
        }
      
        // loop through the track entries
        
        for (int ientry = 0;
             ientry < tfile.simple_params().duration_in_scans; ientry++) {
          
          if (tfile.ReadEntry()) {
            cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
            cerr << tfile.getErrStr() << endl;
            return -1;
          }

          // check scan num for this entry

          const track_file_entry_t &entry = tfile.entry();
          if (entry.scan_num < iscan) {
            continue;
          }
          if (entry.scan_num > iscan) {
            break;
          }
          
          // check that simple and complex track numbers are correct
          
          if (entry.complex_track_num !=
              complexParams.complex_track_num) {
            fprintf(stderr, "\aERROR: complex track num "
                    "incorrect in entry\n");
            fprintf(stderr, "complex_params->complex_track_num : %d\n",
                    complexParams.complex_track_num);
            fprintf(stderr, "entry.complex_track_num : %d\n",
                    entry.complex_track_num);
          }
          
          if (entry.simple_track_num !=
              simpleParams.simple_track_num) {
            fprintf(stderr, "\aERROR: simple track num "
                    "incorrect in entry\n");
            fprintf(stderr, "simple_params->simple_track_num : %d\n",
                    simpleParams.simple_track_num);
            fprintf(stderr, "entry.simple_track_num : %d\n",
                    entry.simple_track_num);
          }

          // read in storm props
          
          if (sfile.ReadProps(entry.storm_num)) {
            cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
            cerr << sfile.getErrStr() << endl;
            return -1;
          }
          
          const storm_file_global_props_t &gprops = sfile.gprops()[entry.storm_num];
          
          // print out sfile.scan info
          
          int timeStep = iscan + 1;
          double centerX = gprops.proj_area_centroid_x;
          double centerY = gprops.proj_area_centroid_y;
          // int centerIx = (int) floor((centerX - grid.minx) / grid.dx + 0.5);
          // int centerIy = (int) floor((centerY - grid.miny) / grid.dy + 0.5);
          int nPoints = (int) (gprops.proj_area / (grid.dx * grid.dy) + 0.5);
          double boxXMin = 1.0e99;
          double boxXMax = -1.0e99;
          double boxYMin = 1.0e99;
          double boxYMax = -1.0e99;
          double lwpMean = gprops.dbz_mean;
          double lwpMin = sparams.low_dbz_threshold;
          double lwpMax = gprops.dbz_max;
          
          // compute box limits from polygon

          int n_sides = sparams.n_poly_sides;
          double poly_delta_az = sparams.poly_delta_az * DEG_TO_RAD;
          double theta = sparams.poly_start_az * DEG_TO_RAD;
          for (int iray = 0; iray < n_sides; iray++) {
            double raylen = gprops.proj_area_polygon[iray];
            double sinTheta, cosTheta;
            ta_sincos(theta, &sinTheta, &cosTheta);
            double xx = centerX + raylen * sinTheta * grid.dx;
            double yy = centerY + raylen * cosTheta * grid.dy;
            // int ixx = (int) floor((xx - grid.minx) / grid.dx + 0.5);
            // int iyy = (int) floor((yy - grid.miny) / grid.dy + 0.5);
            if (xx < boxXMin) {
              boxXMin = xx;
            }
            if (xx > boxXMax) {
              boxXMax = xx;
            }
            if (yy < boxYMin) {
              boxYMin = yy;
            }
            if (yy > boxYMax) {
              boxYMax = yy;
            }
            theta += poly_delta_az;
          } // iray
          
          // print out

          printf("%5d; %7d; %8.3f; %8.3f; %6d; %8.3f; %8.3f; "
                 "%8.3f; %8.3f; %7.3f; %7.3f; %7.3f\n",
                 timeStep,
                 simple_track_num,
                 centerX, centerY,
                 nPoints,
                 boxXMin, boxXMax,
                 boxYMin, boxYMax,
                 lwpMean, lwpMin, lwpMax);
                 
        } // ientry
      
      } // isimple
    
    } // icomplex

  } // iscan

  return 0;

}

/////////////////////////////////////////////////////////////////////
// Print CSV table type 2

int PrintTitanFiles::_printCsvTableType2(TitanStormFile &sfile,
                                         TitanTrackFile &tfile)
  
{
  
  // loop through scans

  for (int iscan = 0; iscan < tfile.header().n_scans - 1; iscan++) {

    int timeStep = iscan + 1;

    // read in entries for next scan, and save storm areas for each simple track num

    if (sfile.ReadScan(iscan + 1)) {
      cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
      cerr << sfile.getErrStr() << endl;
      return -1;
    }
    
    if (tfile.ReadScanEntries(iscan + 1)) {
      cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
      cerr << tfile.getErrStr() << endl;
      return -1;
    }
    
    map<int, double> areasNext;
    for (int ii = 0; ii < tfile.n_scan_entries(); ii++) {
      const track_file_entry_t &entry = tfile.scan_entries()[ii];
      if (sfile.ReadProps(entry.storm_num)) {
        cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
        cerr << sfile.getErrStr() << endl;
        return -1;
      }
      const storm_file_global_props_t &gprops = sfile.gprops()[entry.storm_num];
      areasNext[entry.simple_track_num] = gprops.proj_area;
    }
            
    // read in entries for current scan, and save storm areas for each simple track num

    if (sfile.ReadScan(iscan)) {
      cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
      cerr << sfile.getErrStr() << endl;
      return -1;
    }
    
    if (tfile.ReadScanEntries(iscan)) {
      cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
      cerr << tfile.getErrStr() << endl;
      return -1;
    }

    map<int, double> areasCurrent;
    for (int ii = 0; ii < tfile.n_scan_entries(); ii++) {
      const track_file_entry_t &entry = tfile.scan_entries()[ii];
      if (sfile.ReadProps(entry.storm_num)) {
        cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
        cerr << sfile.getErrStr() << endl;
        return -1;
      }
      const storm_file_global_props_t &gprops = sfile.gprops()[entry.storm_num];
      areasCurrent[entry.simple_track_num] = gprops.proj_area;
    }
            
    // loop through complex tracks
    
    for (int icomplex = 0;
         icomplex < tfile.header().n_complex_tracks; icomplex++) {
      
      int complex_track_num = tfile.complex_track_nums()[icomplex];
      
      if (tfile.ReadComplexParams(complex_track_num, true)) {
        cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
        cerr << tfile.getErrStr() << endl;
        return -1;
      }

      // check scan limits for this complex track
      
      const complex_track_params_t &complexParams = tfile.complex_params();
      if (complexParams.start_scan > iscan ||
          complexParams.end_scan < iscan) {
        continue;
      }
      
      // find all simple tracks in this complex track

      vector<simple_track_params_t> simpleParamsArray;
      
      for (int isimple = 0;
           isimple < tfile.complex_params().n_simple_tracks; isimple++) {
        
        int simple_track_num =
          tfile.simples_per_complex()[complex_track_num][isimple];
        
        // prepare to read in simple track
        
        if (tfile.RewindSimple(simple_track_num)) {
          cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
          cerr << tfile.getErrStr() << endl;
          return -1;
        }
        
        // check scan limits for this simple track
        
        simple_track_params_t simpleParams = tfile.simple_params();
        if (simpleParams.start_scan <= iscan &&
            simpleParams.end_scan >= iscan) {
          simpleParamsArray.push_back(simpleParams);
        }

      } // isimple

      // loop through all simple tracks
      
      for (size_t isimple = 0; isimple < simpleParamsArray.size(); isimple++) {
        
        // rewind simple track entries
        
        if (tfile.RewindSimple(simpleParamsArray[isimple].simple_track_num)) {
          cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
          cerr << tfile.getErrStr() << endl;
          return -1;
        }
        simple_track_params_t simpleParams = tfile.simple_params();
        
        // loop through the track entries
        
        for (int ientry = 0;
             ientry < tfile.simple_params().duration_in_scans; ientry++) {
          
          if (tfile.ReadEntry()) {
            cerr << "ERROR - PrintTitanFiles::_printCsvTableType2" << endl;
            cerr << tfile.getErrStr() << endl;
            return -1;
          }

          // check scan num for this entry
          
          track_file_entry_t entry = tfile.entry();
          if (entry.scan_num < iscan) {
            continue;
          }
          if (entry.scan_num > iscan) {
            break;
          }
          
          // check that simple and complex track numbers are correct
          
          if (entry.complex_track_num !=
              complexParams.complex_track_num) {
            fprintf(stderr, "\aERROR: complex track num "
                    "incorrect in entry\n");
            fprintf(stderr, "complex_params->complex_track_num : %d\n",
                    complexParams.complex_track_num);
            fprintf(stderr, "entry.complex_track_num : %d\n",
                    entry.complex_track_num);
          }
          
          if (entry.simple_track_num !=
              simpleParams.simple_track_num) {
            fprintf(stderr, "\aERROR: simple track num "
                    "incorrect in entry\n");
            fprintf(stderr, "simple_params->simple_track_num : %d\n",
                    simpleParams.simple_track_num);
            fprintf(stderr, "entry.simple_track_num : %d\n",
                    entry.simple_track_num);
          }

          if (iscan != simpleParams.end_scan) {

            // if not at end of simple track, track number does not change
            
            double weight = 1.0;
            printf("%10d; %7d; %7d; %7.3f\n",
                   timeStep,
                   simpleParams.simple_track_num,
                   simpleParams.simple_track_num,
                   weight);
            
          } else {
            
            // this is the last scan for this simple track
            
            if (simpleParams.nchildren == 0) {
              
              // no children, track ends

              int nextTrackNum = -1;
              double weight = 0.0;
              
              printf("%10d; %7d; %7d; %7.3f\n",
                     timeStep,
                     simpleParams.simple_track_num,
                     nextTrackNum,
                     weight);
              
            } else {
              
              // compute total area for all children
              
              double sumAreaChildren = 0.0;
              for (int ichild = 0; ichild < simpleParams.nchildren; ichild++) {
                int childTrackNum = simpleParams.child[ichild];
                sumAreaChildren += areasNext[childTrackNum];
              }
              
              // loop through children
              
              for (int ichild = 0; ichild < simpleParams.nchildren; ichild++) {
                
                // compute initial weight based on fraction of area relative
                // to other children
                
                int childTrackNum = simpleParams.child[ichild];
                double areaChild = areasNext[childTrackNum];
                double weight = areaChild / sumAreaChildren;
                
                // compute total area of parents merging to form this child
                
                double sumAreaParents = 0.0;
                for (size_t jj = 0; jj < simpleParamsArray.size(); jj++) {
                  simple_track_params_t parentParams = simpleParamsArray[jj];
                  for (int kk = 0; kk < parentParams.nchildren; kk++) {
                    int pcTrackNum = parentParams.child[ichild];
                    if (pcTrackNum == childTrackNum) {
                      sumAreaParents += areasCurrent[parentParams.simple_track_num];
                      break;
                    }
                  } // kk
                } // jj

                // adjust weight based on relative area of parents
                
                double areaParent = areasCurrent[simpleParams.simple_track_num];
                weight *= (areaParent / sumAreaParents);

                printf("%10d; %7d; %7d; %7.3f\n",
                       timeStep,
                       simpleParams.simple_track_num,
                       childTrackNum,
                       weight);
                
              } // ichild

            } // if (simpleParams.nchildren == 0)
            
          } // if (iscan == simpleParams.end_scan)
          
        } // ientry
      
      } // isimple
    
    } // icomplex

  } // iscan

  return 0;

}

/////////////////////////////////////////////////////////////////////
// Print CSV table type 3

int PrintTitanFiles::_printCsvTableType3(TitanStormFile &sfile,
                                         TitanTrackFile &tfile)
  

{

  // loop through scans
  
  for (int iscan = 0; iscan < tfile.header().n_scans; iscan++) {

    int timeStep = iscan + 1;

    // read in scan info
    
    if (sfile.ReadScan(iscan)) {
      cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
      cerr << sfile.getErrStr() << endl;
      return -1;
    }
    const storm_file_scan_header_t &scan = sfile.scan();
    
    // print out
    
    printf("%5d; %7d\n",
           timeStep,
           scan.nstorms);

  } // iscan    
    
  return 0;

}

/////////////////////////////////////////////////////////////////////
// Print CSV table type 4
// Duration for complex tracks

int PrintTitanFiles::_printCsvTableType4(TitanStormFile &sfile,
                                         TitanTrackFile &tfile)
  

{

  // loop through complex tracks
  
  for (int icomplex = 0;
       icomplex < tfile.header().n_complex_tracks; icomplex++) {
    
    int complex_track_num = tfile.complex_track_nums()[icomplex];
    
    if (tfile.ReadComplexParams(complex_track_num, true)) {
      cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
      cerr << tfile.getErrStr() << endl;
      return -1;
    }
    
    const complex_track_params_t &complexParams = tfile.complex_params();
    
    printf("%6d; %6d; %6d\n",
           complexParams.complex_track_num,
           complexParams.duration_in_scans,
           complexParams.duration_in_secs);
    
  } // icomplex
  
  return 0;

}

/////////////////////////////////////////////////////////////////////
// Print CSV table type 5
// Duration for simple tracks

int PrintTitanFiles::_printCsvTableType5(TitanStormFile &sfile,
                                         TitanTrackFile &tfile)
  

{

  // loop through complex tracks
  
  for (int icomplex = 0;
       icomplex < tfile.header().n_complex_tracks; icomplex++) {
    
    int complex_track_num = tfile.complex_track_nums()[icomplex];
    
    if (tfile.ReadComplexParams(complex_track_num, true)) {
      cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
      cerr << tfile.getErrStr() << endl;
      return -1;
    }
    
    // simple tracks in this complex track
    
    for (int isimple = 0;
         isimple < tfile.complex_params().n_simple_tracks; isimple++) {
      
      int simple_track_num =
        tfile.simples_per_complex()[complex_track_num][isimple];
      
      // prepare to read in simple track
      
      if (tfile.RewindSimple(simple_track_num)) {
        cerr << "ERROR - PrintTitanFiles::_printCsvTableType1" << endl;
        cerr << tfile.getErrStr() << endl;
        return -1;
      }

      const simple_track_params_t &simpleParams = tfile.simple_params();
    
      printf("%6d; %6d; %6d; %6d\n",
             complex_track_num,
             simple_track_num,
             simpleParams.duration_in_scans,
             simpleParams.duration_in_secs);

    } // isimple
    
  } // icomplex

  return 0;

}

//////////////////////////////////////////////////
// print storms as XML

int PrintTitanFiles::_printStormsXml()

{

  TitanStormFile sfile;
  
  // open storm properties files
  
  if (sfile.OpenFiles("r", _args.path.c_str())) {
    cerr << "ERROR - PrintTitanFiles::_printStormsXml" << endl;
    cerr << sfile.getErrStr() << endl;
    return -1;
  }

  //  read in storm properties file header

  if (sfile.ReadHeader()) {
    cerr << "ERROR - PrintTitanFiles::_printStormsXml" << endl;
    cerr << sfile.getErrStr() << endl;
    return -1;
  }

  int n_scans = sfile.header().n_scans;
  const storm_file_header_t &sHeader = sfile.header();
  const storm_file_params_t &sParams = sHeader.params;
  
  // header

  string xml;
  string mainTag = "titan_data";
  xml += TaXml::writeStartTag(mainTag, 0);
  xml += Titan2Xml::stormFileHeader("storm_file_header", 1, sHeader);

  /*
   * loop through scans
   */
  
  for (int iscan = 0; iscan < n_scans; iscan++) {

    string scanTag("scan");
    xml += TaXml::writeStartTag(scanTag, 1, "scan_num", iscan);
    
    /*
     * read in scan info
     */

    if (sfile.ReadScan(iscan)) {
      cerr << "ERROR - PrintTitanFiles::_printStormsXml" << endl;
      cerr << sfile.getErrStr() << endl;
      return -1;
    }

    const storm_file_scan_header_t &scan = sfile.scan();
    const titan_grid_t &grid = scan.grid;
    
    xml += Titan2Xml::stormScanHeader("scan_header", 2, scan);
    
    for (int istorm = 0; istorm < scan.nstorms; istorm++) {
      
      string stormTag("storm");
      xml += TaXml::writeStartTag(stormTag, 2, "storm_num", istorm);
      
      if (sfile.ReadProps(istorm)) {
        cerr << "ERROR - PrintTitanFiles::_printStormsXml" << endl;
        cerr << sfile.getErrStr() << endl;
        return -1;
      }
      
      const storm_file_global_props_t &gprops = sfile.gprops()[istorm];
      xml += Titan2Xml::stormGlobalProps("global_props", 3, sParams, gprops);

      for (int ilayer = 0; ilayer < gprops.n_layers; ilayer++) {
        const storm_file_layer_props_t &lprops = sfile.lprops()[ilayer];
        int layerNum = ilayer + gprops.base_layer;
        xml += Titan2Xml::stormLayerProps("layer_props", 3, layerNum, grid, lprops);
      }
      
      for (int ihist = 0; ihist < gprops.n_dbz_intervals; ihist++) {
        const storm_file_dbz_hist_t &entry = sfile.hist()[ihist];
        xml += Titan2Xml::stormDbzHistEntry("dbz_hist_bin", 3,
                                            ihist, sParams, entry);
      }

      xml += TaXml::writeEndTag(stormTag, 2);

    } // istorm
    
    xml += TaXml::writeEndTag(scanTag, 1);

  } // iscan
  
  // close files

  sfile.CloseFiles();

  xml += TaXml::writeEndTag(mainTag, 0);

  cout << xml << endl;

  return 0;

}

//////////////////////////////////////////////////
// print tracks as XML

int PrintTitanFiles::_printTracksXml()

{

  // open track properties files
  
  TitanTrackFile tfile;
  if (tfile.OpenFiles("r", _args.path.c_str())) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << tfile.getErrStr() << endl;
    return -1;
  }
  
  // read in track properties file header

  if (tfile.ReadHeader()) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << tfile.getErrStr() << endl;
    return -1;
  }

  if (tfile.ReadSimplesPerComplex()) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << tfile.getErrStr() << endl;
    return -1;
  }

  // print out header
  
  if (_args.printCsvTable) {
      
    if (_args.csvTableType == 1) {
      // table type 1
      printf("%%timestep; id;  centerx;  centery; volume;"
             "  boxxmin;  boxxmax;  boxymin;  boxymax;"
             " lwpmean;  lwpmin;  lwpmax\n");
    } else if (_args.csvTableType == 2) {
      // table type 2
      printf("%%timestep; idstep1; idstep2;  weight\n");
    } else if (_args.csvTableType == 3) {
      // table type 3
      printf("%%timestep; nstorms\n");
    } else if (_args.csvTableType == 4) {
      // table type 4
      printf("%%complex_track_num; duration_in_scans; duration_in_secs\n");
    } else if (_args.csvTableType == 5) {
      // table type 5
      printf("%%complex_track_num; simple_track_num; "
             "duration_in_scans; duration_in_secs\n");
    }

  } else {
    
    printf("TRACK FILE\n");
    printf("==========\n");
    printf("Header file label : %s\n", tfile.header_file_label().c_str());
    printf("Data   file label : %s\n", tfile.data_file_label().c_str());
    printf("\n");
  
    RfPrintTrackHeader(stdout, "  ", &tfile.header());

  }

  if (_args.printFull) {
    RfPrintTrackHeaderArrays(stdout, "  ",
			     &tfile.header(),
			     tfile.complex_track_nums(),
			     tfile.complex_track_offsets(),
			     tfile.simple_track_offsets(),
			     tfile.nsimples_per_complex(),
			     tfile.simples_per_complex_offsets(),
			     (const si32 **) tfile.simples_per_complex(),
			     tfile.scan_index());
  }

  // open storm file

  Path trackPath(_args.path);
  string stormFilePath = trackPath.getDirectory();
  stormFilePath += PATH_DELIM;
  stormFilePath += tfile.header().storm_header_file_name;

  TitanStormFile sfile;
  if (sfile.OpenFiles("r", stormFilePath.c_str())) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << sfile.getErrStr() << endl;
    return -1;
  }

  // read in storm properties file header
  
  if (sfile.ReadHeader()) {
    cerr << "ERROR - PrintTitanFiles::_printTrackFile" << endl;
    cerr << sfile.getErrStr() << endl;
    return -1;
  }

  // if full listing, print out track info
  
  if (_args.printFull) {
    if (_printTrackFull(sfile, tfile)) {
      return -1;
    }
  } else if (_args.printSummary) {
    if (_printTrackSummary(sfile, tfile)) {
      return -1;
    }
  } else if (_args.printCsvTable) {
    if (_args.csvTableType == 1) {
      if (_printCsvTableType1(sfile, tfile)) {
        return -1;
      }
    } else if (_args.csvTableType == 2) {
      if (_printCsvTableType2(sfile, tfile)) {
        return -1;
      }
    } else if (_args.csvTableType == 3) {
      if (_printCsvTableType3(sfile, tfile)) {
        return -1;
      }
    } else if (_args.csvTableType == 4) {
      if (_printCsvTableType4(sfile, tfile)) {
        return -1;
      }
    } else if (_args.csvTableType == 5) {
      if (_printCsvTableType5(sfile, tfile)) {
        return -1;
      }
    }
  }
    
  // close files

  sfile.CloseFiles();
  tfile.CloseFiles();

  return 0;

}

