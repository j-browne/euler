#!/usr/bin/env julia

function largest_product(len, nums)
  max_prod = 0
  for i in 1:(length(nums) - len + 1)
    p = prod(x->parse(BigInt, x), nums[range(i, length=len)])
    max_prod = max(max_prod, p)
  end
  max_prod
end

println(largest_product(13, readline("input.txt")))
