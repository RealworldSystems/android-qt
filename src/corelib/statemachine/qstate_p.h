/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the either Technology Preview License Agreement or the
** Beta Release License Agreement.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QSTATE_P_H
#define QSTATE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qabstractstate_p.h"

#include <QtCore/qlist.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qvariant.h>

QT_BEGIN_NAMESPACE

struct QPropertyAssignment
{
    QPropertyAssignment()
        : object(0) {}
    QPropertyAssignment(QObject *o, const QByteArray &n,
                        const QVariant &v, bool es = true)
        : object(o), propertyName(n), value(v), explicitlySet(es)
        {}
    QObject *object;
    QByteArray propertyName;
    QVariant value;
    bool explicitlySet;
};

class QAbstractTransition;
class QHistoryState;

class QState;
class Q_CORE_EXPORT QStatePrivate : public QAbstractStatePrivate
{
    Q_DECLARE_PUBLIC(QState)
public:
    QStatePrivate();
    ~QStatePrivate();

    static QStatePrivate *get(QState *q);
    static const QStatePrivate *get(const QState *q);

    QList<QAbstractState*> childStates() const;
    QList<QHistoryState*> historyStates() const;
    QList<QAbstractTransition*> transitions() const;

    void emitFinished();
    void emitPolished();

    QAbstractState *errorState;
    QAbstractState *initialState;
    QState::ChildMode childMode;

    QList<QPropertyAssignment> propertyAssignments;
};

QT_END_NAMESPACE

#endif