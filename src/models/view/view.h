#ifndef VIEW_H
#define VIEW_H

#include "../state/state.h"

#include <memory>
#include <gtkmm.h>

// forward declaration
class TileView;

class View : public Gtk::Window {
	std::unique_ptr<State> game;
	TileView *selected_tileView;
	Tower *selected_tower;
	// targets for drag and drop
	std::vector<Gtk::TargetEntry> listTargets;

 protected:
	Gtk::Grid m_grid;
	Gtk::Grid tiles;
	Gtk::Frame panel_menu;
	Gtk::Frame panel_shop;
	Gtk::Frame panel_info;
	Gtk::ButtonBox box_menu;
	Gtk::ButtonBox box_shop;
	Gtk::ButtonBox box_info;
	Gtk::Button m_button_new_game;
	Gtk::Button m_button_round;
	Gtk::Button m_button_buy_damage_tower;
	Gtk::Button m_button_buy_freeze_tower;
	Gtk::Button m_button_buy_money_tower;
	Gtk::Button m_button_upgrade_tower;
	Gtk::Label m_price_damage_tower;
	Gtk::Label m_price_freeze_tower;
	Gtk::Label m_price_money_tower;
	Gtk::Label m_label_user_spec;
	Gtk::Label m_label_tower_spec;
	
	void on_button_new_game_clicked();
	void on_button_round_clicked();
	void on_button_upgrade_tower_clicked();
	bool on_tile_clicked(GdkEventButton *, TileView *);

	void on_button_drag_data_get(const Glib::RefPtr<Gdk::DragContext>& context, Gtk::SelectionData& selection_data, guint info, guint time, char tower);
	void on_label_drop_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time, TileView *tileView);

	void update_view();
	void update_tooltip();
	void update_info();
	void update_selected_tileView(TileView *);
	void update_selected_tower();

 public:
	View();
	virtual ~View();
};

#endif