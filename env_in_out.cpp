
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



#include "areaCheck.hpp"


double settings_version = 5.01;


/*!
  These functions store and retrieve the program settings (environment) from a .ini file.  On both Linux and Windows
  the file will be called areaCheck.ini and will be stored in a directory called ABE.config.  On Linux, the
  ABE.config directory will be stored in your $HOME directory.  On Windows, it will be stored in your $USERPROFILE
  folder.  If you make a change to the way a variable is used and you want to force the defaults to be restored just
  change the settings_version to a newer number (I've been using the program version number from version.hpp - which
  you should be updating EVERY time you make a change to the program!).  You don't need to change the
  settings_version though unless you want to force the program to go back to the defaults (which can annoy your
  users).  So, the settings_version won't always match the program version.
*/

uint8_t envin (OPTIONS *options, MISC *misc, QMainWindow *mainWindow)
{
  double saved_version = 0.0;


  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/areaCheck.ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/areaCheck.ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup ("areaCheck");


  saved_version = settings.value (QString ("settings version"), saved_version).toDouble ();


  //  If the settings version has changed we need to leave the values at the new defaults since they may have changed.

  if (settings_version != saved_version) return (NVFalse);


  options->coast = settings.value (QString ("coastline flag"), options->coast).toBool ();

  options->display_children = settings.value (QString ("sub-feature flag"), options->display_children).toBool ();
  options->display_feature_info = settings.value (QString ("feature info flag"), options->display_feature_info).toBool ();
  options->display_feature_poly = settings.value (QString ("feature polygon flag"), options->display_feature_poly).toBool ();

  options->inputFilter = settings.value (QString ("input filter"), options->inputFilter).toString ();
  options->outputFilter = settings.value (QString ("output filter"), options->outputFilter).toString ();

  options->position_form = settings.value (QString ("position form"), options->position_form).toInt ();

  int32_t red = settings.value (QString ("coast color/red"), options->coast_color.red ()).toInt ();
  int32_t green = settings.value (QString ("coast color/green"), options->coast_color.green ()).toInt ();
  int32_t blue = settings.value (QString ("coast color/blue"), options->coast_color.blue ()).toInt ();
  int32_t alpha = settings.value (QString ("coast color/alpha"), options->coast_color.alpha ()).toInt ();
  options->coast_color.setRgb (red, green, blue, alpha);


  red = settings.value (QString ("background color/red"), options->background_color.red ()).toInt ();
  green = settings.value (QString ("background color/green"), options->background_color.green ()).toInt ();
  blue = settings.value (QString ("background color/blue"), options->background_color.blue ()).toInt ();
  alpha = settings.value (QString ("background color/alpha"), options->background_color.alpha ()).toInt ();
  options->background_color.setRgb (red, green, blue, alpha);


  for (int32_t i = 0 ; i < NUM_TYPES ; i++)
    {
      QString name = misc->type_name[i] + QString (" color/");

      red = settings.value (name + QString ("red"), options->color[i].red ()).toInt ();
      green = settings.value (name + QString ("green"), options->color[i].green ()).toInt ();
      blue = settings.value (name + QString ("blue"), options->color[i].blue ()).toInt ();
      alpha = settings.value (name + QString ("alpha"), options->color[i].alpha ()).toInt ();
      options->color[i].setRgb (red, green, blue, alpha);
    }
  
  
  red = settings.value (QString ("highlight color/red"), options->highlight_color.red ()).toInt ();
  green = settings.value (QString ("highlight color/green"), options->highlight_color.green ()).toInt ();
  blue = settings.value (QString ("highlight color/blue"), options->highlight_color.blue ()).toInt ();
  alpha = settings.value (QString ("highlight color/alpha"), options->highlight_color.alpha ()).toInt ();
  options->highlight_color.setRgb (red, green, blue, alpha);

  
  options->sunopts.sun.x = settings.value (QString ("sunopts sun x"), options->sunopts.sun.x).toDouble ();

  options->sunopts.sun.y = settings.value (QString ("sunopts sun y"), options->sunopts.sun.y).toDouble ();

  options->sunopts.sun.z = settings.value (QString ("sunopts sun y"), options->sunopts.sun.y).toDouble ();

  options->sunopts.azimuth = settings.value (QString ("sunopts azimuth"), options->sunopts.azimuth).toDouble ();

  options->sunopts.elevation = settings.value (QString ("sunopts elevation"), options->sunopts.elevation).toDouble ();

  options->sunopts.exag = settings.value (QString ("sunopts exag"), options->sunopts.exag).toDouble ();

  options->sunopts.power_cos = settings.value (QString ("sunopts power cosine"), options->sunopts.power_cos).toDouble ();

  options->sunopts.num_shades = settings.value (QString ("sunopts number of shades"), options->sunopts.num_shades).toInt ();


  options->stoplight = settings.value (QString ("stoplight"), options->stoplight).toBool ();

  options->minstop = (float) settings.value (QString ("min stoplight"), (double) options->minstop).toDouble ();
  options->maxstop = (float) settings.value (QString ("max stoplight"), (double) options->maxstop).toDouble ();

  options->input_dir = settings.value (QString ("input directory"), options->input_dir).toString ();
  options->output_dir = settings.value (QString ("output directory"), options->output_dir).toString ();

  options->msg_window_x = settings.value (QString ("message window x position"), options->msg_window_x).toInt ();
  options->msg_window_y = settings.value (QString ("message window y position"), options->msg_window_y).toInt ();
  options->msg_width = settings.value (QString ("message window width"), options->msg_width).toInt ();
  options->msg_height = settings.value (QString ("message window height"), options->msg_height).toInt ();


  mainWindow->restoreState (settings.value (QString ("main window state")).toByteArray (), NINT (settings_version * 100.0));

  mainWindow->restoreGeometry (settings.value (QString ("main window geometry")).toByteArray ());

  settings.endGroup ();


  //  We need to get the font from the global settings since it will be used in (hopefully) all of the ABE map GUI applications.

#ifdef NVWIN3X
  QString ini_file2 = QString (getenv ("USERPROFILE")) + "/ABE.config/" + "globalABE.ini";
#else
  QString ini_file2 = QString (getenv ("HOME")) + "/ABE.config/" + "globalABE.ini";
#endif

  QSettings settings2 (ini_file2, QSettings::IniFormat);
  settings2.beginGroup ("globalABE");


  QString defaultFont = options->font.toString ();
  QString fontString = settings2.value (QString ("ABE map GUI font"), defaultFont).toString ();
  options->font.fromString (fontString);


  settings2.endGroup ();


  return (NVTrue);
}


void envout (OPTIONS *options, MISC *misc, QMainWindow *mainWindow)
{
  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/areaCheck.ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/areaCheck.ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup ("areaCheck");


  settings.setValue (QString ("settings version"), settings_version);

  settings.setValue (QString ("coastline flag"), options->coast);

  settings.setValue (QString ("sub-feature flag"), options->display_children);
  settings.setValue (QString ("feature info flag"), options->display_feature_info);
  settings.setValue (QString ("feature polygon flag"), options->display_feature_poly);


  settings.setValue (QString ("input filter"), options->inputFilter);
  settings.setValue (QString ("output filter"), options->outputFilter);

  settings.setValue (QString ("position form"), options->position_form);


  settings.setValue (QString ("coast color/red"), options->coast_color.red ());
  settings.setValue (QString ("coast color/green"), options->coast_color.green ());
  settings.setValue (QString ("coast color/blue"), options->coast_color.blue ());
  settings.setValue (QString ("coast color/alpha"), options->coast_color.alpha ());


  settings.setValue (QString ("background color/red"), options->background_color.red ());
  settings.setValue (QString ("background color/green"), options->background_color.green ());
  settings.setValue (QString ("background color/blue"), options->background_color.blue ());
  settings.setValue (QString ("background color/alpha"), options->background_color.alpha ());

  
  for (int32_t i = 0 ; i < NUM_TYPES ; i++)
    {
      QString name = misc->type_name[i] + QString (" color/");

      settings.setValue (name + QString ("red"), options->color[i].red ());
      settings.setValue (name + QString ("green"), options->color[i].green ());
      settings.setValue (name + QString ("blue"), options->color[i].blue ());
      settings.setValue (name + QString ("alpha"), options->color[i].alpha ());
    }

  
  settings.setValue (QString ("highlight color/red"), options->highlight_color.red ());
  settings.setValue (QString ("highlight color/green"), options->highlight_color.green ());
  settings.setValue (QString ("highlight color/blue"), options->highlight_color.blue ());
  settings.setValue (QString ("highlight color/alpha"), options->highlight_color.alpha ());

  
  settings.setValue (QString ("sunopts sun x"), options->sunopts.sun.x);
  settings.setValue (QString ("sunopts sun y"), options->sunopts.sun.y);
  settings.setValue (QString ("sunopts sun y"), options->sunopts.sun.y);
  settings.setValue (QString ("sunopts azimuth"), options->sunopts.azimuth);
  settings.setValue (QString ("sunopts elevation"), options->sunopts.elevation);
  settings.setValue (QString ("sunopts exag"), options->sunopts.exag);
  settings.setValue (QString ("sunopts power cosine"), options->sunopts.power_cos);
  settings.setValue (QString ("sunopts number of shades"), options->sunopts.num_shades);


  settings.setValue (QString ("stoplight"), options->stoplight);

  settings.setValue (QString ("min stoplight"), (double) options->minstop);
  settings.setValue (QString ("max stoplight"), (double) options->maxstop);

  settings.setValue (QString ("input directory"), options->input_dir);
  settings.setValue (QString ("output directory"), options->output_dir);

  settings.setValue (QString ("message window x position"), options->msg_window_x);
  settings.setValue (QString ("message window y position"), options->msg_window_y);
  settings.setValue (QString ("message window width"), options->msg_width);
  settings.setValue (QString ("message window height"), options->msg_height);


  settings.setValue (QString ("main window state"), mainWindow->saveState (NINT (settings_version * 100.0)));

  settings.setValue (QString ("main window geometry"), mainWindow->saveGeometry ());

  settings.endGroup ();
}
