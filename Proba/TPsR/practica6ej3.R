setwd("/home/pato/Desktop/Estadistica")
graduados <- scan("graduados.txt")

#a)  Calcular la media muestral y la mediana muestral.
media <- mean(graduados)
mediana <-median(graduados)
#b)  Calcular el desv ́ıo est ́andar muestral y la distancia intercuartil.
desvEst <- sd(graduados)
iqr <- quantile(graduados, 0.75) - quantile(graduados, 0.25)
#c)  Realice un histograma con los datos.
hist(graduados, prob = TRUE)

#d)  Realice un boxplot con este conjunto de datos. ¿Cu ́ales son sus caracter ́ısticas m ́assobresalientes? ¿C ́omo relaciona lo observado en los gr ́aficos con los valores estimadosde media y mediana obtenidos en a)? ¿Hay outliers?
boxplot(graduados)
#No se bien como expresarlo, pero esta distribuido de forma bastante "uniforme" (ya se que uniforme es una palabra muy especifica en esta materia). Pareceria que no hay outliers.
#e)  ¿Qu ́e distribuci ́on cree que tienen estos datos?
#normal
#f)  Superponga en el histograma la curva de una densidad apropiada con los par ́ametrosque considere pertinentes. Explore el comandodensityen R.
hist(graduados, prob = TRUE)
lines(density(graduados, bw=0.1))

#g)  ¿Qu ́e otro gr ́afico conoce que le permitir ́ıa verificar si su conjetura es razonable?

qqnorm(graduados)
qqline(graduados)
#es bastante parecido
