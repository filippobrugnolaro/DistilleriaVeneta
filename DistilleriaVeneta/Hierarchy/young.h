#ifndef YOUNG_H_
#define YOUNG_H_

#include "grappa.h"

class young : public grappa {
 private:
  class aux_map_initializer {
   private:
    young* ptr;

   public:
    aux_map_initializer();
    ~aux_map_initializer();
  };

  static aux_map_initializer aux_map;

  color col;
  u_vector<taste> tastes;

 public:
  /**
   * @brief costruttore di young
   * @param c : const color, indica il colore della grappa giovane, default = white_trasparent
   * @param t : const u_vector<taste>&, indica i gusti che può avere la grappa giovane, default = {}
   * @param bs : bottle_size, indica la grandezza della grappa giovane, default = medium
   * @param n : const std::string&, indica il nome della grappa giovane, default = ""
   * @param ac : double, indica il contenuto alcolico della grappa giovane, default = min_ac
   */
  young(const color = white_trasparent, const u_vector<taste>& = {}, bottle_size = medium, const std::string& = "", double = min_ac);

  /**
   * @brief costruttore di copia di young
   * @param y : const young&, indirizzo costante della grappa giovane da copiare
   */
  young(const young&);

  static const double discount_young;

  /**
   * @brief metodo di clonazione
   * @return product*, ritorna un puntatore alla nuova grappa giovane creata
   */
  virtual young* clone() const override;

  /**
   * @brief metodo kind_price
   * @return double, variazione di prezzo della grappa giovane in base alla dimensione
   */
  double kind_price() const;

  /**
   * @brief metodo price_increment
   * @return double, variazione di prezzo totale della grappa giovane
   */
  double price_increment() const;

  /**
   * @brief metodo type_product
   * @return std::string, tipo di prodotto a cui il puntatore sta puntando (young)
   */
  virtual std::string type_product() const override;

  /**
   * @brief metodo getter per il prezzo totale della grappa giovane
   * @return double, prezzo totale della grappa giovane
   */
  virtual double get_price() const override;

  /**
   * @brief metodo promotion
   * @return double, prezzo totale della grappa giovane scontato
   */
  virtual double promotion() const override;

  /**
   * @brief metodo getter per i gusti della grappa giovane
   * @return u_vector<taste>, vettore dei gusti della grappa giovane
   */
  virtual u_vector<taste> get_tastes() const override;

  /**
   * @brief metodo getter per il colore della grappa giovane
   * @return color, colore della grappa giovane
   */
  virtual color get_color() const override;

  /**
   * @brief metodo code
   * @return std::string, codice della grappa giovane
   */
  virtual std::string code() const override;

  /**
   * @brief metodo getter per il path della grappa giovane
   * @return std::string, path della grappa giovane
   */
  virtual std::string get_image_path() const override;

  /**
   * @brief create
   * @param m: QMap<QString, QVariant>&, mappa contentente tutti i dati per la costruzione
   * @return young*, oggetto creato
   */
  virtual young* create(QMap<QString, QVariant>&) const override;

  /**
   * @brief metodo per la preparazione dell'oggetto per la scrittura
   * @return std::string, serializzazione dell'oggetto
   */
  virtual std::string write() const override;
};

#endif  // YOUNG_H_
