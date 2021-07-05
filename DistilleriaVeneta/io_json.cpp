#include "io_json.h"

io_json::io_json(const std::string& path) : __file_path(path) {}

std::string io_json::dir_path = "./file/Receipts/";

u_vector<deep_ptr<product>> io_json::read() const {
  QFile file_obj(QString::fromStdString(__file_path));
  if (!file_obj.open(QIODevice::ReadOnly)) {
    return {};
  }

  QTextStream file_text(&file_obj);
  QString json_string;

  json_string = file_text.readAll();
  file_obj.close();

  QByteArray json_bytes = json_string.toLocal8Bit();

  QJsonDocument json_doc = QJsonDocument::fromJson(json_bytes);

  if (json_doc.isNull()) {
    throw std::exception();
  }
  if (!json_doc.isObject()) {
    throw std::exception();
  }

  QJsonObject json_obj = json_doc.object();

  if (json_obj.isEmpty()) {
    throw std::exception();
  }

  QVariantMap tmp = json_obj.toVariantMap();

  QMap<QString, QVariant> map = tmp["elements"].toMap();

  QMap<QString, QVariant>::iterator it = map.begin();
  QMap<QString, QVariant>::iterator end = map.end();

  u_vector<deep_ptr<product>> result;

  for (; it != end; it++) {
    QMap<QString, QVariant> m = (*it).toMap();
    result.push_back(deep_ptr<product>(product::unserialize(m)));
  }

  return result;
}

bool io_json::write(const u_vector<std::pair<deep_ptr<product>, int>>& a, double _total, double _taxes, unsigned int _elements) const {
  int i = 0;
  time_t rawtime;
  struct tm* timeinfo;
  char buffer[50];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
  std::string str(buffer);
  std::string to_write =
      "{ \n \
         \"metadata\": { \
	          \"timestamp\": \"$1\", \n \
                  \"total_price\": \"$2\", \n \
                  \"total_taxes\": \"$3\", \n \
                  \"number_of_elements\": \"$4\" \n \
          }, \
         \"elements\": {\n";

  to_write = std::regex_replace(to_write, std::regex("\\$1"), str);
  to_write = std::regex_replace(to_write, std::regex("\\$2"), std::to_string(_total));
  to_write = std::regex_replace(to_write, std::regex("\\$3"), std::to_string(_taxes));
  to_write = std::regex_replace(to_write, std::regex("\\$4"), std::to_string(_elements));

  u_vector<std::pair<deep_ptr<product>, int>>::const_iterator it = a.const_begin();
  u_vector<std::pair<deep_ptr<product>, int>>::const_iterator end = a.const_end();

  for (; it != end; ++it) {
    i++;
    to_write.append("\t\"element" + std::to_string(i) + "\":{ \n\t" + (*it).first->write() + "},\n");
  }
  to_write.erase(to_write.end() - 2);
  to_write.append("}\n}");

  QDir dir(dir_path.data());
  if (!dir.exists()) {
    dir.mkpath(".");
  }

  QString jsonString = to_write.c_str();
  QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());

  if (doc.isEmpty()) {
    return false;
  } else {
    strftime(buffer, sizeof(buffer), "-%d-%m-%Y-%H_%M_%S", timeinfo);
    str = buffer;
    QFile file((dir_path + "receipt" + str + ".json").data());

    file.open(QIODevice::WriteOnly);
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
  }
}
