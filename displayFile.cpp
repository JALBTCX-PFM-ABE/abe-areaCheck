
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



#include "displayFile.hpp"
#include "displayFileHelp.hpp"

displayFile::displayFile (QWidget * parent, OPTIONS *op, MISC *mi, int32_t type):
  QDialog (parent, (Qt::WindowFlags) Qt::WA_DeleteOnClose)
{
  options = op;
  misc = mi;
  k = type;


  QString title = tr ("areaCheck Display %1 Files").arg (misc->type_name[k]);
  setWindowTitle (title);


  setSizeGripEnabled (true);


  QVBoxLayout *vbox = new QVBoxLayout (this);
  vbox->setMargin (5);
  vbox->setSpacing (5);


  count = misc->num_overlays[k];


  displayTable = new QTableWidget (count, 2, this);
  displayTable->setWhatsThis (displayTableText);
  displayTable->setAlternatingRowColors (true);
  QTableWidgetItem *dItem = new QTableWidgetItem (tr ("Display"));
  displayTable->setHorizontalHeaderItem (0, dItem);
  dItem->setTextAlignment (Qt::AlignHCenter);
  QTableWidgetItem *fnItem = new QTableWidgetItem (tr ("File name"));
  displayTable->setHorizontalHeaderItem (1, fnItem);
  fnItem->setTextAlignment (Qt::AlignHCenter);


  displayed = (QCheckBox **) calloc (count, sizeof (QCheckBox *));
  vItem = (QTableWidgetItem **) calloc (count, sizeof (QTableWidgetItem *));
  origStatus = (uint8_t *) calloc (count, sizeof (uint8_t));
  newStatus = (uint8_t *) calloc (count, sizeof (uint8_t));


  displayGrp = new QButtonGroup (this);
  displayGrp->setExclusive (false);


  for (int32_t i = 0 ; i < count ; i++)
    {
      QString vh;
      vh.sprintf ("%d", i);
      vItem[i] = new QTableWidgetItem (vh);
      displayTable->setVerticalHeaderItem (i, vItem[i]);

      displayed[i] = new QCheckBox (this);
      displayTable->setCellWidget (i, 0, displayed[i]);
      displayGrp->addButton (displayed[i], i);

      QTableWidgetItem *fn = new QTableWidgetItem (QString (misc->overlays[k][i].filename));
      displayTable->setItem (i, 1, fn);
      fn->setFlags (Qt::ItemIsEnabled);

      if (misc->overlays[k][i].active)
        {
          displayed[i]->setCheckState (Qt::Checked);
          origStatus[i] = newStatus[i] = NVTrue;
        }
      else
        {
          displayed[i]->setCheckState (Qt::Unchecked);
          origStatus[i] = newStatus[i] = NVFalse;
        }
    }
  displayTable->resizeColumnsToContents ();
  displayTable->resizeRowsToContents ();


  vbox->addWidget (displayTable, 0, 0);


  //  Connect after populating table so the slot doesn't get called.

  connect (displayGrp, SIGNAL (buttonClicked (int)), this, SLOT (slotValueChanged (int)));


  int32_t width = qMin (800, displayTable->columnWidth (0) + displayTable->columnWidth (1) + 60);
  int32_t height = qMin (600, displayTable->rowHeight (0) * count + 75);
  resize (width, height);


  displayTable->show ();


  QHBoxLayout *actions = new QHBoxLayout (0);
  vbox->addLayout (actions);

  QPushButton *bHelp = new QPushButton (this);
  bHelp->setIcon (QIcon (":/icons/contextHelp.png"));
  bHelp->setToolTip (tr ("Enter What's This mode for help"));
  connect (bHelp, SIGNAL (clicked ()), this, SLOT (slotHelp ()));
  actions->addWidget (bHelp);

  actions->addStretch (10);

  QPushButton *applyButton = new QPushButton (tr ("Apply"), this);
  applyButton->setToolTip (tr ("Apply changes to display flags"));
  applyButton->setWhatsThis (applyDFText);
  connect (applyButton, SIGNAL (clicked ()), this, SLOT (slotApply ()));
  actions->addWidget (applyButton);

  QString closeTip = tr ("Close the Display ") + misc->type_name[k] + tr (" File Dialog");
  QString closeText = tr ("This button closes the Display %1 File dialog.  Any changes that have not been applied"
                          "by pressing the <b>Apply</b> button will be discarded.").arg (misc->type_name[k]);

  QPushButton *closeButton = new QPushButton (tr ("Close"), this);
  closeButton->setToolTip (closeTip);
  closeButton->setWhatsThis (closeText);
  connect (closeButton, SIGNAL (clicked ()), this, SLOT (slotClose ()));
  actions->addWidget (closeButton);


  show ();
}



displayFile::~displayFile ()
{
}



void
displayFile::slotHelp ()
{
  QWhatsThis::enterWhatsThisMode ();
}



void
displayFile::slotValueChanged (int row)
{
  if (displayed[row]->checkState () == Qt::Checked)
    {
      newStatus[row] = NVTrue;
    }
  else
    {
      newStatus[row] = NVFalse;
    }
}



void
displayFile::slotApply ()
{
  uint8_t changed = NVFalse;
  

  //  Check for a change in status.

  for (int16_t i = 0 ; i < count ; i++)
    {
      if (origStatus[i] != newStatus[i])
        {
          misc->overlays[k][i].active = newStatus[i];
	  origStatus[i] = newStatus[i];
          changed = NVTrue;
        }
    }



  if (changed) emit dataChangedSignal ();
}



void
displayFile::slotClose ()
{
  free (displayed);
  free (vItem);
  free (origStatus);
  free (newStatus);

  emit displayFileDialogClosedSignal (k);

  close ();
}
