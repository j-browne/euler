#!/usr/bin/env julia

function factors(num)
  factors = 2
  for i in 2:sqrt(num)
    if num % i == 0
      factors += 2
    end
  end
  factors
end

function triangle_with_factors(min_factors)
  n = 1
  triangle = 1
  while factors(triangle) <= 500
    n += 1
    triangle += n
  end
  triangle
end

println(triangle_with_factors(500))
