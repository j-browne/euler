#!/usr/bin/env julia

function get_sum(max)
  total = 0
  for i in 1:(max - 1)
    if i % 3 == 0 || i % 5 == 0
      total += i
    end
  end
  total
end

println(get_sum(1000))
