
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



/*  areaCheck class definitions.  */

#ifndef AREA_CHECK_H
#define AREA_CHECK_H

#include <cmath>
#include <cerrno>
#include <getopt.h>

#include "areaCheckDef.hpp"
#include "prefs.hpp"
#include "displayFile.hpp"
#include "version.hpp"




using namespace std;


void overlayData (nvMap *map, MISC *misc, OPTIONS *options, uint8_t raster);


class areaCheck:public QMainWindow
{
  Q_OBJECT 


public:

  areaCheck (int *argc = 0, char **argv = 0, QWidget *parent = 0);
  ~areaCheck ();

  void redrawMap ();
  void initializeMaps ();


protected:

  prefs           *prefs_dialog;

  displayFile     *displayFile_dialog[NUM_TYPES];

  QLabel          *geoLabel, *xyLabel, *chrtrLabel, *modeLabel, *miscLabel;

  nvMap           *map;

  OPTIONS         options;

  MISC            misc;

  int32_t         edit_area_width, edit_area_column, edit_area_height, edit_area_row, num_messages;

  int32_t         prev_area, cur_area, prev_vertex, cur_vertex, prev_line[2], cur_line[2], prev_type, cur_type;

  int32_t         mv_polygon, mv_marker, rb_rectangle, rb_polygon, mv_tracker;

  int32_t         active_window_id, abe_register_group;

  QTimer          *trackCursor;

  uint8_t         area_moving, vertex_moving, line_moving, area_copying, no_save, input_file, empty_file, any_file, 
                  double_click, need_redraw;

  QDialog         *messageD;

  QListWidget     *messageBox;

  QStatusBar      *mapStatus;

  QMenu           *popupMenu;

  QAction         *exitSaveAct, *exitNoSaveAct, *quitAct, *bHelp, *popup0, *popup1, *popup2, *messageAction;

  QMouseEvent     *menu_mouse_event;

  QPalette        modePalette;

  double          menu_cursor_lat, menu_cursor_lon;

  OVERLAY         new_overlay;

  NVMAP_DEF       mapdef;

  QToolBar        *tools, *dataTypes;

  QToolButton     *bOpen, *bZoomOut, *bZoomIn, *bPrefs, *bCoast, *bFile, *bRect, *bPoly, *bMoveArea, *bMoveVertex,
                  *bDeleteVertex, *bEditVertex, *bAddVertex, *bCopyArea, *bLink;

  QToolButton     *bStop, *bISS60Area, *bGenArea, *bACEArea, *bISS60Zone, *bGenZone, *bGeotiff, *bChrtr, *bBag, *bShape, *bTrack,
                  *bYXZ, *bLLZ, *bFlight, *bFeature, *bChildren, *bFeatureInfo, *bFeaturePoly;

  QButtonGroup    *exitGrp, *typeGrp;

  QToolButton     *bQuit, *bExitSave, *bExitNoSave;

  QDialog         *editVertexD;

  QLineEdit       *latEdit, *lonEdit;

  QString         fileName;

  double          tmpLat, tmpLon;

  QCursor         zoomCursor, addVertexCursor, moveVertexCursor, deleteVertexCursor, editVertexCursor, copyAreaCursor,
                  moveAreaCursor, editRectCursor, editPolyCursor;

  QPainterPath    marker;

  QBrush          marker_brush;


  void addOverlay (int32_t k, QString filename);
  void setMainButtons (uint8_t enabled);
  void discardMovableObjects ();
  void closeEvent (QCloseEvent *event);
  void setFunctionCursor (int32_t function);
  void write_generic (FILE *fp, double *mx, double *my, int32_t count);
  void write_ace (FILE *fp, double *mx, double *my, int32_t count);
  void write_shape (char *shape_name, double *mx, double *my, int32_t count);
  void write_ISS60_ARE (FILE *fp, char *fname, double *mx, double *my, int32_t count);
  void write_ISS60_zne (FILE *fp, char *fname, double *mx, double *my, int32_t count);
  void highlight_nearest_area (double lat, double lon);
  void highlight_nearest_vertex (double lat, double lon);
  void highlight_nearest_line (double lat, double lon);
  void clearLine ();
  void clearArea ();
  void clearVertex ();
  void output_file (double *mx, double *my, int32_t count);
  void displayMessage ();


protected slots:

  void slotPopupMenu0 ();
  void slotPopupMenu1 ();
  void slotPopupHelp ();

  void slotMouseDoubleClick (QMouseEvent *e, double lon, double lat);
  void slotMousePress (QMouseEvent *e, double lon, double lat);
  void slotMouseRelease (QMouseEvent *e, double lon, double lat);
  void slotMouseMove (QMouseEvent *e, double lon, double lat);
  void slotResize (QResizeEvent *e);
  void slotPreRedraw (NVMAP_DEF mapdef);
  void slotMidRedraw (NVMAP_DEF mapdef);
  void slotPostRedraw (NVMAP_DEF mapdef);

  void midMouse (QMouseEvent *e, double lon, double lat);
  void leftMouse (QMouseEvent *e, double lon, double lat);
  void rightMouse (QMouseEvent *e, double lon, double lat);

  void slotLink ();
  void slotRegisterABEKeySet (int32_t key);
  void slotTrackCursor ();

  void slotExitSave ();
  void slotExitNoSave ();
  void slotExit (int id);
  void slotQuit (int32_t status);

  void slotOpenFiles ();
  void slotZoomIn ();
  void slotZoomOut ();
  void slotCoast ();
  void slotMoveArea ();
  void slotCopyArea ();
  void slotMoveVertex ();
  void slotDeleteVertex ();
  void slotEditVertex ();
  void slotAddVertex ();

  void slotApplyVertex ();
  void slotCancelVertex ();

  void slotStop ();
  void slotType (int k);
  void slotDisplayFileDataChanged ();
  void slotDisplayFileDialogClosed (int k);
  void slotChildren ();
  void slotFeatureInfo ();
  void slotFeaturePoly ();

  void slotMessage ();
  void slotCloseMessage ();
  void slotClearMessage ();
  void slotSaveMessage ();

  void about ();
  void slotAcknowledgments ();
  void aboutQt ();

  void slotPrefs ();
  void slotPrefDataChanged (uint8_t mapRedrawFlag);

  void slotDefineRectArea ();
  void slotDefinePolyArea ();

private:

  void keyPressEvent (QKeyEvent *e);

};

#endif
