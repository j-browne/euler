#!/usr/bin/env julia

function get_sum(lines)
  sum(x->parse(BigInt, x), lines)
end

println(string(get_sum(readlines("input.txt")))[1:10])
