#!/usr/bin/env julia

function greatest_prime_factor(val)
  factor = 1
  while val != 1
    factor += (factor < 3) ? 1 : 2
    while val % factor == 0
      val /= factor
    end
  end
  factor
end

println(greatest_prime_factor(600851475143))
