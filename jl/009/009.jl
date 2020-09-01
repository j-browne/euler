#!/usr/bin/env julia

function triplet_product(sum)
  for i in 1:sum
    for j in i:sum
      k = sum - i - j
      if i^2 + j^2 == k^2
        return i*j*k
      end
    end
  end
end

println(triplet_product(1000))
