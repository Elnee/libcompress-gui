#ifndef WINDOW_H
#define WINDOW_H

#include <gtkmm.h>
#include <fstream>
#include <sstream>
#include "libcompress.h"

class LibCompressGui : public Gtk::Window
{
  public:
    LibCompressGui();
    virtual ~LibCompressGui();
  protected:
    // Handlers
    void on_button_open_clicked();
    void on_button_save_clicked();
    void on_input_or_combo_box_changed();

    // Widgets
    Gtk::Button m_button_open, m_button_save;
    Gtk::ComboBoxText m_combo_box;
    Gtk::HeaderBar m_header;
    Gtk::Paned m_pane;
    Gtk::Box m_hbox, m_left_box, m_right_box;
    Gtk::Label m_label_input, m_label_result;
    Gtk::TextView m_input_tv, m_result_tv;
    Gtk::ScrolledWindow m_left_sw, m_right_sw;

    // Methods
    void encode_input_with(std::string encoding_name);

    // Compressor instance
    LibCompress libcompress;
};

#endif
