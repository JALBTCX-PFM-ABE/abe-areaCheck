
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


void hatchr (int32_t k, int32_t file_number, nvMap *map, OPTIONS *options, MISC *misc, float *current_row, 
	     float *next_row, int32_t start_row, int32_t row, int32_t cols, double min_z,
	     double max_z, NV_F64_XYMBR mbr)
{
  double              cur_y[2] = {0.0, 0.0}, cur_x[2] = {0.0, 0.0};
  float               shade_factor;
  static int32_t      i, h_index = 0, s_index = 0, numhues = NUMHUES - 1;
  QColor              temp, prev;
  uint8_t             first;


  first = NVTrue;


  cur_y[0] = mbr.min_y + (row - start_row) * misc->overlays[k][file_number].y_bin_size_degrees;
  cur_y[1] = cur_y[0] + misc->overlays[k][file_number].y_bin_size_degrees;


  //  Loop for the width of the displayed/edited area.

  for (i = 0 ; i < cols ; i++)
    {
      //  Set the HSV fill color.

      if (min_z < 0.0 && max_z >= 0.0)
        {
          if (current_row[i] <= 0.0)
            {
              h_index = (int32_t) (numhues - fabs ((current_row[i] - min_z) / (-min_z) * numhues));
            }
          else
            {
              h_index = (int32_t) (numhues - fabs (current_row[i] / max_z * numhues));
            }
        }
      else
        {
	  float range = max_z - min_z;
	  if (range == 0.0) range = 1.0;

          h_index = (int32_t) (numhues - fabs ((current_row[i] - min_z) / range * numhues));
        }


      //  Clear nulls

      if (current_row[i] >= CHRTRNULL) h_index = -2; 


      //  Select the color if not null.

      if (h_index >= 0)
        {
          shade_factor = sunshade_null (current_row[i], next_row[i], next_row[i + 1], CHRTRNULL, 
                                        &options->sunopts, misc->overlays[k][file_number].x_bin_size_meters,
                                        misc->overlays[k][file_number].y_bin_size_meters);


          //  The shade_factor will sometimes come back just slightly larger than 1.0.

          if (shade_factor < 0.0) shade_factor = 0.0;

          if (shade_factor > 1.0) shade_factor = 1.0;

          s_index = (int32_t) ((NUMSHADES - 1) * shade_factor + 0.5);

          temp = misc->color_array[h_index][s_index];
        }
      else
        {
          //  Set to background for null depth.  We don't actually plot these since we've blanked the
          //  area to be redrawn.

          temp = options->background_color;

	  s_index = NUMSHADES - 1;
        }


      if (prev != temp || i == cols - 1)
        {
          //  Compute longitude.
    
          if (first) 
            {
              cur_x[0] = mbr.min_x + i * misc->overlays[k][file_number].x_bin_size_degrees;
              cur_x[1] = cur_x[0];
            }
          else
            {
              cur_x[1] = mbr.min_x + (i + 1) * misc->overlays[k][file_number].x_bin_size_degrees;
            }


          if (first)
            {
              prev = temp;

              first = NVFalse;
            }
          else
            {
              if (prev != options->background_color) map->fillRectangle (cur_x[0], cur_y[0], cur_x[1], cur_y[1], prev, NVFalse);

              prev = temp;


              //  Compute x position.

              cur_x[0] = mbr.min_x + i * misc->overlays[k][file_number].x_bin_size_degrees;
            }
        }
    }
}
