setwd("/home/pato/Desktop/Estadistica")
lamparas <- scan("lamparas.txt", 0)
#a)Estimar la probabilidad de que una lampara producida por esta fabrica dure mas de 30 horas.
length(lamparas[lamparas>30])/27

#b)Implementar y graficar la funci ́on de distribuci ́on emp ́ırica de este conjunto de datos.
hist(lamparas, prob=TRUE)

#c)Completar:  Estos  datos  permiten  estimar  que  el  90 %  de  las  l ́amparas  producidaspor esta f ́abrica dura m ́as de . . . . . . horas y el 10 % dura menos de . . . . . . horas.

#P(X>x) = 0.9
#1- P(X<x) = 0.9
#P(X<x) = 0.1
#Estoy buscando el percentil 10?
quantile(lamparas, 0.1)
