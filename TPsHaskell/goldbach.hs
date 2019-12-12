esPrimo :: Integer -> Bool
esPrimo n = ((sumaDivisoresHasta n n) == (n + 1))

sumaDivisoresHasta :: Integer -> Integer -> Integer
sumaDivisoresHasta n k | k == 1 = 1
					   					 | k > 1 && (mod n k) == 0 = (sumaDivisoresHasta n (k-1)) + k
					   			 		 | k > 1 && (mod n k) /= 0 = (sumaDivisoresHasta n (k-1))


iterPrimos :: Integer -> Integer -> Integer -> Bool
iterPrimos n p1 p2 | n < p1 + p2 && p2 >= p1 = iterPrimos n (siguientePrimo p1) 2
					  					| n < p1 + p2 && p1 > p2 = False
			          			| n == p1 + p2 = True
			          			| n > p1 + p2 = iterPrimos n p1 (siguientePrimo p2)

siguientePrimo :: Integer -> Integer
siguientePrimo p | esPrimo (p+1) = p+1
				 				 | not (esPrimo (p+1)) = siguientePrimo (p + 1)


esSumaDeDosPrimos :: Integer -> Bool
esSumaDeDosPrimos n | n == 2 + 2 = True
								 		| otherwise = iterPrimos n 2 3

goldbach :: Integer -> Bool
goldbach 2 = True
goldbach n = esSumaDeDosPrimos n && goldbach (n-2)
