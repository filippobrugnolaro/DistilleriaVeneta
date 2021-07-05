#ifndef QSTACKEDWIDGETHOVER_H
#define QSTACKEDWIDGETHOVER_H

#include <QEvent>
#include <QHoverEvent>
#include <QStackedWidget>
#include <QWidget>

#include "overlay.h"
#include "qproduct.h"

class QStackedWidgetHover : public QStackedWidget {
  Q_OBJECT
 protected:
  /**
   * @brief definizione evento all'entrata del mouse
   */
  void hoverEnter(QHoverEvent*);

  /**
   * @brief definizione evento all'uscita del mouse
   */
  void hoverLeave(QHoverEvent*);

  /**
   * @brief definizione evento durante il movimento del mouse
   */
  void hoverMove(QHoverEvent*);

  /**
   * @brief event
   * @return bool, 'true' sse l'evento viene riconosciuto, 'false' altrimenti
   */
  bool event(QEvent*);

 public:
  /**
   * @brief costruttore di QStackedWidgetHover
   * @param p : QProduct*, puntatore al prodotto che si vuole aggiungere
   * @param o : QOverlay*, puntatore all'overlay che si vuole aggiungere
   * @param parent : QStackedWidget*, puntatore al parent, default = nullptr
   */
  explicit QStackedWidgetHover(QProduct*, QOverlay*, QWidget* = nullptr);
};

#endif  // QSTACKEDWIDGETHOVER_H
