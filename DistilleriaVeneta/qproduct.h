#ifndef QPRODUCT_H
#define QPRODUCT_H

#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>
#include <functional>

#include "./Hierarchy/product.h"
#include "./Utilities/deep_ptr.hpp"

class QProduct : public QWidget {
  Q_OBJECT
 private:
  QVBoxLayout* mainlayout;
  QHBoxLayout* image_layout;
  QLabel* img;
  QPixmap* pix;
  QFrame* left_widget_image;
  QLabel* left_widget_name;
  QLabel* left_widget_price;
  QLabel* left_widget_code;
  deep_ptr<product> item;
  std::function<void(deep_ptr<product>)> product_callback;

 public:
  /**
   * @brief costruttore di QProduct
   * @param _product : const deep_ptr<product>&, indirizzo del puntatore al prodotto da rappresentare
   * @param callback : std::function<void(const deep_ptr<product>&)>, callback della funzione per il prodotto
   * @param parent : QWidget*, puntatore al padre, default = nullptr
   */
  explicit QProduct(const deep_ptr<product>&, std::function<void(const deep_ptr<product>&)>, QWidget* = nullptr);
  ~QProduct();
 public slots:
  void insert_small();
  void insert_medium();
  void insert_big();
};

#endif  // QPRODUCT_H
