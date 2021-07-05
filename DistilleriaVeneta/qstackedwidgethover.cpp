#include "qstackedwidgethover.h"

void QStackedWidgetHover::hoverEnter(QHoverEvent *) { setCurrentIndex(1); }

void QStackedWidgetHover::hoverLeave(QHoverEvent *) { setCurrentIndex(0); }

void QStackedWidgetHover::hoverMove(QHoverEvent *) { setCurrentIndex(1); }

bool QStackedWidgetHover::event(QEvent *event) {
  switch (event->type()) {
    case QEvent::HoverEnter:
      hoverEnter(static_cast<QHoverEvent *>(event));
      return true;
      break;

    case QEvent::HoverLeave:
      hoverLeave(static_cast<QHoverEvent *>(event));
      return true;
      break;

    case QEvent::HoverMove:
      hoverMove(static_cast<QHoverEvent *>(event));
      return true;
      break;

    default:
      break;
  }
  return QWidget::event(event);
}

QStackedWidgetHover::QStackedWidgetHover(QProduct *p, QOverlay *o, QWidget *parent) : QStackedWidget(parent) {
  setMouseTracking(true);
  setAttribute(Qt::WA_Hover);
  addWidget(p);
  addWidget(o);
  setObjectName("qstackedhover");
}
