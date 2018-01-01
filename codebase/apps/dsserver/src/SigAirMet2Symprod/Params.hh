// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c)
// ** University Corporation for Atmospheric Research(UCAR)
// ** National Center for Atmospheric Research(NCAR)
// ** Boulder, Colorado, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
////////////////////////////////////////////
// Params.hh
//
// TDRP header file for 'Params' class.
//
// Code for program SigAirMet2Symprod
//
// This header file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.hh
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @class Params
 *
 * @author automatically generated
 *
 */

#ifndef Params_hh
#define Params_hh

using namespace std;

#include <tdrp/tdrp.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>

// Class definition

class Params {

public:

  // enum typedefs

  typedef enum {
    DEBUG_OFF = 0,
    DEBUG_NORM = 1,
    DEBUG_VERBOSE = 2
  } debug_t;

  typedef enum {
    PLOT_SIGMETS = 0,
    PLOT_AIRMETS = 1,
    PLOT_ALL = 2
  } plot_data_group_t;

  typedef enum {
    VERT_ALIGN_TOP = 0,
    VERT_ALIGN_CENTER = 1,
    VERT_ALIGN_BOTTOM = 2
  } vert_align_t;

  typedef enum {
    HORIZ_ALIGN_LEFT = 0,
    HORIZ_ALIGN_CENTER = 1,
    HORIZ_ALIGN_RIGHT = 2
  } horiz_align_t;

  typedef enum {
    TEXT_NORM = 0,
    TEXT_BOLD = 1,
    TEXT_ITALICS = 2,
    TEXT_SUBSCRIPT = 3,
    TEXT_SUPERSCRIPT = 4,
    TEXT_UNDERLINE = 5,
    TEXT_STRIKETHROUGH = 6
  } font_style_t;

  typedef enum {
    LINETYPE_SOLID = 0,
    LINETYPE_DASH = 1,
    LINETYPE_DOT_DASH = 2
  } line_type_t;

  typedef enum {
    CAPSTYLE_BUTT = 0,
    CAPSTYLE_NOT_LAST = 1,
    CAPSTYLE_PROJECTING = 2,
    CAPSTYLE_ROUND = 3
  } capstyle_t;

  typedef enum {
    JOINSTYLE_BEVEL = 0,
    JOINSTYLE_MITER = 1,
    JOINSTYLE_ROUND = 2
  } joinstyle_t;

  typedef enum {
    ALWAYS_ON = 0,
    ALWAYS_OFF = 1,
    ON_IF_NO_POLYGON = 2
  } draw_icon_t;

  typedef enum {
    DO_NOT_SCALE = 0,
    DO_SCALE = 1,
    NO_SCALE_IF_NO_POLYGON = 2
  } client_scale_icon_t;

  // struct typedefs

  typedef struct {
    int x;
    int y;
  } text_offset_t;

  typedef struct {
    char* WxWildcard;
    tdrp_bool_t plotID;
    tdrp_bool_t plotWx;
    tdrp_bool_t plotFlightLevels;
    tdrp_bool_t plotSource;
    tdrp_bool_t plotTimes;
    tdrp_bool_t plotText;
    tdrp_bool_t renderPolygonSpokes;
    tdrp_bool_t renderPolygon;
    tdrp_bool_t renderForecasts;
    tdrp_bool_t renderOutlooks;
    draw_icon_t renderIcon;
    char* iconName;
    char* iconNameSouth;
    float iconScale;
    client_scale_icon_t allowClientScaling;
    char* mainColor;
    char* forecastColor;
    char* outlookColor;
    tdrp_bool_t includeHiddenPolygon;
  } sigmet_item_t;

  typedef struct {
    char* icon_name;
    char* icon_points;
  } icon_defs_t;

  ///////////////////////////
  // Member functions
  //

  ////////////////////////////////////////////
  // Default constructor
  //

  Params ();

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params (const Params&);

  ////////////////////////////////////////////
  // Destructor
  //

  ~Params ();

  ////////////////////////////////////////////
  // Assignment
  //

  void operator=(const Params&);

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

  int loadFromArgs(int argc, char **argv,
                   char **override_list,
                   char **params_path_p,
                   bool defer_exit = false);

  bool exitDeferred() { return (_exitDeferred); }

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

  int loadApplyArgs(const char *params_path,
                    int argc, char **argv,
                    char **override_list,
                    bool defer_exit = false);

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  static bool isArgValid(const char *arg);

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

  int load(const char *param_file_path,
           char **override_list,
           int expand_env, int debug);

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

  int loadFromBuf(const char *param_source_str,
                  char **override_list,
                  const char *inbuf, int inlen,
                  int start_line_num,
                  int expand_env, int debug);

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int loadDefaults(int expand_env);

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void sync() const;

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

  void print(FILE *out, tdrp_print_mode_t mode = PRINT_NORM);

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int checkAllSet(FILE *out);

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int checkIsSet(const char *param_name);

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

  int arrayRealloc(const char *param_name,
                   int new_array_n);

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

  int array2DRealloc(const char *param_name,
                     int new_array_n1,
                     int new_array_n2);

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void freeAll(void);

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  static void usage(ostream &out);

  ///////////////////////////
  // Data Members
  //

  char _start_; // start of data region
                // needed for zeroing out data
                // and computing offsets

  debug_t debug;

  char* instance;

  tdrp_bool_t no_threads;

  int port;

  int qmax;

  int max_clients;

  plot_data_group_t plotDataGroup;

  char* text_background_color;

  char* font_name;

  text_offset_t text_offset;

  vert_align_t text_vert_align;

  horiz_align_t text_horiz_align;

  int text_font_size;

  font_style_t text_font_style;

  int plotTextLineLen;

  int plot_text_line_offset;

  tdrp_bool_t plotPolygonIsFirBoundary_PrintFirName;

  char* unknown_wx_text;

  int line_width;

  tdrp_bool_t requirePolygon;

  line_type_t polygon_line_type;

  line_type_t forecast_line_type;

  line_type_t outlook_line_type;

  line_type_t fir_polygon_line_type;

  int polygon_line_width;

  capstyle_t polygon_capstyle;

  joinstyle_t polygon_joinstyle;

  sigmet_item_t *_sigmet_items;
  int sigmet_items_n;

  icon_defs_t *_icon_defs;
  int icon_defs_n;

  int forecast_arrow_head_len_pixels;

  double forecast_arrow_head_half_angle;

  int outlook_arrow_head_len_pixels;

  double outlook_arrow_head_half_angle;

  tdrp_bool_t render_forecast_and_outlook_times;

  tdrp_bool_t label_forecast_and_outlook_times;

  tdrp_bool_t activate_hidden_text;

  int hidden_text_x_offset;

  int hidden_text_y_offset;

  int hidden_text_font_size;

  vert_align_t hidden_text_vert_align;

  horiz_align_t hidden_text_horiz_align;

  char* hidden_text_foreground_color;

  char* hidden_text_background_color;

  double hidden_polygons_alpha_value;

  char _end_; // end of data region
              // needed for zeroing out data

private:

  void _init();

  mutable TDRPtable _table[56];

  const char *_className;

  bool _exitDeferred;

};

#endif

