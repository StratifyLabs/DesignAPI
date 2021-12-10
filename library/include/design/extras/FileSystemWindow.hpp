// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_

#include <api/api.hpp>

#include <lvgl/Window.hpp>

namespace design {

class FileSystemWindow : public lvgl::ObjectAccess<FileSystemWindow> {
public:
  enum class ExitStatus { null, closed, selected, cancelled };

  static const char *root_drive_path();

  class Data : public lvgl::UserDataAccess<Data> {
  public:
    explicit Data(const char *name = "") : UserDataBase(name) {}

    API_PMAZ(animation_time, Data, chrono::MicroTime, chrono::MicroTime{});
    API_PMAZ(back_symbol, Data, const char *, LV_SYMBOL_LEFT);
    API_PMAZ(base_path, Data, var::PathString, {});
    API_PMAZ(close_symbol, Data, const char *, LV_SYMBOL_CLOSE);
    API_PMAZ(directory_symbol, Data, const char *, LV_SYMBOL_DIRECTORY);
    API_PMAZ(exit_status, Data, ExitStatus, ExitStatus::null);
    API_PMAZ(file_symbol, Data, const char *, LV_SYMBOL_FILE);

    // members start with `is_`
    API_PUBLIC_BOOL(Data, select_file, false);
    API_PUBLIC_BOOL(Data, select_folder, false);
    API_PUBLIC_BOOL(Data, show_hidden, false);

    API_PMAZ(path, Data, var::PathString, {});
  };

  explicit FileSystemWindow(
    Data &data,
    lv_coord_t header_height = lvgl::Percent(15).value());
  explicit FileSystemWindow(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->window_class; }

private:
  struct Names {
    static constexpr auto ok_button = "OkButton";
    static constexpr auto back_button = "BackButton";
    static constexpr auto entry_list = "EntryList";
    static constexpr auto tile_view = "TileView";
    static constexpr auto file_browser_window = "FileBrowser";
    static constexpr auto window_title = "WindowTitle";
    static constexpr auto file_details_table = "FileDetails";
    static constexpr auto home_button = "HomeButton";
    static constexpr auto root_drive_button = "RootDriveButton";
    static constexpr auto select_button = "SelectButton";
    static constexpr auto cancel_button = "CancelButton";
    static constexpr auto show_hidden_checkbox = "ShowHidden";
  };

  class TileData : public lvgl::UserDataAccess<TileData> {
  public:
    explicit TileData(const char *path) : UserDataBase(""), m_path(path) {}

  private:
    API_AC(TileData, var::PathString, path);
  };

  API_NO_DISCARD lvgl::Generic get_header() const {
    return lvgl::Generic(api()->win_get_header(m_object));
  }
  API_NO_DISCARD lvgl::Generic get_content() const {
    return lvgl::Generic(api()->win_get_content(m_object));
  }

  static void configure_details(lvgl::Generic container);
  static void configure_list(lvgl::Generic container);

  static var::PathString
  get_next_path(const var::PathString &path, const char *entry);

  static void
  set_back_button_label(const lvgl::Window &window, const char *symbol);
  static lvgl::Label get_title_label(const lvgl::Window &window);
  static lvgl::Window get_window(Object object) {
    return object.find_parent<lvgl::Window>();
  }
};

} // namespace design

namespace printer {
class Printer;
// Add operators to send any important debug tracing data to a printer
Printer &operator<<(Printer &printer, const design::FileSystemWindow &a);
} // namespace printer

#endif // DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_
