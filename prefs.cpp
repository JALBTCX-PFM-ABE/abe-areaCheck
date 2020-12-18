
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



#include "prefs.hpp"
#include "prefsHelp.hpp"

prefs::prefs (QWidget * parent, OPTIONS *op, MISC *mi):
  QDialog (parent, (Qt::WindowFlags) Qt::WA_DeleteOnClose)
{
  options = op;
  mod_options = *options;
  misc = mi;
  dataChanged = NVFalse;


  setWindowTitle (tr ("areaCheck preferences"));


  QVBoxLayout *vbox = new QVBoxLayout (this);
  vbox->setMargin (5);
  vbox->setSpacing (5);


  QGroupBox *fbox = new QGroupBox (tr ("Position Format"), this);
  fbox->setWhatsThis (bGrpText);

  QRadioButton *hdms = new QRadioButton (tr ("Hemisphere Degrees Minutes Seconds.decimal"));
  QRadioButton *hdm_ = new QRadioButton (tr ("Hemisphere Degrees Minutes.decimal"));
  QRadioButton *hd__ = new QRadioButton (tr ("Hemisphere Degrees.decimal"));
  QRadioButton *sdms = new QRadioButton (tr ("+/-Degrees Minutes Seconds.decimal"));
  QRadioButton *sdm_ = new QRadioButton (tr ("+/-Degrees Minutes.decimal"));
  QRadioButton *sd__ = new QRadioButton (tr ("+/-Degrees.decimal"));

  bGrp = new QButtonGroup (this);
  bGrp->setExclusive (true);
  connect (bGrp, SIGNAL (buttonClicked (int)), this, SLOT (slotPositionClicked (int)));

  bGrp->addButton (hdms, 0);
  bGrp->addButton (hdm_, 1);
  bGrp->addButton (hd__, 2);
  bGrp->addButton (sdms, 3);
  bGrp->addButton (sdm_, 4);
  bGrp->addButton (sd__, 5);

  QHBoxLayout *fboxSplit = new QHBoxLayout;
  QVBoxLayout *fboxLeft = new QVBoxLayout;
  QVBoxLayout *fboxRight = new QVBoxLayout;
  fboxSplit->addLayout (fboxLeft);
  fboxSplit->addLayout (fboxRight);
  fboxLeft->addWidget (hdms);
  fboxLeft->addWidget (hdm_);
  fboxLeft->addWidget (hd__);
  fboxRight->addWidget (sdms);
  fboxRight->addWidget (sdm_);
  fboxRight->addWidget (sd__);
  fbox->setLayout (fboxSplit);

  vbox->addWidget (fbox, 1);


  QGroupBox *cbox = new QGroupBox (tr ("Colors"), this);
  QHBoxLayout *cboxSplit = new QHBoxLayout;
  cbox->setLayout (cboxSplit);
  QVBoxLayout *cboxLeft = new QVBoxLayout;
  QVBoxLayout *cboxRight = new QVBoxLayout;
  cboxSplit->addLayout (cboxLeft);
  cboxSplit->addLayout (cboxRight);


  bCoastColor = new QPushButton (tr ("Coast"), this);
  bCoastPalette = bCoastColor->palette ();
  bCoastColor->setToolTip (tr ("Change coastline color"));
  bCoastColor->setWhatsThis (coastColorText);
  connect (bCoastColor, SIGNAL (clicked ()), this, SLOT (slotCoastColor ()));
  cboxLeft->addWidget (bCoastColor);


  bBackgroundColor = new QPushButton (tr ("Background"), this);
  bBackgroundPalette = bBackgroundColor->palette ();
  bBackgroundColor->setToolTip (tr ("Change display background color"));
  bBackgroundColor->setWhatsThis (backgroundColorText);
  connect (bBackgroundColor, SIGNAL (clicked ()), this, SLOT (slotBackgroundColor ()));
  cboxRight->addWidget (bBackgroundColor);


  bHighlightColor = new QPushButton (tr ("Highlight"), this);
  bHighlightPalette = bHighlightColor->palette ();
  bHighlightColor->setToolTip (tr ("Change highlight color"));
  bHighlightColor->setWhatsThis (highlightColorText);
  connect (bHighlightColor, SIGNAL (clicked ()), this, SLOT (slotHighlightColor ()));
  cboxRight->addWidget (bHighlightColor);


  vbox->addWidget (cbox, 1);


  QGroupBox *c2box = new QGroupBox (tr ("Data Type Colors"), this);
  c2box->setWhatsThis (colorGrpText);

  c2[0] = new QPushButton (misc->type_name[ISS60_AREA], this);
  c2Palette[0] = c2[0]->palette ();
  c2[1] = new QPushButton (misc->type_name[GENERIC_AREA], this);
  c2Palette[1] = c2[1]->palette ();
  c2[2] = new QPushButton (misc->type_name[ACE_AREA], this);
  c2Palette[2] = c2[2]->palette ();
  c2[3] = new QPushButton (misc->type_name[ISS60_ZONE], this);
  c2Palette[3] = c2[3]->palette ();
  c2[4] = new QPushButton (misc->type_name[GENERIC_ZONE], this);
  c2Palette[4] = c2[4]->palette ();
  c2[5] = new QPushButton (misc->type_name[SHAPE], this);
  c2Palette[5] = c2[5]->palette ();
  c2[6] = new QPushButton (misc->type_name[TRACK], this);
  c2Palette[6] = c2[6]->palette ();
  c2[7] = new QPushButton (misc->type_name[FEATURE], this);
  c2Palette[7] = c2[7]->palette ();
  c2[8] = new QPushButton (misc->type_name[YXZ], this);
  c2Palette[8] = c2[8]->palette ();
  c2[9] = new QPushButton (misc->type_name[LLZ_DATA], this);
  c2Palette[9] = c2[9]->palette ();
  c2[10] = new QPushButton (misc->type_name[GEOTIFF], this);
  c2Palette[10] = c2[10]->palette ();
  c2[11] = new QPushButton (misc->type_name[CHRTR], this);
  c2Palette[11] = c2[11]->palette ();
  c2[12] = new QPushButton (misc->type_name[BAG], this);
  c2Palette[12] = c2[12]->palette ();
  c2[13] = new QPushButton (misc->type_name[OPTECH_FLT], this);
  c2Palette[13] = c2[13]->palette ();


  colorGrp = new QButtonGroup (c2box);
  colorGrp->setExclusive (false);
  connect (colorGrp, SIGNAL (buttonClicked (int)), this, SLOT (slotColor (int)));

  colorGrp->addButton (c2[0], ISS60_AREA);
  colorGrp->addButton (c2[1], GENERIC_AREA);
  colorGrp->addButton (c2[2], ACE_AREA);
  colorGrp->addButton (c2[3], ISS60_ZONE);
  colorGrp->addButton (c2[4], GENERIC_ZONE);
  colorGrp->addButton (c2[5], SHAPE);
  colorGrp->addButton (c2[6], TRACK);
  colorGrp->addButton (c2[7], FEATURE);
  colorGrp->addButton (c2[8], YXZ);
  colorGrp->addButton (c2[9], LLZ_DATA);
  colorGrp->addButton (c2[10], GEOTIFF);
  colorGrp->addButton (c2[11], CHRTR);
  colorGrp->addButton (c2[12], BAG);
  colorGrp->addButton (c2[13], OPTECH_FLT);

  QHBoxLayout *c2boxSplit = new QHBoxLayout;
  QVBoxLayout *c2boxLeft = new QVBoxLayout;
  QVBoxLayout *c2boxRight = new QVBoxLayout;
  c2boxSplit->addLayout (c2boxLeft);
  c2boxSplit->addLayout (c2boxRight);
  c2boxLeft->addWidget (c2[0]);
  c2boxLeft->addWidget (c2[1]);
  c2boxLeft->addWidget (c2[2]);
  c2boxLeft->addWidget (c2[3]);
  c2boxLeft->addWidget (c2[4]);
  c2boxLeft->addWidget (c2[5]);
  c2boxLeft->addWidget (c2[6]);
  c2boxRight->addWidget (c2[7]);
  c2boxRight->addWidget (c2[8]);
  c2boxRight->addWidget (c2[9]);
  c2boxRight->addWidget (c2[10]);
  c2boxRight->addWidget (c2[11]);
  c2boxRight->addWidget (c2[12]);
  c2boxRight->addWidget (c2[13]);
  c2box->setLayout (c2boxSplit);

  vbox->addWidget (c2box, 1);


  QGroupBox *sunBox = new QGroupBox (tr ("CHRTR/BAG Sun Shading"), this);
  QHBoxLayout *sunBoxLayout = new QHBoxLayout;
  sunBox->setLayout (sunBoxLayout);

  QGroupBox *angBox = new QGroupBox (tr ("Angle"), this);
  QHBoxLayout *angBoxLayout = new QHBoxLayout;
  angBox->setLayout (angBoxLayout);
  sunAz = new QDoubleSpinBox (angBox);
  sunAz->setDecimals (1);
  sunAz->setRange (0.0, 359.9);
  sunAz->setSingleStep (1.0);
  sunAz->setValue (mod_options.sunopts.azimuth);
  sunAz->setWrapping (true);
  sunAz->setToolTip (tr ("Change the sun angle (0.0-360.0)"));
  sunAz->setWhatsThis (sunAzText);
  angBoxLayout->addWidget (sunAz);
  sunBoxLayout->addWidget (angBox);


  QGroupBox *eleBox = new QGroupBox (tr ("Elevation"), this);
  QHBoxLayout *eleBoxLayout = new QHBoxLayout;
  eleBox->setLayout (eleBoxLayout);
  sunEl = new QDoubleSpinBox (eleBox);
  sunEl->setDecimals (1);
  sunEl->setRange (0.0, 90.0);
  sunEl->setSingleStep (1.0);
  sunEl->setValue (mod_options.sunopts.elevation);
  sunEl->setWrapping (true);
  sunEl->setToolTip (tr ("Change the sun elevation (0.0-90.0)"));
  sunEl->setWhatsThis (sunElText);
  eleBoxLayout->addWidget (sunEl);
  sunBoxLayout->addWidget (eleBox);


  QGroupBox *exaBox = new QGroupBox (tr ("Exaggeration"), this);
  QHBoxLayout *exaBoxLayout = new QHBoxLayout;
  exaBox->setLayout (exaBoxLayout);
  sunEx = new QDoubleSpinBox (exaBox);
  sunEx->setDecimals (1);
  sunEx->setRange (0.0, 359.9);
  sunEx->setSingleStep (1.0);
  sunEx->setValue (mod_options.sunopts.exag);
  sunEx->setWrapping (true);
  sunEx->setToolTip (tr ("Change the sun Z exaggeration (1-10)"));
  sunEx->setWhatsThis (sunExText);
  exaBoxLayout->addWidget (sunEx);
  sunBoxLayout->addWidget (exaBox);


  vbox->addWidget (sunBox, 1);


  QGroupBox *mbox = new QGroupBox (tr ("MINMAX parameters"), this);
  mbox->setWhatsThis (colorGrpText);
  QHBoxLayout *mboxLayout = new QHBoxLayout;
  mbox->setLayout (mboxLayout);

  QGroupBox *sBox = new QGroupBox (tr ("Use stoplight colors"), this);
  QHBoxLayout *sBoxLayout = new QHBoxLayout;
  sBox->setLayout (sBoxLayout);
  stopLight = new QCheckBox (this);
  connect (stopLight, SIGNAL (clicked ()), this, SLOT (slotStopLightClicked ()));
  stopLight->setToolTip (tr ("Use stoplight colors when displaying MINMAX .trk files"));
  stopLight->setWhatsThis (stopLightText);
  sBoxLayout->addWidget (stopLight);
  mboxLayout->addWidget (sBox);

  QGroupBox *gBox = new QGroupBox (tr ("Green to yellow value"), this);
  QHBoxLayout *gBoxLayout = new QHBoxLayout;
  gBox->setLayout (gBoxLayout);
  minStop = new QLineEdit (this);
  mboxLayout->addWidget (minStop);
  minStop->setToolTip (tr ("Set value below which data is green"));
  minStop->setWhatsThis (minStopText);
  gBoxLayout->addWidget (minStop);
  mboxLayout->addWidget (gBox);

  QGroupBox *yBox = new QGroupBox (tr ("Yellow to red value"), this);
  QHBoxLayout *yBoxLayout = new QHBoxLayout;
  yBox->setLayout (yBoxLayout);
  maxStop = new QLineEdit (this);
  mboxLayout->addWidget (maxStop);
  maxStop->setToolTip (tr ("Set value above which data is red"));
  maxStop->setWhatsThis (maxStopText);
  yBoxLayout->addWidget (maxStop);
  mboxLayout->addWidget (yBox);


  vbox->addWidget (mbox, 1);


  setFields ();


  QHBoxLayout *actions = new QHBoxLayout (0);
  vbox->addLayout (actions);

  QPushButton *bHelp = new QPushButton (this);
  bHelp->setIcon (QIcon (":/icons/contextHelp.png"));
  bHelp->setToolTip (tr ("Enter What's This mode for help"));
  connect (bHelp, SIGNAL (clicked ()), this, SLOT (slotHelp ()));
  actions->addWidget (bHelp);

  actions->addStretch (10);

  bRestoreDefaults = new QPushButton (tr ("Restore Defaults"), this);
  bRestoreDefaults->setToolTip (tr ("Restore all preferences to the default state"));
  bRestoreDefaults->setWhatsThis (restoreDefaultsText);
  connect (bRestoreDefaults, SIGNAL (clicked ()), this, SLOT (slotRestoreDefaults ()));
  actions->addWidget (bRestoreDefaults);

  QPushButton *applyButton = new QPushButton (tr ("OK"), this);
  applyButton->setToolTip (tr ("Accept changes and close dialog"));
  applyButton->setWhatsThis (applyPrefsText);
  connect (applyButton, SIGNAL (clicked ()), this, SLOT (slotApplyPrefs ()));
  actions->addWidget (applyButton);

  QPushButton *closeButton = new QPushButton (tr ("Cancel"), this);
  closeButton->setToolTip (tr ("Discard changes and close dialog"));
  closeButton->setWhatsThis (closePrefsText);
  connect (closeButton, SIGNAL (clicked ()), this, SLOT (slotClosePrefs ()));
  actions->addWidget (closeButton);


  show ();
}



prefs::~prefs ()
{
}



void
prefs::slotCoastColor ()
{
  QColor clr;

  clr = QColorDialog::getColor (mod_options.coast_color, this, tr ("areaCheck Coastline Color"), QColorDialog::ShowAlphaChannel);

  if (clr.isValid ()) mod_options.coast_color = clr;

  setFields ();
}



void
prefs::slotBackgroundColor ()
{
  QColor clr;

  clr = QColorDialog::getColor (mod_options.background_color, this, tr ("areaCheck Background Color"));

  if (clr.isValid ()) mod_options.background_color = clr;

  setFields ();
}



void
prefs::slotColor (int id)
{
  QString name;


  switch (id)
    {
    case 0:
      name = tr ("ISS-60 Area File");
      break;

    case 1:
      name = tr ("Generic Area File");
      break;

    case 2:
      name = tr ("ACE Area File");
      break;

    case 3:
      name = tr ("ISS-60 Zone File");
      break;

    case 4:
      name = tr ("Generic Zone File");
      break;

    case 5:
      name = tr ("Shape File");
      break;

    case 6:
      name = tr ("Track File");
      break;

    case 7:
      name = tr ("Feature File");
      break;

    case 8:
      name = tr ("YXZ File");
      break;

    case 9:
      name = tr ("LLZ File");
      break;

    case 10:
      name = tr ("GeoTIFF File");
      break;

    case 11:
      name = tr ("CHRTR File");
      break;

    case 12:
      name = tr ("BAG File");
      break;

    case 13:
      name = tr ("Optech Flightline File");
      break;
    }

  QColor clr;

  clr = QColorDialog::getColor (mod_options.color[id], this, tr ("areaCheck %1 Color").arg (name), QColorDialog::ShowAlphaChannel);

  if (clr.isValid ()) mod_options.color[id] = clr;

  setFields ();
}



void
prefs::slotHighlightColor ()
{
  QColor clr;

  clr = QColorDialog::getColor (mod_options.highlight_color, this, tr ("areaCheck Highlight Color"), QColorDialog::ShowAlphaChannel);

  if (clr.isValid ()) mod_options.highlight_color = clr;

  setFields ();
}



void
prefs::slotHelp ()
{
  QWhatsThis::enterWhatsThisMode ();
}



void
prefs::slotRestoreDefaults ()
{
  void set_defaults (MISC *misc, OPTIONS *options, uint8_t restore);


  set_defaults (misc, options, NVTrue);


  mod_options = *options;


  setFields ();


  emit dataChangedSignal (NVTrue);


  close ();
}



void
prefs::slotPositionClicked (int id)
{
  mod_options.position_form = id;
}



void 
prefs::setFields ()
{
  QString string;


  bGrp->button (mod_options.position_form)->setChecked (true);


  int32_t hue, sat, val;

  mod_options.coast_color.getHsv (&hue, &sat, &val);
  if (val < 128)
    {
      bCoastPalette.setColor (QPalette::Normal, QPalette::ButtonText, Qt::white);
      bCoastPalette.setColor (QPalette::Inactive, QPalette::ButtonText, Qt::white);
    }
  else
    {
      bCoastPalette.setColor (QPalette::Normal, QPalette::ButtonText, Qt::black);
      bCoastPalette.setColor (QPalette::Inactive, QPalette::ButtonText, Qt::black);
    }
  bCoastPalette.setColor (QPalette::Normal, QPalette::Button, mod_options.coast_color);
  bCoastPalette.setColor (QPalette::Inactive, QPalette::Button, mod_options.coast_color);
  bCoastColor->setPalette (bCoastPalette);


  mod_options.background_color.getHsv (&hue, &sat, &val);
  if (val < 128)
    {
      bBackgroundPalette.setColor (QPalette::Normal, QPalette::ButtonText, Qt::white);
      bBackgroundPalette.setColor (QPalette::Inactive, QPalette::ButtonText, Qt::white);
    }
  else
    {
      bBackgroundPalette.setColor (QPalette::Normal, QPalette::ButtonText, Qt::black);
      bBackgroundPalette.setColor (QPalette::Inactive, QPalette::ButtonText, Qt::black);
    }
  bBackgroundPalette.setColor (QPalette::Normal, QPalette::Button, mod_options.background_color);
  bBackgroundPalette.setColor (QPalette::Inactive, QPalette::Button, mod_options.background_color);
  bBackgroundColor->setPalette (bBackgroundPalette);


  for (int32_t i = 0 ; i < NUM_TYPES ; i++)
    {
      mod_options.color[i].getHsv (&hue, &sat, &val);
      if (i != GEOTIFF && i != CHRTR && i != BAG && val < 128)
        {
          c2Palette[i].setColor (QPalette::Normal, QPalette::ButtonText, Qt::white);
          c2Palette[i].setColor (QPalette::Inactive, QPalette::ButtonText, Qt::white);
        }
      else
        {
          c2Palette[i].setColor (QPalette::Normal, QPalette::ButtonText, Qt::black);
          c2Palette[i].setColor (QPalette::Inactive, QPalette::ButtonText, Qt::black);
        }
      c2Palette[i].setColor (QPalette::Normal, QPalette::Button, mod_options.color[i]);
      c2Palette[i].setColor (QPalette::Inactive, QPalette::Button, mod_options.color[i]);
      c2[i]->setPalette (c2Palette[i]);
    }


  mod_options.highlight_color.getHsv (&hue, &sat, &val);
  if (val < 128)
    {
      bHighlightPalette.setColor (QPalette::Normal, QPalette::ButtonText, Qt::white);
      bHighlightPalette.setColor (QPalette::Inactive, QPalette::ButtonText, Qt::white);
    }
  else
    {
      bHighlightPalette.setColor (QPalette::Normal, QPalette::ButtonText, Qt::black);
      bHighlightPalette.setColor (QPalette::Inactive, QPalette::ButtonText, Qt::black);
    }
  bHighlightPalette.setColor (QPalette::Normal, QPalette::Button, mod_options.highlight_color);
  bHighlightPalette.setColor (QPalette::Inactive, QPalette::Button, mod_options.highlight_color);
  bHighlightColor->setPalette (bHighlightPalette);


  sunAz->setValue (mod_options.sunopts.azimuth);
  sunEl->setValue (mod_options.sunopts.elevation);
  sunEx->setValue (mod_options.sunopts.exag);
  mod_options.sunopts.sun = sun_unv (mod_options.sunopts.azimuth, mod_options.sunopts.elevation);


  stopLight->setChecked (mod_options.stoplight);

  QString tmp;

  tmp = QString ("%L1").arg (mod_options.minstop, 0, 'f', 2);
  minStop->setText (tmp);
  tmp = QString ("%L1").arg (mod_options.maxstop, 0, 'f', 2);
  maxStop->setText (tmp);
}


void 
prefs::slotStopLightClicked ()
{
  if (stopLight->isChecked ())
    {
      mod_options.stoplight = NVTrue;
    }
  else
    {
      mod_options.stoplight = NVFalse;
    }
}


void
prefs::slotApplyPrefs ()
{
  if (mod_options.position_form != options->position_form) dataChanged = NVTrue;

  if (mod_options.stoplight != options->stoplight) dataChanged = NVTrue;

  sscanf (minStop->text ().toLatin1 (), "%f", &mod_options.minstop);
  if (mod_options.minstop != options->minstop) dataChanged = NVTrue;

  sscanf (maxStop->text ().toLatin1 (), "%f", &mod_options.maxstop);
  if (mod_options.maxstop != options->maxstop) dataChanged = NVTrue;

  mod_options.sunopts.azimuth = sunAz->value ();
  if (mod_options.sunopts.azimuth != options->sunopts.azimuth) dataChanged = NVTrue;
  mod_options.sunopts.elevation = sunEl->value ();
  if (mod_options.sunopts.elevation != options->sunopts.elevation) dataChanged = NVTrue;
  mod_options.sunopts.exag = sunEx->value ();
  if (mod_options.sunopts.exag != options->sunopts.exag) dataChanged = NVTrue;


  mod_options.sunopts.sun = sun_unv (mod_options.sunopts.azimuth, mod_options.sunopts.elevation);


  if (mod_options.coast_color != options->coast_color) dataChanged = NVTrue;
  if (mod_options.background_color != options->background_color) dataChanged = NVTrue;
  if (mod_options.highlight_color != options->highlight_color) dataChanged = NVTrue;

  for (int32_t i = 0 ; i < NUM_TYPES ; i++)
    {
      if (mod_options.color[i] != options->color[i]) dataChanged = NVTrue;
    }


  if (mod_options.color[CHRTR] != options->color[CHRTR] || mod_options.color[BAG] != options->color[BAG])
    {
      //  Redefine the surface colors because the CHRTR/BAG alpha value has changed..

      float hue_inc = 315.0 / (float) (NUMHUES + 1);

      for (int32_t i = 0 ; i < NUMHUES ; i++)
        {
          for (int32_t j = 0 ; j < NUMSHADES ; j++)
            {
              misc->color_array[i][j].setHsv ((int32_t) (((NUMHUES + 1) - i) * hue_inc), 255, j, mod_options.color[CHRTR].alpha ());
            }
        }
      dataChanged = NVTrue;
    }


  setFields ();


  if (dataChanged)
    {
      *options = mod_options;

      emit dataChangedSignal (NVTrue);
    }

  close ();
}


void
prefs::slotClosePrefs ()
{
  close ();
}
