// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_

#include <api/api.hpp>

#include <lvgl/Window.hpp>

namespace design {

class FileSystemWindow : public lvgl::ObjectAccess<FileSystemWindow> {
public:
  enum class NotifyStatus { null, closed, selected, cancelled };

  static const char *root_drive_path();

  class Data : public lvgl::UserDataAccess<Data> {
  public:
    explicit Data(const char *name = "") : UserDataBase(name) {}

    API_PMAZ(animation_time, Data, chrono::MicroTime, chrono::MicroTime{});
    API_PMAZ(back_symbol, Data, const char *, LV_SYMBOL_LEFT);
    API_PMAZ(base_path, Data, var::PathString, {});
    API_PMAZ(close_symbol, Data, const char *, LV_SYMBOL_CLOSE);
    API_PMAZ(directory_symbol, Data, const char *, LV_SYMBOL_DIRECTORY);
    API_PMAZ(file_symbol, Data, const char *, LV_SYMBOL_FILE);

    // members start with `is_`
    API_PUBLIC_BOOL(Data, select_file, false);
    API_PUBLIC_BOOL(Data, select_folder, false);
    API_PUBLIC_BOOL(Data, show_hidden, false);

    API_PMAZ(notify_status, Data, NotifyStatus, NotifyStatus::null);
    API_PMAZ(path, Data, var::PathString, {});
    API_PMAZ(selected_file, Data, var::NameString, {});
    API_PMAZ(user_data, Data, void*, nullptr);
  };

  explicit FileSystemWindow(Data &data);
  explicit FileSystemWindow(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->window_class; }

private:
  struct Names {
    static constexpr auto top_column = "TopColumn";
    static constexpr auto header_row = "HeaderRow";
    static constexpr auto content_area = "ContentArea";
    static constexpr auto path_label = "PathLabel";

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


  FileSystemWindow& set_back_button_label(const char * label);
  FileSystemWindow& update_path(var::StringView path);
  lvgl::Generic get_content_area() const {
    return find<lvgl::Generic>(Names::content_area);
  }

  static void configure_details(lvgl::Generic container);
  static void configure_list(lvgl::Generic container);
  static void back_button_pressed(lv_event_t*e);
  static void select_button_pressed(lv_event_t*e);

  static var::PathString
  get_next_path(const var::PathString &path, const char *entry);

  static lvgl::Label get_title_label(const lvgl::Window &window);

  static FileSystemWindow get_window(lvgl::Object child);


};

} // namespace design


#endif // DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_
