#ifndef VIEW_H_
#define VIEW_H_

#include <QAction>
#include <QApplication>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QKeySequence>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <functional>

#include "./Utilities/deep_ptr.hpp"
#include "./Utilities/u_vector.hpp"
#include "controller.h"
#include "gridshow.h"
#include "qproduct.h"
#include "receiptshow.h"

using namespace std::placeholders;

class controller;

class view : public QWidget {
  Q_OBJECT
 private:
  QVBoxLayout* main_layout;
  QHBoxLayout* object_layout;
  QMenuBar* menu_bar;
  QMenu* file;
  QAction* close_action;
  QMenu* filters;
  QMenu* alcohols;
  QAction* cresc;
  QAction* desc;
  QMenu* colors;
  QMenu* flavors;
  QLabel* title;
  QHBoxLayout* filter_buttons;
  QPushButton* grappa_button;
  QPushButton* liquor_button;
  QPushButton* cream_button;
  QPushButton* all_button;
  QVBoxLayout* left_app;
  QGridShow* product_area;
  QHBoxLayout* receipt_buttons;
  QPushButton* delete_receipt;
  QPushButton* pay_button;
  QVBoxLayout* right_app;
  QReceiptShow* receipt_area;
  controller* presenter;
  const QKeySequence* closing;

  /**
   * @brief metodo di aggiunta della bar
   * @param main_layout : QVBoxLayout*, puntatore al layout per aggiungere la menubar
   */
  void add_menu_bar(QVBoxLayout*);

  /**
   * @brief metodo di aggiunta del titolo
   * @param layout : QVBoxLayout*, puntatore al puntatore al layout dove si aggiunge il titolo
   * @param message : const QString&, titolo da aggiungere
   */
  void add_title(QVBoxLayout*, const QString&);

  /**
   * @brief metodo di aggiunta dei filtri principali
   * @return QHBoxLayout*, puntatore al layout contenente il bottoni
   */
  QHBoxLayout* add_filter_buttons();

  /**
   * @brief metodo di aggiunta della griglia prodotti
   * @param object_layout : QHBoxLayout*, puntatore al layout contenente la parte sinistra dell'app
   */
  void add_grid(QHBoxLayout*);

  /**
   * @brief metodo di aggiunta dei bottoni utili per lo scontrino
   * @return QHBoxLayout*, puntatore al layout contenente i bottoni utili per lo scontrino
   */
  QHBoxLayout* add_receipt_buttons();

  /**
   * @brief metodo per l'aggiunta dello scontrino
   * @param object_layout : QHBoxLayout*, puntatore al layout contenente la parte destra dell'app
   */
  void add_receipt(QHBoxLayout*);

  /**
   * @brief metodo per l'inserimento dei prodotti nella griglia tramite json
   */
  void update_json();

 public:
  /**
   * @brief costruttore della view
   * @param parent : QWidget*, puntatore al parent, default = nullptr
   */
  view(QWidget* = nullptr);

  ~view();

  /**
   * @brief metodo setter per il controller
   * @param c : controller*, puntatore controller riferito alla view
   */
  void set_controller(controller*);

  /**
   * @brief metodo per aggiornare lo scontrino
   * @param _vector : const u_vector<pair<deep_ptr<product>, int>>&, indirizzo del vettore scontrino
   */
  void refresh_scontrino(const u_vector<pair<deep_ptr<product>, int>>&);

  /**
   * @brief metodo per aggiornare la griglia dei prodotti
   * @param _vector : const u_vector<pair<deep_ptr<product>, int>>&, indirizzo del vettore dei prodotti inseribili nello scontrino
   */
  void refresh_grid_view(const u_vector<deep_ptr<product>>&);

 private slots:
  void pay_banner();
  void confirm_deletion();
  void delete_all();
};

#endif  // VIEW_H_
