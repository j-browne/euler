#!/usr/bin/env julia

function primes(val)
  prime_factors = Dict()
  factor = 1
  while val != 1
    factor += (factor < 3) ? 1 : 2
    while val % factor == 0
      val /= factor
      prime_factors[factor] = get(prime_factors, factor, 0) + 1
    end
  end
  return prime_factors
end

function smallest_multiple(range)
  prime_factors = Dict()
  for i in range
    merge!(max, prime_factors, primes(i))
  end

  multiple = 1
  for (k, v) in prime_factors
    multiple *= k^v
  end
  multiple
end

println(smallest_multiple(2:20))

