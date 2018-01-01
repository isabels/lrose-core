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
// Code for program combine_ltg_radar
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

    // Parameter 'debug_level'
    // ctype is '_debug_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("debug_level");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed appropriately");
    tt->val_offset = (char *) &debug_level - &_start_;
    tt->enum_def.name = tdrpStrDup("debug_t");
    tt->enum_def.nfields = 4;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("DEBUG_OFF");
      tt->enum_def.fields[0].val = DEBUG_OFF;
      tt->enum_def.fields[1].name = tdrpStrDup("DEBUG_WARNINGS");
      tt->enum_def.fields[1].val = DEBUG_WARNINGS;
      tt->enum_def.fields[2].name = tdrpStrDup("DEBUG_NORM");
      tt->enum_def.fields[2].val = DEBUG_NORM;
      tt->enum_def.fields[3].name = tdrpStrDup("DEBUG_EXTRA");
      tt->enum_def.fields[3].val = DEBUG_EXTRA;
    tt->single_val.e = DEBUG_OFF;
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
    
    // Parameter 'mode'
    // ctype is '_mode_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("mode");
    tt->descr = tdrpStrDup("operation mode");
    tt->help = tdrpStrDup("In REALTIME_MODE, processing is triggered by a change in the _latest_data_info file associated with the triggering URL.  In ARCHIVE_MODE, processing is triggered by the file list specified with the -if command line argument.  In TIME_LIST_MODE, processing is triggered for each data time available for the triggering URL between the times specified by the -start and -end command line parameters.");
    tt->val_offset = (char *) &mode - &_start_;
    tt->enum_def.name = tdrpStrDup("mode_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("REALTIME_MODE");
      tt->enum_def.fields[0].val = REALTIME_MODE;
      tt->enum_def.fields[1].name = tdrpStrDup("ARCHIVE_MODE");
      tt->enum_def.fields[1].val = ARCHIVE_MODE;
      tt->enum_def.fields[2].name = tdrpStrDup("TIME_LIST_MODE");
      tt->enum_def.fields[2].val = TIME_LIST_MODE;
    tt->single_val.e = REALTIME_MODE;
    tt++;
    
    // Parameter 'trigger'
    // ctype is '_trigger_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("trigger");
    tt->descr = tdrpStrDup("file trigger");
    tt->help = tdrpStrDup("Used to specify the data set used to trigger combined file generation.");
    tt->val_offset = (char *) &trigger - &_start_;
    tt->enum_def.name = tdrpStrDup("trigger_t");
    tt->enum_def.nfields = 2;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("RADAR");
      tt->enum_def.fields[0].val = RADAR;
      tt->enum_def.fields[1].name = tdrpStrDup("LIGHTNING");
      tt->enum_def.fields[1].val = LIGHTNING;
    tt->single_val.e = RADAR;
    tt++;
    
    // Parameter 'input_wait_msecs'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("input_wait_msecs");
    tt->descr = tdrpStrDup("input wait msecs");
    tt->help = tdrpStrDup("Number of msecs to wait when checking for a new radar data file.");
    tt->val_offset = (char *) &input_wait_msecs - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 1;
    tt->single_val.i = 1000;
    tt++;
    
    // Parameter 'max_valid_file_age'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("max_valid_file_age");
    tt->descr = tdrpStrDup("maximum valid file age in seconds");
    tt->help = tdrpStrDup("If an input file is older than this, it will not be processed.");
    tt->val_offset = (char *) &max_valid_file_age - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 0;
    tt->single_val.i = 300;
    tt++;
    
    // Parameter 'radar_input_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("radar_input_url");
    tt->descr = tdrpStrDup("Radar data input URL");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &radar_input_url - &_start_;
    tt->single_val.s = tdrpStrDup("mdvp:://localhost::mdv/radar");
    tt++;
    
    // Parameter 'ltg_input_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("ltg_input_url");
    tt->descr = tdrpStrDup("Lightning data input URL");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &ltg_input_url - &_start_;
    tt->single_val.s = tdrpStrDup("mdvp:://localhost::mdv/ltg");
    tt++;
    
    // Parameter 'radar_field_name'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("radar_field_name");
    tt->descr = tdrpStrDup("Name of radar data field.");
    tt->help = tdrpStrDup("If empty, radar_field_pos will be used.");
    tt->val_offset = (char *) &radar_field_name - &_start_;
    tt->single_val.s = tdrpStrDup("");
    tt++;
    
    // Parameter 'radar_field_pos'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("radar_field_pos");
    tt->descr = tdrpStrDup("radar data field position");
    tt->help = tdrpStrDup("Position of the radar data field within the MDV data file.");
    tt->val_offset = (char *) &radar_field_pos - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 0;
    tt->single_val.i = 0;
    tt++;
    
    // Parameter 'ltg_field_name'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("ltg_field_name");
    tt->descr = tdrpStrDup("Name of ltg data field.");
    tt->help = tdrpStrDup("If empty, ltg_field_pos will be used.");
    tt->val_offset = (char *) &ltg_field_name - &_start_;
    tt->single_val.s = tdrpStrDup("");
    tt++;
    
    // Parameter 'ltg_field_pos'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("ltg_field_pos");
    tt->descr = tdrpStrDup("lightning data field position");
    tt->help = tdrpStrDup("Position of the lightning data field within the MDV data file.");
    tt->val_offset = (char *) &ltg_field_pos - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 0;
    tt->single_val.i = 0;
    tt++;
    
    // Parameter 'time_offset_max'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("time_offset_max");
    tt->descr = tdrpStrDup("max data offset time in seconds");
    tt->help = tdrpStrDup("In REALTIME mode, the maximum amount of time between the time the radar data was GENERATED and the valid time of the lightning grid.  In ARCHIVE mode, maximum amount of time allowed between the lightning data time and the radar data time for the files to be combined to form an output grid.");
    tt->val_offset = (char *) &time_offset_max - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 0;
    tt->single_val.i = 0;
    tt++;
    
    // Parameter 'request_composite_fields'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("request_composite_fields");
    tt->descr = tdrpStrDup("Option to request composite fields for radar and lightning data.");
    tt->help = tdrpStrDup("If true, both radar and lightning grids will be requested as a composite.");
    tt->val_offset = (char *) &request_composite_fields - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'process_if_no_lightning'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("process_if_no_lightning");
    tt->descr = tdrpStrDup("Option to produce output even if no lightning data is available.");
    tt->help = tdrpStrDup("If true, the program will generate an output field based only on the radar data if lightning data is not available.");
    tt->val_offset = (char *) &process_if_no_lightning - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'ltg_factors'
    // ctype is '_ltg_factor_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("ltg_factors");
    tt->descr = tdrpStrDup("lightning factor table");
    tt->help = tdrpStrDup("This table gives the step function used to assign data values to the lightning information.  When assigning a data value, the program will step through this table in order and assign the value for the first entry where the actual number of strikes is >= to num_strikes but < num_strikes for the next entry.");
    tt->array_offset = (char *) &_ltg_factors - &_start_;
    tt->array_n_offset = (char *) &ltg_factors_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(ltg_factor_t);
    tt->array_n = 4;
    tt->struct_def.name = tdrpStrDup("ltg_factor_t");
    tt->struct_def.nfields = 2;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("int");
      tt->struct_def.fields[0].fname = tdrpStrDup("num_strikes");
      tt->struct_def.fields[0].ptype = INT_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &_ltg_factors->num_strikes - (char *) _ltg_factors;
      tt->struct_def.fields[1].ftype = tdrpStrDup("double");
      tt->struct_def.fields[1].fname = tdrpStrDup("ltg_value");
      tt->struct_def.fields[1].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &_ltg_factors->ltg_value - (char *) _ltg_factors;
    tt->n_struct_vals = 8;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].i = 0;
      tt->struct_vals[1].d = 0;
      tt->struct_vals[2].i = 1;
      tt->struct_vals[3].d = 20;
      tt->struct_vals[4].i = 2;
      tt->struct_vals[5].d = 40;
      tt->struct_vals[6].i = 3;
      tt->struct_vals[7].d = 50;
    tt++;
    
    // Parameter 'data_time_stamp_flag'
    // ctype is '_data_time_stamp_flag_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("data_time_stamp_flag");
    tt->descr = tdrpStrDup("flag indicating which time stamp to use for the output data");
    tt->help = tdrpStrDup("Note that you cannot use USE_CURRENT_TIME when in ARCHIVE_MODE since this doesn't make sense.");
    tt->val_offset = (char *) &data_time_stamp_flag - &_start_;
    tt->enum_def.name = tdrpStrDup("data_time_stamp_flag_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("USE_RADAR_DATA_TIME");
      tt->enum_def.fields[0].val = USE_RADAR_DATA_TIME;
      tt->enum_def.fields[1].name = tdrpStrDup("USE_LTG_DATA_TIME");
      tt->enum_def.fields[1].val = USE_LTG_DATA_TIME;
      tt->enum_def.fields[2].name = tdrpStrDup("USE_CURRENT_TIME");
      tt->enum_def.fields[2].val = USE_CURRENT_TIME;
    tt->single_val.e = USE_RADAR_DATA_TIME;
    tt++;
    
    // Parameter 'data_start_time_offset'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("data_start_time_offset");
    tt->descr = tdrpStrDup("data start time offset");
    tt->help = tdrpStrDup("When data_time_stamp_flag is set to USE_CURRENT_TIME, this is the number of seconds to subtract from the current time to get the data begin time.  This value is ignored for any other setting of data_time_stamp_flag.");
    tt->val_offset = (char *) &data_start_time_offset - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 0;
    tt->single_val.i = 150;
    tt++;
    
    // Parameter 'data_end_time_offset'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("data_end_time_offset");
    tt->descr = tdrpStrDup("data end time offset");
    tt->help = tdrpStrDup("When data_time_stamp_flag is set to USE_CURRENT_TIME, this is the number of seconds to add to the current time to get the data end time.  This value is ignored for any other setting of data_time_stamp_flag.");
    tt->val_offset = (char *) &data_end_time_offset - &_start_;
    tt->has_min = TRUE;
    tt->min_val.i = 0;
    tt->single_val.i = 150;
    tt++;
    
    // Parameter 'output_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("output_url");
    tt->descr = tdrpStrDup("Output directory");
    tt->help = tdrpStrDup("Path of output directory");
    tt->val_offset = (char *) &output_url - &_start_;
    tt->single_val.s = tdrpStrDup("mdvp:://localhost::mdv/output");
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }
