#nombre = input("Ingrese su nombre: ")
#print("Hola "+nombre+", welcome back to python")
fr = open("entrada.txt", "r")
cant_at_R = int(fr.readline().strip())
print("Cantidad de atributos de R: ",cant_at_R)
atributos_R = fr.readline().strip().split()
print("Los atributos de R son",atributos_R)
cant_tuplas_R = int(fr.readline().strip())
print("Tiene "+str(cant_tuplas_R)+" tuplas")
lista_tuplas_R=[]
for i in range(cant_tuplas_R):
    lista_tuplas_R.append(tuple(fr.readline().strip().split()))
print("Sus tuplas son: ",lista_tuplas_R)
cant_at_S = int(fr.readline().strip())
print("Cantidad de atributos de S: ",cant_at_S)
atributos_S = fr.readline().strip().split()
print("Los atributos de S son",atributos_S)
cant_tuplas_S = int(fr.readline().strip())
print("Tiene "+str(cant_tuplas_S)+" tuplas")
lista_tuplas_S=[]
for i in range(cant_tuplas_S):
    lista_tuplas_S.append(tuple(fr.readline().strip().split()))
print("Sus tuplas son: ",lista_tuplas_S)
atributos_de_join=set(atributos_R)&set(atributos_S)
atributos_en_orden=list(set(atributos_R)|set(atributos_S))
atributos_en_orden.sort()
print(atributos_en_orden)
fw = open("salida.txt", "w")
fw.write(str(len(atributos_en_orden))+"\n")
for i in atributos_en_orden:
    fw.write(i+" ")
fw.write("\n")
for i in atributos_de_join:
    print(i)
    pos_R=atributos_R.index(i)
    pos_S=atributos_S.index(i)
    respuesta=[]
    for tupla_R in lista_tuplas_R:
        for tupla_S in lista_tuplas_S:
            if tupla_R[pos_R]==tupla_S[pos_S]:
                linea=""
                for x in atributos_en_orden:
                    if x in atributos_R:
                        linea=linea+tupla_R[atributos_R.index(x)]+" "
                    else:
                        linea=linea+tupla_S[atributos_S.index(x)]+" "
                respuesta.append(linea+"\n")
    fw.write(str(len(respuesta))+"\n")
    for r in respuesta:
        fw.write(r)
fr.close()
fw.close()