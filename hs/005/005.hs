main :: IO ()
facts :: Int -> Int -> [Int] -> Int

facts a b xs
  | a == 1  = head xs
  | otherwise  = if a `rem` b == 0
          then facts (a `quot` b) b (a:xs)
          else facts a (succ b) xs

main = print $ facts 600851475143 2 []
