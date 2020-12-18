
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


uint8_t chrtr2 (int32_t file_number, nvMap *map, MISC *misc, OPTIONS *options)
{
  void hatchr (int32_t k, int32_t file_number, nvMap *map, OPTIONS *options, MISC *misc, float *current_row, float *next_row,
	       int32_t start_row, int32_t row, int32_t cols, double min_z, double max_z, NV_F64_XYMBR mbr);


  CHRTR2_HEADER        header;
  int32_t             k = CHRTR;


  //  Open the file.

  int32_t hnd = chrtr2_open_file (misc->overlays[k][file_number].filename, &header, CHRTR2_READONLY);

  if (hnd < 0) return (NVTrue);


  misc->overlays[k][file_number].x_bin_size_degrees = (double) header.lon_grid_size_degrees;
  misc->overlays[k][file_number].y_bin_size_degrees = (double) header.lat_grid_size_degrees;
  misc->overlays[k][file_number].mbr.min_x = (double) header.mbr.wlon;
  misc->overlays[k][file_number].mbr.min_y = (double) header.mbr.slat;
  misc->overlays[k][file_number].mbr.max_x = (double) header.mbr.elon;
  misc->overlays[k][file_number].mbr.max_y = (double) header.mbr.nlat;
  misc->overlays[k][file_number].bin_width = header.width;
  misc->overlays[k][file_number].bin_height = header.height;

  misc->overlays[k][file_number].center.x = header.mbr.wlon + (header.mbr.elon - header.mbr.wlon);
  if (header.mbr.wlon > header.mbr.elon) misc->overlays[k][file_number].center.x = header.mbr.wlon + 
    ((header.mbr.elon + 360.0) - header.mbr.wlon) / 2.0;
  misc->overlays[k][file_number].center.y = header.mbr.slat + (header.mbr.nlat - header.mbr.slat);


  //  Compute the x and y bin size in meters for sunshading

  double az;

  invgp (NV_A0, NV_B0, misc->overlays[k][file_number].center.y, misc->overlays[k][file_number].center.x, 
	 misc->overlays[k][file_number].center.y + misc->overlays[k][file_number].y_bin_size_degrees,
	 misc->overlays[k][file_number].center.x, &misc->overlays[k][file_number].y_bin_size_meters, &az);

  invgp (NV_A0, NV_B0, misc->overlays[k][file_number].center.y, misc->overlays[k][file_number].center.x, 
	 misc->overlays[k][file_number].center.y, misc->overlays[k][file_number].center.x +
	 misc->overlays[k][file_number].x_bin_size_degrees, &misc->overlays[k][file_number].x_bin_size_meters, &az);


  //  Shorthand ;-)

  double min_x = misc->displayed_area.min_x;
  double min_y = misc->displayed_area.min_y;
  double max_x = misc->displayed_area.max_x;
  double max_y = misc->displayed_area.max_y;


  //  Set the bounds

  NV_F64_XYMBR mbr;
  int32_t start_col, end_col, start_row, end_row;

  if (min_y < header.mbr.slat)
    {
      start_row = 0;
      mbr.min_y = header.mbr.slat;
    }
  else
    {
      start_row = (int32_t) ((min_y - header.mbr.slat) / misc->overlays[k][file_number].y_bin_size_degrees);
      mbr.min_y = min_y;
    }
  if (max_y > header.mbr.nlat)
    {
      end_row = misc->overlays[k][file_number].bin_height;
      mbr.max_y = header.mbr.nlat;
    }
  else
    {
      end_row = (int32_t) ((max_y - header.mbr.slat) / misc->overlays[k][file_number].y_bin_size_degrees);
      mbr.max_y = max_y;
    }

  if (min_x < header.mbr.wlon)
    {
      start_col = 0;
      mbr.min_x = header.mbr.wlon;
    }
  else
    {
      start_col = (int32_t) ((min_x - header.mbr.wlon) / misc->overlays[k][file_number].x_bin_size_degrees);
      mbr.min_x = min_x;
    }
  if (max_x > header.mbr.elon)
    {
      end_col = misc->overlays[k][file_number].bin_width;
      mbr.max_x = header.mbr.elon;
    }
  else
    {
      end_col = (int32_t) ((max_x - header.mbr.wlon) / misc->overlays[k][file_number].x_bin_size_degrees);
      mbr.max_x = max_x;
    }


  if (start_row < 0)
    {
      end_row = (int32_t) ((header.mbr.nlat - mbr.min_y) / misc->overlays[k][file_number].y_bin_size_degrees);
      start_row = 0;
    }

  if (end_row > misc->overlays[k][file_number].bin_height)
    {
      end_row = misc->overlays[k][file_number].bin_height;
      start_row = (int32_t) ((header.mbr.nlat - mbr.max_y) / misc->overlays[k][file_number].y_bin_size_degrees);
    }


  //  Number of rows and columns of the CHRTR file to draw.

  int32_t rows = end_row - start_row;
  int32_t cols = end_col - start_col;


  //  Allocate the needed arrays.

  CHRTR2_RECORD *current_record_row = (CHRTR2_RECORD *) calloc (cols + 1, sizeof (CHRTR2_RECORD));
  if (current_record_row == NULL)
    {
      fprintf (stderr, "%s %s %s %d - current_record - %s", misc->progname, __FILE__, __FUNCTION__, __LINE__, strerror (errno));
      exit (-1);
    }

  float *current_row = (float *) calloc (cols + 1, sizeof (float));
  if (current_row == NULL)
    {
      fprintf (stderr, "%s %s %s %d - current_row - %s", misc->progname, __FILE__, __FUNCTION__, __LINE__, strerror (errno));
      exit (-1);
    }

  float *next_row = (float *) calloc (cols + 1, sizeof (float));

  if (next_row == NULL)
    {
      fprintf (stderr, "%s %s %s %d - next_row - %s", misc->progname, __FILE__, __FUNCTION__, __LINE__, strerror (errno));
      exit (-1);
    }


  //  Set the last column to CHRTRNULL so that hatchr won't freak.

  next_row[cols] = current_row[cols] = CHRTRNULL;


  //  Pre-read the data to get the min and max (since most disk systems cache this isn't much of a
  //  performance hit).

  float min_z = CHRTRNULL;
  float max_z = -CHRTRNULL;


  QProgressDialog prog (areaCheck::tr ("Loading..."), areaCheck::tr ("Cancel"), 0, rows, 0);

  prog.setWindowModality (Qt::WindowModal);
  prog.show ();

  qApp->processEvents();


  //  We only want to update the progress bar at about 20% increments.  This makes things go
  //  marginally faster.

  int32_t prog_inc = rows / 5;
  if (!prog_inc) prog_inc = 1;


  for (int32_t i = 0 ; i < rows ; i++)
    {
      if (!(i % prog_inc)) prog.setValue (i);

      qApp->processEvents();


      if (prog.wasCanceled ())
	{
	  free (current_record_row);
	  free (current_row);
	  free (next_row);
	  chrtr2_close_file (hnd);
	  return (NVFalse);
	}


      chrtr2_read_row (hnd, start_row + i, start_col, cols, current_record_row);


      for (int32_t j = 0 ; j < cols ; j++)
	{
	  if (current_record_row[j].status)
	    {
	      min_z = qMin (current_record_row[j].z, min_z);
	      max_z = qMax (current_record_row[j].z, max_z);
	    }
	}
    }

  prog.setValue (rows);


  //  Read input data row by row.

  for (int32_t row = start_row ; row <= end_row ; row++)
    {
      //  Read data from disk.

      if (row == start_row)
	{
          chrtr2_read_row (hnd, row, start_col, cols, current_record_row);
          for (int32_t i = 0 ; i < cols ; i++)
            {
              if (current_record_row[i].status & CHRTR2_NULL)
                {
                  current_row[i] = CHRTRNULL;
                }
              else
                {
                  current_row[i] = current_record_row[i].z;
                }
            }

	  memcpy (next_row, current_row, cols * sizeof (float));
	}
      else
	{
	  memcpy (current_row, next_row, cols * sizeof (float));
	  if (row < end_row) 
	    {
              chrtr2_read_row (hnd, row, start_col, cols, current_record_row);

              for (int32_t i = 0 ; i < cols ; i++)
                {
                  if (current_record_row[i].status & CHRTR2_NULL)
                    {
                      next_row[i] = CHRTRNULL;
                    }
                  else
                    {
                      next_row[i] = current_record_row[i].z;
                    }
                }
	    }
	  else
	    {
              chrtr2_read_row (hnd, row, start_col, cols, current_record_row);

              for (int32_t i = 0 ; i < cols ; i++)
                {
                  if (current_record_row[i].status & CHRTR2_NULL)
                    {
                      current_row[i] = CHRTRNULL;
                    }
                  else
                    {
                      current_row[i] = current_record_row[i].z;
                    }
                }
	    }
	}


      //  Sunshade.

      if (row < end_row) hatchr (k, file_number, map, options, misc, current_row, next_row, start_row, row, cols, min_z, max_z, mbr);


      if (qApp->hasPendingEvents ())
	{
	  qApp->processEvents();
	  if (misc->drawing_canceled) break;
	}
    }


  //  Flush all of the saved fillRectangles from hatchr to screen

  map->flush ();


  //  Free allocated memory.

  free (next_row);
  free (current_row);
  free (current_record_row);


  chrtr2_close_file (hnd);


  if (misc->drawing_canceled) return (NVFalse);


  return (NVTrue);
}
