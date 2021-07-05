#ifndef __RECEIPT_H__
#define __RECEIPT_H__

#include <chrono>

#include "./Hierarchy/product.h"
#include "./Utilities/deep_ptr.hpp"
#include "./Utilities/u_vector.hpp"

using std::chrono::steady_clock;
using std::chrono::time_point;

class receipt {
 private:
  time_point<steady_clock> date;
  u_vector<std::pair<deep_ptr<product>, int>> items;

 public:
  /**
   * @brief definizione del costruttore dello scontrino
   */
  receipt();

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
   * @brief metodo per rimuovere tutti i prodotti dal vettore scontrino
   */
  void delete_all();

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
   * @brief metodo per contare il numero degli elementi totale nel vettore scontrino
   * @return unsigned int, numero di prodotti totale nel vettore
   */
  unsigned int total_number_items() const;

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
   * @brief metodo per le tasse totali incluse nel prezzo
   * @return double, indica il totale delle tasse dello scontrino
   */
  double total_taxes() const;

  /**
   * @brief metodo getter per avere lo scontrino
   * @return u_vector<std::pair<deep_ptr<product>, int>>, scontrino contenente tutti i prodotti
   */
  u_vector<std::pair<deep_ptr<product>, int>> get_items() const;
};
#endif  // __RECEIPT_H__
