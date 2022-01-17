//
// Created by Tyler Gilbert on 12/16/21.
//

#include <lvgl/Generic.hpp>
#include <lvgl/Event.hpp>

#include "design/Worker.hpp"

using namespace design;
using namespace lvgl;


ModelScope::ModelScope(ModelScope::Construct &options)
  : thread::Mutex::Scope(options.mutex), m_construct(&options) {
  options.pthread_scoped = thread::Thread::self();
  ++options.lock_count;
}

ModelScope::~ModelScope() {
  --m_construct->lock_count;
  if (m_construct->lock_count == 0) {
    m_construct->pthread_scoped = {};
  }
}

bool ModelScope::Construct::is_available() const {
  return pthread_scoped == thread::Thread::self();
}

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
  std::swap(m_associated_object, a.m_associated_object);
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
  api::ErrorScope error_scope;
  m_user_task = nullptr;
  m_user_data = nullptr;
  m_cond.signal();
}

Worker &Worker::wait_runtime_task(){
  lock_user_data(nullptr, nullptr);
  return *this;
}

void Worker::push_task_void_to_runtime(void *user_data, void (*task)(void *)) {
  lock_user_data(user_data, task);
  runtime().push(this, execute_runtime_task_function);
}

void Worker::execute_runtime_task_function(void *context) {
  reinterpret_cast<Worker *>(context)->execute_runtime_task();
}

void Worker::execute_runtime_task() {
  m_user_task(m_user_data);
  unlock_user_data();
}

void Worker::notify_task(lv_obj_t * object) {
  Event::send(Generic(object), EventCode::notified);
}

Worker &Worker::notify(lv_obj_t *object) {
  return push_task_to_runtime<lv_obj_t>(object, notify_task);
}

bool Worker::is_running() const {
  return m_thread.is_valid() && m_thread.is_running();
}

Worker &Worker::notify_associated_object() {
  if( associated_object() ) {
    return notify(associated_object());
  }
  return *this;
}
