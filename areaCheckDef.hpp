
/*********************************************************************************************

    This is public domain software that was developed by or for the U.S. Naval Oceanographic
    Office and/or the U.S. Army Corps of Engineers.

    This is a work of the U.S. Government. In accordance with 17 USC 105, copyright protection
    is not available for any work of the U.S. Government.

    Neither the United States Government, nor any employees of the United States Government,
    nor the author, makes any warranty, express or implied, without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, or assumes any liability or
    responsibility for the accuracy, completeness, or usefulness of any information,
    apparatus, product, or process disclosed, or represents that its use would not infringe
    privately-owned rights. Reference herein to any specific commercial products, process,
    or service by trade name, trademark, manufacturer, or otherwise, does not necessarily
    constitute or imply its endorsement, recommendation, or favoring by the United States
    Government. The views and opinions of authors expressed herein do not necessarily state
    or reflect those of the United States Government, and shall not be used for advertising
    or product endorsement purposes.
*********************************************************************************************/


/****************************************  IMPORTANT NOTE  **********************************

    Comments in this file that start with / * ! or / / ! are being used by Doxygen to
    document the software.  Dashes in these comment blocks are used to create bullet lists.
    The lack of blank lines after a block of dash preceeded comments means that the next
    block of dash preceeded comments is a new, indented bullet list.  I've tried to keep the
    Doxygen formatting to a minimum but there are some other items (like <br> and <pre>)
    that need to be left alone.  If you see a comment that starts with / * ! or / / ! and
    there is something that looks a bit weird it is probably due to some arcane Doxygen
    syntax.  Be very careful modifying blocks of Doxygen comments.

*****************************************  IMPORTANT NOTE  **********************************/



#ifndef _AREA_CHECK_DEF_H_
#define _AREA_CHECK_DEF_H_


#include "nvutility.h"
#include "nvutility.hpp"
#include "pfm.h"

#include "llz.h"
#include "chrtr2.h"

#include "bag.h"
#include "bag_legacy.h"

#include "binaryFeatureData.h"

#include "gdal_priv.h"
#include "shapefil.h"


#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif


using namespace std;  // Windoze bullshit - God forbid they should follow a standard


//  Pointer interaction functions.

#define         EDIT_AREA                   0
#define         ZOOM_IN_AREA                1
#define         DEFINE_RECT_AREA            2
#define         DEFINE_POLY_AREA            3
#define         MOVE_AREA                   4
#define         ADD_VERTEX                  5
#define         DELETE_VERTEX               6
#define         MOVE_VERTEX                 7
#define         EDIT_VERTEX                 8
#define         COPY_AREA                   9

#define         VERTEX_SIZE                 8
#define         NUMSHADES                   256
#define         NUMHUES                     128
#define         POLYGON_POINTS              NVMAP_POLYGON_POINTS


//  Data types

//  Modifiable

#define         GENERIC_AREA                0
#define         ACE_AREA                    1
#define         ISS60_AREA                  2
#define         ISS60_ZONE                  3
#define         GENERIC_ZONE                4

#define         MOD_TYPES                   5


//  Non-modifiable

#define         SHAPE                       5
#define         TRACK                       6
#define         FEATURE                     7
#define         YXZ                         8
#define         LLZ_DATA                    9
#define         GEOTIFF                     10
#define         CHRTR                       11
#define         BAG                         12
#define         OPTECH_FLT                  13


#define         NUM_TYPES                   14


//  The OPTIONS structure contains all those variables that can be saved to the
//  users areaCheck QSettings.


typedef struct
{
  uint8_t     coast;                      //  Coastline flag
  int32_t     position_form;              //  Position format number
  QColor      coast_color;                //  Color to be used for coast
  QColor      background_color;           //  Color to be used for background
  QColor      color[NUM_TYPES];           //  Colors to be used for different data types
  QColor      highlight_color;            //  Color to be used for highlight
  QFont       font;                       //  Font used for all ABE map GUI applications
  QString     inputFilter;
  QString     outputFilter;
  uint8_t     stoplight;                  //  Set if displaying MINMAX .trk files in stop light colors
  float       minstop;                    //  Value under which MINMAX .trk data is displayed as green
  float       maxstop;                    //  Value over which MINMAX .trk data is displayed as red
  uint8_t     display_children;           //  Set to display sub-features
  uint8_t     display_feature_info;       //  Set to display feature description and remarks
  uint8_t     display_feature_poly;       //  Set to display feature polygons if present
  SUN_OPT     sunopts;                    //  Sun shading options
  QString     input_dir;
  QString     output_dir;
  int32_t     msg_width;                  //  Message window width
  int32_t     msg_height;                 //  Message window height
  int32_t     msg_window_x;               //  Message window x position
  int32_t     msg_window_y;               //  Message window y position
} OPTIONS;


typedef struct
{
  int32_t     type;
  uint8_t     chrtr2;
  uint8_t     modified;
  QColor      color;
  char        filename[512];
  std::vector<double>      x;
  std::vector<double>      y;
  int32_t     count;
  NV_F64_COORD2 center;
  double      x_bin_size_degrees;
  double      y_bin_size_degrees;
  double      x_bin_size_meters;
  double      y_bin_size_meters;
  NV_F64_XYMBR mbr;
  int32_t     bin_width;
  int32_t     bin_height;
  uint8_t     active;
} OVERLAY;


//  General stuff.

typedef struct
{
  int32_t     function;                   //  Active edit or zoom function
  int32_t     poly_count;                 //  Polygon point count
  double      polygon_x[POLYGON_POINTS];  //  Polygon X
  double      polygon_y[POLYGON_POINTS];  //  Polygon Y
  uint8_t     drawing;                    //  set if we are drawing the surface
  uint8_t     drawing_canceled;           //  set to cancel drawing
  NV_F64_XYMBR displayed_area;            //  displayed area
  NV_F64_XYMBR prev_mbr;                  //  previously displayed area
  int32_t     displayed_area_width;       //  displayed area width in columns
  int32_t     displayed_area_height;      //  displayed area height in rows
  std::vector<OVERLAY>     overlays[NUM_TYPES];       //  data file overlay information (see data types above for type values)
  int32_t     num_overlays[NUM_TYPES];    //  number of data overlays
  QString     type_name[NUM_TYPES];       //  Data type names
  QToolButton *overlayButton[NUM_TYPES];  //  Button associated with each type;
  QColor      color_array[NUMHUES][NUMSHADES]; //  Colors for minmax, CHRTR, and BAG
  QSharedMemory *abeRegister;             //  ABE's process register
  ABE_REGISTER *abe_register;             //  Pointer to the ABE_REGISTER structure in shared memory.
  uint8_t     linked;                     //  Set if we have linked to another ABE application.
  int32_t     width;                      //  Main window width
  int32_t     height;                     //  Main window height
  int32_t     window_x;                   //  Main window x position
  int32_t     window_y;                   //  Main window y position
  char        progname[256];              //  This is the program name.  It will be used in all output to stderr so that shelling programs (like abe)
                                          //  will know what program printed out the error message.  */
  QStringList *messages;                  //  Message list
} MISC;


#endif
