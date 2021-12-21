//
// Created by Tyler Gilbert on 12/16/21.
//

#ifndef DESIGNLAB_WORKER_HPP
#define DESIGNLAB_WORKER_HPP

#include <algorithm>

#include <lvgl/Bar.hpp>
#include <lvgl/Runtime.hpp>

#include <thread/Cond.hpp>
#include <thread/Mutex.hpp>
#include <thread/Thread.hpp>

namespace design {

class ModelScope : public thread::Mutex::Scope {

public:
  struct Construct {
    thread::Mutex mutex = thread::Mutex(
      thread::Mutex::Attributes().set_type(thread::Mutex::Type::recursive));
    size_t lock_count = 0;
    pthread_t pthread_scoped{};

    bool is_available() const;
  };

  ModelScope(Construct &options);
  ~ModelScope();

private:
  Construct *m_construct = nullptr;
};

class Worker : public api::ExecutionContext {
  using VoidTask = void (*)(void*);
public:

  using Work = void (*)(Worker *);
  Worker() : m_cond(m_mutex) {}
  Worker(lvgl::Runtime *runtime, Work work);

  Worker(const Worker &) = delete;
  Worker &operator=(const Worker &) = delete;

  Worker(Worker &&a) : m_cond(m_mutex) { move_worker(a); }

  Worker &operator=(Worker &&a) {
    move_worker(a);
    return *this;
  }

  lvgl::Runtime &runtime() { return *m_runtime; }
  const lvgl::Runtime &runtime() const { return *m_runtime; }

  Worker& notify(lv_obj_t * object);
  Worker& notify_associated_object();

  template<class ArgumentType> Worker&
  push_task_to_runtime(ArgumentType * user_data, void (*task)(ArgumentType*)){
    push_task_void_to_runtime(user_data, reinterpret_cast<VoidTask>(task));
    return *this;
  }

  bool is_running() const;

  Worker &start(const thread::Thread::Attributes &thread_attributes = {});
  Worker &wait_runtime_task();

private:
  lvgl::Runtime *m_runtime = nullptr;
  thread::Mutex m_mutex;
  thread::Cond m_cond;
  void *m_user_data = nullptr;
  void (*m_user_task)(void *) = nullptr;
  Work m_work_callback = nullptr;
  thread::Thread m_thread;
  API_AF(Worker,lv_obj_t*,associated_object,nullptr);

  void move_worker(Worker &a);
  static void *thread_work_function(void *args);
  void work_function();
  void lock_user_data(void *user_data, void (*task)(void *));
  void unlock_user_data();
  void push_task_void_to_runtime(void *user_data, void (*task)(void *));
  static void execute_runtime_task_function(void *context);
  void execute_runtime_task();

  static void notify_task(lv_obj_t * object);
};

} // namespace design

#endif // DESIGNLAB_WORKER_HPP
