#include "qproduct.h"

#include <QDebug>

QProduct::QProduct(const deep_ptr<product>& _product, std::function<void(const deep_ptr<product>&)> callback, QWidget* parent) : QWidget(parent), item(_product), product_callback(callback) {
  item = _product;

  mainlayout = new QVBoxLayout();
  image_layout = new QHBoxLayout(this);

  img = new QLabel(this);
  pix = new QPixmap(_product->get_image_path().data());
  img->setPixmap(*pix);
  img->setObjectName("p_image");

  left_widget_image = new QFrame(this);
  image_layout->addWidget(img);
  left_widget_image->setLayout(image_layout);
  left_widget_image->layout()->setMargin(0);
  left_widget_image->layout()->setSpacing(0);
  left_widget_image->layout()->setAlignment(Qt::AlignCenter);
  left_widget_image->setMinimumSize(100, 125);
  left_widget_image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  mainlayout->addWidget(left_widget_image, Qt::AlignCenter);

  left_widget_name = new QLabel(_product->get_name().data());
  left_widget_name->setAlignment(Qt::AlignCenter);
  mainlayout->addWidget(left_widget_name, Qt::AlignCenter);

  left_widget_price = new QLabel(QString::number(_product->get_price(), 'f', 2) + " €");
  left_widget_price->setAlignment((Qt::AlignCenter));
  mainlayout->addWidget(left_widget_price, Qt::AlignCenter);

  left_widget_code = new QLabel("Codice:\n" + QString::fromStdString(_product->code()));
  left_widget_code->setStyleSheet("font: 11px");
  left_widget_code->setAlignment((Qt::AlignRight));
  mainlayout->addWidget(left_widget_code, Qt::AlignRight);

  setLayout(mainlayout);
}

QProduct::~QProduct() { delete pix; }

void QProduct::insert_small() {
  item->set_kind_bottle(small);
  product_callback(item);
}

void QProduct::insert_medium() {
  item->set_kind_bottle(medium);
  product_callback(item);
}

void QProduct::insert_big() {
  item->set_kind_bottle(large);
  product_callback(item);
}
