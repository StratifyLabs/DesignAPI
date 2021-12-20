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
  Construct *m_construct;

};

class Worker : public api::ExecutionContext {
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

  Worker &update_runtime(void *user_data, void (*task)(void *));

  bool is_running() const {
    return m_thread.is_valid() && m_thread.is_running();
  }

  Worker &start(const thread::Thread::Attributes &thread_attributes = {});

private:
  lvgl::Runtime *m_runtime = nullptr;
  thread::Mutex m_mutex;
  thread::Cond m_cond;

  void *m_user_data = nullptr;
  void (*m_user_task)(void *) = nullptr;

  Work m_work_callback = nullptr;
  thread::Thread m_thread;

  void move_worker(Worker &a);

  static void *thread_work_function(void *args);
  void work_function();
  void lock_user_data(void *user_data, void (*task)(void *));
  void unlock_user_data();

  static void runtime_task_function(void *context);
  void runtime_task();
};

} // namespace design

#endif // DESIGNLAB_WORKER_HPP
