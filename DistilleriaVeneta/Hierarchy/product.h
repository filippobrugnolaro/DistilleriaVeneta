#ifndef _PRODOTTO_H_
#define _PRODOTTO_H_

#include <QMap>
#include <QString>
#include <QVariant>
#include <map>
#include <regex>
#include <string>

#include "./Utilities/u_vector.hpp"
#include "enum.h"

class product {
 private:
  bottle_size kind;
  std::string name;
  double alcohol_content;

 protected:
  static const double fixed_price;

  /**
   * @brief metodo getter per il prezzo di default del prodotto
   * @return double, prezzo di default del prodotto
   */
  double get_default_price() const;
  inline static std::map<std::string, product*> _map;

 public:
  /**
   * @brief costruttore di product
   * @param bs : bottle_size, indica la grandezza del prodotto, default = medium
   * @param n : const std::string&, indica il nome del prodotto, default = ""
   * @param ac : double, indica il contenuto alcolico del prodotto, default = min_ac
   */
  product(bottle_size = medium, const std::string& = "", double = min_ac);

  /**
   * @brief costruttore di copia di product
   * @param p : const product&, indirizzo costante del prodotto da copiare
   */
  product(const product&);

  virtual ~product() = default;

  static const double multiplier_taxes;
  static const double min_ac;
  static const double max_ac;

  /**
   * @brief metodo di clonazione
   * @return product*, ritorna un puntatore al nuovo prodotto creato
   */
  virtual product* clone() const = 0;

  /**
   * @brief metodo kind_price
   * @return double, variazione di prezzo del prodotto in base alla dimensione
   */
  double kind_price() const;

  /**
   * @brief metodo price_increment
   * @return double, variazione di prezzo totale del prodotto
   */
  double price_increment() const;

  /**
   * @brief metodo getter per il prezzo totale del prodotto
   * @return double, prezzo totale del prodotto
   */
  virtual double get_price() const = 0;

  /**
   * @brief metodo type_product
   * @return std::string, tipo di prodotto a cui il puntatore sta puntando
   */
  virtual std::string type_product() const = 0;

  /**
   * @brief metodo code
   * @return std::string, codice del prodotto
   */
  virtual std::string code() const = 0;

  /**
   * @brief metodo promotion
   * @return double, prezzo totale del prodotto scontato
   */
  virtual double promotion() const = 0;

  /**
   * @brief metodo getter per i gusti del prodotto
   * @return u_vector<taste>, vettore dei gusti del prodotto
   */
  virtual u_vector<taste> get_tastes() const = 0;

  /**
   * @brief metodo getter per il colore del prodotto
   * @return color, colore del prodotto
   */
  virtual color get_color() const = 0;

  /**
   * @brief metodo getter per il path del prodotto
   * @return std::string, path del prodotto
   */
  virtual std::string get_image_path() const;

  /**
   * @brief metodo getter per il nome del prodotto
   * @return std::string, nome del prodotto
   */
  std::string get_name() const;

  /**
   * @brief metodo taxes
   * @return double, calcolo delle tasse del prodotto in base alla sua gradazione alcolica e alla sua dimensione
   */
  double taxes() const;

  /**
   * @brief metodo getter per la gradazione alcolica del prodotto
   * @return double, gradazione alcolica del prodotto
   */
  double get_alcohol_content() const;

  /**
   * @brief metodo getter per la dimensione del prodotto
   * @return bottle_size, dimensione del prodotto
   */
  bottle_size get_kind() const;

  /**
   * @brief metodo setter per cambiare la dimensione del prodotto
   * @param __bottle_size : bottle_size, nuova dimensione del prodotto, default = medium
   */
  void set_kind_bottle(bottle_size = medium);

  /**
   * @brief metodo per convertire enum in std::string
   * @param b : bottle_size, dimensione da convertire
   * @return std::string, dimensione del prodotto
   */
  std::string fromKindToStdString(bottle_size) const;

  // TODO

  /**
   * @brief metodo per la creazione polimorfa degli oggetti
   * @return product*, oggetto creato
   */
  static product* unserialize(QMap<QString, QVariant>&);

  /**
   * @brief create
   * @param m: QMap<QString, QVariant>&, mappa contentente tutti i dati per la costruzione
   * @return product*, oggetto creato
   */
  virtual product* create(QMap<QString, QVariant>&) const = 0;

  /**
   * @brief metodo per la preparazione dell'oggetto per la scrittura
   * @return std::string, serializzazione dell'oggetto
   */
  virtual std::string write() const = 0;

  /**
   * @brief definizione di operator+
   * @param p : const product&, indirizzo costante del prodotto da sommare
   * @return double, somma dei prezzi di due prodotti
   */
  double operator+(const product&) const;

  /**
   * @brief definizione di operator-
   * @param p : const product&, indirizzo costante del prodotto da sottrarre
   * @return double, se differenza positiva, differenza dei prezzi di due prodotti
   *                 se differenza negativa, prezzo del prodotto di invocazione
   */
  double operator-(const product&) const;

  /**
   * @brief definizone operator<
   * @param p : const product&, indirizzo costante del prodotto da confrontare
   * @return bool, `true` sse il contenuto alcolico è minore, `false` altrimenti
   */
  bool operator<(const product&) const;

  /**
   * @brief definizone operator>
   * @param p : const product&, indirizzo costante del prodotto da confrontare
   * @return bool, `true` sse il contenuto alcolico è maggiore, `false` altrimenti
   */
  bool operator>(const product&) const;
};

#endif  // PRODOTTO_H_
