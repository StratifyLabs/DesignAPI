//
// Created by Tyler Gilbert on 12/16/21.
//

#include <lvgl/Generic.hpp>

#include "design/Worker.hpp"

using namespace design;
using namespace lvgl;

Worker::Worker(lvgl::Runtime *runtime, Worker::Work work)
  : m_runtime(runtime), m_cond(m_mutex), m_work_callback(work) {}

void *Worker::thread_work_function(void *args) {
  reinterpret_cast<Worker *>(args)->work_function();
  return nullptr;
}

Worker &Worker::start(const thread::Thread::Attributes &thread_attributes) {
  if (!is_running()) {
    m_thread = thread::Thread(thread_attributes, this, thread_work_function);
  }
  return *this;
}

void Worker::move_worker(Worker &a) {
  // Cannot move a running thread
  API_ASSERT(a.is_running() == false);

  std::swap(m_runtime, a.m_runtime);
  std::swap(m_user_data, a.m_user_data);
  std::swap(m_user_task, a.m_user_task);
  std::swap(m_work_callback, a.m_work_callback);
}

void Worker::work_function() {
  API_ASSERT(m_work_callback != nullptr);
  m_work_callback(this);
}

void Worker::lock_user_data(void *user_data, void (*task)(void *)) {
  // this is run in the worker thread
  thread::Mutex::Scope ms(m_cond.mutex());
  while (m_user_task != nullptr) {
    m_cond.wait();
  }
  m_user_task = task;
  m_user_data = user_data;
}

void Worker::unlock_user_data() {
  thread::Mutex::Scope ms(m_cond.mutex());
  m_user_task = nullptr;
  m_user_data = nullptr;
  m_cond.signal();
}

Worker &Worker::update_runtime(void *user_data, void (*task)(void *)) {
  lock_user_data(user_data, task);
  runtime().push(this, runtime_task_function);
  return *this;
}

void Worker::runtime_task_function(void *context) {
  reinterpret_cast<Worker *>(context)->runtime_task();
}

void Worker::runtime_task() {
  m_user_task(m_user_data);
  unlock_user_data();
}
