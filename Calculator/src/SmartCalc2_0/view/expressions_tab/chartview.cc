#include "chartview.h"

void ChartView::wheelEvent(QWheelEvent *event) {
  chart()->zoomReset();

  mFactor *= event->angleDelta().y() > 0 ? 0.5 : 2;

  QRectF rect = chart()->plotArea();
  QPointF c = chart()->plotArea().center();
  rect.setWidth(mFactor * rect.width());
  rect.moveCenter(c);
  chart()->zoomIn(rect);
  emit wheel_event(event);
  QChartView::wheelEvent(event);
}

void ChartView::mouseMoveEvent(QMouseEvent *event) {
    emit move_event(event);
    QChartView::mouseMoveEvent(event);}
