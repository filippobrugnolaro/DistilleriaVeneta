#ifndef RECEIPTSHOW_H
#define RECEIPTSHOW_H

#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QMessageBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>

#include "./Hierarchy/product.h"
#include "./Utilities/deep_ptr.hpp"
#include "./Utilities/u_vector.hpp"
#include "tablerow.h"
using std::pair;

class controller;

class QReceiptShow : public QWidget {
  Q_OBJECT
 private:
  QTableWidget* table;
  QGridLayout* resoconto;
  QLabel* prezzo_finale;
  QLabel* tasse_finale;
  QLabel* n_items;
  QPushButton* elimina_prodotto;
  controller* presenter;
  QList<QSpinBox*> list_spin;

 public:
  /**
   * @brief costruttore di QReceiptShow
   * @param parent : QWidget*, puntatore al padre, default = nullptr
   */
  explicit QReceiptShow(QWidget* = nullptr);

  /**
   * @brief metodo setter per il controller
   * @param c : controller*, puntatore al controller
   */
  void setpresenter(controller*);

  /**
   * @brief metodo per l'aggiunta del background dello scontrino
   * @param table_layout : QVBoxLayout*, puntatore al layout contenente il background dello scontrino
   */
  void addTable(QVBoxLayout*);

  /**
   * @brief metodo per aggiornare lo scontrino
   * @param _products : const u_vector<std::pair<deep_ptr<product>, int>>&, indirizzo del vettore scontrino
   */
  void refreshTable(const u_vector<std::pair<deep_ptr<product>, int>>&);

  /**
   * @brief metodo che aggiunge del layout contente tutti i totali
   * @return QGridLayout*, puntatore al layout contenente tutti i totali
   */
  QGridLayout* add_total();

  /**
   * @brief metodo che aggiorna i totali
   */
  void refresh_totali();

  /**
   * @brief metodo che costruisce i dialog per l'eliminazione dei prodotti
   */
  void elimina_prodotto_dialog();

 public slots:
  void EliminaButtonSlot();
  void CancellaProdottoSlot();
  void refresh_spinbox(int);
};

#endif  // RECEIPTSHOW_H
