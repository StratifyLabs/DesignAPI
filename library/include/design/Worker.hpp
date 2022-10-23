//
// Created by Tyler Gilbert on 12/16/21.
//

#ifndef DESIGN_API_DESIGN_WORKER_HPP
#define DESIGN_API_DESIGN_WORKER_HPP

#include <algorithm>

#include <lvgl/Bar.hpp>
#include <lvgl/Runtime.hpp>

#include <thread/Cond.hpp>
#include <thread/Mutex.hpp>
#include <thread/Thread.hpp>

namespace design {

class Worker : public api::ExecutionContext {
public:
  using Task = api::Function<void()>;
  Worker() : m_cond(m_mutex) {}

  Worker(Worker &&a) : m_cond(m_mutex) { swap_worker(a); }
  Worker &operator=(Worker &&a) {
    swap_worker(a);
    return *this;
  }

  lvgl::Runtime &runtime();
  const lvgl::Runtime &runtime() const;
  bool is_running() const;
  Worker &wait_runtime_task();
  void start(const thread::Thread::Attributes &thread_attributes = {});

protected:
  Worker(lvgl::Runtime *runtime, lv_obj_t *associated_object);

  void push_user_task_to_runtime(Task task);
  static void notify_task(lv_obj_t *object);

private:
  lvgl::Runtime *m_runtime = nullptr;
  thread::Mutex m_mutex;
  thread::Cond m_cond;
  Task m_user_task;
  thread::Thread m_thread;
  API_RAF(Worker, lv_obj_t *, associated_object, nullptr);

  void swap_worker(Worker &a);
  void lock_user_task(Task task);
  void unlock_user_task();
  void execute_runtime_task();

  virtual void work() = 0;
};

template <class Derived> class WorkerAccess : public Worker {
public:
  WorkerAccess() = default;
  WorkerAccess(
    lvgl::Runtime *runtime,
    lv_obj_t *associated_object)
    : Worker(runtime, associated_object) {}

  Derived &push_task_to_runtime(Task task) {
    push_user_task_to_runtime(std::move(task));
    return static_cast<Derived &>(*this);
  }

  Derived &notify(lv_obj_t *object) {
    push_user_task_to_runtime([object]() { notify_task(object); });
    return static_cast<Derived &>(*this);
  }

  Derived &notify_associated_object() {
    if (associated_object()) {
      return notify_task(associated_object());
    }
    return static_cast<Derived &>(*this);
  }

private:
};

} // namespace design

#endif // DESIGN_API_DESIGN_WORKER_HPP
