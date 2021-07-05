#ifndef CREAM_H_
#define CREAM_H_

#include <algorithm>

#include "non_spirits.h"

class cream : public non_spirits {
 private:
  class aux_map_initializer {
   private:
    cream* ptr;

   public:
    aux_map_initializer();
    ~aux_map_initializer();
  };

  static aux_map_initializer aux_map;

  color col;
  u_vector<taste> tastes;

 protected:
  static const double cream_incr;

 public:
  /**
   * @brief costruttore di cream
   * @param c : const color, indica il colore della crema, default = white
   * @param t : const u_vector<taste>&, indica i gusti che può avere la crema, default = {}
   * @param bs : bottle_size, indica la grandezza della crema, default = medium
   * @param n : const std::string&, indica il nome della crema, default = ""
   * @param ac : double, indica il contenuto alcolico della crema, default = min_ac
   */
  cream(const color = white, const u_vector<taste>& = {}, bottle_size = medium, const std::string& = "", double = min_ac);

  /**
   * @brief costruttore di copia di cream
   * @param p : const cream&, indirizzo costante della crema da copiare
   */
  cream(const cream&);

  static const double discount_cream;
  static const double min_ac;
  static const double max_ac;

  /**
   * @brief metodo di clonazione
   * @return product*, ritorna un puntatore alla nuova crema creato
   */
  virtual cream* clone() const override;

  /**
   * @brief metodo kind_price
   * @return double, variazione di prezzo della crema in base alla dimensione
   */
  double kind_price() const;

  /**
   * @brief metodo price_increment
   * @return double, variazione di prezzo totale della crema
   */
  double price_increment() const;

  /**
   * @brief metodo getter per il prezzo totale della crema
   * @return double, prezzo totale della crema
   */
  virtual double get_price() const override;

  /**
   * @brief metodo type_product
   * @return std::string, tipo di prodotto a cui il puntatore sta puntando (crema)
   */
  virtual std::string type_product() const override;

  /**
   * @brief metodo promotion
   * @return double, prezzo totale della crema scontato
   */
  virtual double promotion() const override;

  /**
   * @brief metodo getter per i gusti della crema
   * @return u_vector<taste>, vettore dei gusti della crema
   */
  virtual u_vector<taste> get_tastes() const override;

  /**
   * @brief metodo getter per il colore della crema
   * @return color, colore della crema
   */
  virtual color get_color() const override;

  /**
   * @brief metodo code
   * @return std::string, codice della crema
   */
  virtual std::string code() const override;

  /**
   * @brief metodo getter per il path della crema
   * @return std::string, path della crema
   */
  virtual std::string get_image_path() const override;

  /**
   * @brief create
   * @param m: QMap<QString, QVariant>&, mappa contentente tutti i dati per la costruzione
   * @return cream*, oggetto creato
   */
  virtual cream* create(QMap<QString, QVariant>&) const override;

  /**
   * @brief metodo per la preparazione dell'oggetto per la scrittura
   * @return std::string, serializzazione dell'oggetto
   */
  virtual std::string write() const override;
};

#endif  // CREAM_H_
