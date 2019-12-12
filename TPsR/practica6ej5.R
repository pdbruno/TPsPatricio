setwd("/home/pato/Desktop/Estadistica")
ingresos <- scan("ingresos.txt")

#a)  ¿Cu ́al es el ingreso m ́ınimo percibido por los trabajadores encuestados? Estime laproporci ́on de los trabajadores de la ciudad que percibe el ingreso m ́ınimo.
min <- min(ingresos)
length(ingresos[ingresos == min])/length(ingresos)
#b)  Estimar el ingreso mensual que se necesita para pertenecer al 10 % de trabajadoresde la ciudad con ingresos m ́as altos.
quantile(ingresos, 0.9)
#c)  Calcular la media muestral, la mediana muestral y la mediaα-podada conα= 0,10(10 %).
mean(ingresos)
median(ingresos)
mean(ingresos,trim = 0.1)
#d)  Calcular el desv ́ıo est ́andar muestral y la distancia intercuartil.
sd(ingresos)
quantile(ingresos, 0.75) - quantile(ingresos, 0.25)
#e)  Realizar un histograma y un boxplot. ¿Cu ́ales son las caracter ́ısticas m ́as sobresa-lientes? ¿Hay outliers?
#muchisimas personas cobran la minima o un poco mas. hay muchos outliers
#)  ¿Cree que los datos tienen distribuci ́on normal?
#no bro
#g)  Discutir ventajas y desventajas de cada medida de posici ́on para describir el centrode los datos.
#uff me estas pidiendo mucho
