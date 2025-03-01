/*
** Copyright (c) Alexis Megas.
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
** 3. The name of the author may not be used to endorse or promote products
**    derived from Porque without specific prior written permission.
**
** PORQUE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
** IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
** OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
** IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
** NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
** PORQUE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "porque-settings.h"

#include <QSettings>

porque_settings::porque_settings(QWidget *parent):QWidget(parent)
{
  m_ui.setupUi(this);
  restore();

  foreach(auto check_box, findChildren<QCheckBox *> ())
    connect(check_box,
	    SIGNAL(stateChanged(int)),
	    this,
	    SLOT(slot_check_box_state_changed(int)));

  foreach(auto combination_box, findChildren<QComboBox *> ())
    connect(combination_box,
	    SIGNAL(currentIndexChanged(int)),
	    this,
	    SLOT(slot_combination_box_current_index_changed(int)));
}

porque_settings::~porque_settings()
{
}

void porque_settings::restore(void)
{
  foreach(auto check_box, findChildren<QCheckBox *> ())
    {
      auto const key(QString("settings/%1").arg(check_box->objectName()));

      check_box->setChecked(QSettings().value(key).toInt());
    }

  foreach(auto combination_box, findChildren<QComboBox *> ())
    {
      auto const key
	(QString("settings/%1").arg(combination_box->objectName()));

      combination_box->setCurrentIndex
	(qBound(0,
		QSettings().value(key).toInt(),
		combination_box->count() - 1));
    }
}

void porque_settings::slot_check_box_state_changed(int state)
{
  auto check_box = qobject_cast<QCheckBox *> (sender());

  if(!check_box)
    return;

  QSettings().setValue
    (QString("settings/%1").arg(check_box->objectName()), state);
}

void porque_settings::slot_combination_box_current_index_changed(int index)
{
  auto combination_box = qobject_cast<QComboBox *> (sender());

  if(!combination_box)
    return;

  QSettings().setValue
    (QString("settings/%1").arg(combination_box->objectName()), index);
}
