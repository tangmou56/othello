#include <stdio.h>
#define N 8

#include<stdio.h>
#include<stdlib.h>
#define N 8

void grille_initialise(int mat[N][N]){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			mat[i][j]=0;
			
		}
	}
	mat[3][3]=1;
	mat[3][4]=2;
	mat[4][3]=2;
	mat[4][4]=1;
}

void grille_afficher(int mat[N][N]){

 	
 		printf("   0  1  2  3  4  5  6  7\n");
 	printf("%i ",0);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			printf(" %i ",mat[i][j]);
		}
		printf("\n");
		if(i+1!=8)printf("%i ",i+1);
	}
}

void case_choisir(int* x,int *y){
	int xx,yy;
	printf("x: ");
	scanf("%i",&xx);
	printf("y: ");
	scanf("%i",&yy);
	*x=xx;
	*y=yy;
}

void pion_placer(int x,int y,int mat[N][N],int joueur){
	mat[x][y]=joueur;
}

void joueur_changer(int *joueur){
	if(*joueur==1){
		*joueur=2;
	}
	else{
		*joueur=1;
	}
	printf("Joueur %i :\n",*joueur);
}

int bCase_verifier(int mat[N][N], int x, int y,int joueur){

	int i;
	
	//definition du joueur adverse
	int jadv;
	if (joueur==1) jadv=2;
	else if (joueur==2) jadv=1;
	
	//verification de dÃ©passement de borne
	if (x<0 || x>(N-1) || y<0 || y>(N-1) ) return 0;
	
	//verification si case est vide
	if (mat[x][y]!=0) return 0;		
	else {
			//verification si case choisie adjacente a celle d'un pion adverse et si encadrement de pion adverse
			if (mat[x-1][y]==jadv) {
			
				for(i=x-1; i>=0; i--){
				
					if (mat[i][y]==joueur) return 1;
				}
			}
			
			if (mat[x+1][y]==jadv) {
			
				for(i=x+1; i<N; i++){
				
					if (mat[i][y]==joueur) return 1;
				}
			}
			if (mat[x][y-1]==jadv) {
			
				for(i=y-1; i>=0; i--){
				
					if (mat[x][i]==joueur) return 1;
				}
			}
			if (mat[x][y+1]==jadv) {
			
				for(i=y+1; i<N; i++){
				
					if (mat[x][i]==joueur) return 1;
				}
			}
			
			return 0;	//si pas de pion adjacent ou si pas d'encadrement	
	} 
}

int jeu_gagner(int mat[N][N]){

	int i,j, nb1=0, nb2=0;
	
	for(i=0; i<N ; i++){
		for(j=0; j<N ; j++){
		
			if (mat[i][j] == 1) nb1++;
			if (mat[i][j] == 2) nb2++;
	
		}
	}
	
	if(nb1>nb2) return 1;		//le joueur 1 gagne
	else if(nb2>nb1) return 2;		//le joueur 2 gagne
	else return 3;		//egalitÃ©

}

int jeu_fini(int mat[N][N], int joueur){		//retourne 0 si jeu non fini, 1 si joueur 1 a gagnÃ©, 2 si joueur 2 a gagnÃ©

	int entier=0;
	int i,j;
	
	for(i=0; i<N ; i++){
		for(j=0; j<N ; j++){
		
			if(bCase_verifier(mat,i,j,joueur)) entier =1;
	
		}
	}
	
	if(entier==0){	//jeu est fini
		return jeu_gagner(mat);
	}
	return 0; 	//jeu n'est pas fini
}

int pion_capturer(int mat[N][N],int joueur){
	int i,j,x,y;
	
	int autre_joueur;
	int possible=0;

		if(joueur==1)autre_joueur=2;
		else autre_joueur=1;
	
		for(i=0; i<N ; i++){
		for(j=0; j<N ; j++){
		
		
			if(mat[i][j]==joueur&&mat[i+1][j]==autre_joueur){	//condition à bas
				for(x=i+1;x<N;x++){
					if(mat[x][j]==joueur){
						possible=1;
						x=N+1;
					}
					else if(mat[x][j]==0){
						x=N+1;
					}
				}
			}	
			if(possible){		//à bas
				printf("a");
				for(x=i+1;x<N;x++){				
					if(mat[x][j]!=joueur){
						mat[x][j]=joueur;
					}
					else if(mat[x][j]==joueur){
						x=N+1;
					}			
				}	
			}
			possible=0;
			
			if(mat[i][j]==joueur&&mat[i-1][j]==autre_joueur){	//condition à haut
				for(x=i-1;x>=0;x--){
					if(mat[x][j]==joueur){
						possible=1;
						x=-1;
					}
					else if(mat[x][j]==0){
						x=-1;
					}
				}
			}
			if(possible){		//à haut
			printf("b");
				for(x=i-1;x>=0;x--){				
					if(mat[x][j]!=joueur){
						mat[x][j]=joueur;
					}
					else if(mat[x][j]==joueur){
						x=-1;
					}			
				}	
			}
			possible=0;
			
			
			if(mat[i][j]==joueur&&mat[i][j-1]==autre_joueur){	//condition à gauche
				for(x=j-1;x>=0;x--){
					if(mat[i][x]==joueur){
						possible=1;
						x=-1;
					}
					else if(mat[i][x]==0){
						x=-1;
					}
				}
			}
			if(possible){		//à gauche
			printf("c");
				for(x=j-1;x>=0;x--){				
					if(mat[i][x]!=joueur){
						mat[i][x]=joueur;
					}
					else if(mat[i][x]==joueur){
						x=-1;
					}			
				}	
			}
			possible=0;
			
			if(mat[i][j]==joueur&&mat[i][j+1]==autre_joueur){	//condition à droite
				for(x=j+1;x<N;x++){
					if(mat[i][x]==joueur){
						possible=1;
						x=N+1;
					}
					else if(mat[i][x]==0){
						x=N+1;
					}
				}
			}
			if(possible){		//à droite
			printf("d");
				for(x=j+1;x<N;x++){				
					if(mat[i][x]!=joueur){
						mat[i][x]=joueur;
					}
					else if(mat[i][x]==joueur){
						x=N+1;
					}			
				}	
			}	
			possible=0;
			
			
		}
	}

	return 1;
}


int main(){
	int mat[N][N];
	int x,y;
	int fini=0;
	int joueur=1;
	grille_initialise(mat);
	while(fini==0){
		fini=jeu_fini(mat,joueur);
		grille_afficher(mat);
		case_choisir(&x,&y);
			while(!bCase_verifier(mat,x,y,joueur) && fini==0){
				case_choisir(&x,&y);
				//fini=jeu_fini(mat,joueur);
			}
		pion_placer(x,y,mat,joueur);
		pion_capturer(mat,joueur);
		joueur_changer(&joueur);
		//fini=jeu_fini(mat,joueur);
	}
}

