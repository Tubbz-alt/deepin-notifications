/*
 * Copyright (C) 2014 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BUBBLE_H
#define BUBBLE_H

#include <QFrame>
#include <DBlurEffectWidget>
#include <QStandardPaths>
#include <QDir>
#include <DPlatformWindowHandle>
#include <DWindowManagerHelper>
#include <QDBusArgument>

DWIDGET_USE_NAMESPACE

class QLabel;
class AppIcon;
class QPropertyAnimation;
class QParallelAnimationGroup;
class NotificationEntity;
class ActionButton;
class AppBody;
class QGraphicsDropShadowEffect;

static const QStringList Directory = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
static const QString CachePath = Directory.first() + "/.cache/deepin/deepin-notifications/";

class Bubble : public DBlurEffectWidget
{
    Q_OBJECT
public:
    Bubble(NotificationEntity *entity=0);

    void setBasePosition(int,int, QRect = QRect());

    NotificationEntity *entity() const;
    void setEntity(NotificationEntity *entity);


signals:
    void expired(int);
    void dismissed(int);
    void replacedByOther(int);
    void actionInvoked(uint, QString);

public slots:
    QPoint getCursorPos();
    void setMask(int, int, int, int);
    void closeButtonClicked();
    void compositeChanged();
    void onDelayQuit();

protected:
    void mousePressEvent(QMouseEvent *) Q_DECL_OVERRIDE;
    void moveEvent(QMoveEvent *) Q_DECL_OVERRIDE;
    void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
    void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

private:
    NotificationEntity *m_entity;

    AppIcon *m_icon = nullptr;
    AppBody *m_body = nullptr;
    ActionButton *m_actionButton = nullptr;

    QPropertyAnimation *m_inAnimation = nullptr;
    QPropertyAnimation *m_outAnimation = nullptr;
    QTimer *m_outTimer = nullptr;
    DPlatformWindowHandle *m_handle;
    DWindowManagerHelper *m_wmHelper;

    bool m_offScreen = true;
    QRect m_screenGeometry;
    QTimer *m_quitTimer;

    void updateContent();
    void initUI();
    void initAnimations();
    void initTimers();
    bool containsMouse() const;

    void processActions();
    void processIconData();

    void saveImg(const QImage &image);
    const QPixmap converToPixmap(const QDBusArgument &value);
};

#endif // BUBBLE_H
