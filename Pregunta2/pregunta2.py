
def comprobar(atributos,tupla1,tupla2):
    resultado=0
    for i in atributos:
        pos_R=atributos_R.index(i)
        pos_S=atributos_S.index(i)
        if tupla1[pos_R]==tupla2[pos_S]:
            resultado+=1
    if resultado==len(atributos):
        return True
    else: return False
fr = open("grafo.txt", "r") #se abre el archivo
cant_at_R = 2 #se le la primera linea, que corresponde a la cantidad de relaciones
print("Cantidad de atributos de R: ",cant_at_R)
atributos_R = ('1' '2') #se lee la segunda linea, que son los atributos de la relacion
print("Los atributos de R son",atributos_R)
lista_tuplas_R=[] #se define un arreglo
c = 0
for i in fr:
    lista_tuplas_R.append(tuple(i.strip().split())) #se lee el contenido de cada tupla
    c += 1
cant_tuplas_R = 9  # lee la tercera linea, que corresponde a la cantidad de
print("Tiene " + str(cant_tuplas_R) + " tuplas")
print("Sus tuplas son: ",lista_tuplas_R)  #imprime todas las tuplas leidas
cant_at_S = 2
print("Cantidad de atributos de S: ",cant_at_S)
atributos_S = ('2' '3')
print("Los atributos de S son",atributos_S)
cant_tuplas_S = c
print("Tiene "+str(cant_tuplas_S)+" tuplas")
lista_tuplas_S= lista_tuplas_R
print("Sus tuplas son: ",lista_tuplas_S)
atributos_de_join=list(set(atributos_R)&set(atributos_S))
atributos_en_orden=list(set(atributos_R)|set(atributos_S))
atributos_en_orden.sort()
print("Los atributos de Join son:",atributos_de_join)
print("Los atributos de la relacion final es",atributos_en_orden)
#fw = open("salida.txt", "w")
#fw.write(str(len(atributos_en_orden))+"\n") #escribe la cantidad de atributos totales de la relacion R
#for i in atributos_en_orden:
    #fw.write(i+" ") #escribe todos los atributos en la siguiente linea
#fw.write("\n")
respuesta=[]
for tupla_R in lista_tuplas_R:
    for tupla_S in lista_tuplas_S:
        if comprobar(atributos_de_join,tupla_R,tupla_S):
            linea=""
            for x in atributos_en_orden:
                if x in atributos_R:
                    linea=linea+tupla_R[atributos_R.index(x)]+" "
                else:
                    linea=linea+tupla_S[atributos_S.index(x)]+" "
            respuesta.append(linea+"\n")
#fw.write(str(len(respuesta))+"\n")
lista_final = []
ciclos = 0
aux = respuesta
repeticiones = []
i = 0
auxiliar = []
for uwu in respuesta:
    auxiliar.append((uwu[0],uwu[2],uwu[4]))
for r in aux:
    if i not in repeticiones:
        lol = (r[4],r[0])
        if lol in lista_tuplas_R:
            goku = (r[2],r[4],r[0])
            vegeta = (r[4],r[0],r[2])
            repeticiones.append(auxiliar.index(goku))
            repeticiones.append(auxiliar.index(vegeta))
            ciclos += 1
    i += 1
    #fw.write(r)
print('El grafo evaluado tiene',ciclos,'ciclos')
ff = open("salida2.txt", "w")
ff.write(str(ciclos) + "\n")  # resultado final
fr.close()
#fw.close()
ff.close()