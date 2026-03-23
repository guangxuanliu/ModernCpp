/*************************************************************************************
 * NOTE: The coroutine transformation you've enabled is a hand coded transformation! *
 *       Most of it is _not_ present in the AST. What you see is an approximation.   *
 *************************************************************************************/
#include <coroutine>
#include <iostream>

struct Generator
{
  struct promise_type
  {
    int current_value;
    inline Generator get_return_object()
    {
      return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
    }
    
    inline std::suspend_always initial_suspend()
    {
      std::operator<<(std::cout, "initial_suspend()").operator<<(std::endl);
      return {};
    }
    
    inline std::suspend_always final_suspend() noexcept
    {
      std::operator<<(std::cout, "final_suspend()").operator<<(std::endl);
      return {};
    }
    
    inline std::suspend_always yield_value(int value)
    {
      std::operator<<(std::operator<<(std::cout, "yield_value(").operator<<(value), ")").operator<<(std::endl);
      this->current_value = value;
      return {};
    }
    
    inline void return_void()
    {
      std::operator<<(std::cout, "return_void()").operator<<(std::endl);
    }
    
    inline void unhandled_exception()
    {
      std::operator<<(std::cout, "unhandled_exception()").operator<<(std::endl);
      std::terminate();
    }
    
    // inline constexpr promise_type() noexcept = default;
  };
  
  inline Generator(std::coroutine_handle<promise_type> h)
  : handle{std::coroutine_handle<promise_type>(h)}
  {
    std::operator<<(std::cout, "Generator()").operator<<(std::endl);
  }
  
  inline ~Generator() noexcept
  {
    std::operator<<(std::cout, "~Generator()").operator<<(std::endl);
    this->handle.destroy();
  }
  
  inline bool next()
  {
    if(!this->handle.done()) {
      this->handle.resume();
      return !this->handle.done();
    } 
    
    return false;
  }
  
  inline int value()
  {
    return this->handle.promise().current_value;
  }
  
  std::coroutine_handle<promise_type> handle;
};


struct __counterFrame
{
  void (*resume_fn)(__counterFrame *);
  void (*destroy_fn)(__counterFrame *);
  std::__coroutine_traits_impl<Generator>::promise_type __promise;
  int __suspend_index;
  bool __initial_await_suspend_called;
  int from;
  int to;
  int i;
  std::suspend_always __suspend_107_11;
  std::suspend_always __suspend_112_9;
  std::suspend_always __suspend_107_11_1;
};

Generator counter(int from, int to)
{
  /* Allocate the frame including the promise */
  /* Note: The actual parameter new is __builtin_coro_size */
  __counterFrame * __f = reinterpret_cast<__counterFrame *>(operator new(sizeof(__counterFrame)));
  __f->__suspend_index = 0;
  __f->__initial_await_suspend_called = false;
  __f->from = std::forward<int>(from);
  __f->to = std::forward<int>(to);
  
  /* Construct the promise. */
  new (&__f->__promise)std::__coroutine_traits_impl<Generator>::promise_type{};
  
  /* Forward declare the resume and destroy function. */
  void __counterResume(__counterFrame * __f);
  void __counterDestroy(__counterFrame * __f);
  
  /* Assign the resume and destroy function pointers. */
  __f->resume_fn = &__counterResume;
  __f->destroy_fn = &__counterDestroy;
  
  /* Call the made up function with the coroutine body for initial suspend.
     This function will be called subsequently by coroutine_handle<>::resume()
     which calls __builtin_coro_resume(__handle_) */
  __counterResume(__f);
  
  
  return __f->__promise.get_return_object();
}

/* This function invoked by coroutine_handle<>::resume() */
void __counterResume(__counterFrame * __f)
{
  try 
  {
    /* Create a switch to get to the correct resume point */
    switch(__f->__suspend_index) {
      case 0: break;
      case 1: goto __resume_counter_1;
      case 2: goto __resume_counter_2;
      case 3: goto __resume_counter_3;
    }
    
    /* co_await insights.cpp:107 */
    __f->__suspend_107_11 = __f->__promise.initial_suspend();
    if(!__f->__suspend_107_11.await_ready()) {
      __f->__suspend_107_11.await_suspend(std::coroutine_handle<Generator::promise_type>::from_address(static_cast<void *>(__f)).operator std::coroutine_handle<void>());
      __f->__suspend_index = 1;
      __f->__initial_await_suspend_called = true;
      return;
    } 
    
    __resume_counter_1:
    __f->__suspend_107_11.await_resume();
    for(__f->i = __f->from; __f->i <= __f->to; ++__f->i) {
      std::operator<<(std::cout, "co_yield ").operator<<(__f->i).operator<<(std::endl);
      
      /* co_yield insights.cpp:112 */
      __f->__suspend_112_9 = __f->__promise.yield_value(__f->i);
      if(!__f->__suspend_112_9.await_ready()) {
        __f->__suspend_112_9.await_suspend(std::coroutine_handle<Generator::promise_type>::from_address(static_cast<void *>(__f)).operator std::coroutine_handle<void>());
        __f->__suspend_index = 2;
        return;
      } 
      
      __resume_counter_2:
      __f->__suspend_112_9.await_resume();
    }
    
    /* co_return insights.cpp:107 */
    __f->__promise.return_void()/* implicit */;
    goto __final_suspend;
  } catch(...) {
    if(!__f->__initial_await_suspend_called) {
      throw ;
    } 
    
    __f->__promise.unhandled_exception();
  }
  
  __final_suspend:
  
  /* co_await insights.cpp:107 */
  __f->__suspend_107_11_1 = __f->__promise.final_suspend();
  if(!__f->__suspend_107_11_1.await_ready()) {
    __f->__suspend_107_11_1.await_suspend(std::coroutine_handle<Generator::promise_type>::from_address(static_cast<void *>(__f)).operator std::coroutine_handle<void>());
    __f->__suspend_index = 3;
    return;
  } 
  
  __resume_counter_3:
  __f->destroy_fn(__f);
}

/* This function invoked by coroutine_handle<>::destroy() */
void __counterDestroy(__counterFrame * __f)
{
  /* destroy all variables with dtors */
  __f->~__counterFrame();
  /* Deallocating the coroutine frame */
  /* Note: The actual argument to delete is __builtin_coro_frame with the promise as parameter */
  operator delete(static_cast<void *>(__f), sizeof(__counterFrame));
}


int main()
{
  Generator gen = counter(1, 5);
  while(gen.next()) {
    std::operator<<(std::cout, "Generated value: ").operator<<(gen.value()).operator<<(std::endl);
  }
  
  return 0;
}
