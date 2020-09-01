#!/usr/bin/env julia

function is_palindrome(num)
  s = string(num)
  s == reverse(s)
end

function largest_palindrome(range)
  largest = 0
  for i in range.start:range.stop
    for j in i:range.stop
      if is_palindrome(i * j)
        largest = max(largest, i*j)
      end
    end
  end
  largest
end

println(largest_palindrome(100:999))
