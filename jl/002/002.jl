#!/usr/bin/env julia

function sum_fib(max)
  sum = 0
  fib = (1, 2)
  while fib[2] <= max
    if fib[2] % 2 == 0
      sum += fib[2]
    end
    fib = (fib[2], fib[1] + fib[2])
  end
  sum
end

println(sum_fib(4_000_000))
