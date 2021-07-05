#ifndef GRIDSHOW_H
#define GRIDSHOW_H

#include <QFrame>
#include <QGridLayout>
#include <QScrollArea>
#include <QWidget>
#include <functional>

#include "./Hierarchy/product.h"
#include "./Utilities/deep_ptr.hpp"
#include "./Utilities/u_vector.hpp"
#include "overlay.h"
#include "qproduct.h"
#include "qstackedwidgethover.h"

class QGridShow : public QWidget {
  Q_OBJECT
 private:
  QVBoxLayout* main_layout;
  QScrollArea* product_area;
  QFrame* contenitore;
  QGridLayout* grid;
  QList<QStackedWidgetHover*> lista_prodotti;

  /**
   * @brief metodo per eliminare tutti gli elementi della griglia
   */
  void clear_grid();

 public:
  /**
   * @brief costruttore di QGridShow
   * @param parent : QWidget*, puntatore al padre, default = nullptr
   */
  QGridShow(QWidget* = nullptr);

  /**
   * @brief metodo per aggiornare la griglia dei prodotti
   * @param _products : const u_vector<deep_ptr<product>>&, indirizzo del vettore dei prodotti inseribili nello scontrino
   * @param bind : std::function<void(const deep_ptr<product>&)>, funzione che aggiunge un elemento della grandezza corrispondente
   */
  void refresh_grid(const u_vector<deep_ptr<product>>&, std::function<void(const deep_ptr<product>&)>);
};

#endif  // GRIDSHOW_H
