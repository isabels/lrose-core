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
// Code for program MdvCircularFilt
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
    tt->comment_hdr = tdrpStrDup("MdvCircularFilt allows user to apply circular filter of user statistic and user specified radius around each point of an Mdv field");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup("DEBUGGING AND PROCESS CONTROL");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'debug'
    // ctype is '_debug_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("debug");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed with the appropriate level of detail.");
    tt->val_offset = (char *) &debug - &_start_;
    tt->enum_def.name = tdrpStrDup("debug_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("DEBUG_OFF");
      tt->enum_def.fields[0].val = DEBUG_OFF;
      tt->enum_def.fields[1].name = tdrpStrDup("DEBUG_NORM");
      tt->enum_def.fields[1].val = DEBUG_NORM;
      tt->enum_def.fields[2].name = tdrpStrDup("DEBUG_VERBOSE");
      tt->enum_def.fields[2].val = DEBUG_VERBOSE;
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
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("PROGRAM MODES OF OPERATION.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'mode'
    // ctype is '_mode_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("mode");
    tt->descr = tdrpStrDup("Operating mode");
    tt->help = tdrpStrDup("In REALTIME mode, the program triggers off of a latest data info file. REALTIME_FCST_DATA triggers off RAL forecast directory structure data. In FILELIST mode the program processed data between start and end times entered on the command line.In FILELIST mode the file processes files entered on the command line");
    tt->val_offset = (char *) &mode - &_start_;
    tt->enum_def.name = tdrpStrDup("mode_t");
    tt->enum_def.nfields = 4;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("TIME_INTERVAL");
      tt->enum_def.fields[0].val = TIME_INTERVAL;
      tt->enum_def.fields[1].name = tdrpStrDup("FILELIST");
      tt->enum_def.fields[1].val = FILELIST;
      tt->enum_def.fields[2].name = tdrpStrDup("REALTIME");
      tt->enum_def.fields[2].val = REALTIME;
      tt->enum_def.fields[3].name = tdrpStrDup("REALTIME_FCST_DATA");
      tt->enum_def.fields[3].val = REALTIME_FCST_DATA;
    tt->single_val.e = FILELIST;
    tt++;
    
    // Parameter 'Comment 3'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 3");
    tt->comment_hdr = tdrpStrDup("DATA INPUT.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'data_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("data_url");
    tt->descr = tdrpStrDup("");
    tt->help = tdrpStrDup("Data input");
    tt->val_offset = (char *) &data_url - &_start_;
    tt->single_val.s = tdrpStrDup("mdvp:://localhost::mdv/");
    tt++;
    
    // Parameter 'field_name'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("field_name");
    tt->descr = tdrpStrDup("Field name string of data in input file on which to perform filtering");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &field_name - &_start_;
    tt->single_val.s = tdrpStrDup("dataField");
    tt++;
    
    // Parameter 'field_number'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("field_number");
    tt->descr = tdrpStrDup("Number of field in data input file on which to perform filtering");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &field_number - &_start_;
    tt->single_val.i = 0;
    tt++;
    
    // Parameter 'use_field_name'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("use_field_name");
    tt->descr = tdrpStrDup("Option to use field name instead of number. If false, field_number_will be used.\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &use_field_name - &_start_;
    tt->single_val.b = pTRUE;
    tt++;
    
    // Parameter 'max_valid_realtime_age'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("max_valid_realtime_age");
    tt->descr = tdrpStrDup("Max valid realtime age of input data\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &max_valid_realtime_age - &_start_;
    tt->single_val.i = 300;
    tt++;
    
    // Parameter 'vert_action'
    // ctype is '_vert_action_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("vert_action");
    tt->descr = tdrpStrDup("Set vertical limits on data being read. You can choose\na composite( VERT_ACTION_COMPOSITE) or choose to read\ndata between vertical limits( VERT_ACTION_SET_LIMITS)\nIf not VERT_ACTION_NONE, choose VERT_ACTION_SET_LIMITS\nor VERT_ACTION_COMPOSITE.\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &vert_action - &_start_;
    tt->enum_def.name = tdrpStrDup("vert_action_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("VERT_ACTION_NONE");
      tt->enum_def.fields[0].val = VERT_ACTION_NONE;
      tt->enum_def.fields[1].name = tdrpStrDup("VERT_ACTION_SET_LIMITS");
      tt->enum_def.fields[1].val = VERT_ACTION_SET_LIMITS;
      tt->enum_def.fields[2].name = tdrpStrDup("VERT_ACTION_COMPOSITE");
      tt->enum_def.fields[2].val = VERT_ACTION_COMPOSITE;
    tt->single_val.e = VERT_ACTION_NONE;
    tt++;
    
    // Parameter 'vlevel_type'
    // ctype is '_vlevel_type_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("vlevel_type");
    tt->descr = tdrpStrDup("If choosing VERT_ACTION_SET_LIMITS, or VERT_ACTION_COMPOSITE choose\nVLEVEL_PLANE_NUM to specify the boundind planes by\nnumber or choose VLEVEL_DATA_UNITS to specify\nthe bounding planes in vertical units defined in\nthe data file.\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &vlevel_type - &_start_;
    tt->enum_def.name = tdrpStrDup("vlevel_type_t");
    tt->enum_def.nfields = 2;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("VLEVEL_PLANE_NUM");
      tt->enum_def.fields[0].val = VLEVEL_PLANE_NUM;
      tt->enum_def.fields[1].name = tdrpStrDup("VLEVEL_DATA_UNITS");
      tt->enum_def.fields[1].val = VLEVEL_DATA_UNITS;
    tt->single_val.e = VLEVEL_DATA_UNITS;
    tt++;
    
    // Parameter 'vertical_min'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("vertical_min");
    tt->descr = tdrpStrDup("Used if vertical action is not VERT_ACTION_NONE. This is the minimum vertical level plane in units\nspecified by vlevel_type.\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &vertical_min - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'vertical_max'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("vertical_max");
    tt->descr = tdrpStrDup("Used if vertical action is not VERT_ACTION_NONE. This is the maximun vertical level plane in units\nspecified by vlevel_type.\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &vertical_max - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'search_margin'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("search_margin");
    tt->descr = tdrpStrDup("This defines the time window around data search time. Only used in realtime mode.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &search_margin - &_start_;
    tt->single_val.i = 0;
    tt++;
    
    // Parameter 'doMax'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("doMax");
    tt->descr = tdrpStrDup("Apply max filter over circular region\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &doMax - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'doMin'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("doMin");
    tt->descr = tdrpStrDup("Apply min filter over circular region\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &doMin - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'doAvg'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("doAvg");
    tt->descr = tdrpStrDup("Apply average filter over circular region\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &doAvg - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'doStd'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("doStd");
    tt->descr = tdrpStrDup("Apply standard deviation filter over circular region\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &doStd - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'doPtile'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("doPtile");
    tt->descr = tdrpStrDup("Apply percentile filter over circular region\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &doPtile - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'ptile'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("ptile");
    tt->descr = tdrpStrDup("If doing a percentile filter, use this percentile of data in circular region\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &ptile - &_start_;
    tt->single_val.f = 50;
    tt++;
    
    // Parameter 'doPercentCov'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("doPercentCov");
    tt->descr = tdrpStrDup("Apply percentile filter over circular region\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &doPercentCov - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'percent_cov_thresh'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("percent_cov_thresh");
    tt->descr = tdrpStrDup("If doing a percent coverage filter, use this threshhold to test data in circular region\n");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &percent_cov_thresh - &_start_;
    tt->single_val.f = 50;
    tt++;
    
    // Parameter 'radius'
    // ctype is 'float'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = FLOAT_TYPE;
    tt->param_name = tdrpStrDup("radius");
    tt->descr = tdrpStrDup("radius of circular filter region in kilometers.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &radius - &_start_;
    tt->single_val.f = 10;
    tt++;
    
    // Parameter 'remap_grid'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("remap_grid");
    tt->descr = tdrpStrDup("Set to true to remap the data.");
    tt->help = tdrpStrDup("Defaults to false");
    tt->val_offset = (char *) &remap_grid - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'grid_projection'
    // ctype is '_projection_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("grid_projection");
    tt->descr = tdrpStrDup("Projection type for remapped grid");
    tt->help = tdrpStrDup("Projections currently supported are PROJ_FLAT, PROJ_LATLON and PROJ_LAMBERT");
    tt->val_offset = (char *) &grid_projection - &_start_;
    tt->enum_def.name = tdrpStrDup("projection_t");
    tt->enum_def.nfields = 3;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("PROJ_FLAT");
      tt->enum_def.fields[0].val = PROJ_FLAT;
      tt->enum_def.fields[1].name = tdrpStrDup("PROJ_LATLON");
      tt->enum_def.fields[1].val = PROJ_LATLON;
      tt->enum_def.fields[2].name = tdrpStrDup("PROJ_LAMBERT");
      tt->enum_def.fields[2].val = PROJ_LAMBERT;
    tt->single_val.e = PROJ_LATLON;
    tt++;
    
    // Parameter 'grid_params'
    // ctype is '_grid_params_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("grid_params");
    tt->descr = tdrpStrDup("Grid parameters for remapping in x,y.");
    tt->help = tdrpStrDup("These params apply to all projection types.");
    tt->val_offset = (char *) &grid_params - &_start_;
    tt->struct_def.name = tdrpStrDup("grid_params_t");
    tt->struct_def.nfields = 6;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("int");
      tt->struct_def.fields[0].fname = tdrpStrDup("nx");
      tt->struct_def.fields[0].ptype = INT_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &grid_params.nx - (char *) &grid_params;
      tt->struct_def.fields[1].ftype = tdrpStrDup("int");
      tt->struct_def.fields[1].fname = tdrpStrDup("ny");
      tt->struct_def.fields[1].ptype = INT_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &grid_params.ny - (char *) &grid_params;
      tt->struct_def.fields[2].ftype = tdrpStrDup("double");
      tt->struct_def.fields[2].fname = tdrpStrDup("minx");
      tt->struct_def.fields[2].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[2].rel_offset = 
        (char *) &grid_params.minx - (char *) &grid_params;
      tt->struct_def.fields[3].ftype = tdrpStrDup("double");
      tt->struct_def.fields[3].fname = tdrpStrDup("miny");
      tt->struct_def.fields[3].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[3].rel_offset = 
        (char *) &grid_params.miny - (char *) &grid_params;
      tt->struct_def.fields[4].ftype = tdrpStrDup("double");
      tt->struct_def.fields[4].fname = tdrpStrDup("dx");
      tt->struct_def.fields[4].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[4].rel_offset = 
        (char *) &grid_params.dx - (char *) &grid_params;
      tt->struct_def.fields[5].ftype = tdrpStrDup("double");
      tt->struct_def.fields[5].fname = tdrpStrDup("dy");
      tt->struct_def.fields[5].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[5].rel_offset = 
        (char *) &grid_params.dy - (char *) &grid_params;
    tt->n_struct_vals = 6;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].i = 812;
      tt->struct_vals[1].i = 485;
      tt->struct_vals[2].d = -99.086;
      tt->struct_vals[3].d = 31.515;
      tt->struct_vals[4].d = 0.038239;
      tt->struct_vals[5].d = 0.035933;
    tt++;
    
    // Parameter 'origin_lat'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("origin_lat");
    tt->descr = tdrpStrDup("Remapped grid origin latitude.");
    tt->help = tdrpStrDup("This applies only to PROJ_FLAT and PROJ_LAMBERT projections.");
    tt->val_offset = (char *) &origin_lat - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'origin_lon'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("origin_lon");
    tt->descr = tdrpStrDup("Remapped grid origin longitude.");
    tt->help = tdrpStrDup("This applies only to PROJ_FLAT and PROJ_LAMBERT projections.");
    tt->val_offset = (char *) &origin_lon - &_start_;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'flat_rotation'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("flat_rotation");
    tt->descr = tdrpStrDup("Rotation (in degrees) of grid from true north");
    tt->help = tdrpStrDup("Usually 0 - applied to flat earth only");
    tt->val_offset = (char *) &flat_rotation - &_start_;
    tt->has_min = TRUE;
    tt->min_val.d = -360;
    tt->single_val.d = 0;
    tt++;
    
    // Parameter 'lambert_lat1'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("lambert_lat1");
    tt->descr = tdrpStrDup("First true latitude for PROJ_LAMBERT projection.");
    tt->help = tdrpStrDup("Applies only to PROJ_LAMBERT.");
    tt->val_offset = (char *) &lambert_lat1 - &_start_;
    tt->has_min = TRUE;
    tt->has_max = TRUE;
    tt->min_val.d = -90;
    tt->max_val.d = 90;
    tt->single_val.d = 25.1;
    tt++;
    
    // Parameter 'lambert_lat2'
    // ctype is 'double'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = DOUBLE_TYPE;
    tt->param_name = tdrpStrDup("lambert_lat2");
    tt->descr = tdrpStrDup("Second true latitude for PROJ_LAMBERT projection.");
    tt->help = tdrpStrDup("Applies only to PROJ_LAMBERT.");
    tt->val_offset = (char *) &lambert_lat2 - &_start_;
    tt->has_min = TRUE;
    tt->has_max = TRUE;
    tt->min_val.d = -90;
    tt->max_val.d = 90;
    tt->single_val.d = 25;
    tt++;
    
    // Parameter 'Comment 4'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 4");
    tt->comment_hdr = tdrpStrDup("DATA OUTPUT.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'output_url'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("output_url");
    tt->descr = tdrpStrDup("Url of output mdv dataset");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &output_url - &_start_;
    tt->single_val.s = tdrpStrDup("mdvp:://localhost::$(PROJECT)/mdv");
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }
