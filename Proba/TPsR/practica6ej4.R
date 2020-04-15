setwd("/home/pato/Desktop/Estadistica")
ciudades <- read.table("ciudades.txt", header = TRUE)
View(ciudades)
boxplot(ciudades)
#a)  Construir en paralelo, para facilitar la comparaci ́on, un box-plot para los datos de cada paıs e identificar los puntos extremos en cada uno de ellos.
#arg
boxplot(ciudades[,1])
#usa
boxplot(ciudades[,2])
#ppbb
boxplot(ciudades[,3])
#japon
boxplot(ciudades[,4])

#b)  Comparar los centros de cada poblaci ́on, sus dispersiones y su simetr ́ıa. ¿Cu ́al es elpa ́ıs m ́as homog ́eneamente habitado?
#No me siento capaz de responder esta pregunta
