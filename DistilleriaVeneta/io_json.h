#ifndef IO_JSON_H
#define IO_JSON_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QTime>
#include <regex>
#include <string>

#include "Hierarchy/product.h"
#include "Utilities/deep_ptr.hpp"
#include "Utilities/u_vector.hpp"

class io_json {
 private:
  std::string __file_path;

 public:
  io_json(const std::string& = ":/data/data.json");
  static std::string dir_path;

  /**
   * @brief read, metodo per la lettura del file
   * @return u_vector<deep_ptr<product>>, vettore contenente gli oggetti creati
   */
  u_vector<deep_ptr<product>> read() const;

  /**
   * @brief write, metodo per la scrittura del file
   * @param a: const u_vector<std::pair<deep_ptr<product>, int>>&, vettore contenente gli oggetti da scrivere nel file
   * @param _total: double, prezzo totale dello scontrino
   * @param _taxes: double, totale delle tasse
   * @param _elements: unsigned int, numero totale degli oggetti
   * @return bool: true sse tutto è andato correttamente, false altrimenti
   */
  bool write(const u_vector<std::pair<deep_ptr<product>, int>>&, double, double, unsigned int) const;
};

#endif  // IO_JSON_H
