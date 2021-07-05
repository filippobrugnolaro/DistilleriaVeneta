#include "view.h"

void view::add_menu_bar(QVBoxLayout* main_layout) {
  menu_bar = new QMenuBar(this);

  file = new QMenu("File", menu_bar);
  filters = new QMenu("Filtri", menu_bar);

  alcohols = new QMenu("Contenuto Alcolico", filters);
  colors = new QMenu("Colore", filters);
  flavors = new QMenu("Gusto", filters);

  menu_bar->addMenu(file);
  menu_bar->addMenu(filters);

  filters->addMenu(alcohols);
  filters->addMenu(colors);
  filters->addMenu(flavors);

  close_action = new QAction("Chiudi", file);
  close_action->setShortcut(*closing);
  file->addAction(close_action);

  QAction* cresc = new QAction("Ordine Crescente", alcohols);
  QAction* desc = new QAction("Ordine Decrescente", alcohols);
  cresc->setCheckable(true);
  cresc->setChecked(false);
  desc->setCheckable(true);
  desc->setChecked(false);
  alcohols->addAction(cresc);
  alcohols->addAction(desc);

  u_vector<QString> colours_actions = {"Giallo", "Rosso", "Rosa", "Marrone", "Nero", "Violetto", "Bianco", "Verde", "Bianco Trasparente", "Giallo Trasparente"};
  u_vector<QString>::const_iterator _color_cit = colours_actions.const_begin();
  u_vector<QString>::const_iterator _color_end = colours_actions.const_end();

  for (std::pair<u_vector<QString>::const_iterator, int> _pair = std::make_pair(_color_cit, 0); _pair.first != _color_end; _pair.first++, _pair.second++) {
    QAction* action = new QAction(*(_pair.first), colors);
    action->setCheckable(true);
    action->setObjectName(QString::number(_pair.second));
    action->setChecked(false);
    colors->addAction(action);
  }

  u_vector<QString> flavors_actions = {"Limone", "Nocciola", "Caffè", "Liquirizia", "Cioccolato", "Uovo", "Rum", "Panna", "Fragola", "Frutti di bosco", "Mirtillo", "Ribes", "Prugna", "Miele", "Secco", "Dolce", "Amabile", "Menta"};

  u_vector<QString>::const_iterator _flavor_cit = flavors_actions.const_begin();
  u_vector<QString>::const_iterator _flavor_end = flavors_actions.const_end();
  for (std::pair<u_vector<QString>::const_iterator, int> _pair = std::make_pair(_flavor_cit, 10); _pair.first != _flavor_end; _pair.first++, _pair.second++) {
    QAction* action = new QAction(*(_pair.first), flavors);
    action->setObjectName(QString::number(_pair.second));
    action->setCheckable(true);
    action->setChecked(false);
    flavors->addAction(action);
  }

  main_layout->addWidget(menu_bar);
}

void view::add_title(QVBoxLayout* layout, const QString& message) {
  title = new QLabel(message, this);
  QFont font = QFont();
  font.setBold(true);
  font.setPointSize(message == "Distilleria Veneta" ? 24 : 17);
  title->setFont(font);
  title->setAlignment(Qt::AlignCenter);
  title->setContentsMargins(5, 5, 5, 5);

  layout->addWidget(title);
}

QHBoxLayout* view::add_filter_buttons() {
  filter_buttons = new QHBoxLayout();

  grappa_button = new QPushButton("Grappa", this);
  grappa_button->setObjectName("old-young");
  liquor_button = new QPushButton("Liquore", this);
  liquor_button->setObjectName("liquor-null");
  cream_button = new QPushButton("Crema", this);
  cream_button->setObjectName("cream-null");
  all_button = new QPushButton("Tutti", this);
  all_button->setObjectName("all-null");

  filter_buttons->addWidget(grappa_button);
  filter_buttons->addWidget(liquor_button);
  filter_buttons->addWidget(cream_button);
  filter_buttons->addWidget(all_button);

  filter_buttons->setSpacing(30);
  filter_buttons->setContentsMargins(20, 20, 20, 20);
  return filter_buttons;
}

void view::add_grid(QHBoxLayout* object_layout) {
  left_app = new QVBoxLayout();
  left_app->setObjectName("left_app");

  add_title(left_app, "Prodotti");

  product_area = new QGridShow(this);
  left_app->addWidget(product_area);

  left_app->addLayout(add_filter_buttons());

  left_app->setSpacing(0);
  left_app->setContentsMargins(20, 20, 20, 20);
  object_layout->addLayout(left_app);
}

QHBoxLayout* view::add_receipt_buttons() {
  receipt_buttons = new QHBoxLayout();

  delete_receipt = new QPushButton("Elimina", this);
  delete_receipt->setObjectName("delete_button");
  pay_button = new QPushButton("Paga", this);
  pay_button->setObjectName("pay_button");

  receipt_buttons->addWidget(delete_receipt);
  receipt_buttons->addWidget(pay_button);

  receipt_buttons->setSpacing(50);
  receipt_buttons->setContentsMargins(25, 20, 25, 20);

  return receipt_buttons;
}

void view::add_receipt(QHBoxLayout* object_layout) {
  right_app = new QVBoxLayout();

  add_title(right_app, "Scontrino");

  receipt_area = new QReceiptShow(this);
  right_app->addWidget(receipt_area);

  right_app->addLayout(add_receipt_buttons());

  right_app->setSpacing(0);
  right_app->setContentsMargins(20, 20, 20, 20);

  object_layout->addLayout(right_app);
}

void view::update_json() {
  auto bind_item = std::bind(&controller::add_item, presenter, _1);
  product_area->refresh_grid(presenter->get_products_json(), bind_item);
}

view::view(QWidget* parent) : QWidget(parent), closing(new QKeySequence("Ctrl+Q")) {
  main_layout = new QVBoxLayout(this);
  object_layout = new QHBoxLayout();

  QRect desktopRect = QApplication::desktop()->availableGeometry(this);
  QPoint center = desktopRect.center();

  move(center.x() - width(), 0);

  add_menu_bar(main_layout);

  add_title(main_layout, "Distilleria Veneta");

  add_grid(object_layout);
  add_receipt(object_layout);

  main_layout->addLayout(object_layout);
  main_layout->setSpacing(20);

  setLayout(main_layout);
}

view::~view() { delete closing; }

void view::set_controller(controller* c) {
  presenter = c;

  receipt_area->setpresenter(c);

  update_json();

  connect(alcohols->actions()[0], SIGNAL(triggered()), presenter, SLOT(filter_by_ac_cre()));
  connect(alcohols->actions()[1], SIGNAL(triggered()), presenter, SLOT(filter_by_ac_dec()));

  connect(file->actions()[0], SIGNAL(triggered()), this, SLOT(close()));

  connect(pay_button, SIGNAL(clicked()), this, SLOT(pay_banner()));
  connect(delete_receipt, SIGNAL(clicked()), this, SLOT(confirm_deletion()));

  connect(grappa_button, SIGNAL(clicked()), presenter, SLOT(filter_by_products()));
  connect(liquor_button, SIGNAL(clicked()), presenter, SLOT(filter_by_products()));
  connect(cream_button, SIGNAL(clicked()), presenter, SLOT(filter_by_products()));
  connect(all_button, SIGNAL(clicked()), presenter, SLOT(filter_by_products()));

  QList<QAction*>::const_iterator _color_cit = colors->actions().constBegin();
  QList<QAction*>::const_iterator _color_end = colors->actions().constEnd();
  for (; _color_cit != _color_end; _color_cit++) {
    connect(*_color_cit, SIGNAL(triggered()), presenter, SLOT(filter_by_color()));
  }

  QList<QAction*>::const_iterator _flavor_cit = flavors->actions().constBegin();
  QList<QAction*>::const_iterator _flavor_end = flavors->actions().constEnd();
  for (; _flavor_cit != _flavor_end; _flavor_cit++) {
    connect(*_flavor_cit, SIGNAL(triggered()), presenter, SLOT(filter_by_taste()));
  }
}

void view::refresh_scontrino(const u_vector<pair<deep_ptr<product>, int>>& _vector) { receipt_area->refreshTable(_vector); }

void view::refresh_grid_view(const u_vector<deep_ptr<product>>& _vector) {
  auto bind_item = std::bind(&controller::add_item, presenter, _1);
  product_area->refresh_grid(_vector, bind_item);
}

void view::pay_banner() {
  QMessageBox* pay_dialog = new QMessageBox(this);

  if (presenter->get_receipt().size()) {
    pay_dialog->setIcon(QMessageBox::Warning);
    pay_dialog->setText("Confermi il pagamento?");
    QPushButton* ok_button = new QPushButton("Ok", pay_dialog);
    QPushButton* annulla_button = new QPushButton("Annulla", pay_dialog);
    pay_dialog->addButton(ok_button, QMessageBox::YesRole);
    connect(ok_button, SIGNAL(clicked()), presenter, SLOT(pay()));
    pay_dialog->addButton(annulla_button, QMessageBox::NoRole);

  } else {
    pay_dialog->setIcon(QMessageBox::Information);
    pay_dialog->setText("Nessun prodotto presente nel carrello.\n Pagamento non effettuato!");
  }

  pay_dialog->show();
}

void view::confirm_deletion() {
  QMessageBox* delete_dialog = new QMessageBox(this);

  if (presenter->get_receipt().size()) {
    delete_dialog->setIcon(QMessageBox::Warning);
    delete_dialog->setText("   Vuoi davvero eliminare\ntutti i prodotti dal carrello?");
    QPushButton* ok_button = new QPushButton("Ok", delete_dialog);
    QPushButton* annulla_button = new QPushButton("Annulla", delete_dialog);
    delete_dialog->addButton(ok_button, QMessageBox::YesRole);
    connect(ok_button, SIGNAL(clicked()), presenter, SLOT(delete_all()));
    delete_dialog->addButton(annulla_button, QMessageBox::NoRole);

  } else {
    delete_dialog->setIcon(QMessageBox::Information);
    delete_dialog->setText("Nessun prodotto presente\n nel carrello!");
  }

  delete_dialog->show();
}

void view::delete_all() { presenter->delete_all(); }
