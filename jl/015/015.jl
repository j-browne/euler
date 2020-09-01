#!/usr/bin/env julia

function num_paths(size)
  binomial(2*size, size)
end

println(num_paths(20))
