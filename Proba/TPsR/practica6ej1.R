#Ejercicio1
setwd("/home/pato/Desktop/Estadistica")
alfajores <- read.table("alfajores.txt", header = TRUE)
table(alfajores)

# a) la probabilidad de que una caja provenga de la sede Quilmes.
res1 <- 1-mean(alfajores[,2])

# b) la probabilidad de que una caja sea producida por la sede Quilmes y tenga 3 alfajoresdefectuosos.
sum <- 0
for (i in 1:500){
    if ((alfajores[i, 1] == 3) && (alfajores[i,2] == 0)){
        sum <- sum + 1
    }
}
res2 <- sum/500

# c) la funci ́on de probabilidad puntual conjunta del vector (X,Y).
#lo mismo que hice arriba pero para todas las combinaciones de X e Y

# d) la esperanza y la varianza deX.
res4a <- mean(alfajores[,1])
res4b <- var(alfajores[,1])
#  la  probabilidad  de  que  una  caja  producida  por  la  sede  Quilmes  tenga  3  alfajoresdefectuosos.
#P(X=3 | Y=0) = P(X=3 & Y=0)/P(Y=0)
res5 <- res2/res1

# e) la probabilidad de que una caja producida por la empresa y elegida al azar tenga 3alfajores defectuosos (es decirX= 3).

sum <- 0
for (i in 1:500){
    if ((alfajores[i, 1] == 3)){
        sum <- sum + 1
    }
}
res6 <- sum/500

# f) la probabilidad de que una caja con 3 alfajores defectuosos haya sido producida porla sede Quilmes.
#P(Y=0 | X=3) =  P(X=3 & Y=0)/P(X=3)
res7 <- res2/res6
# g) la probabilidad de que una caja con 3 alfajores defectuosos haya sido producida porla sede Pilar.
#P(Y=1 | X=3) =  P(X=3 & Y=1)/P(X=3)
