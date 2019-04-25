#include "window.h"

LibCompressGui::LibCompressGui()
: m_button_open("Open"),
  m_button_save("Save"),
  m_pane(Gtk::ORIENTATION_HORIZONTAL),
  m_left_box(Gtk::ORIENTATION_VERTICAL),
  m_right_box(Gtk::ORIENTATION_VERTICAL),
  m_label_input("Input:"), 
  m_label_result("Result:")
{
  // Connect signal handlers
  m_button_open.signal_clicked().connect(sigc::mem_fun(*this, &LibCompressGui::on_button_open_clicked));
  m_button_save.signal_clicked().connect(sigc::mem_fun(*this, &LibCompressGui::on_button_save_clicked));

  m_input_tv.get_buffer()->signal_changed()
    .connect(sigc::mem_fun(*this, &LibCompressGui::on_input_or_combo_box_changed));

  m_combo_box.signal_changed()
    .connect(sigc::mem_fun(*this, &LibCompressGui::on_input_or_combo_box_changed));

  // Combo box setup
  m_combo_box.append("RLE");
  m_combo_box.append("LZ77");
  m_combo_box.set_active(0);

  // Header setup
  m_header.set_title("Libcompress GUI");
  m_header.set_subtitle("Demonstration of libcompress algorithms");
  m_hbox.pack_start(m_button_open);
  m_hbox.pack_start(m_combo_box);
  m_hbox.get_style_context()->add_class("linked");
  m_header.pack_start(m_hbox);
  m_header.pack_end(m_button_save);
  m_header.set_show_close_button(true);
  set_titlebar(m_header);

  // Scrolled windows setup
  m_left_sw.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  m_right_sw.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_left_sw.add(m_input_tv);
  m_right_sw.add(m_result_tv);

  // Left box setup
  m_label_input.set_halign(Gtk::ALIGN_START);
  m_label_input.set_margin_bottom(5);
  m_left_box.pack_start(m_label_input, false, false); 
  m_left_box.pack_end(m_left_sw, true, true);
  m_input_tv.set_wrap_mode(Gtk::WRAP_WORD_CHAR);

  // Right box setup
  m_label_result.set_halign(Gtk::ALIGN_START);
  m_label_result.set_margin_start(5);
  m_label_result.set_margin_bottom(5);
  m_right_box.pack_start(m_label_result, false, false);
  m_right_box.pack_end(m_right_sw, true, true);
  m_result_tv.set_wrap_mode(Gtk::WRAP_WORD_CHAR);
  m_result_tv.set_editable(false);

  // Pane setup
  add(m_pane);
  m_pane.pack1(m_left_box, true, false);
  m_pane.pack2(m_right_box, true, false);
  m_pane.set_position(400);
  
  // Window setup
  set_border_width(10);
  set_default_size(800, 400);
  show_all_children();
}

LibCompressGui::~LibCompressGui() {}

void LibCompressGui::encode_input_with(std::string encoding_name)
{
  std::string inputed = m_input_tv.get_buffer()->get_text();
  if (encoding_name == "RLE") {
    m_result_tv.get_buffer()->set_text(libcompress.rle_encode(inputed));
  } else if (encoding_name == "LZ77") {
    m_result_tv.get_buffer()->set_text(libcompress.lz77_encode(inputed));
  }
}

void LibCompressGui::on_button_open_clicked()
{
  Gtk::FileChooserDialog open_dialog("Choose a file to open", Gtk::FILE_CHOOSER_ACTION_OPEN);
  open_dialog.set_transient_for(*this);

  open_dialog.add_button("_Open", Gtk::RESPONSE_OK);
  open_dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);

  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  open_dialog.add_filter(filter_text);

  auto filter_encoded = Gtk::FileFilter::create();
  filter_encoded->set_name("Encoded files");
  filter_text->add_pattern("*.encRLE");
  filter_text->add_pattern("*.encLZ77");
  open_dialog.add_filter(filter_encoded);

  int res = open_dialog.run();
  if (res == Gtk::RESPONSE_OK) {
    std::string file_name = open_dialog.get_filename();
    std::ifstream file(file_name);
    std::stringstream buffer;
    buffer << file.rdbuf();

    if (file_name.substr(file_name.find_last_of(".") + 1, 3) == "enc") {
      std::string encoding = file_name.substr(file_name.find_last_of(".") + 4);
      std::string buffer_str = buffer.str();
      if (encoding == "RLE") {
        m_combo_box.set_active(0);
        m_input_tv.get_buffer()->set_text(libcompress.rle_decode(buffer_str));
      } else if (encoding == "LZ77") {
        m_combo_box.set_active(1);
        m_input_tv.get_buffer()->set_text(libcompress.lz77_decode(buffer_str));
      }
    } else {
      m_input_tv.get_buffer()->set_text(buffer.str());
    }

    file.close();
  }
}

void LibCompressGui::on_button_save_clicked()
{
  Gtk::FileChooserDialog save_dialog("Save file", Gtk::FILE_CHOOSER_ACTION_SAVE);
  save_dialog.set_transient_for(*this);

  save_dialog.add_button("_Save", Gtk::RESPONSE_ACCEPT);
  save_dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  std::string suggested_name = "compressed.enc" + m_combo_box.get_active_text();
  save_dialog.set_current_name(suggested_name);

  int res = save_dialog.run();
  if (res == Gtk::RESPONSE_ACCEPT) {
    std::ofstream file(save_dialog.get_filename());
    file << m_result_tv.get_buffer()->get_text();
    file.close();
  }
}

void LibCompressGui::on_input_or_combo_box_changed()
{ 
  std::string encoding_name = m_combo_box.get_active_text();
  encode_input_with(encoding_name);
}
