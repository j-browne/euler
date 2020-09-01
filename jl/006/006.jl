#!/usr/bin/env julia

function difference(range)
  sum(range)^2 - sum(abs2, range)
end

println(difference(1:100))
