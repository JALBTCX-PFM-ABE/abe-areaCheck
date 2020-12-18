
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

void set_defaults (MISC *misc, OPTIONS *options, uint8_t restore)
{
  //  Set Defaults so that if keys don't for envin the parms are defined.

  if (!restore)
    {
      misc->poly_count = 0;
      misc->drawing_canceled = NVFalse;
      misc->drawing = NVFalse;
      misc->prev_mbr.min_x = 999.0;

      for (int32_t k = 0 ; k < NUM_TYPES ; k++) misc->num_overlays[k] = 0;

      misc->type_name[SHAPE] = areaCheck::tr ("Shape");
      misc->type_name[ISS60_AREA] = areaCheck::tr ("ISS60 Area");
      misc->type_name[GENERIC_AREA] = areaCheck::tr ("Generic Area");
      misc->type_name[ACE_AREA] = areaCheck::tr ("Army Corps Area");
      misc->type_name[ISS60_ZONE] = areaCheck::tr ("ISS60 Zone");
      misc->type_name[GENERIC_ZONE] = areaCheck::tr ("Generic Zone");
      misc->type_name[TRACK] = areaCheck::tr ("Trackline");
      misc->type_name[FEATURE] = areaCheck::tr ("Feature");
      misc->type_name[YXZ] = areaCheck::tr ("YXZ");
      misc->type_name[LLZ_DATA] = areaCheck::tr ("LLZ");
      misc->type_name[GEOTIFF] = areaCheck::tr ("GeoTIFF");
      misc->type_name[CHRTR] = areaCheck::tr ("CHRTR");
      misc->type_name[BAG] = areaCheck::tr ("BAG");
      misc->type_name[OPTECH_FLT] = areaCheck::tr ("Optech flight");

      misc->width = 950;
      misc->height = 750;
      misc->window_x = 0;
      misc->window_y = 0;

      misc->linked = NVFalse;
    }


  options->coast = NVTrue;
  options->position_form = 0;
  options->inputFilter = areaCheck::tr ("AREA (*.ARE *.are *.afs)");
  options->outputFilter = areaCheck::tr ("Generic area file (*.are)");
  options->coast_color = Qt::black;
  options->background_color = Qt::white;
  options->color[ISS60_AREA] = QColor (0, 170, 0);
  options->color[GENERIC_AREA] = QColor (0, 170, 0);
  options->color[ACE_AREA] = QColor (0, 170, 0);
  options->color[ISS60_ZONE] = QColor (0, 0, 255);
  options->color[GENERIC_ZONE] = QColor (0, 0, 255);
  options->color[SHAPE] = QColor (255, 0, 255, 127);
  options->color[TRACK] = QColor (0, 0, 0);
  options->color[FEATURE] = QColor (0, 0, 255);
  options->color[YXZ] = QColor (0, 0, 0);
  options->color[LLZ_DATA] = QColor (0, 85, 255);
  options->color[GEOTIFF] = QColor (255, 0, 0, 255);
  options->color[CHRTR] = QColor (0, 255, 0, 255);
  options->color[BAG] = QColor (0, 0, 255, 255);
  options->highlight_color = Qt::yellow;
  options->font = QApplication::font ();
  options->display_children = NVTrue;
  options->display_feature_info = NVFalse;
  options->display_feature_poly = NVFalse;
  options->stoplight = NVFalse;
  options->minstop = 1.5;
  options->maxstop = 2.0;
  options->sunopts.azimuth = 30.0;
  options->sunopts.elevation = 30.0;
  options->sunopts.exag = 1.0;
  options->sunopts.power_cos = 1.0;
  options->sunopts.num_shades = NUMSHADES;
  options->input_dir = ".";
  options->output_dir = ".";
  options->msg_window_x = 0;
  options->msg_window_y = 0;
  options->msg_width = 800;
  options->msg_height = 600;
}
