//
// Created by Tyler Gilbert on 12/16/21.
//

#include <lvgl/Event.hpp>
#include <lvgl/Generic.hpp>

#if !defined LVGL_RUNTIME_TASK_ARRAY_SIZE
#error "DesignAPI requires LVGL_RUNTIME_TASK_ARRAY_SIZE to be defined in lv_conf.h"
#endif

#include "design/Worker.hpp"

using namespace design;
using namespace lvgl;

Worker::Worker(lvgl::Runtime *runtime, lv_obj_t *associated_object)
  : m_runtime(runtime), m_cond(m_mutex), m_associated_object{associated_object} {}

void Worker::start(const thread::Thread::Attributes &thread_attributes) {
  API_ASSERT(m_runtime != nullptr);
  if (!is_running()) {
    m_thread = thread::Thread(thread_attributes, [this]() -> void * {
      work();
      return nullptr;
    });
  }
}

void Worker::swap_worker(Worker &a) {
  // Cannot move a running thread
  API_ASSERT(a.is_running() == false);
  std::swap(m_runtime, a.m_runtime);
  std::swap(m_user_task, a.m_user_task);
  std::swap(m_associated_object, a.m_associated_object);
}

void Worker::lock_user_task(Task task) {
  // this is run in the worker thread
  thread::Mutex::Scope ms(m_cond.mutex());
  while (m_user_task) {
    m_cond.wait();
  }
  m_user_task = task;
}

void Worker::unlock_user_task() {
  thread::Mutex::Scope ms(m_cond.mutex());
  api::ErrorScope error_scope;
  m_user_task = {};
  m_cond.signal();
}

Worker &Worker::wait_runtime_task() {
  lock_user_task(nullptr);
  return *this;
}

void Worker::push_user_task_to_runtime(Task task) {
  lock_user_task(std::move(task));
  runtime().push([this]() { execute_runtime_task(); });
}

void Worker::execute_runtime_task() {
  if (m_user_task) {
    m_user_task();
  }
  unlock_user_task();
}

void Worker::notify_task(lv_obj_t *object) {
  Event::send(Generic(object), EventCode::notified);
}

bool Worker::is_running() const { return m_thread.is_valid() && m_thread.is_running(); }

lvgl::Runtime &Worker::runtime() {
  API_ASSERT(m_runtime != nullptr);
  return *m_runtime;
}

const lvgl::Runtime &Worker::runtime() const {
  API_ASSERT(m_runtime != nullptr);
  return *m_runtime;
}
