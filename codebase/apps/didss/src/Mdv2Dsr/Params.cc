// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c)
// ** University Corporation for Atmospheric Research(UCAR)
// ** National Center for Atmospheric Research(NCAR)
// ** Boulder, Colorado, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
////////////////////////////////////////////
// Params.cc
//
// TDRP C++ code file for class 'Params'.
//
// Code for program Mdv2Dsr
//
// This file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.cc
 *
 * @class Params
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @note Source is automatically generated from
 *       paramdef file at compile time, do not modify
 *       since modifications will be overwritten.
 *
 *
 * @author Automatically generated
 *
 */
using namespace std;

#include "Params.hh"
#include <cstring>

  ////////////////////////////////////////////
  // Default constructor
  //

  Params::Params()

  {

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // initialize table

    _init();

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params::Params(const Params& source)

  {

    // sync the source object

    source.sync();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // copy table

    tdrpCopyTable((TDRPtable *) source._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Destructor
  //

  Params::~Params()

  {

    // free up

    freeAll();

  }

  ////////////////////////////////////////////
  // Assignment
  //

  void Params::operator=(const Params& other)

  {

    // sync the other object

    other.sync();

    // free up any existing memory

    freeAll();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // copy table

    tdrpCopyTable((TDRPtable *) other._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = other._exitDeferred;

  }

  ////////////////////////////////////////////
  // loadFromArgs()
  //
  // Loads up TDRP using the command line args.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   char **params_path_p:
  //     If this is non-NULL, it is set to point to the path
  //     of the params file used.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromArgs(int argc, char **argv,
                           char **override_list,
                           char **params_path_p,
                           bool defer_exit)
  {
    int exit_deferred;
    if (_tdrpLoadFromArgs(argc, argv,
                          _table, &_start_,
                          override_list, params_path_p,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadApplyArgs()
  //
  // Loads up TDRP using the params path passed in, and applies
  // the command line args for printing and checking.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   const char *param_file_path: the parameter file to be read in
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadApplyArgs(const char *params_path,
                            int argc, char **argv,
                            char **override_list,
                            bool defer_exit)
  {
    int exit_deferred;
    if (tdrpLoadApplyArgs(params_path, argc, argv,
                          _table, &_start_,
                          override_list,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  bool Params::isArgValid(const char *arg)
  {
    return (tdrpIsArgValid(arg));
  }

  ////////////////////////////////////////////
  // load()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to load
  // up more than one class for a single application. It is a
  // lower-level routine than loadFromArgs, and hence more
  // flexible, but the programmer must do more work.
  //
  //   const char *param_file_path: the parameter file to be read in.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::load(const char *param_file_path,
                   char **override_list,
                   int expand_env, int debug)
  {
    if (tdrpLoad(param_file_path,
                 _table, &_start_,
                 override_list,
                 expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadFromBuf()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to
  // load up more than one module for a single application,
  // using buffers which have been read from a specified source.
  //
  //   const char *param_source_str: a string which describes the
  //     source of the parameter information. It is used for
  //     error reporting only.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   const char *inbuf: the input buffer
  //
  //   int inlen: length of the input buffer
  //
  //   int start_line_num: the line number in the source which
  //     corresponds to the start of the buffer.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromBuf(const char *param_source_str,
                          char **override_list,
                          const char *inbuf, int inlen,
                          int start_line_num,
                          int expand_env, int debug)
  {
    if (tdrpLoadFromBuf(param_source_str,
                        _table, &_start_,
                        override_list,
                        inbuf, inlen, start_line_num,
                        expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadDefaults(int expand_env)
  {
    if (tdrpLoad(NULL,
                 _table, &_start_,
                 NULL, expand_env, FALSE)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void Params::sync(void) const
  {
    tdrpUser2Table(_table, (char *) &_start_);
  }

  ////////////////////////////////////////////
  // print()
  // 
  // Print params file
  //
  // The modes supported are:
  //
  //   PRINT_SHORT:   main comments only, no help or descriptions
  //                  structs and arrays on a single line
  //   PRINT_NORM:    short + descriptions and help
  //   PRINT_LONG:    norm  + arrays and structs expanded
  //   PRINT_VERBOSE: long  + private params included
  //

  void Params::print(FILE *out, tdrp_print_mode_t mode)
  {
    tdrpPrint(out, _table, _className, mode);
  }

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int Params::checkAllSet(FILE *out)
  {
    return (tdrpCheckAllSet(out, _table, &_start_));
  }

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int Params::checkIsSet(const char *paramName)
  {
    return (tdrpCheckIsSet(paramName, _table, &_start_));
  }

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void Params::freeAll(void)
  {
    tdrpFreeAll(_table, &_start_);
  }

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  void Params::usage(ostream &out)
  {
    out << "TDRP args: [options as below]\n"
        << "   [ -params/--params path ] specify params file path\n"
        << "   [ -check_params/--check_params] check which params are not set\n"
        << "   [ -print_params/--print_params [mode]] print parameters\n"
        << "     using following modes, default mode is 'norm'\n"
        << "       short:   main comments only, no help or descr\n"
        << "                structs and arrays on a single line\n"
        << "       norm:    short + descriptions and help\n"
        << "       long:    norm  + arrays and structs expanded\n"
        << "       verbose: long  + private params included\n"
        << "       short_expand:   short with env vars expanded\n"
        << "       norm_expand:    norm with env vars expanded\n"
        << "       long_expand:    long with env vars expanded\n"
        << "       verbose_expand: verbose with env vars expanded\n"
        << "   [ -tdrp_debug] debugging prints for tdrp\n"
        << "   [ -tdrp_usage] print this usage\n";
  }

  ////////////////////////////////////////////
  // arrayRealloc()
  //
  // Realloc 1D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::arrayRealloc(const char *param_name, int new_array_n)
  {
    if (tdrpArrayRealloc(_table, &_start_,
                         param_name, new_array_n)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // array2DRealloc()
  //
  // Realloc 2D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::array2DRealloc(const char *param_name,
                             int new_array_n1,
                             int new_array_n2)
  {
    if (tdrpArray2DRealloc(_table, &_start_, param_name,
                           new_array_n1, new_array_n2)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // _init()
  //
  // Class table initialization function.
  //
  //

  void Params::_init()

  {

    TDRPtable *tt = _table;

    // Parameter 'Comment 0'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 0");
    tt->comment_hdr = tdrpStrDup("Mdv2Dsr PARAMETER FILE");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup("PROGRAM MODES OF OPERATION");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'debug'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("debug");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed");
    tt->val_offset = (char *) &debug - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'info'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("info");
    tt->descr = tdrpStrDup("Info option");
    tt->help = tdrpStrDup("Print info messages");
    tt->val_offset = (char *) &info - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'instance'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("instance");
    tt->descr = tdrpStrDup("Process instance");
    tt->help = tdrpStrDup("Used for registration with procmap.");
    tt->val_offset = (char *) &instance - &_start_;
    tt->single_val.s = tdrpStrDup("Test");
    tt++;
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("LOGGING");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'log_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("log_dir");
    tt->descr = tdrpStrDup("Directory for log file output");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &log_dir - &_start_;
    tt->single_val.s = tdrpStrDup("");
    tt++;
    
    // Parameter 'Comment 3'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 3");
    tt->comment_hdr = tdrpStrDup("INPUT");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'input_files'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("input_files");
    tt->descr = tdrpStrDup("Input files");
    tt->help = tdrpStrDup("If no input files are specified, the input directory will be used");
    tt->array_offset = (char *) &_input_files - &_start_;
    tt->array_n_offset = (char *) &input_files_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(char*);
    tt->array_n = 0;
    tt->array_vals = (tdrpVal_t *)
        tdrpMalloc(tt->array_n * sizeof(tdrpVal_t));
    tt++;
    
    // Parameter 'input_dir'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("input_dir");
    tt->descr = tdrpStrDup("Input directory path");
    tt->help = tdrpStrDup("The start and end times specified below will be used to select files from this directory");
    tt->val_offset = (char *) &input_dir - &_start_;
    tt->single_val.s = tdrpStrDup("");
    tt++;
    
    // Parameter 'start_time'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("start_time");
    tt->descr = tdrpStrDup("Start time for files to be processed");
    tt->help = tdrpStrDup("Files from this time through the end time will be processed.\n\nSupported time formats are:\n  yyyy mm dd hh mm ss (preferred)\n  hh:mm:ss mm/dd/yyyy\n\n");
    tt->val_offset = (char *) &start_time - &_start_;
    tt->single_val.s = tdrpStrDup("00:00:00 12/31/1998");
    tt++;
    
    // Parameter 'end_time'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("end_time");
    tt->descr = tdrpStrDup("End time for files to be processed");
    tt->help = tdrpStrDup("Files from the start time through this time will be processed.\n\nSupported time formats are:\n  yyyy mm dd hh mm ss (preferred)\n  hh:mm:ss mm/dd/yyyy\n\n");
    tt->val_offset = (char *) &end_time - &_start_;
    tt->single_val.s = tdrpStrDup("00:00:00 12/31/1998");
    tt++;
    
    // Parameter 'Comment 4'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 4");
    tt->comment_hdr = tdrpStrDup("PROCESSING PARAMS");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'use_field_headers'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("use_field_headers");
    tt->descr = tdrpStrDup("Option to take nz and the array of elevation from the first field header. By default, the radarParams stuct is used if it is available, but this may not be correct if the MDV data have been remapped so that the radar params are not current. Setting this flag forces the use of field headers.");
    tt->help = tdrpStrDup("Default is to go for the brass ring and attempt to use the radar parameters if they are there. This is almost always correct.");
    tt->val_offset = (char *) &use_field_headers - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'use_current_time'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("use_current_time");
    tt->descr = tdrpStrDup("Use current time for beam times");
    tt->help = tdrpStrDup("The current time will be used for the beams as they are written to the fmq");
    tt->val_offset = (char *) &use_current_time - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'simulate_time'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("simulate_time");
    tt->descr = tdrpStrDup("Use a simulated time for beam times");
    tt->help = tdrpStrDup("Use the times listed below to construct the data time for the beams.  Note that this mode can only be used if files are listed above, instead of specifying an input directory");
    tt->val_offset = (char *) &simulate_time - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'start_end_times'
    // ctype is '_simulate_times_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("start_end_times");
    tt->descr = tdrpStrDup("Simulated start and end times for each file listed above");
    tt->help = tdrpStrDup("There must be one set of start and end times for each file listed in input_files above.\n\nSupported time formats are:\n  yyyy mm dd hh mm ss (preferred)\n  hh:mm:ss mm/dd/yyyy\n\n");
    tt->array_offset = (char *) &_start_end_times - &_start_;
    tt->array_n_offset = (char *) &start_end_times_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(simulate_times_t);
    tt->array_n = 1;
    tt->struct_def.name = tdrpStrDup("simulate_times_t");
    tt->struct_def.nfields = 2;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("string");
      tt->struct_def.fields[0].fname = tdrpStrDup("simulate_start_time");
      tt->struct_def.fields[0].ptype = STRING_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &_start_end_times->simulate_start_time - (char *) _start_end_times;
      tt->struct_def.fields[1].ftype = tdrpStrDup("string");
      tt->struct_def.fields[1].fname = tdrpStrDup("simulate_end_time");
      tt->struct_def.fields[1].ptype = STRING_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &_start_end_times->simulate_end_time - (char *) _start_end_times;
    tt->n_struct_vals = 2;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].s = tdrpStrDup("00:00:00 12/31/1998");
      tt->struct_vals[1].s = tdrpStrDup("00:06:00 12/31/1998");
    tt++;
    
    // Parameter 'beam_wait_msecs'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("beam_wait_msecs");
    tt->descr = tdrpStrDup("Wait per beam (milli-secs)");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &beam_wait_msecs - &_start_;
    tt->single_val.i = 10;
    tt++;
    
    // Parameter 'vol_wait_secs'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("vol_wait_secs");
    tt->descr = tdrpStrDup("Wait per vol (secs)");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &vol_wait_secs - &_start_;
    tt->single_val.i = 1;
    tt++;
    
    // Parameter 'simulate_repeat_forever'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("simulate_repeat_forever");
    tt->descr = tdrpStrDup("Loop through the data repeatedly, for simulate mode.");
    tt->help = tdrpStrDup("Should be used with 'use_current_time'.");
    tt->val_offset = (char *) &simulate_repeat_forever - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'Comment 5'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 5");
    tt->comment_hdr = tdrpStrDup("OPTION to override radar params");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'override_radar_params'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("override_radar_params");
    tt->descr = tdrpStrDup("Override radar params in MDV file");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &override_radar_params - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'radar_params'
    // ctype is '_radar_params_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("radar_params");
    tt->descr = tdrpStrDup("Overrride radar params in file with these params.");
    tt->help = tdrpStrDup("========== Radar params ==========\n\t\n\tradarId:            unique number\n\tradarType:          use radar type defs in ds_radar.h\n\tsamplesPerBeam:     number of pulses per data beam\n\tscanType:           the current scan strategy\n\tpolarization:       see ds_radar.h\n\tradarConstant:      radar constant\n\taltitude:           km\n\tlatitude:           degrees\n\tlongitude:          degrees\n\tgateSpacing:        km\n\tstartRange:         km\n\thorizBeamWidth:     degrees\n\tvertBeamWidth:      degrees\n\tpulseWidth:         micro-seconds\n\tpulseRepFreq:       pulse repitition freq (/s)\n\twavelength:         cm\n\txmitPeakPower:      watts\n\treceiverMds:        dBm\n\treceiverGain:       dB\n\tantennaGain:        dB\n\tsystemGain:         dB\n\tunambigVelocity:    m/s\n\tunambigRange:       km\n\tradarName:          name of radar site\n\tscanTypeName:       name of scanType\n\t\n");
    tt->val_offset = (char *) &radar_params - &_start_;
    tt->struct_def.name = tdrpStrDup("radar_params_t");
    tt->struct_def.nfields = 25;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("int");
      tt->struct_def.fields[0].fname = tdrpStrDup("radarId");
      tt->struct_def.fields[0].ptype = INT_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &radar_params.radarId - (char *) &radar_params;
      tt->struct_def.fields[1].ftype = tdrpStrDup("int");
      tt->struct_def.fields[1].fname = tdrpStrDup("radarType");
      tt->struct_def.fields[1].ptype = INT_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &radar_params.radarType - (char *) &radar_params;
      tt->struct_def.fields[2].ftype = tdrpStrDup("int");
      tt->struct_def.fields[2].fname = tdrpStrDup("samplesPerBeam");
      tt->struct_def.fields[2].ptype = INT_TYPE;
      tt->struct_def.fields[2].rel_offset = 
        (char *) &radar_params.samplesPerBeam - (char *) &radar_params;
      tt->struct_def.fields[3].ftype = tdrpStrDup("int");
      tt->struct_def.fields[3].fname = tdrpStrDup("scanType");
      tt->struct_def.fields[3].ptype = INT_TYPE;
      tt->struct_def.fields[3].rel_offset = 
        (char *) &radar_params.scanType - (char *) &radar_params;
      tt->struct_def.fields[4].ftype = tdrpStrDup("int");
      tt->struct_def.fields[4].fname = tdrpStrDup("polarization");
      tt->struct_def.fields[4].ptype = INT_TYPE;
      tt->struct_def.fields[4].rel_offset = 
        (char *) &radar_params.polarization - (char *) &radar_params;
      tt->struct_def.fields[5].ftype = tdrpStrDup("double");
      tt->struct_def.fields[5].fname = tdrpStrDup("radarConstant");
      tt->struct_def.fields[5].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[5].rel_offset = 
        (char *) &radar_params.radarConstant - (char *) &radar_params;
      tt->struct_def.fields[6].ftype = tdrpStrDup("double");
      tt->struct_def.fields[6].fname = tdrpStrDup("altitude");
      tt->struct_def.fields[6].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[6].rel_offset = 
        (char *) &radar_params.altitude - (char *) &radar_params;
      tt->struct_def.fields[7].ftype = tdrpStrDup("double");
      tt->struct_def.fields[7].fname = tdrpStrDup("latitude");
      tt->struct_def.fields[7].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[7].rel_offset = 
        (char *) &radar_params.latitude - (char *) &radar_params;
      tt->struct_def.fields[8].ftype = tdrpStrDup("double");
      tt->struct_def.fields[8].fname = tdrpStrDup("longitude");
      tt->struct_def.fields[8].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[8].rel_offset = 
        (char *) &radar_params.longitude - (char *) &radar_params;
      tt->struct_def.fields[9].ftype = tdrpStrDup("double");
      tt->struct_def.fields[9].fname = tdrpStrDup("gateSpacing");
      tt->struct_def.fields[9].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[9].rel_offset = 
        (char *) &radar_params.gateSpacing - (char *) &radar_params;
      tt->struct_def.fields[10].ftype = tdrpStrDup("double");
      tt->struct_def.fields[10].fname = tdrpStrDup("startRange");
      tt->struct_def.fields[10].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[10].rel_offset = 
        (char *) &radar_params.startRange - (char *) &radar_params;
      tt->struct_def.fields[11].ftype = tdrpStrDup("double");
      tt->struct_def.fields[11].fname = tdrpStrDup("horizBeamWidth");
      tt->struct_def.fields[11].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[11].rel_offset = 
        (char *) &radar_params.horizBeamWidth - (char *) &radar_params;
      tt->struct_def.fields[12].ftype = tdrpStrDup("double");
      tt->struct_def.fields[12].fname = tdrpStrDup("vertBeamWidth");
      tt->struct_def.fields[12].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[12].rel_offset = 
        (char *) &radar_params.vertBeamWidth - (char *) &radar_params;
      tt->struct_def.fields[13].ftype = tdrpStrDup("double");
      tt->struct_def.fields[13].fname = tdrpStrDup("pulseWidth");
      tt->struct_def.fields[13].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[13].rel_offset = 
        (char *) &radar_params.pulseWidth - (char *) &radar_params;
      tt->struct_def.fields[14].ftype = tdrpStrDup("double");
      tt->struct_def.fields[14].fname = tdrpStrDup("pulseRepFreq");
      tt->struct_def.fields[14].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[14].rel_offset = 
        (char *) &radar_params.pulseRepFreq - (char *) &radar_params;
      tt->struct_def.fields[15].ftype = tdrpStrDup("double");
      tt->struct_def.fields[15].fname = tdrpStrDup("wavelength");
      tt->struct_def.fields[15].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[15].rel_offset = 
        (char *) &radar_params.wavelength - (char *) &radar_params;
      tt->struct_def.fields[16].ftype = tdrpStrDup("double");
      tt->struct_def.fields[16].fname = tdrpStrDup("xmitPeakPower");
      tt->struct_def.fields[16].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[16].rel_offset = 
        (char *) &radar_params.xmitPeakPower - (char *) &radar_params;
      tt->struct_def.fields[17].ftype = tdrpStrDup("double");
      tt->struct_def.fields[17].fname = tdrpStrDup("receiverMds");
      tt->struct_def.fields[17].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[17].rel_offset = 
        (char *) &radar_params.receiverMds - (char *) &radar_params;
      tt->struct_def.fields[18].ftype = tdrpStrDup("double");
      tt->struct_def.fields[18].fname = tdrpStrDup("receiverGain");
      tt->struct_def.fields[18].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[18].rel_offset = 
        (char *) &radar_params.receiverGain - (char *) &radar_params;
      tt->struct_def.fields[19].ftype = tdrpStrDup("double");
      tt->struct_def.fields[19].fname = tdrpStrDup("antennaGain");
      tt->struct_def.fields[19].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[19].rel_offset = 
        (char *) &radar_params.antennaGain - (char *) &radar_params;
      tt->struct_def.fields[20].ftype = tdrpStrDup("double");
      tt->struct_def.fields[20].fname = tdrpStrDup("systemGain");
      tt->struct_def.fields[20].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[20].rel_offset = 
        (char *) &radar_params.systemGain - (char *) &radar_params;
      tt->struct_def.fields[21].ftype = tdrpStrDup("double");
      tt->struct_def.fields[21].fname = tdrpStrDup("unambigVelocity");
      tt->struct_def.fields[21].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[21].rel_offset = 
        (char *) &radar_params.unambigVelocity - (char *) &radar_params;
      tt->struct_def.fields[22].ftype = tdrpStrDup("double");
      tt->struct_def.fields[22].fname = tdrpStrDup("unambigRange");
      tt->struct_def.fields[22].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[22].rel_offset = 
        (char *) &radar_params.unambigRange - (char *) &radar_params;
      tt->struct_def.fields[23].ftype = tdrpStrDup("string");
      tt->struct_def.fields[23].fname = tdrpStrDup("radarName");
      tt->struct_def.fields[23].ptype = STRING_TYPE;
      tt->struct_def.fields[23].rel_offset = 
        (char *) &radar_params.radarName - (char *) &radar_params;
      tt->struct_def.fields[24].ftype = tdrpStrDup("string");
      tt->struct_def.fields[24].fname = tdrpStrDup("scanTypeName");
      tt->struct_def.fields[24].ptype = STRING_TYPE;
      tt->struct_def.fields[24].rel_offset = 
        (char *) &radar_params.scanTypeName - (char *) &radar_params;
    tt->n_struct_vals = 25;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].i = 0;
      tt->struct_vals[1].i = 0;
      tt->struct_vals[2].i = 192;
      tt->struct_vals[3].i = 0;
      tt->struct_vals[4].i = 5;
      tt->struct_vals[5].d = -73.1;
      tt->struct_vals[6].d = 0.168;
      tt->struct_vals[7].d = -27.6692;
      tt->struct_vals[8].d = 152.862;
      tt->struct_vals[9].d = 0.15;
      tt->struct_vals[10].d = 0;
      tt->struct_vals[11].d = 0.93;
      tt->struct_vals[12].d = 0.93;
      tt->struct_vals[13].d = 1;
      tt->struct_vals[14].d = 1000;
      tt->struct_vals[15].d = 10.9;
      tt->struct_vals[16].d = 4.9545e+08;
      tt->struct_vals[17].d = -112.63;
      tt->struct_vals[18].d = 44.83;
      tt->struct_vals[19].d = 45.3;
      tt->struct_vals[20].d = 90.13;
      tt->struct_vals[21].d = 27.25;
      tt->struct_vals[22].d = 150;
      tt->struct_vals[23].s = tdrpStrDup("CP2_S");
      tt->struct_vals[24].s = tdrpStrDup("Default_s");
    tt++;
    
    // Parameter 'Comment 6'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 6");
    tt->comment_hdr = tdrpStrDup("DIAGNOSTICS");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'print_summary'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("print_summary");
    tt->descr = tdrpStrDup("Print summary");
    tt->help = tdrpStrDup("If set to true, summaries are printed at given interval");
    tt->val_offset = (char *) &print_summary - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'summary_interval'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("summary_interval");
    tt->descr = tdrpStrDup("Summary interval");
    tt->help = tdrpStrDup("See print_summary");
    tt->val_offset = (char *) &summary_interval - &_start_;
    tt->single_val.i = 90;
    tt++;
    
    // Parameter 'Comment 7'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 7");
    tt->comment_hdr = tdrpStrDup("OUTPUT");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'output_fmq_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("output_fmq_url");
    tt->descr = tdrpStrDup("output fmq url");
    tt->help = tdrpStrDup("Path for FMQ output data.");
    tt->val_offset = (char *) &output_fmq_url - &_start_;
    tt->single_val.s = tdrpStrDup("fmqp:://localhost::./fmq.dsRadar");
    tt++;
    
    // Parameter 'output_fmq_size'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("output_fmq_size");
    tt->descr = tdrpStrDup("Size of output FMQ, in bytes.");
    tt->help = tdrpStrDup("This is the total size of the output FMQ buffer. Some of this buffer will be used for control bytes (12 bytes per message.");
    tt->val_offset = (char *) &output_fmq_size - &_start_;
    tt->single_val.i = 2000000;
    tt++;
    
    // Parameter 'output_fmq_nslots'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("output_fmq_nslots");
    tt->descr = tdrpStrDup("Number of slots in output FMQ.");
    tt->help = tdrpStrDup("The number of slots corresponds to the maximum number of messages which may be written to the buffer before overwrites occur. However, overwrites may occur sooner if the size is not set large enough.");
    tt->val_offset = (char *) &output_fmq_nslots - &_start_;
    tt->single_val.i = 3600;
    tt++;
    
    // Parameter 'output_fmq_compress'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("output_fmq_compress");
    tt->descr = tdrpStrDup("FMQ compression option.");
    tt->help = tdrpStrDup("If TRUE FMQ messages are compressed.");
    tt->val_offset = (char *) &output_fmq_compress - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'output_encoding'
    // ctype is '_encoding_type_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("output_encoding");
    tt->descr = tdrpStrDup("Set encoding type for output data.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &output_encoding - &_start_;
    tt->enum_def.name = tdrpStrDup("encoding_type_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("ENCODING_INT8");
      tt->enum_def.fields[0].val = ENCODING_INT8;
      tt->enum_def.fields[1].name = tdrpStrDup("ENCODING_INT16");
      tt->enum_def.fields[1].val = ENCODING_INT16;
      tt->enum_def.fields[2].name = tdrpStrDup("ENCODING_FLOAT32");
      tt->enum_def.fields[2].val = ENCODING_FLOAT32;
    tt->single_val.e = ENCODING_INT16;
    tt++;
    
    // Parameter 'write_blocking'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("write_blocking");
    tt->descr = tdrpStrDup("Blocking FMQ output");
    tt->help = tdrpStrDup("If TRUE, this application will wait for a reader to catch up. Can only be used with a single reader.");
    tt->val_offset = (char *) &write_blocking - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // Parameter 'az_offset'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("az_offset");
    tt->descr = tdrpStrDup("Offset to add to azimuth angles.");
    tt->help = tdrpStrDup("Will rotate data on output.");
    tt->val_offset = (char *) &az_offset - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }
