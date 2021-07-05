#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "./Hierarchy/product.h"
#include "model.h"
#include "view.h"

class view;

class controller : public QObject {
  Q_OBJECT
 private:
  view* _view;
  model* _model;
  QAction* previous_sender;

 public:
  /**
   * @brief costruttore di controller
   * @param parent : QObject*, puntatore al padre, default = nullptr
   */
  explicit controller(QObject* = nullptr);

  /**
   * @brief metodo setter per settare il modello
   * @param model*, puntatore al modello
   */
  void set_model(model*);

  /**
   * @brief metodo setter per settare la view
   * @param view*, puntatore alla view
   */
  void set_view(view*);

  /**
   * @brief metodo per aggiungere un elemento al vettore scontrino
   * @param p : const deep_ptr<product>&, indirizzo del puntatore profondo al prodotto
   */
  void add_item(const deep_ptr<product>&);

  /**
   * @brief metodo per rimuove un elemento dal vettore scontrino
   * @param name : std::string, indica il nome del prodotto da rimuovere
   * @param dim : std::string, indica la dimensione del prodotto da rimuovere
   */
  void remove_item(const std::string&, const std::string&);

  /**
   * @brief metodo per cambiare la quantità di un prodotto nel vettore scontrino
   * @param name : std::string, indica il nome del prodotto di cui si vuole modificare la quantità
   * @param dim : std::string, indica la dimensione del prodotto di cui si vuole modificare la quantità
   * @param v : int, nuovo quantità del prodotto
   */
  void refresh_quantity(const std::string&, const std::string&, int);

  /**
   * @brief metodo per verificare la presenza di un prodotto nel vettore scontrino
   * @param p : const deep_ptr<product>&, indirizzo del puntatore profondo al prodotto
   * @return bool, 'true' sse nome e dimensione del prodotto coincide, 'false' altrimenti
   */
  bool presenza(const deep_ptr<product>&) const;

  /**
   * @brief metodo per le tasse totali incluse nel prezzo
   * @return double, indica il totale delle tasse dello scontrino
   */
  double total_taxes() const;

  /**
   * @brief metodo che ritorna il prezzo di un prodotto in base alla quantità
   * @param l : std::pair<deep_ptr<product>, int>, coppia puntatore-quantità del prodotto
   * @return double, prezzo di un prodotto in base alla quantità
   */
  double total_price_line(const std::pair<deep_ptr<product>, int>&) const;

  /**
   * @brief metodo per il prezzo totale del vettore scontrino
   * @return double, indica il prezzo totale dello scontrino
   */
  double total_price() const;

  /**
   * @brief metodo per contare il numero degli elementi totale nel vettore scontrino
   * @return unsigned int, numero di prodotti totale nel vettore
   */
  unsigned int total_number_items() const;

  /**
   * @brief metodo getter per ottenere i prodotti inseribili nello scontrino
   * @return u_vector<deep_ptr<product>>, vettore dei prodotti inseribili nello scontrino
   */
  u_vector<deep_ptr<product>> get_products_json() const;

  /**
   * @brief metodo getter per avere lo scontrino
   * @return u_vector<std::pair<deep_ptr<product>, int>>, scontrino contenente tutti i prodotti
   */
  u_vector<std::pair<deep_ptr<product>, int>> get_receipt() const;

 public slots:
  void delete_all();
  void pay();
  void filter_by_products() const;
  void filter_by_color();
  void filter_by_taste();
  void filter_by_ac_cre();
  void filter_by_ac_dec();
};

#endif  // CONTROLLER_H
