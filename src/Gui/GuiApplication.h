/***************************************************************************
 *   Copyright (c) 2015 Werner Mayer <wmayer[at]users.sourceforge.net>     *
 *                                                                         *
 *   This file is part of the FreeCAD CAx development system.              *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Library General Public           *
 *   License as published by the Free Software Foundation; either          *
 *   version 2 of the License, or (at your option) any later version.      *
 *                                                                         *
 *   This library  is distributed in the hope that it will be useful,      *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Library General Public License for more details.                  *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this library; see the file COPYING.LIB. If not,    *
 *   write to the Free Software Foundation, Inc., 59 Temple Place,         *
 *   Suite 330, Boston, MA  02111-1307, USA                                *
 *                                                                         *
 ***************************************************************************/


#ifndef GUI_APPLICATION_H
#define GUI_APPLICATION_H

#include "GuiApplicationNativeEventAware.h"
#include <QList>

class QSessionManager;

namespace Gui
{
/** Override QCoreApplication::notify() to fetch exceptions in Qt widgets
 * properly that are not handled in the event handler or slot.
 */
class GUIApplication : public GUIApplicationNativeEventAware
{
    Q_OBJECT

public:
    explicit GUIApplication(int & argc, char ** argv, int exitcode);
    virtual ~GUIApplication();

    /**
     * Make forwarding events exception-safe and get more detailed information
     * where an unhandled exception comes from.
     */
    bool notify (QObject * receiver, QEvent * event);
    void commitData(QSessionManager &manager);

private:
    int systemExit;
};

class GUISingleApplication : public GUIApplication
{
    Q_OBJECT

public:
    explicit GUISingleApplication(int & argc, char ** argv, int exitcode);
    virtual ~GUISingleApplication();

    bool isRunning() const;
    bool sendMessage(const QByteArray &message, int timeout = 5000);

private Q_SLOTS:
    void receiveConnection();
    void processMessages();

Q_SIGNALS:
    void messageReceived(const QList<QByteArray> &);

private:
    class Private;
    QScopedPointer<Private> d_ptr;
};

}

#endif // GUI_APPLICATION_H
