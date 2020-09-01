main :: IO ()

tri = (1,1):(fst (last tri) + 1,snd (last tri) + fst (last tri))

main = print "hi" 
