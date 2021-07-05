#include "gridshow.h"

QGridShow::QGridShow(QWidget* parent) : QWidget(parent) {
  main_layout = new QVBoxLayout(this);

  product_area = new QScrollArea(this);
  product_area->setMinimumSize(550, 500);
  product_area->setWidgetResizable(true);
  product_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

  contenitore = new QFrame(product_area);
  grid = new QGridLayout(contenitore);

  contenitore->setLayout(grid);
  contenitore->setObjectName("container");
  product_area->setWidget(contenitore);

  main_layout->addWidget(product_area);

  setLayout(main_layout);
}

void QGridShow::clear_grid() {
  while (QLayoutItem* item = grid->takeAt(0)) {
    delete item->widget();
    delete item;
  }
}

void QGridShow::refresh_grid(const u_vector<deep_ptr<product>>& _products, std::function<void(const deep_ptr<product>&)> bind) {
  clear_grid();

  int r = 1;
  int c = 1;
  const int n_ele = 3;

  u_vector<deep_ptr<product>>::const_iterator it = _products.const_begin();
  u_vector<deep_ptr<product>>::const_iterator end = _products.const_end();

  lista_prodotti.clear();

  for (; it != end; it++) {
    QProduct* p = new QProduct(*it, bind, product_area);
    p->setMaximumSize(240, 240);
    QOverlay* o = new QOverlay(product_area);
    o->setMaximumSize(240, 240);
    QStackedWidgetHover* stack = new QStackedWidgetHover(p, o, product_area);

    lista_prodotti.append(stack);
    grid->addWidget(stack, r, c);

    connect(o->get_small_button(), SIGNAL(clicked()), p, SLOT(insert_small()));
    connect(o->get_medium_button(), SIGNAL(clicked()), p, SLOT(insert_medium()));
    connect(o->get_large_button(), SIGNAL(clicked()), p, SLOT(insert_big()));

    if (c == n_ele) {
      r++;
      c = 1;
    } else {
      c++;
    }
  }
}
