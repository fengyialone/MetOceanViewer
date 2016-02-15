//-------------------------------GPL-------------------------------------//
//
// MetOcean Viewer - A simple interface for viewing hydrodynamic model data
// Copyright (C) 2015  Zach Cobell
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// The name "MetOcean Viewer" is specific to this project and may not be
// used for projects "forked" or derived from this work.
//
//-----------------------------------------------------------------------//
#include <mov_qchartview.h>
#include <QtGui/QResizeEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QGraphicsTextItem>
#include <QtGui/QMouseEvent>
#include <QDateTime>

mov_QChartView::mov_QChartView(QWidget *parent) : QChartView(parent)
{
    setDragMode(QChartView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setMouseTracking(true);

    m_chart  = NULL;
    m_coord  = NULL;
    m_info   = NULL;
    m_style  = 0;

}

void mov_QChartView::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
        if(m_chart)
        {
            m_chart->resize(event->size());
            m_coord->setPos(m_chart->size().width()/2 - 100, m_chart->size().height() - 20);
        }
        if(m_info)
        {
            m_info->setPos(10,m_chart->size().height() - 50);
        }
    }
    QChartView::resizeEvent(event);
}

void mov_QChartView::mouseMoveEvent(QMouseEvent *event)
{
    QString   dateString;
    QDateTime date;
    qreal     x,y;

    if(this->m_coord)
    {
        x = this->m_chart->mapToValue(event->pos()).x();
        y = this->m_chart->mapToValue(event->pos()).y();
        if(x<this->x_axis_max && x>this->x_axis_min && y<this->y_axis_max && y>this->y_axis_min)
        {
            if(this->m_style==1)
            {
                date = QDateTime::fromMSecsSinceEpoch(x);
                date.setTimeSpec(Qt::UTC);
                dateString = QString("Date: ")+date.toString("MM/dd/yyyy hh:mm AP");
                this->m_coord->setText(dateString+QString("     Value: %1").arg(y));
            }
            else if(this->m_style==2)
                this->m_coord->setText(QString("Measured: %1     Modeled: %2     Diff: %3").arg(x).arg(y).arg(y-x));
        }
        else
        {
            this->m_coord->setText("");
        }
    }
    QChartView::mouseMoveEvent(event);
}
