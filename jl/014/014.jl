#!/usr/bin/env julia

function collatz_len(num)
  len = 1
  curr = num
  while curr != 1
    if curr % 2 == 0
      curr = div(curr, 2)
    else
      curr = 3 * curr + 1
    end
    len += 1
  end
  len
end

function longest_chain(max_num)
  longest = (0, 0)
  for i in 1:(max_num-1)
    len = collatz_len(i)
    if len > longest[2]
      longest = (i, len)
    end
  end
  longest[1]
end

println(longest_chain(1_000_000))
