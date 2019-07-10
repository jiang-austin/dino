#include "view.h"
#include "../tile/path/pathTile.h"
#include "./../enemy/enemy.h"
#include "./../map/map.h"
#include "./../state/state.h"
#include "./../tower/tower.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

View::View() : m_button_start("Start Game"),
               m_button_print("Print Map"),
               m_button_round("Start Next Round"),
               m_button_buy_damage_tower("Buy Damage Tower"),
               m_button_buy_freeze_tower("Buy Freeze Tower"),
               m_button_buy_money_tower("Buy Money Tower"),
               m_label("\t\n\t\n") {
  set_title("Tower Defense");
  set_border_width(10);
  m_label.override_background_color(Gdk::RGBA("green"), Gtk::STATE_FLAG_NORMAL);

  //Targets:
  std::vector<Gtk::TargetEntry> listTargets;
  listTargets.push_back(Gtk::TargetEntry("STRING"));
  listTargets.push_back(Gtk::TargetEntry("text/plain"));

  //Drag site:

  //Make button a DnD drag source:
  m_button_buy_damage_tower.drag_source_set(listTargets);
  m_button_buy_freeze_tower.drag_source_set(listTargets);
  m_button_buy_money_tower.drag_source_set(listTargets);

  //Connect signals:
  m_button_buy_damage_tower.signal_drag_data_get().connect(sigc::mem_fun(*this, &View::on_button_drag_data_get));
  m_button_buy_freeze_tower.signal_drag_data_get().connect(sigc::mem_fun(*this, &View::on_button_drag_data_get));
  m_button_buy_money_tower.signal_drag_data_get().connect(sigc::mem_fun(*this, &View::on_button_drag_data_get));

  //Drop site:

  //Make m_label a DnD drop destination:
  m_label.drag_dest_set(listTargets);

  //Connect signals:
  m_label.signal_drag_data_received().connect(sigc::mem_fun(*this, &View::on_label_drop_drag_data_received));

  m_button_start.signal_clicked().connect(sigc::mem_fun(*this, &View::on_button_start_clicked));
  m_button_print.signal_clicked().connect(sigc::mem_fun(*this, &View::on_button_print_clicked));
  m_button_round.signal_clicked().connect(sigc::mem_fun(*this, &View::on_button_round_clicked));
  m_button_buy_damage_tower.signal_clicked().connect(sigc::mem_fun(*this, &View::on_button_buy_damage_tower_clicked));
  m_button_buy_freeze_tower.signal_clicked().connect(sigc::mem_fun(*this, &View::on_button_buy_freeze_tower_clicked));
  m_button_buy_money_tower.signal_clicked().connect(sigc::mem_fun(*this, &View::on_button_buy_money_tower_clicked));

  m_grid.add(m_button_start);
  m_grid.add(m_button_print);
  m_grid.add(m_button_round);
  m_grid.add(m_button_buy_damage_tower);
  m_grid.add(m_button_buy_freeze_tower);
  m_grid.add(m_button_buy_money_tower);
  m_grid.add(m_label);
  add(m_grid);

  show_all();
}

View::~View() {}

void View::on_button_start_clicked() {
  game = State();
  cout << "game created" << endl;
}

void View::on_button_print_clicked() {
  game.displayMap();
}

void View::on_button_round_clicked() {
  game.startRound();
}

void View::on_button_buy_damage_tower_clicked() {
  if (!game.buyTower('D', x, y)) {
    cout << "Invalid Purchase! Damage tower @ (" << x << ", " << y << ") could not be bought" << endl;
  } else {
    cout << "Damage tower purchase successful!" << endl;
  }
}

void View::on_button_buy_freeze_tower_clicked() {
  if (!game.buyTower('F', x, y)) {
    cout << "Invalid Purchase! Freeze tower @ (" << x << ", " << y << ") could not be bought" << endl;
  } else {
    cout << "Freeze tower purchase successful!" << endl;
  }
}

void View::on_button_buy_money_tower_clicked() {
  if (!game.buyTower('M', x, y)) {
    cout << "Invalid Purchase! Money tower @ (" << x << ", " << y << ") could not be bought" << endl;
  } else {
    cout << "Money tower purchase successful!" << endl;
  }
}

void View::on_button_drag_data_get(
    const Glib::RefPtr<Gdk::DragContext>&,
    Gtk::SelectionData& selection_data, guint, guint) {
  selection_data.set(selection_data.get_target(), 8 /* 8 bits format */,
                     (const guchar*)"I'm Data!",
                     9 /* the length of I'm Data! in bytes */);
}

void View::on_label_drop_drag_data_received(
    const Glib::RefPtr<Gdk::DragContext>& context, int, int,
    const Gtk::SelectionData& selection_data, guint, guint time) {
  const int length = selection_data.get_length();
  if ((length >= 0) && (selection_data.get_format() == 8)) {
    std::cout << "Received \"" << selection_data.get_data_as_string()
              << "\" in label " << std::endl;
  }

  context->drag_finish(false, false, time);
}

