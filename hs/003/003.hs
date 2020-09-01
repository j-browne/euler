main :: IO ()
high :: Int -> Int -> [Int] -> Int

high a b xs
	| a == 1	= head xs
	| otherwise	= if a `rem` b == 0
					then high (a `quot` b) b (a:xs)
					else high a (succ b) xs

main = print $ high 600851475143 2 []
