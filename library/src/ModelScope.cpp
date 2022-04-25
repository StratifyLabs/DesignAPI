//
// Created by Tyler Gilbert on 3/7/22.
//

#include "design/ModelScope.hpp"

using namespace design;

ModelScope::ModelScope(ModelScope::Construct &options)
  : thread::Mutex::Scope(options.mutex), m_pointer(&options, &deleter) {
  options.pthread_scoped = thread::Thread::self();
  ++options.lock_count;
}

void ModelScope::deleter(Construct * construct){
  --construct->lock_count;
  if (construct->lock_count == 0) {
    construct->pthread_scoped = {};
  }
}

bool ModelScope::Construct::is_available() const {
  return pthread_scoped == thread::Thread::self();
}