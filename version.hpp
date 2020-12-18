
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




#ifndef VERSION

#define     VERSION     "PFM Software - areaCheck V5.35 - 09/22/17"

#endif

/*! <pre>


    Version 1.0
    Jan C. Depner
    06/26/05

    First working version.


    Version 1.01
    Jan C. Depner
    08/09/05

    Added command line options so that you can shell areaCheck as a single file editor/creator from other programs.
    The first example is from chrtrGUI.


    Version 1.02
    Jan C. Depner
    01/30/06

    It sure helps if you close the files after you've finished with them - DOH!  Also, updated map and rproj.


    Version 2.0
    Jan C. Depner
    04/06/06

    Massive Qt changes - new cursors, left click to finish operations, right click menu in some modes.  Replaced
    QVBox, QHBox, QVGroupBox, QHGroupBox with QVBoxLayout, QHBoxLayout, QGroupBox to prepare for Qt 4.


    Version 2.01
    Jan C. Depner
    05/15/06

    Added display of XML target files.


    Version 2.02
    Jan C. Depner
    05/25/06

    Added 1:50,000 coastlines.


    Version 2.03
    Jan C. Depner
    05/30/06

    Removed function tool tips from map and moved them to the status bar.


    Version 2.1
    Jan C. Depner
    06/30/06

    Fixed ISS60 format screwup on output.


    Version 2.11
    Jan C. Depner
    08/15/06

    Added status to exit in slotQuit.


    Version 2.12
    Jan C. Depner
    08/23/06

    Added yxz display.


    Version 2.13
    Jan C. Depner
    08/31/06

    Added llz display.


    Version 2.2
    Jan C. Depner
    09/06/06

    Added shape display.  Cleaned up color stuff.


    Version 2.3
    Jan C. Depner
    09/11/06

    Added clipping.


    Version 2.31
    Jan C. Depner
    09/13/06

    Had to change map.cpp and map.hpp to nvmap.hpp and nvmap.cpp in utility.


    Version 2.32
    Jan C. Depner
    10/05/06

    Added ability to display SRTM3/30 landmask for smaller than 5 degree squares.


    Version 2.33
    Jan C. Depner
    01/25/07

    Added markers when viewing larger than 5 degrees in longitude (so you
    can find the damn things).


    Version 2.34
    Jan C. Depner
    02/09/07

    Added ability to read MINMAX version .trk files (like from dump_dop).


    Version 3.0
    Jan C. Depner
    03/14/07

    Ported to Qt 4.  This is the first of many to be ported.


    Version 3.01
    Jan C. Depner
    05/30/07

    Added alpha values to saved colors.


    Version 3.02
    Jan C. Depner
    07/27/07

    Added support for Army Corps area files (*.afs).


    Version 3.03
    Jan C. Depner
    08/24/07

    Switched from setGeometry to resize and move.  See Qt4 X11 window geometry documentation.


    Version 3.04
    Jan C. Depner
    09/26/07

    Added ability to display target file polygonal areas.


    Version 3.05
    Jan C. Depner
    10/22/07

    Added fflush calls after prints to stderr since flush is not automatic in Windows.


    Version 3.06
    Jan C. Depner
    12/20/07

    Added ability to read file on command line without --file option.


    Version 3.07
    Jan C. Depner
    01/01/08

    Changed to use multiple movable objects in nvMap.


    Version 3.09
    Jan C. Depner
    03/19/08

    Stop button now kills drawing of overlays.


    Version 3.10
    Jan C. Depner
    03/20/08

    Added display buttons for data types.  GeoTIFF is now just another data type although there
    is no associated color, only associated alpha value.


    Version 3.11
    Jan C. Depner
    03/21/08

    Began (but not finished) adding support for displaying CHRTR files.  I added a read-only
    CHRTR API to the utility library.


    Version 4.00
    Jan C. Depner
    03/25/08

    Finished adding support for displaying CHRTR files.


    Version 4.01
    Jan C. Depner
    03/26/08

    Forgot to take out a debug statement... DOH!  Also, cleaned up overlayData and made raster
    files (CHRTR and GeoTIFF) plot prior to the coastline.


    Version 4.02
    Jan C. Depner
    03/28/08

    Cleaned up the overlayData code so that it doesn't draw asterisks at 0.0,0.0 when it doesn't
    draw a particular data type.  Don't redraw full map on file open unless one of the files is
    a raster file.


    Version 4.03
    Jan C. Depner
    04/01/08

    Added acknowledgments to the Help pulldown menu.


    Version 4.04
    Jan C. Depner
    04/03/08

    Fixed minor chrtr annoyance dealing with CHRTRNULL.


    Version 4.07
    Jan C. Depner
    04/07/08

    Removed fget_coord code (it's in the utility library).  Replaced all of the single include
    files from the utility library with nvutility.h and nvutility.hpp.


    Version 4.10
    Jan C. Depner
    04/14/08

    Added the new ABE register functions so we can hook up to programs that we didn't shell.


    Version 4.11
    Jan C. Depner
    06/09/08

    Modified yxz overlay to be + marks when greater than 1 degree is displayed (just like LLZ).


    Version 4.12
    Jan C. Depner
    06/16/08

    Only draw chrtr and geotiff files if we're displaying less than 10 degrees in longitude and latitude.
    Set override "wait" cursor when redrawing.


    Version 4.20
    Jan C. Depner
    06/19/08

    Added display of BAG files.


    Version 4.21
    Jan C. Depner
    07/17/08

    Got rid of the GeoTIFF file preview and Qt3 dependencies.


    Version 4.22
    Jan C. Depner
    07/21/08

    Wasn't reading .afs files properly.


    Version 4.23
    Jan C. Depner
    08/01/08

    Handles Optech flightline planning files (0#MP#####_###_######.txt).


    Version 4.24
    Jan C. Depner
    09/15/08

    Doesn't handle BAG files in Windoze.


    Version 4.25
    Jan C. Depner
    11/24/08

    Fix stupid bug in prefs.cpp.  I forgot to add Optech FLT data to the color buttons, DOH!


    Version 4.26
    Jan C. Depner
    02/24/09

    Changed CHRTR, BAG, and GeoTIFF drawing limits from 10 to 30 degrees.


    Version 4.30
    Jan C. Depner
    04/02/09

    Replaced support for NAVO standard XML target file with Binary Feature Data (BFD) file support.


    Version 4.31
    Jan C. Depner
    04/08/09

    Changes to deal with "flush" argument on all nvmap.cpp (nvutility library) drawing functions.
    Fixed weird blanking when clicking tool bar buttons - always make your own status bars!


    Version 4.32
    Jan C. Depner
    04/13/09

    Use NINT instead of typecasting to NV_INT32 when saving Qt window state.  Integer truncation was inconsistent on Windows.


    Version 4.33
    Jan C. Depner
    04/23/09

    Changed the acknowledgments help to include Qt and a couple of others.


    Version 4.34
    Jan C. Depner
    04/27/09

    Replaced QColorDialog::getRgba with QColorDialog::getColor.


    Version 4.35
    Jan C. Depner
    05/01/09

    YXZ files can now have either comma or space separators.


    Version 4.36
    Jan C. Depner
    05/21/09

    Set all QFileDialogs to use List mode instead of Detail mode.


    Version 4.37
    Jan C. Depner
    05/22/09

    Dealing with multiple resize events when "Display content in resizing windows" is 
    enabled.


    Version 4.38
    Jan C. Depner
    06/24/09

    Changed the BFD names to avoid collision with GNU Binary File Descriptor library.


    Version 4.39
    Jan C. Depner
    08/04/09

    Changed to use OpenNS 1.2 RC1.


    Version 4.40
    Jan C. Depner
    09/11/09

    Fixed getColor calls so that cancel works.  Never forget!


    Version 5.00
    Jan C. Depner
    09/17/09

    Allow turning on or off of each separate file.  No more display_geotiff, display_chrtr, etc.


    Version 5.01
    Jan C. Depner
    10/28/09

    Fixed bug with raster display.


    Version 5.02
    Jan C. Depner
    04/19/10

    Added support (tentatively) for CHRTR2 format.  Not tested yet.  If it works, great.  If not, I'll fix it later.


    Version 5.03
    Jan C. Depner
    05/11/10

    Fixed chrtr2 support (I told you I would).  Also, added support for generic position info in YXZ files.
    Fixed posfix and fixpos calls to use numeric constants instead of strings for type.


    Version 5.04
    Jan C. Depner
    07/13/10

    Fixed chrtr2 display bug.  Wasn't checking the status bits properly.


    Version 5.05
    Jan C. Depner
    08/16/10

    Added compile option to exclude support for BAG.  Only NAVO is really interested in BAG anyway.  Removed UTM northing and easting
    because - who cares ;-)


    Version 5.06
    Jan C. Depner
    01/06/11

    Correct problem with the way I was instantiating the main widget.  This caused an intermittent error on Windows7/XP.


    Version 5.07
    Jan C. Depner
    02/10/11

    Removed BAG exclusion code.


    Version 5.08
    Jan C. Depner
    04/15/11

    Fixed the geoTIFF reading by switching to using GDAL instead of Qt.  Hopefully Qt will get fixed eventually.


    Version 5.09
    Jan C. Depner
    06/24/11

    Fixed shape file display bug.


    Version 5.10
    Jan C. Depner
    06/27/11

    Save all directories used by the QFileDialogs.  Add current working directory to the sidebar for all QFileDialogs.


    Version 5.11
    Jan C. Depner
    07/22/11

    Using setSidebarUrls function from nvutility to make sure that current working directory (.) and
    last used directory are in the sidebar URL list of QFileDialogs.


    Version 5.12
    Jan C. Depner
    11/30/11

    Converted .xpm icons to .png icons.


    Version 5.13
    Jan C. Depner (PFM Software)
    07/01/13

    Fixed shapefile display.


    Version 5.14
    Jan C. Depner (PFM Software)
    10/14/13

    Modified overlay of YXZ data to use a string for the third field instead of assuming that it 
    is a floating point value.  This allows you to output symbols.


    Version 5.15
    Jan C. Depner (PFM Software)
    12/09/13

    Switched to using .ini file in $HOME (Linux) or $USERPROFILE (Windows) in the ABE.config directory.  Now
    the applications qsettings will not end up in unknown places like ~/.config/navo.navy.mil/blah_blah_blah on
    Linux or, in the registry (shudder) on Windows.


    Version 5.16
    Jan C. Depner (PFM Software)
    12/17/13

    Removed the landmask code.  Now that we have a really good coastline based on SWBD (and a mask built from it)
    we don't really need to draw the landmask anymore.  If you want to see where the landmask will be, just look
    at the coastline.

    Verison 5.17
    Stacy Johnson
    12/31/2013

    Added support for bag 1.5.2


    Version 5.18
    Jan C. Depner (PFM Software)
    02/07/14

    Somehow I removed the conversion to pixels in the YXZ overlay.  Fixed.


    Version 5.19
    Jan C. Depner (PFM Software)
    02/28/14

    Reverted to using Qt to read geoTIFFs.  It quit working in Qt 4.7.2 but is working again.  It's
    much faster than using GDAL and it's probably a lot more bulletproof.


    Version 5.20
    Jan C. Depner (PFM Software)
    03/19/14

    - Straightened up the Open Source acknowledgments.


    Version 5.21
    Jan C. Depner (PFM Software)
    05/07/14

    Fixed fgets calls without checks to get rid of GCC warnings.


    Version 5.22
    Jan C. Depner (PFM Software)
    05/27/14

    - Added the new LGPL licensed GSF library to the acknowledgments.


    Version 5.23
    Jan C. Depner (PFM Software)
    07/01/14

    - Replaced all of the old, borrowed icons with new, public domain icons.  Mostly from the Tango set
      but a few from flavour-extended and 32pxmania.


    Version 5.24
    Jan C. Depner (PFM Software)
    07/23/14

    - Switched from using the old NV_INT64 and NV_U_INT32 type definitions to the C99 standard stdint.h and
      inttypes.h sized data types (e.g. int64_t and uint32_t).


    Version 5.25
    Jan C. Depner (PFM Software)
    07/29/14

    - Fixed memory leaks discovered by cppcheck.


    Version 5.26
    Jan C. Depner (PFM Software)
    02/13/15

    - To give better feedback to shelling programs in the case of errors I've added the program name to all
      output to stderr.


    Version 5.27
    Jan C. Depner (PFM Software)
    02/16/15

    - More error message cleanup.  All non-fatal error messages will now be displayed in a message dialog that will
      automatically pop up when a message is sent to stderr.  At the moment there aren't any non-fatal error messages
      but I'm leaving this here as a placeholder for possible future use.


    Version 5.28
    Jan C. Depner (PFM Software)
    02/22/15

    - Added "Save" button for the error messages dialog.


    Version 5.29
    Jan C. Depner (PFM Software)
    03/08/15

    - Replaced realloc with std::vector resize ().


    Version 5.30
    Jan C. Depner (PFM Software)
    06/09/15

    - Added ability to output areas in ESRI Shape file format (POLYGON_Z).


    Version 5.31
    Jan C. Depner (PFM Software)
    07/12/16

    - Removed COMPD_CS from Well-known Text.


    Version 5.32
    Jan C. Depner (PFM Software)
    08/08/16

    - Now gets font from globalABE.ini as set in Preferences by pfmView.
    - To avoid possible confusion, removed translation setup from QSettings in env_in_out.cpp.


    Version 5.33
    Jan C. Depner (PFM Software)
    10/13/16

    - Changed Ctrl+Q to be the exit shortcut instead of "About Qt".


    Version 5.34
    Jan C. Depner (PFM Software)
    10/16/16

    - Removed VERT_CS from Well-known Text.  We're only dumping shapes, no Z needed.


    Version 5.35
    Jan C. Depner (PFM Software)
    09/21/17

    - A bunch of changes to support doing translations in the future.  There is a generic
      areaCheck_xx.ts file that can be run through Qt's "linguist" to translate to another language.

</pre>*/
