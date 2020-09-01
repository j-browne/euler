#!/usr/bin/env julia

function is_prime(num, primes)
  !any(x-> (num % x == 0), primes)
end

function nth_prime(nth_val)
  primes = Set()
  num = 1
  while length(primes) < nth_val
    num += (num < 3) ? 1 : 2
    if is_prime(num, primes)
      union!(primes, num)
    end
  end
  num
end

println(nth_prime(10001))
