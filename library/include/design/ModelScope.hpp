//
// Created by Tyler Gilbert on 12/16/21.
//

#ifndef DESIGN_API_DESIGN_MODEL_SCOPE_HPP
#define DESIGN_API_DESIGN_MODEL_SCOPE_HPP

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

private:
  static void deleter(Construct * construct);
  using Pointer = api::UniquePointer<Construct, decltype(&deleter)>;
  Pointer m_pointer;
};

} // namespace design

#endif // DESIGN_API_DESIGN_MODEL_SCOPE_HPP
