
/*
	Objetivo: Administración de alumnos y materias
	Fecha de entrega: 17/Mayo/2017
	Elaboró: Jesús Alejandro Yahuitl Rodríguez y Belén Tepoz Romero
*/

#include <stdio.h>
#include <string.h>   //<------------agregamos una nueva libreria
#include <stdlib.h>
#define max 20
#define materi 9


//declaramos nuestra estructura
typedef struct {
	char nomb[20],app[20],apm[20];
}nom;
typedef struct {	
	char matricula[10];
	char plan[15];
	nom  nombre;
	int edad;
	int num_materias;
	float calif[materi];
	char cve_materias[materi][10];
	int total_creditos;
	char nivel[20];
	float promedio;
}info;


struct nodo{
	info informacion;
	struct nodo *sig;
};
//---------------------------------------
typedef struct {
	char clave[10];
	char nombre[30];
	char nivel[10];
	int creditos;
	
}datos;

struct materias{
	datos dato;
	struct materias *sig;
};
typedef struct materias ingenieria;
typedef struct materias licenciatura;

typedef struct nodo Datos;

int menu();
int submenu();
void altas(Datos **apun_alum_inicial, Datos **apun_alum, ingenieria **inicioIng, ingenieria **iniciolLic);
void agregar_alumno(Datos **apun_alum_inicial,Datos **apun_alum,char matricula[10],char plan[15],nom nombres,int edad,int num_materias,float calif[materi],char cve_materias[materi][10],int total_creditos,char nivel[20],float promedio);
void mayusculas(Datos *);
int validarMatricula(Datos *,char matricula[10]);
int repetir();
void eliminar(Datos **, Datos **);
int registros(Datos **);
void modificar(Datos **,ingenieria **inicioIng, ingenieria **iniciolLic);
int menu_consultas();
void consultas(Datos **,ingenieria **inicioIng, ingenieria **inicioLic);
void todos_alum(Datos **);
void un_alum(Datos **);
void alumnos_reprobados(Datos **);
void alumnos_aprobados(Datos **);
void guardar_alumnos(Datos **);
void carga_alumnos(Datos **,Datos **);
void consulta_por_materia(Datos **apun_alum_inicial,ingenieria **inicioIng, ingenieria **inicioLic);
//------------------------------catalogos
int consultasing_lic(void);
int menu_licenciatura_ingenieria(void);
void insertar_materia(ingenieria **inicio,ingenieria **actual, char clave[10],char nombre[30],char nivel[10],int creditos);
void ver(ingenieria **);
void guardar(ingenieria **,int *);
void cargar(ingenieria **,ingenieria **,int *);
void buscar(ingenieria **);
void borrar(ingenieria **,ingenieria **);
void cambiar(ingenieria **);
int nregistros(ingenieria **);
void agregar_materia(ingenieria **,ingenieria **);
ingenieria *validar_clave(ingenieria **inicio, char clave[20]);

int main(){
	Datos *apun_alum;
	Datos *apun_alum_inicial=NULL;
	int op,ops,r,menu_licenciatura_ingenieria_op;
	carga_alumnos(&apun_alum_inicial,&apun_alum);
 	//---------------catalogos
	int dato,ingenieria_licenciatura_op;
	ingenieria *inicioIng=NULL;
	ingenieria *actualIng;
	ingenieria *inicioLic=NULL;
	ingenieria *actualLic;
	ingenieria_licenciatura_op=1;
	cargar(&inicioIng,&actualIng,&ingenieria_licenciatura_op);
	ingenieria_licenciatura_op=2;
	cargar(&inicioLic,&actualLic,&ingenieria_licenciatura_op);
	do{
		op=menu();
		switch (op)
	 	{
		case 1:
			do{
				printf("\n\t\t\t\t---Altas---\n\t\t\t\t");
				ops=submenu();
				switch (ops){
					case 1:
							printf("\n\t\t\t\t---Altas Alumnos---\n\t\t\t\t");
							do{
								altas(&apun_alum_inicial,&apun_alum,&inicioIng,&inicioLic);
							}while(repetir()==1);
						
					break;
					case 2:
						printf("\n\t\t\t\t---Altas Materias---\n\t\t\t\t");
						do{
							menu_licenciatura_ingenieria_op=menu_licenciatura_ingenieria();
							switch (menu_licenciatura_ingenieria_op){
								case 1:
										do{
											agregar_materia(&inicioIng,&actualIng);
											r=repetir();
										}while(r==1);
									
								break;
								case 2: 
										do{
												agregar_materia(&inicioLic,&actualLic);
												r=repetir();
										}while(r==1);
								break;
								case 3: break;
								default:
									printf("ERROR: Opcion no encontrada\n");
								break;
							}
						}while(menu_licenciatura_ingenieria_op!=3);

					break;
					case 3: break;
					default:printf("ERROR: Opcion no encontrada\n");break;
				}
			}while(ops!=3);
		break;
		case 2:
			do{
				printf("\n\t\t\t\t---Bajas---\n\t\t\t\t");
				ops=submenu();
				switch (ops){
					
					case 1:
						printf("\n\t\t\t\t--- Alumnos---\n\t\t\t\t");
						do{
							eliminar(&apun_alum_inicial,&apun_alum);
						}while(repetir()==1);
					break;
					case 2: 
						printf("\n\t\t\t\t---Materias---\n\t\t\t\t");
						do{
							menu_licenciatura_ingenieria_op=menu_licenciatura_ingenieria();
							switch (menu_licenciatura_ingenieria_op){
								case 1:
									do{
										borrar(&inicioIng,&actualIng);
									}while(repetir()==1);
								break;
								case 2: 
									do{
										borrar(&inicioLic,&actualLic);
									}while(repetir()==1);
								break;
								case 3: break;
								default:
									printf("ERROR: Opcion no encontrada\n");
								break;
							}
						}while(menu_licenciatura_ingenieria_op!=3);
					break;
					case 3: break;
					default:
						printf("ERROR: Opcion no encontrada\n");
					break;
				}
			}while(ops!=3);
		break;
			case 3:
				do{
					printf("\n\t\t\t\t---Modificar informacion---\n\t\t\t\t");
					ops=submenu();
					switch (ops){
						case 1:
							printf("\n\t\t\t\t---Alumnos---\n\t\t\t\t");
							do{
								modificar(&apun_alum_inicial,&inicioIng,&inicioLic);
							}while(repetir()==1);
						break;
						case 2: 
							printf("\n\t\t\t\t---Materias---\n\t\t\t\t");
							do{
								menu_licenciatura_ingenieria_op=menu_licenciatura_ingenieria();
								switch (menu_licenciatura_ingenieria_op){
									case 1:
										do{
											cambiar(&inicioIng);
										}while(repetir()==1);
									break;
									case 2: 
										do{
											cambiar(&inicioLic);
										}while(repetir()==1);
									break;
									case 3: break;
									default:
										printf("ERROR: Opcion no encontrada\n");
									break;
								}
							}while(menu_licenciatura_ingenieria_op!=3);
						
						break;
						case 3: break;
						default:
							printf("ERROR: Opcion no encontrada\n");
						break;
					}
				}while(ops!=3);
			break;
		case 4:
			
			do{
				printf("\n\t\t\t\t---Consultas---\n\t\t\t\t");
				ops=submenu();
				switch (ops){
					case 1:
						printf("\n\t\t\t\t---Alumnos---\n\t\t\t\t");
						if(apun_alum_inicial==NULL)
							printf("No hay Consultas ya que no se ha ingresado ningun alumno\n");
							
						else
							do{
								consultas(&apun_alum_inicial,&inicioIng,&inicioLic);
							}while(repetir()==1);
							
					break;
					case 2:
						do{
							
							printf("\n\t\t\t\t---Materias---\n\t\t\t\t");
							switch (consultasing_lic()){
								case 1:
									if(menu_licenciatura_ingenieria()==1)
										ver(&inicioIng);
									else
										ver(&inicioLic);
								break;
								case 2: 
									if(menu_licenciatura_ingenieria()==1)
									buscar(&inicioIng);
								else
									buscar(&inicioLic);
								
								break;
								case 3: break;
								default:
									printf("ERROR: Opcion no encontrada\n");
								break;
								}
						}while(consultasing_lic()!=3);
					break;
					case 3: break;
					default:
						printf("ERROR: Opcion no encontrada\n");
					break;
				}
			}while(ops!=3);
		break;
		
		case 5:
				guardar_alumnos(&apun_alum_inicial);
				ingenieria_licenciatura_op=1;
				guardar(&inicioIng,&ingenieria_licenciatura_op);
				ingenieria_licenciatura_op=2;
				guardar(&inicioLic,&ingenieria_licenciatura_op);
			printf("\n\t\t\tGRACIAS POR USAR EL PROGRAMA..!!!\t\t\t\t\n\n");
			break;
		default:
			printf("ERROR: Opcion no encontrada\n");
			break;
		}
	}while(op!=5);
	
	
	return 0;
}

int consultasing_lic(){
	int op;
	printf("Bienvenido MENÚ\n1.Ver todos \n2.Buscar\n3.Salir\nElija su opción deseada: "); scanf("%d",&op);
	return op;
}
//Funcion: Muestra el menú principal.
//Recibe: 
//Modifica:
//Retorna: La opción elegida.
int menu(){
	int opcion;
		printf("\n\t\t\t---M E N U  P R I N C I P A L---\n\n\t\t\t\t1.-Altas.\n\t\t\t\t2.-Bajas.\n\t\t\t\t3.-Mod.Informacion.\n\t\t\t\t4.-Consultas.\n\t\t\t\t5.-Salir\n\t\t\t\tElija la opcion que desee: \n\t\t\t\t");
	scanf("%d",&opcion);
	return opcion;
}
//Funcion: Muestra el submenú.
//Recibe:
//Modifica: 
//Retorna: La opción elegida.
int submenu(){
	int opcion;
		printf("\n\t\t\t\t1.-Alumnos\n\t\t\t\t2.-Catalogos\n\t\t\t\t3.-Regresar\n\t\t\t\tSeleccione opcion: \n\t\t\t\t");
	scanf("%d",&opcion);
	return opcion;
}
//Funcion: Muestra las opciones para elegir ingeniería o licenciatura.
//Recibe:
//Modifica:
//Retorna: La opción elegida.
int menu_licenciatura_ingenieria(){
	int opcion;
		printf("\n\t\t\t\t1.-Ingenieria\n\t\t\t\t2.-Licenciatura\n\t\t\t\t3.-Regresar\n\t\t\t\tSeleccione opcion: \n\t\t\t\t");
	scanf("%d",&opcion);
	return opcion;
}
//Funcion: Muestra la opción a repetir
//Recibe:
//Modifica:
//Retorna: La opción elegida.
int repetir(){
	int r;
		printf("¿Desea repetir? 1-. Otro.-No\nIngrese su opcion: ");
		scanf("%d",&r);
	return r;
}
//Funcion: Lectura de los datos de alumnos.
//Recibe: Apuntadores inicial y actual de la lista ligada de alumnos, de materias de ingenieria y de materias de licenciatura.
//Modifica: Apuntadores inicial y actual de la lista ligada de alumnos, de materias de ingenieria y de materias de licenciatura.
//Retorna:
void altas(Datos **apun_alum_inicial, Datos **apun_alum, ingenieria **inicioIng, ingenieria **inicioLic){
	char matricula[10];
	char plan[15];
	nom nombres;
	int edad,num_materias,aux_materia,j;
	float calif[materi];
	char cve_mat[materi][10];
	int total_creditos=0;
	char nivel[15];
	float promedio,prom=0;
	int aux1,p,i=0,contBasica=0,contFormativa=0;
	char  inge[]="INGENIERIA",licen[]="LICENCIATURA";
	char basica[]="Básica";
	char formativa[]="Formativa";
	Datos *aux=*apun_alum;
	Datos *cabecera=*apun_alum_inicial;
	ingenieria *validarIng,*validarLic;
	getchar();
	do{
		printf("Ingrese matricula: "); scanf("%s",matricula);
		if(cabecera==NULL)
			aux1=1;
		else{
			aux1=validarMatricula(cabecera,matricula);
			if(aux1==0)
				printf("ERROR: La matricula ya existe.\n");
		}
	}while(aux1==0);
	
	do{
		printf("Plan de Estudios.\n1.-Ingenieria\n2.-Licenciatura:\n");
		scanf("%d",&p);
		if(p!=1 && p!=2)
			printf("opcion no valida intentelo nuevamente\n");
	}while(p!=1 && p!=2);	
	if(p==1)
		strcpy(plan,inge);
	if(p==2)
		strcpy(plan,licen);
	getchar();
	printf("Ingrese nombre(s): "); 
	gets(nombres.nomb);	
	printf("Ingrese apellido paterno: ");  gets(nombres.app);
	printf("Ingrese apellido materno: "); gets(nombres.apm);
	do{
		printf("Ingrese Edad del Alumno:");
		scanf("%d",&edad);
		if(edad<0 )
			printf("ERROR:  debe ser>0\n");
	}while(edad<0);
	do{
		printf("Ingrese No. de Materias:");
		scanf("%d",&num_materias);
		if(num_materias<0 )
			printf("ERROR:  debe ser>0\n");
		if(p==1)  i=nregistros(inicioIng);
		if(p==2)  i=nregistros(inicioLic);
		if(num_materias>i)
			printf("ERROR:  NO existen todo ese numero de materias\n");
	}while(num_materias<0 || num_materias>i);

	for(i=0;i<num_materias;i++){
			if(p==1){
				do{
					do{
						getchar();
						printf("\nIngrese la %d Clave:",i+1);	 gets(cve_mat[i]);
						aux_materia=1;
						j=0;
						while(aux_materia==1 && j<i){
							if(strcmp(cve_mat[j],cve_mat[i])==0)
								aux_materia=0;
							j++;
						}
						if(aux_materia==0)
							printf("ERROR: Materia ya ingresada\n");
					}while(aux_materia==0);
					validarIng=validar_clave(inicioIng,cve_mat[i]);
					if(validarIng!=NULL){
						printf("Eligió %s\n", validarIng->dato.nombre);
						total_creditos+=validarIng->dato.creditos;
						if(strcmp(basica,validarIng->dato.nivel)==0)
							contBasica++;
						if(strcmp(formativa,validarIng->dato.nivel)==0)
							contFormativa++;
					}
					else
						printf("Error: La clave de matería no existe.\n");
				}while(validarIng==NULL);
			}

			if(p==2){
				do{
					do{
						getchar();
						printf("\nIngrese la %d Clave:",i+1);	 gets(cve_mat[i]);
						aux_materia=1;
						j=0;
						while(aux_materia==1 && j<i){
							if(strcmp(cve_mat[j],cve_mat[i])==0)
								aux_materia=0;
							j++;
						}
						if(aux_materia==0)
							printf("ERROR: Materia ya ingresada\n");
					}while(aux_materia==0);
					validarLic=validar_clave(inicioLic,cve_mat[i]);
					if(validarLic!=NULL){
						printf("Eligió %s\n", validarLic->dato.nombre);
						total_creditos+=validarLic->dato.creditos;
						if(strcmp(basica,validarLic->dato.nivel)==0)
							contBasica++;
						if(strcmp(formativa,validarLic->dato.nivel)==0)
							contFormativa++;
					}
					else
						printf("Error: La clave de matería no existe.\n");
				}while(validarLic==NULL);
			}
			do{
				printf("\nIngrese la %d calificacion:",i+1);
				scanf("%f", &calif[i]);
				if(calif[i]<0 || calif[i]>10)
					printf("ERROR: La calificacion debe estar entre 0 y 10\n");
				else
					prom+=calif[i];
			}while(calif[i]<0 || calif[i]>10);
	}
		
	if(contBasica>=contFormativa) strcpy(nivel,basica);
	else strcpy(nivel,formativa);
	
	printf("El total de creditos es: %d y el alumno esta en el nivel %s.",total_creditos,nivel);
	promedio=prom/num_materias;
	agregar_alumno(apun_alum_inicial,apun_alum,matricula,plan,nombres,edad,num_materias,calif,cve_mat,total_creditos,nivel,promedio);
	return;

}
//Funcion: Lectura de los datos de alumnos.
//Recibe: Todos los datos de los alumnos y apuntadores inicial y actual.
//Modifica: Todos los datos de los alumnos y apuntadores inicial y actual.
//Retorna:
void agregar_alumno(Datos **apun_alum_inicial,Datos **apun_alum,char matricula[10],char plan[15],nom nombres,int edad,int num_materias,float calif[materi],char cve_materias[materi][10],int total_creditos,char nivel[20],float promedio){
	
	Datos *apunta=(Datos *)malloc(sizeof(Datos));//se crea nodo
	Datos *aux=*apun_alum;
	Datos *cabecera=*apun_alum_inicial;
	int i=0;
	if(apunta==NULL)
		printf("\n No se pudo asignar memoria");
	else{
	
		strcpy(apunta->informacion.matricula,matricula);
		strcpy(apunta->informacion.plan,plan);
		strcpy(apunta->informacion.nombre.nomb,nombres.nomb);	
		strcpy(apunta->informacion.nombre.app,nombres.app);
		strcpy(apunta->informacion.nombre.apm,nombres.apm);
		apunta->informacion.edad=edad;
		apunta->informacion.num_materias=num_materias;
		mayusculas(apunta);
		for(i=0;i< apunta->informacion.num_materias;i++)
			strcpy(apunta->informacion.cve_materias[i],cve_materias[i]);
		for(i=0;i< apunta->informacion.num_materias;i++)
			apunta->informacion.calif[i]=calif[i];
		apunta->informacion.total_creditos=total_creditos;
		strcpy(apunta->informacion.nivel,nivel);
		apunta->informacion.promedio=promedio;
		apunta->sig=NULL;
		printf("\nAlumno %s %s %s registrado exitosamente con la matricula %s  y con un promedio de %f\n",apunta->informacion.nombre.app,apunta->informacion.nombre.apm,apunta->informacion.nombre.nomb,apunta->informacion.matricula,apunta->informacion.promedio);
		
		//se enlaza en el nodo o se coloca como cabeza de la lista
		if(cabecera==NULL)//si la lista esta vacia
			*apun_alum_inicial=apunta;//es el primer elemento de la lista
		else
			aux -> sig = apunta;

		*apun_alum=apunta;//se actualiza el apuntador al ultimo
		
	}

	return;	
}
//Funcion: Valida la matricula mediante un aux.
//Recibe: La matricula a validar y apuntador inicial.
//Modifica:
//Retorna:
int validarMatricula(Datos *apun_alum_inicial,char matricula[10]){
	int aux;
	Datos *apun_alum_incrementa;
	apun_alum_incrementa=apun_alum_inicial;
	aux=1;
	while(apun_alum_incrementa!= NULL && aux==1){
		if(strcmp(matricula,apun_alum_incrementa->informacion.matricula)==0)
			aux=0;
		else
			apun_alum_incrementa=apun_alum_incrementa->sig;
		
	}
	return aux;
}
//Funcion: Trasforma todo a mayusculas.
//Recibe: Apuntador inicial de alumnos.
//Modifica: Minusculas a mayusculas de los datos ingresados por alumno.
//Retorna:
void mayusculas(Datos *apunta){
	int i;
	Datos	*apun_aluma=apunta;
	i=0;
	while(apun_aluma->informacion.nombre.nomb[i] != '\0'){
		if(apun_aluma->informacion.nombre.nomb[i] >= 'a' && apun_aluma->informacion.nombre.nomb[i] <= 'z')
			apun_aluma->informacion.nombre.nomb[i]+='A'-'a';
		i++;
	}
	i=0;
	while(apun_aluma->informacion.nombre.app[i] != '\0'){
		if(apun_aluma->informacion.nombre.app[i] >= 'a' && apun_aluma->informacion.nombre.app[i] <= 'z')
			apun_aluma->informacion.nombre.app[i]+='A'-'a';
		i++;
	}
	i=0;
	while(apun_aluma->informacion.nombre.apm[i] != '\0'){
		if(apun_aluma->informacion.nombre.apm[i] >= 'a' && apun_aluma->informacion.nombre.apm[i] <= 'z')
			apun_aluma->informacion.nombre.apm[i]+='A'-'a';
		i++;
	}

}
//Funcion: Eliminar a alumnos.
//Recibe: Apuntador inicial y apuntador actual.
//Modifica: Apuntador inicial y actual.
//Retorna:
void eliminar(Datos **apun_alum_inicial, Datos **apun_alum){
	Datos *actual=*apun_alum_inicial;
	Datos *anterior=*apun_alum_inicial;
	Datos *auxComunica=*apun_alum;
	char matricula[10];
	getchar();
	printf("Ingrese la matricula a buscar: "); 
	gets(matricula);
	if(actual==NULL) 
		printf("No existen datos\n");
	else{
		while(actual != NULL && strcmp(matricula,actual->informacion.matricula)!=0){//se recorre la lista hasta encontrar
			anterior=actual;
			actual=actual->sig;
		}
		if(actual==NULL) 
			printf("ERROR: No existe el dato\n");
		else{
			if(registros(apun_alum_inicial)>0){
				if(anterior==actual)
					*apun_alum_inicial=actual->sig;
				if(anterior!=actual)
					anterior->sig=actual->sig;
				if(actual==auxComunica)
					*apun_alum=anterior;
				free(actual);
				printf("\nBorrado Exitoso\n\n");
			}
			else
			*apun_alum_inicial=NULL;
		}
	}
	return;
}
//Funcion: Cuenta el número de registros.
//Recibe: Apuntador inicial.
//Modifica:
//Retorna:
int registros(Datos **apun_alum_inicial){
	Datos *actual=*apun_alum_inicial;
	int n=0;
	while(actual != NULL){//se recorre la lista hasta encontrar
		actual=actual->sig;
		n++;
	}
	return n;
}
//Funcion: Cuenta el número de registros.
//Recibe: Apuntador inicial y actual del alumnos, apuntador inicial y actual de las materias de ingeniería y de las materias de licenciatura.
//Modifica: Datos de un alumno.
//Retorna:
void modificar(Datos **apun_alum_inicial,ingenieria **inicioIng, ingenieria **inicioLic){
	Datos *actual,*cabecera,*compar;
	int i,aux1,op,plan,num_materias,contBasica=0,contFormativa=0,total_creditos,j,aux_materia ; 
	float prom=0;
	char  inge[max]="INGENIERIA",licen[max]="LICENCIATURA",matricula[10];
	float calif[materi];
	char cve_materias[materi][5];
	char basica[]="Básica";
	char formativa[]="Formativa";
	ingenieria *validarIng,*validarLic;
	do{
		actual=*apun_alum_inicial;
		compar=*apun_alum_inicial;
		printf("Ingrese la matricula del alumno que desea cambiar: "); scanf("%s",matricula);	
		if(actual==NULL) printf("No existen datos\n");
		else{
			while(actual != NULL && strcmp(matricula,actual->informacion.matricula)!=0)//se recorre la lista hasta encontrar
				actual=actual->sig;
			
			if(actual!=NULL){
				do{
					printf("\nIngrese matricula:");			
					scanf("%s",(actual->informacion.matricula));	
					i=0;
					while(compar != NULL ){//se recorre la lista hasta encontrar
						if(strcmp(actual->informacion.matricula,compar->informacion.matricula)==0)
							i++;
						compar=compar->sig;	
					}
					if(i>1)	printf("ERROR: La matricula ya existe.\n");		
				}while(i>1);
				do{
					printf("Plan de Estudios.\n1.-Ingenieria\n2.-Licenciatura:\n");
					scanf("%d",&plan);
					if(plan!=1 && plan!=2)
						printf("opcion no valida intentelo nuevamente\n");
				}while(plan!=1 && plan!=2);	
				if(plan==1)
					strcpy(actual->informacion.plan,inge);
				else
					strcpy(actual->informacion.plan,licen);
				getchar();
				printf("Ingrese nombre(s): ");
				gets(actual->informacion.nombre.nomb);	
				printf("Ingrese apellido paterno: ");
				gets(actual->informacion.nombre.app);
				printf("Ingrese apellido materno: ");
				gets(actual->informacion.nombre.apm);
				printf("Ingrese Edad del Alumno:");
				scanf("%d",&(actual->informacion.edad));
				do{
					printf("Ingrese No. de Materias:");
							scanf("%d",&(actual->informacion.num_materias));
					if(actual->informacion.num_materias<0 )
						printf("ERROR:  debe ser>0\n");
					if(plan==1)  i=nregistros(inicioIng);
					if(plan==2)  i=nregistros(inicioLic);
					if(actual->informacion.num_materias>i)
						printf("ERROR:  NO existen todo ese numero de materias\n");
				}while(actual->informacion.num_materias<0 || actual->informacion.num_materias>i);
							i=0;
				mayusculas(actual);printf("%d",i);
				for(i=0;i<actual->informacion.num_materias;i++){
					if(plan==1){
						do{
							do{
								getchar();
								printf("\nIngrese la %d Clave:",i+1);	 gets(cve_materias[i]);
								aux_materia=1;
								j=0;
								while(aux_materia==1 && j<i){
									if(strcmp(cve_materias[j],actual->informacion.cve_materias[i])==0)
										aux_materia=0;
									j++;
								}
								if(aux_materia==0)
									printf("ERROR: Materia ya ingresada\n");
							}while(aux_materia==0);
							validarIng=validar_clave(inicioIng,cve_materias[i]);
							if(validarIng!=NULL){
								printf("Eligió %s\n", validarIng->dato.nombre);
								total_creditos+=validarIng->dato.creditos;
								if(strcmp(basica,validarIng->dato.nivel)==0)
									contBasica++;
								if(strcmp(formativa,validarIng->dato.nivel)==0)
									contFormativa++;
							}
							else
								printf("Error: La clave de matería no existe.\n");
						}while(validarIng==NULL);
					}

					if(plan==2){
						do{
							do{
								getchar();
								printf("\nIngrese la %d Clave:",i+1); gets(cve_materias[i]);
								aux_materia=1;
								j=0;
								while(aux_materia==1 && j<i){
									if(strcmp(cve_materias[j],cve_materias[i])==0)
										aux_materia=0;
									j++;
								}
								if(aux_materia==0)
									printf("ERROR: Materia ya ingresada\n");
							}while(aux_materia==0);
							validarLic=validar_clave(inicioLic,cve_materias[i]);
							if(validarLic!=NULL){
								printf("Eligió %s\n", validarLic->dato.nombre);
								total_creditos+=validarLic->dato.creditos;
								if(strcmp(basica,validarLic->dato.nivel)==0)
									contBasica++;
								if(strcmp(formativa,validarLic->dato.nivel)==0)
									contFormativa++;
							}
							else
								printf("Error: La clave de matería no existe.\n");
						}while(validarLic==NULL);
					}
					do{
						printf("\nIngrese la %d calificacion:",i+1);
						scanf("%f", &calif[i]);
						if(calif[i]<0 || calif[i]>10)
							printf("ERROR: La calificacion debe estar entre 0 y 10\n");
						else
							prom+=calif[i];
					}while(calif[i]<0 || calif[i]>10);
					strcpy(actual->informacion.cve_materias[i],cve_materias[i]);
					actual->informacion.calif[i]=calif[i];
					
				}
					
				if(contBasica>=contFormativa) strcpy(actual->informacion.nivel,basica);
				else strcpy(actual->informacion.nivel,formativa);
				actual->informacion.total_creditos=total_creditos;
				actual->informacion.promedio=prom/(actual->informacion.num_materias);
			}else printf("No existe esta MATRICULA\n");
		}
	}while(actual==NULL);
	return;
}
//Funcion: Muestra el menú de consultas.
//Recibe:
//Modifica:
//Retorna: La opción elegida.
int menu_consultas(){
		int opcion;
			printf("\nElija la informacion que desea:\n1.-Todos los alumnos.\n2.-Un Alumno.\n3.-Alumnos Reprobados \n4.-Alumnos Aprobados.\n5.-Alumnos por Materia\n6.-Salir\n");
		scanf("%d",&opcion);
	return opcion;
}
//Funcion: Cuenta el número de registros.
//Recibe: Apuntador inicial y actual del alumnos, apuntador inicial y actual de las materias de ingeniería y de las materias de licenciatura.
//Modifica:
//Retorna:
void consultas(Datos **apun_alum_inicial, ingenieria **inicioIng, ingenieria **inicioLic){
    
	int op;
	do{
		op=menu_consultas();
		switch (op)
	 	{
		case 1:		
			do{		
				todos_alum(apun_alum_inicial);
			}while(repetir()==1);
			break;
		case 2:
			do{
				un_alum(apun_alum_inicial);
			}while(repetir()==1);
		break;
		case 3:
			do{		
				alumnos_reprobados(apun_alum_inicial);
			}while(repetir()==1);

		break;
		case 4:
			do{		
				alumnos_aprobados(apun_alum_inicial);
			}while(repetir()==1);
		break;
		case 5: consulta_por_materia(apun_alum_inicial,inicioIng,inicioLic);break;
		case 6: break;
		}
	}while(op!=6);
	return;

}
//Funcion: Muestra todos los alumnos.
//Recibe: Apuntador inicial del los alumnos.
//Modifica:
//Retorna:
void todos_alum(Datos **apun_alum_inicial){
	Datos *actual=*apun_alum_inicial;
	int i;
	if(actual==NULL) printf("No existen datos\n");
	else{
		printf("\n\n---LOS DATOS DE  LOS ALUMNOS SON:---\n\n");
		while(actual != NULL){//se recorre la lista hasta encontrar
			printf("Matricula: %s \nPlan: %s\nNombre: %s %s %s\nEdad: %d\nNo.Materias: %d\nTotal de Creditos: %d\nNivel: %s\nPromedio: %f",actual->informacion.matricula,actual->informacion.plan,actual->informacion.nombre.app,actual->informacion.nombre.apm,actual->informacion.nombre.nomb,actual->informacion.edad,actual->informacion.num_materias,actual->informacion.total_creditos,actual->informacion.nivel,actual->informacion.promedio);
			for(i=0;i< actual->informacion.num_materias;i++)
				printf("\n%d.-Clave: %s",i+1,actual->informacion.cve_materias[i]);
			for(i=0;i< actual->informacion.num_materias;i++)
				printf("\n%d.-Calificacion: %f",i+1,actual->informacion.calif[i]);
			actual=actual->sig;
			printf("\n\n");
		}
		
	}
	return;
}
//Funcion: Muestra un alumno.
//Recibe: Apuntador inicial del los alumnos.
//Modifica:
//Retorna:
void un_alum(Datos **apun_alum_inicial){
	Datos *actual,*cabecera;
	int i,aux1,op,plan,num_materias ; 
	float prom=0;
	char matricula[10];
	
	actual=*apun_alum_inicial;
	getchar();
	printf("Ingrese la matricula del alumno: "); gets(matricula);	
	if(actual==NULL) printf("No existen datos\n");
	else{
		while(actual != NULL && strcmp(matricula,actual->informacion.matricula)!=0){//se recorre la lista hasta encontrar
			actual=actual->sig;
		}
		
		if(actual==NULL)
			printf("No existe esta MATRICULA\n");
		else{
			printf("\n\n---LOS DATOS DEL ALUMNO ES:---\n\n");
			printf("Matricula: %s \nPlan: %s\nNombre: %s %s %s\nEdad: %d\nNo.Materias: %d\nTotal de Creditos: %d\nNivel: %s\nPromedio: %f",actual->informacion.matricula,actual->informacion.plan,actual->informacion.nombre.app,actual->informacion.nombre.apm,actual->informacion.nombre.nomb,actual->informacion.edad,actual->informacion.num_materias,actual->informacion.total_creditos,actual->informacion.nivel,actual->informacion.promedio);
			for(i=0;i< actual->informacion.num_materias;i++)
				printf("\n%d.-Clave: %s",i+1,actual->informacion.cve_materias[i]);
			for(i=0;i< actual->informacion.num_materias;i++)
				printf("\n%d.-Calificacion: %f",i+1,actual->informacion.calif[i]);
		}
	}
	
}
//Funcion: Muestra los alumnos reprobados.
//Recibe: Apuntador inicial del los alumnos.
//Modifica:
//Retorna:
void alumnos_reprobados(Datos **apun_alum_inicial){
	int j,i,k=0;
	Datos *actual=*apun_alum_inicial;
		printf("\n\n---LOS DATOS DE  LOS ALUMNOS REPROBADOS SON:---\n\n");
		while(actual != NULL){	
			if (actual->informacion.promedio < 6){	
			printf("Matricula: %s \nPlan: %s\nNombre: %s %s %s\nEdad: %d\nNo.Materias: %d\nTotal de Creditos: %d\nNivel: %s\nPromedio: %f",actual->informacion.matricula,actual->informacion.plan,actual->informacion.nombre.app,actual->informacion.nombre.apm,actual->informacion.nombre.nomb,actual->informacion.edad,actual->informacion.num_materias,actual->informacion.total_creditos,actual->informacion.nivel,actual->informacion.promedio);
				for(i=0;i< actual->informacion.num_materias;i++)
					printf("\n%d.-Clave: %s",i+1,actual->informacion.cve_materias[i]);
				for(i=0;i< actual->informacion.num_materias;i++)
					printf("\n%d.-Calificacion: %f",i+1,actual->informacion.calif[i]);
					k++;
			}
			actual=actual->sig;
		}
		if (k==0)
			printf("\n\nNO HAY ALUMNOS REPROBADOS\n\n");;
	return;
}
//Funcion: Muestra los alumnos aprobados.
//Recibe: Apuntador inicial del los alumnos.
//Modifica:
//Retorna:
void alumnos_aprobados(Datos **apun_alum_inicial){
	int j,i,k=0;
	Datos *actual=*apun_alum_inicial;
		printf("\n\n---LOS DATOS DE  LOS ALUMNOS APROBADOS SON:---\n\n");
		while(actual != NULL){	
			if (actual->informacion.promedio >= 6){	
			printf("Matricula: %s \nPlan: %s\nNombre: %s %s %s\nEdad: %d\nNo.Materias: %d\nTotal de Creditos: %d\nNivel: %s\nPromedio: %f",actual->informacion.matricula,actual->informacion.plan,actual->informacion.nombre.app,actual->informacion.nombre.apm,actual->informacion.nombre.nomb,actual->informacion.edad,actual->informacion.num_materias,actual->informacion.total_creditos,actual->informacion.nivel,actual->informacion.promedio);
			for(i=0;i< actual->informacion.num_materias;i++)
				printf("\n%d.-Clave: %s",i+1,actual->informacion.cve_materias[i]);
			for(i=0;i< actual->informacion.num_materias;i++)
				printf("\n%d.-Calificacion: %f",i+1,actual->informacion.calif[i]);
				k++;
			}
			actual=actual->sig;
		}
		if (k==0)
			printf("\n\nNO HAY ALUMNOS APROBADOS\n\n");;
	return;
}
//Funcion: Guardar en archivo los datos de los alumnos.
//Recibe: Apuntador inicial del los alumnos.
//Modifica:
//Retorna:
void guardar_alumnos(Datos **apun_alum_inicial){
	Datos *actual=*apun_alum_inicial,*aux,*nulo=NULL;
	FILE *archivo;
	if(actual==NULL) printf("No existen datos\n");
	else{
		archivo=fopen("alumnos.txt","w");
		if(archivo==NULL){
			printf("ERROR: No se pudo crear el archivo");
			return;
		}
		else{
			while(actual != NULL){//se recorre la lista hasta encontrar
				fwrite(actual,sizeof(info),1,archivo);
				//aux=actual;
				actual=actual->sig;
				//free(aux);
			}
		}
	//*inicio=nulo;
	}
	fclose(archivo);
	printf("\nGuardado de datos exitoso.\n");
	return;
}
//Funcion: Recupera del archivo los datos de los alumnos.
//Recibe: Apuntador inicial y actual del los alumnos.
//Modifica:
//Retorna:
void carga_alumnos(Datos **apun_alum_inicial,Datos **apun_alum){

	FILE *archivo;
	archivo=fopen("alumnos.txt","r");
	if(archivo==NULL){
		printf("ERROR: No se abrir el archivo");
		return;
		}
	else{
			info dato;
			int leidos;
			do{
				leidos=fread(&dato,sizeof(dato),1,archivo);
				if(leidos==1)
					agregar_alumno(apun_alum_inicial,apun_alum,dato.matricula,dato.plan,dato.nombre,dato.edad,dato.num_materias,dato.calif,dato.cve_materias,dato.total_creditos,dato.nivel,dato.promedio);
			}while(leidos==1);
	}
	fclose(archivo);
	printf("\nCarga de datos exitosa.\n\n");
	return;
}
//------------------------------------------------------------------------------------------------------Catalogos
//Funcion: Lectura de los datos de las materias.
//Recibe: Apuntadores inicial y actual de materias de ingenieria y de materias de licenciatura.
//Modifica: 
//Retorna:
void agregar_materia(ingenieria **inicio,ingenieria **actual){
	char clave[10];
	char nombre[30];
	char nivel[10];
	int creditos;
	int bf;
	char basica[]="Básica";
	char formativa[]="Formativa";
	ingenieria *validar;
	getchar();
	do{
		printf("\nIngrese la  Clave:");	gets(clave);
		validar=validar_clave(inicio,clave);
		if(validar!=NULL)
			printf("Error: La clave de matería ya existe.\n");
	}while(validar!=NULL);
	printf("Nombre: "); gets(nombre);
	do{
		printf("¿Es básica(1) o formativa?(2)");	scanf("%d",&bf);
		if(bf==1)
			strcpy(nivel,basica);
		if(bf==2)
			strcpy(nivel,formativa);		
			
	}while(bf < 1 && bf > 2);
	do{	
		printf("Creditos: "); scanf("%d",&creditos);
		if(creditos<=0)	printf("Error: Número invalido de creditos\n");
	}while(creditos<=0);			
	insertar_materia(inicio,actual,clave,nombre,nivel,creditos);
	return;
}
//Funcion: Ingreso a la lista ligada de los datos de las materias.
//Recibe: Todos los datos de una materia y apuntadores inicial y actual de materias de ingenieria y de materias de licenciatura.
//Modifica: Apuntadores inicial y actual de materias de ingenieria y de materias de licenciatura.
//Retorna:
void insertar_materia(ingenieria **inicio,ingenieria **actual, char clave[10],char nombre[30],char nivel[10],int creditos){
	ingenieria *apunta=(ingenieria *)malloc(sizeof(ingenieria));//se crea nodo
	ingenieria *aux=*actual;
	ingenieria *cabecera=*inicio;


	printf("Matricula: %s Nombre: %s Nivel: %s Creditos: %d\n",clave,nombre,nivel,creditos);	
	
	if(apunta==NULL)
		printf("\n No se pudo asignar memoria");
	else{
		//SI SE PUDO CREAR
		//se guarda la informacion en el nodo 
		strcpy(apunta->dato.clave,clave);
		strcpy(apunta->dato.nombre,nombre);
		strcpy(apunta->dato.nivel,nivel);
		apunta->dato.creditos=creditos;
		apunta->sig=NULL;
		//se enlaza en el nodo o se coloca como cabeza de la lista
		if(cabecera==NULL)//si la lista esta vacia
			*inicio=apunta;//es el primer elemento de la lista
		else
			aux -> sig = apunta;

		*actual=apunta;//se actualiza el apuntador al ultimo
	}
	return;
	
}
//Funcion: Muestra todas las materias.
//Recibe: Apuntadores inicial de materias.
//Modifica:
//Retorna:	
void ver(ingenieria **inicio){
	ingenieria *actual=*inicio;
	if(actual==NULL) printf("No existen datos\n");
	else{
		printf("\nLa lista es:\n");
		while(actual != NULL){//se recorre la lista hasta encontrar
			printf("Matricula: %s Nombre: %s Nivel: %s Creditos: %d\n",actual->dato.clave,actual->dato.nombre,actual->dato.nivel,actual->dato.creditos);
			actual=actual->sig;
		}
		printf("\n");
	}
	return;
}
//Funcion: Muestra una materias.
//Recibe: Apuntadores inicial de materias.
//Modifica:
//Retorna:
void buscar(ingenieria **inicio){
	ingenieria *actual=*inicio;
	char clave[10];
	ingenieria *validar;
	getchar();
	do{
		printf("\nIngrese la  Clave:");	gets(clave);
		validar=validar_clave(inicio,clave);
		if(validar!=NULL)
			printf("Error: La clave de matería ya existe.\n");
	}while(validar!=NULL);
	if(actual==NULL) printf("No existen datos\n");
	else{
		while(actual != NULL && strcmp(clave,actual->dato.clave)!=0){//se recorre la lista hasta encontrar
			actual=actual->sig;
		}
		if(actual==NULL)
			printf("No existe la clave\n");
		else
			printf("Matricula: %s Nombre: %s Nivel: %s Creditos: %d\n",actual->dato.clave,actual->dato.nombre,actual->dato.nivel,actual->dato.creditos);
	}
	return;
}
//Funcion: Muestra todas las materias.
//Recibe: Apuntador inicial de materias.
//Modifica: Apuntar inicial y actual.
//Retorna:
void borrar(ingenieria **inicio,ingenieria **actuaLuis){
	ingenieria *actual=*inicio;
	ingenieria *anterior=*inicio;
	ingenieria *auxLuis=*actuaLuis;
	char clave[10];
	getchar();
	ingenieria *validar;
	do{
		getchar();
		printf("\nIngrese la  clave:");	gets(clave);
		validar=validar_clave(inicio,clave);
		if(validar==NULL)
			printf("Error: La clave de matería no existe.\n");
	}while(validar==NULL);
	if(actual==NULL) printf("No existen datos\n");
	else{
		while(actual != NULL && strcmp(clave,actual->dato.clave)!=0){//se recorre la lista hasta encontrar
			anterior=actual;
			actual=actual->sig;
		}
		if(actual==NULL) printf("ERROR: No existe el dato\n");
		else{
			if(nregistros(inicio)>0){
				if(anterior==actual)
					*inicio=actual->sig;
				if(anterior!=actual)
					anterior->sig=actual->sig;
				if(actual==auxLuis)
					*actuaLuis=anterior;
				free(actual);
				printf("\nBorrado Exitoso\n\n");

			}
			else
				*inicio=NULL;
		}
	}
	return;
}

//Funcion: Cambia los datos de una de las materias.
//Recibe: Apuntadores inicial de materias.
//Modifica:
//Retorna:
void cambiar(ingenieria **inicio){
	ingenieria *actual=*inicio;
	char clave[10];
	char nombre[30];
	char nivel[30];
	int creditos;
	int bf;
	char basica[]="Basica";
	char formativa[]="Formativa";
	ingenieria *validar;
	getchar();
	do{
		printf("\nIngrese la  Clave:");	gets(clave);
		validar=validar_clave(inicio,clave);
		if(validar==NULL)
			printf("Error: La clave de matería no ya existe.\n");
	}while(validar==NULL);
	
	if(actual==NULL) printf("No existen datos\n");
	else{
		while(actual != NULL && strcmp(clave,actual->dato.clave)!=0){//se recorre la lista hasta encontrar
			actual=actual->sig;
		}
		if(actual==NULL)
			printf("No existe la clave\n");
		else{
			printf("Clave: "); gets(clave);
			printf("Nombre: "); gets(nombre);
			do{
				printf("¿Es básica(1) o formativa?(2)");	scanf("%d",&bf);
				if(bf==1)
					strcpy(nivel,basica);
				if(bf==2)
					strcpy(nivel,formativa);			
			}while(bf < 1 && bf > 2);
			printf("Creditos: "); scanf("%d",&creditos);

			strcpy(actual->dato.clave,clave);
			strcpy(actual->dato.nombre,nombre);
			strcpy(actual->dato.nivel,nivel);
			actual->dato.creditos=creditos;
		}		
	}	
	return;
}
//Funcion: Guarda todas las materias en un archivo.
//Recibe: Apuntadores inicial de materias.
//Modifica:
//Retorna:
void guardar(ingenieria **inicio,int *ingenieria_licenciatura){
	ingenieria *actual=*inicio,*aux,*nulo=NULL;
	FILE *archivo;
	if(actual==NULL) printf("No existen datos\n");
	else{
		if(*ingenieria_licenciatura==1)
			archivo=fopen("ingenieria.txt","w");
		else
			archivo=fopen("licenciatura.txt","w");
		if(archivo==NULL){
			printf("ERROR: No se pudo crear el archivo");
			return;
		}
		else{
			while(actual != NULL){//se recorre la lista hasta encontrar
				fwrite(actual,sizeof(datos),1,archivo);
				//aux=actual;
				actual=actual->sig;
				//free(aux);
			}
		}
	//*inicio=nulo;
	}
	fclose(archivo);
	printf("\nGuardado de datos exitoso.\n");
	return;
}
//Funcion: Recupera todas las materias en un archivo.
//Recibe: Apuntadores inicial de materias.
//Modifica:
//Retorna:
void cargar(ingenieria **inicio,ingenieria **actual,int *ingenieria_licenciatura_op){

	FILE *archivo;
	printf("Valor: %d",*ingenieria_licenciatura_op);
	if(*ingenieria_licenciatura_op==1){
		archivo=fopen("ingenieria.txt","r");
	}
	else{
		archivo=fopen("licenciatura.txt","r");
	}
	if(archivo==NULL){
		printf("ERROR: No se abrir el archivo");
		return;
		}
	else{
			datos dato;
			int leidos;
			do{
				leidos=fread(&dato,sizeof(dato),1,archivo);
				if(leidos==1)
					insertar_materia(inicio,actual,dato.clave,dato.nombre,dato.nivel,dato.creditos);
			}while(leidos==1);
		
			
	}
	fclose(archivo);
	printf("\nCarga de datos exitosa.\n\n");
	return;
}
//Funcion: Cuenta el numero de registros.
//Recibe: Apuntadores inicial de materias.
//Modifica:
//Retorna:
int nregistros(ingenieria **inicio){
	ingenieria *actual=*inicio;
	int n=0;
	while(actual != NULL){//se recorre la lista hasta encontrar
		actual=actual->sig;
		n++;
	}
	return n;
}
//Funcion: Valida la clave de las las materias.
//Recibe: Apuntadores inicial de materias.
//Modifica:
//Retorna: Apuntador de la clave si ya existe, nulo si no existe.
ingenieria *validar_clave(ingenieria **inicio, char clave[20]){
	ingenieria *actual=*inicio;
	int aux=1;
	while(actual!=NULL && aux==1){
		if(strcmp(clave,actual->dato.clave)==0)
			aux=0;
		else
			actual=actual->sig;
	}
	return actual;
}
//Funcion: Consulta por materia de los alumnos.
//Recibe: Apuntadores inicial de materias, de materias de ingeniería y de licenciatura.
//Modifica:
//Retorna:
void consulta_por_materia(Datos **apun_alum_inicial,ingenieria **inicioIng, ingenieria **inicioLic){
	int op,n,i,j;
	char clave[10];
	ingenieria *validar;
	Datos *actual=*apun_alum_inicial;
	op=menu_licenciatura_ingenieria();
	switch(op){
		case 1: 
			do{
				getchar();
				printf("Ingrese Clave de la Materia:"); gets(clave);
				validar=validar_clave(inicioIng,clave);
				if(validar==NULL) printf("Error: La clave no existe\n");
			}while(validar==NULL);
			if(actual==NULL) printf("No existen datos\n");
			else{
				printf("\nLa lista es:\n");
				while(actual != NULL){//se recorre la lista hasta encontrar
					n=actual->informacion.num_materias;
					for(i=0;i<n;i++){
						if(strcmp(clave,actual->informacion.cve_materias[i])==0){	
							printf("\n\n---LOS DATOS DEL ALUMNO ES:---\n\n");
							printf("Matricula: %s \nNombre: %s %s %s\nEdad: %d\nNo.Materias: %d\nTotal de Creditos: %d\nNivel: %s\nPromedio: %f",actual->informacion.matricula,actual->informacion.nombre.app,actual->informacion.nombre.apm,actual->informacion.nombre.nomb,actual->informacion.edad,actual->informacion.num_materias,actual->informacion.total_creditos,actual->informacion.nivel,actual->informacion.promedio);
							for(j=0;j< actual->informacion.num_materias;j++)
								printf("\n%d.-Clave: %s",j+1,actual->informacion.cve_materias[j]);
							for(j=0;j< actual->informacion.num_materias;j++)
								printf("\n%d.-Calificacion: %f",j+1,actual->informacion.calif[j]);
						}
					}
					actual=actual->sig;
					printf("\n\n");
				}
			}
		break;

		case 2:
			do{
				getchar();
				printf("Ingrese Clave de la Materia:"); gets(clave);
				validar=validar_clave(inicioLic,clave);
				if(validar==NULL) printf("Error: La clave no existe\n");
			}while(validar==NULL);
			if(actual==NULL) printf("No existen datos\n");
			else{
				printf("\nLa lista es:\n");
				while(actual != NULL){//se recorre la lista hasta encontrar
					n=actual->informacion.num_materias;
					for(i=0;i<n;i++){
						if(strcmp(clave,actual->informacion.cve_materias[i])==0){
							printf("\n\n---LOS DATOS DEL ALUMNO ES:---\n\n");
							printf("Matricula: %s \nPlan: %s\nNombre: %s %s %s\nEdad: %d\nNo.Materias: %d\nTotal de Creditos: %d\nNivel: %s\nPromedio: %f",actual->informacion.matricula,actual->informacion.plan,actual->informacion.nombre.app,actual->informacion.nombre.apm,actual->informacion.nombre.nomb,actual->informacion.edad,actual->informacion.num_materias,actual->informacion.total_creditos,actual->informacion.nivel,actual->informacion.promedio);
							for(j=0;j< actual->informacion.num_materias;j++)
								printf("\n%d.-Clave: %s",i+1,actual->informacion.cve_materias[j]);
							for(j=0;j< actual->informacion.num_materias;j++)
								printf("\n%d.-Calificacion: %f",i+1,actual->informacion.calif[j]);
						}
					}
					actual=actual->sig;
					printf("\n\n");
				}
			}
		break;
		case 3: break;
		}
		
	return;
}
