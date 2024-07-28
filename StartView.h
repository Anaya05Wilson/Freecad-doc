// SPDX-License-Identifier: LGPL-2.1-or-later
/****************************************************************************
 *                                                                          *
 *   Copyright (c) 2024 The FreeCAD Project Association AISBL               *
 *                                                                          *
 *   This file is part of FreeCAD.                                          *
 *                                                                          *
 *   FreeCAD is free software: you can redistribute it and/or modify it     *
 *   under the terms of the GNU Lesser General Public License as            *
 *   published by the Free Software Foundation, either version 2.1 of the   *
 *   License, or (at your option) any later version.                        *
 *                                                                          *
 *   FreeCAD is distributed in the hope that it will be useful, but         *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of             *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU       *
 *   Lesser General Public License for more details.                        *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with FreeCAD. If not, see                                *
 *   <https://www.gnu.org/licenses/>.                                       *
 *                                                                          *
 ***************************************************************************/

#ifndef FREECAD_STARTVIEW_H
#define FREECAD_STARTVIEW_H

#include <Mod/Start/StartGlobal.h>
#include <Base/Type.h>
#include <Gui/MDIView.h>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QGridLayout>
#include <QListView>
#include <QScrollArea>

#include "../App/DisplayedFilesModel.h"
#include "../App/RecentFilesModel.h"
#include "../App/ExamplesModel.h"

// Define the ClickableLabel class
class ClickableLabel : public QLabel {
    Q_OBJECT

public:
    explicit ClickableLabel(QWidget* parent = nullptr) : QLabel(parent) {}

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        QLabel::mousePressEvent(event);
        emit clicked();
    }
};

// Custom QPushButton that contains a ClickableLabel
class MyPushButton : public QPushButton {
    Q_OBJECT

public:
    MyPushButton(const QString& text, QWidget* parent = nullptr) : QPushButton(parent) {
        auto* label = new ClickableLabel(this);
        label->setText(text);
        label->setAlignment(Qt::AlignCenter);

        // Connect the label's clicked signal to the button's clicked slot
        connect(label, &ClickableLabel::clicked, this, &QPushButton::clicked);
    }
};

namespace StartGui {

class StartView : public QWidget {
    Q_OBJECT

public:
    explicit StartView(QWidget* parent = nullptr);
    ~StartView();

private slots:
    void newEmptyFile();
    void openExistingFile();
    void newPartDesignFile();
    void newAssemblyFile();
    void newDraftFile();
    void newArchFile();

private:
    struct NewButton {
        QString heading;
        QString description;
        QString iconPath;
    };

    gsl::owner<QPushButton*> createNewButton(const NewButton& newButton, StartView* view, void (StartView::*slot)());
    void configureNewFileButtons(QLayout* layout);
};

} // namespace StartGui

#endif  // FREECAD_STARTVIEW_
