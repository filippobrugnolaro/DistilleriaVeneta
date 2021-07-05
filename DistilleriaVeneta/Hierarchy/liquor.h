#ifndef LIQUOR_H_
#define LIQUOR_H_

#include "spirits.h"

class liquor : public spirits {
 private:
  class aux_map_initializer {
   private:
    liquor* ptr;

   public:
    aux_map_initializer();
    ~aux_map_initializer();
  };
  static aux_map_initializer aux_map;
  color col;
  u_vector<taste> tastes;

 protected:
  static const double liquor_incr;
  static const double taste_incr;

 public:
  /**
   * @brief costruttore di product
   * @param c : const color, indica il colore del liquore, default = white
   * @param t : const u_vector<taste>&, indica i gusti che può avere il liquore, default = {}
   * @param bs : bottle_size, indica la grandezza del liquore, default = medium
   * @param n : const std::string&, indica il nome del liquore, default = ""
   * @param ac : double, indica il contenuto alcolico del liquore, default = min_ac
   */
  liquor(const color = white, const u_vector<taste>& = {}, bottle_size = medium, const std::string& = "", double = min_ac);

  /**
   * @brief costruttore di copia di liquor
   * @param l : const liquor&, indirizzo costante del liquore da copiare
   */
  liquor(const liquor&);

  static const double min_ac;
  static const double max_ac;
  static const double discount_liquor;

  /**
   * @brief metodo di clonazione
   * @return product*, ritorna un puntatore al nuovo liquore creato
   */
  virtual liquor* clone() const override;

  /**
   * @brief metodo kind_price
   * @return double, variazione di prezzo del liquore in base alla dimensione
   */
  double kind_price() const;

  /**
   * @brief metodo price_increment
   * @return double, variazione di prezzo totale del liquore
   */
  double price_increment() const;

  /**
   * @brief metodo type_product
   * @return std::string, tipo di prodotto a cui il puntatore sta puntando (liquore)
   */
  virtual std::string type_product() const override;

  /**
   * @brief metodo getter per il prezzo totale del liquore
   * @return double, prezzo totale del liquore
   */
  virtual double get_price() const override;

  /**
   * @brief metodo promotion
   * @return double, prezzo totale del liquore scontato
   */
  virtual double promotion() const override;

  /**
   * @brief metodo getter per i gusti del liquore
   * @return u_vector<taste>, vettore dei gusti del liquore
   */
  virtual u_vector<taste> get_tastes() const override;

  /**
   * @brief metodo getter per il colore del liquore
   * @return color, colore del liquore
   */
  virtual color get_color() const override;

  /**
   * @brief metodo code
   * @return std::string, codice del liquore
   */
  virtual std::string code() const override;

  /**
   * @brief metodo getter per il path del liquore
   * @return std::string, path del liquore
   */
  virtual std::string get_image_path() const override;

  /**
   * @brief create
   * @param m: QMap<QString, QVariant>&, mappa contentente tutti i dati per la costruzione
   * @return liquor*, oggetto creato
   */
  virtual liquor* create(QMap<QString, QVariant>&) const override;

  /**
   * @brief metodo per la preparazione dell'oggetto per la scrittura
   * @return std::string, serializzazione dell'oggetto
   */
  virtual std::string write() const override;
};

#endif  // LIQUOR_H_
