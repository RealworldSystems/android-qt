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

#ifndef QANIMATION_P_H
#define QANIMATION_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of QIODevice. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qvariantanimation.h"
#include <QtCore/qeasingcurve.h>
#include <QtCore/qmetaobject.h>
#include <QtCore/qvector.h>

#include "qabstractanimation_p.h"

QT_BEGIN_NAMESPACE

class QVariantAnimationPrivate : public QAbstractAnimationPrivate
{
    Q_DECLARE_PUBLIC(QVariantAnimation)
public:

    QVariantAnimationPrivate() : duration(250), hasStartValue(false)
    {
    }

    void init()
    {
        //we keep the mask so that we emit valueChanged only when needed (for performance reasons)
        changedSignalMask = (1 << q_func()->metaObject()->indexOfSignal("valueChanged(QVariant)"));
        currentInterval.start.first = currentInterval.end.first = 2; //will force the initial refresh
        interpolator = 0;
    }

    static QVariantAnimationPrivate *get(QVariantAnimation *q)
    {
        return q->d_func();
    }

    void setDefaultStartValue(const QVariant &value);

    int duration;
    QEasingCurve easing;

    QVariantAnimation::KeyValues keyValues;
    QVariant currentValue;
    QVariant defaultStartValue;
    bool hasStartValue;

    //this is used to keep track of the KeyValue interval in which we currently are
    struct
    {
        QVariantAnimation::KeyValue start, end;
    } currentInterval;

    mutable QVariantAnimation::Interpolator interpolator;

    quint32 changedSignalMask;

    void setCurrentValueForProgress(const qreal progress);
    void recalculateCurrentInterval(bool force=false);
    void setValueAt(qreal, const QVariant &);
    QVariant valueAt(qreal step) const;
    void convertValues(int t);

    static QVariantAnimation::Interpolator getInterpolator(int interpolationType);
};

//this should make the interpolation faster
template<typename T> inline T _q_interpolate(const T &f, const T &t, qreal progress)
{
    return T(f + (t - f) * progress);
}

template<typename T > inline QVariant _q_interpolateVariant(const T &from, const T &to, qreal progress)
{
    return _q_interpolate(from, to, progress);
}


QT_END_NAMESPACE

#endif //QANIMATION_P_H