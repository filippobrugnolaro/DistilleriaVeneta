#include "tablerow.h"

tablerow::tablerow(QTableWidget*& t) : QWidget(t), table(t), icon(new QIcon(":/icon/delete.png")), bin_item(new QTableWidgetItem(*icon, "")), name_item(new QTableWidgetItem()), dim_item(new QTableWidgetItem()), num_item(new QSpinBox(this)), price_item(new QTableWidgetItem()) {}

tablerow::~tablerow() { delete icon; }

void tablerow::set_row(const deep_ptr<product>& p, int value_spin, int riga) {
  table->setRowHeight(riga, 50);

  table->setVerticalHeaderItem(riga, bin_item);

  name_item->setText(p->get_name().data());
  name_item->setTextAlignment(Qt::AlignCenter);
  table->setItem(riga, 0, name_item);

  dim_item->setText(QString::fromStdString(p->fromKindToStdString(p->get_kind())));
  dim_item->setTextAlignment(Qt::AlignCenter);
  table->setItem(riga, 1, dim_item);

  num_item->setHidden(true);
  table->setCellWidget(riga, 2, num_item);
  num_item->setRange(1, 2147483647);
  num_item->setValue(value_spin);
  num_item->setObjectName(QString::number(riga));
  num_item->setHidden(false);

  price_item->setText(QString::number(p->get_price() * value_spin, 'f', 2) + " €");
  price_item->setTextAlignment(Qt::AlignCenter);
  table->setItem(riga, 3, price_item);
}

QSpinBox*& tablerow::get_spin() { return num_item; }
