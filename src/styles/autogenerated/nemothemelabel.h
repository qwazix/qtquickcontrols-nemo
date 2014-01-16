/*
 * Copyright (C) 2013 Lucien Xu <sfietkonstantin@free.fr>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

// This class is autogenerated using themehelper.py
// Any modification done in this file will be overridden

#ifndef NEMOTHEMELABEL_H
#define NEMOTHEMELABEL_H

#include <QtCore/QObject>
#include <QtGui/QColor>

class NemoThemeLabel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(int pointSize READ pointSize NOTIFY pointSizeChanged)
public:
    explicit NemoThemeLabel(QObject *parent = 0);
    QColor color() const;
    void setColor(const QColor &color);
    int pointSize() const;
    void setPointSize(int pointSize);
    void setPointSizeDefault();
Q_SIGNALS:
    void colorChanged();
    void pointSizeChanged();
private:
    QColor m_color;
    int m_pointSize;
};

#endif //NEMOTHEMELABEL_H
