
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




using namespace std;  // Windoze bullshit - God forbid they should follow a standard


QString bGrpText = 
  prefs::tr ("Select the format in which you want all geographic positions to be displayed.");

QString backgroundColorText = 
  prefs::tr ("Click this button to change the color that is used as NULL background.  After "
             "selecting a color the map will be redrawn.");

QString coastColorText = 
  prefs::tr ("Click this button to change the color that is used to plot the coasts.  After "
             "selecting a color the map will be redrawn.");

QString colorGrpText = 
  prefs::tr ("Click a button to change the associated plotting color.  After selecting a color the map will be redrawn.");

QString sunAzText = 
  prefs::tr ("Set the sun angle.  Sun angle is the direction from which the sun appears to be "
             "illuminating the sun shaded surface.  The default value is 30 degrees which would be "
             "from the upper right of the display.");

QString sunElText = 
  prefs::tr ("Set the sun elevation.  Sun elevation is the apparent elevation of the sun above the "
             "horizon for the sun shaded surface.  The default value is 30 degrees.  Acceptable "
             "values are from 0.0 (totally dark) to 90.0 (directly overhead).");

QString sunExText = 
  prefs::tr ("Set the sun shading Z exaggeration.  This is the apparent exaggeration of the surface "
             "in the Z direction.  The default is 1.0 (no exaggeration).");

QString stopLightText = 
  prefs::tr ("If selected, data that is stored in MINMAX type .trk files will be displayed using stop light colors (red, "
             "yellow, green).  The values at which the colors change are specified in the <b>Green to yellow value</b> "
             "and <b>Yellow to reed value</b> locations.  If this button is not selected then data from MINMAX .trk files "
             "will be displayed in colors ranging from blue to red with blue representing the minimum and red representing "
             "the max.");

QString minStopText = 
  prefs::tr ("This is the value below which data from MINMAX .trk files will be displayed in green.  This value is meaningless "
             "if the <b>Use stoplight colors</b> check box is not selected.");

QString maxStopText = 
  prefs::tr ("This is the value above which data from MINMAX .trk files will be displayed in red.  This value is meaningless "
             "if the <b>Use stoplight colors</b> check box is not selected.");

QString highlightColorText = 
  prefs::tr ("Click this button to change the color that is used to highlight selected lines or areas.  After selecting "
             "a color the map will be redrawn.");

QString restoreDefaultsText = 
  prefs::tr ("Click this button to restore all of the preferences to the original default values and close "
	     "the dialog.  This includes <b><i>all</i></b> of the system preferences, not just those in the "
             "preferences dialog.");

QString closePrefsText = 
  prefs::tr ("Click this button to discard all preference changes and close the dialog.  The main map and "
             "will not be redrawn.");

QString applyPrefsText = 
  prefs::tr ("Click this button to apply all changes and close the dialog.  The main map map will "
             "be redrawn.");
