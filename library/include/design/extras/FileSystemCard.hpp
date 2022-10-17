// Copyright 2016-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#ifndef DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_
#define DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_

#include <api/api.hpp>
#include <fs/FileSystem.hpp>

#include <lvgl/Window.hpp>

#include "../macros.hpp"

namespace design {

class FileSystemCard : public lvgl::ObjectAccess<FileSystemCard> {
public:
  enum class NotifyStatus { null, closed, selected, cancelled };

  static const char *root_drive_path();

  class Data : public lvgl::UserDataAccess<Data> {
  public:
    explicit Data(const char *name = "") : UserDataBase(name) {}

    API_PMAZ(animation_time, Data, chrono::MicroTime, chrono::MicroTime{});
    API_PMAZ(back_symbol, Data, const char *, LV_SYMBOL_UP);
    API_PMAZ(base_path, Data, var::PathString, {});
    API_PMAZ(close_symbol, Data, const char *, LV_SYMBOL_CLOSE);
    API_PMAZ(directory_symbol, Data, const char *, LV_SYMBOL_DIRECTORY);
#if defined __link
    API_PMAZ(drop_symbol, Data, const char *, nullptr);
#endif
    API_PMAZ(file_symbol, Data, const char *, LV_SYMBOL_FILE);
    API_PMAZ(full_path, Data, var::PathString, {});

    // members start with `is_`
    API_PUBLIC_BOOL(Data, absolute_path, false);
    API_PUBLIC_BOOL(Data, select_file, false);
    API_PUBLIC_BOOL(Data, select_folder, false);
    API_PUBLIC_BOOL(Data, show_hidden, false);

    API_PMAZ(notify_status, Data, NotifyStatus, NotifyStatus::null);
    API_PMAZ(relative_path, Data, var::PathString, {});
    API_PMAZ(selected_file, Data, var::NameString, {});
    API_PMAZ(suffix_filter, Data, const char *, "");
    API_PMAZ(user_data, Data, void*, nullptr);



    auto & copy(const Data & data){
      animation_time = data.animation_time;
      back_symbol = data.back_symbol;
      base_path = data.base_path;
      close_symbol = data.close_symbol;
      directory_symbol = data.directory_symbol;
#if defined __link
      drop_symbol = data.drop_symbol;
#endif
      file_symbol = data.file_symbol;
      full_path = data.full_path;
      is_absolute_path = data.is_absolute_path;
      is_select_file = data.is_select_file;
      is_select_folder = data.is_select_folder;
      is_show_hidden = data.is_show_hidden;
      notify_status = data.notify_status;
      relative_path = data.relative_path;
      selected_file = data.selected_file;
      suffix_filter = data.suffix_filter;
      user_data = data.user_data;
      return *this;
    }

    void enter_directory(var::StringView name);
    bool is_base_path() const;
    void exit_directory();
    var::PathString get_path_with_entry(var::StringView entry) const;
    void update_full_path();

  private:
    friend FileSystemCard;
  };

  explicit FileSystemCard(Data &data);
  explicit FileSystemCard(lv_obj_t *object) { m_object = object; }

  static const lv_obj_class_t *get_class() { return api()->window_class; }

};

} // namespace design


#endif // DESIGNAPI_DESIGN_EXTRAS_FILESYSTEM_WINDOW_HPP_
