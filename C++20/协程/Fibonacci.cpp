#include <coroutine>
#include <iostream>

struct Fibonacci 
{
  struct promise_type 
  {
    int current = 0;
    int next = 1;

    Fibonacci get_return_object() 
    {
      return Fibonacci{ std::coroutine_handle<promise_type>::from_promise(*this) };
    }
    std::suspend_always initial_suspend() 
    {
      return { };
    }
    std::suspend_always final_suspend() noexcept 
    {
      return {};
    }
    void return_void() {}
    void unhandled_exception() {}

    // 生成下一个值
    std::suspend_always yield_value(int value) 
    {
      std::swap(current, next);
      next += current;
      return {};
    }
  };

  std::coroutine_handle<promise_type> coro;

  explicit Fibonacci(std::coroutine_handle<promise_type> h) : coro(h) {}

  bool next() 
  {
    if (coro.done())
    {
        return false;
    }

    std::cout << coro.promise().current << '\n';
    coro();
    return true;
  }
};

Fibonacci fibonacci() 
{
  for (int i = 0; i < 10; ++i)
  {
    co_yield i;
  }
}

int main() {

  Fibonacci fib = fibonacci();

  while (fib.next()) {

    // 打印斐波那契数列的前10项
  }

  // 确保协程柄正确销毁
  fib.coro.destroy();
  return 0;
}
