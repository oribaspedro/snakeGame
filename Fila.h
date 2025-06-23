struct no {
	char info;
	no *link;
	int posx;
	int posy;
};

no *inicializaFila(no *L) {
	return NULL;
}

void imprimeFila(no *L) {
	no *P;
	P = L;	
	
	printf("\n Imprime Fila: \n");	
	while(P != NULL) {
		cout << P->posx << " " << P->posy << "\n";	
		P = P->link;
	}	
}

no *insereFila(no *L, int x, int posx, int posy) {
	no *N, *P;

	N = new no;
	N->info = x;
	N->link = NULL;
	N->posx = posx;
	N->posy = posy;
	 
	if (L == NULL){
		L = N;
	}
	else {
		P = L;	
		while(P->link != NULL) {
			P = P->link;
		}
		P->link = N; 	
	} 
	return L;
}

no *removeFila(no *L, int *n) {
	no *AUX;

	if (L != NULL) {
		*n = L->info;
		AUX = L;
		L = L->link;
		delete AUX;
	}
	else{
		*n = 0;
	}
	return (L);
}

