/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Qt Software Information (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class QStateMachine;
class QState;
QT_END_NAMESPACE
class GameOverTransition;
class TankItem;

class MainWindow: public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(bool started READ started WRITE setStarted)
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setStarted(bool b) { m_started = b; }
    bool started() const { return m_started; }

public slots:
    void addTank();
    void addRocket();
    void runStep();
    void gameOver();

signals:
    void mapFull();

private:
    void init();
    void addWall(const QRectF &wall);

    QGraphicsScene *m_scene;

    QStateMachine *m_machine;
    QState *m_runningState;
    GameOverTransition *m_gameOverTransition;

    QList<TankItem *> m_spawns;
    QTime m_time;

    bool m_started : 1;
};

#endif
