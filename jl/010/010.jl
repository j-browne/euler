#!/usr/bin/env julia

function prime_sum(max_num)
  primes = fill(true, max_num)
  primes[1] = false
  i = 2
  while i < max_num
    primes[range(2i, stop=max_num, step=i)] .= false
    i += (i < 3) ? 1 : 2
    while i < max_num && primes[i] == false
      i += (i < 3) ? 1 : 2
    end
  end
  sum(x->(x[2] ? x[1] : 0), enumerate(primes))
end

println(prime_sum(2_000_000))
