
#include <stdlib.h>
#include <stdio.h>
#define N 8

void grille_initialiser(int mat[N][N]){
	
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			
			mat[i][j]=0;
		}
	}
	mat[3][3]=1;
	mat[3][4]=2;
	mat[4][3]=2;
	mat[4][4]=1;
}		//initialise la matrice a 0 pour les case vides et a 1 et 2 pour les 4 pions au milieu

void grille_afficher(int mat[N][N]){
 	
 	printf("   0  1  2  3  4  5  6  7\n");
 	printf("%i ",0);
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
		
			if (mat[i][j]==0) printf ("   ");
			else if (mat[i][j]==1) printf(" \033[0;30m●\033[1;37m ");
			else if (mat[i][j]==2) printf(" ● ");
			else if (mat[i][j]==3) printf(" \033[0;32;31m●\033[1;37m ");
			else printf("Error");
		}
		printf("\n");
		if(i+1!=8)printf("%i ",i+1);
	}
}		//affiche la matrice en representant les pions noirs (j1) par * et les pions blanc (j2) par o

void case_choisir(int* x,int *y){
	int xx,yy;
	printf("x: ");
	scanf("%i",&xx);
	printf("y: ");
	scanf("%i",&yy);
	*x=xx;
	*y=yy;
}		//demande au joueur de choisir une case

void pion_placer(int x,int y,int mat[N][N],int joueur){
	mat[x][y]=joueur;
}		//place un pion du joueur actuel aux coordonnÃ©es donnÃ©es

void joueur_changer(int *joueur){

	if(*joueur==1) *joueur=2;
	else *joueur=1;
	
	printf("\n\tJoueur %i :\n",*joueur);
}		//passe au tour du joueur suivant

int bCase_verifier(int mat[N][N], int x, int y,int joueur){

	int i,j;
	
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
			//cotÃ©s
			if (mat[x-1][y]==jadv) {	 //gauche
			
				for(i=x-1; i>=0; i--){
				
					if (mat[i][y]==joueur) return 1;
				}
			}
			
			if (mat[x+1][y]==jadv) {	//droit
			
				for(i=x+1; i<N; i++){
				
					if (mat[i][y]==joueur) return 1;
				}
			}
			if (mat[x][y-1]==jadv) {	//bas
			
				for(i=y-1; i>=0; i--){
				
					if (mat[x][i]==joueur) return 1;
				}
			}
			if (mat[x][y+1]==jadv) {	//haut
			
				for(i=y+1; i<N; i++){
				
					if (mat[x][i]==joueur) return 1;
				}
			}
			//diagonales
			if (mat[x-1][y-1]==jadv) {	//bas gauche
			
				for(i=x-1, j=y-1; i>=0 && j>=0; i--,j--){
				
					if (mat[i][j]==joueur) return 1;
				}
			}
			if (mat[x+1][y+1]==jadv) {	//haut droit
			
				for(i=x+1, j=y+1; i<N && j<N; i++,j++){
				
					if (mat[i][j]==joueur) return 1;
				}
			}
			
			if (mat[x-1][y+1]==jadv) {	//haut gauche
			
				for(i=x-1,j=y+1; i>=0 && j<N; i--,j++){
				
					if (mat[i][j]==joueur) return 1;
				}
			}
			if (mat[x+1][y-1]==jadv) {	//bas droit
			
				for(i=x+1,j=y-1; i<N && j>=0; i++,j--){
				
					if (mat[i][j]==joueur) return 1;
				}
			}
			
			return 0;	//si pas de pion adjacent ou si pas d'encadrement	
	} 
}		//verifie si la case choisie est disponible (vide, adjacente a pion adverse et encadrant pion adverse




int jeu_gagner(int mat[N][N]){		
//Appelant : jeu_fini
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

} 		//determine le gagnant de la partie

int jeu_fini(int mat[N][N], int joueur){		
	//retourne 1 si joueur 1 a gagnÃ©, 2 si joueur 2 a gagnÃ© sinon 0 (jeu non fini) 3 si jeux passe à l'autre joueur
	int peut_jouer1=0,peut_jouer2=0;
	int i,j;
	int autre_joueur;
	if(joueur==1){
		autre_joueur=2;	
	}
	else{
		autre_joueur=1;
	}
	

	for(i=0; i<N ; i++){
		for(j=0; j<N ; j++){
		
			if(bCase_verifier(mat,i,j,joueur)) peut_jouer1 =1;
	
		}
	}
	
	if(peut_jouer1==0){	
		for(i=0; i<N ; i++){
			for(j=0; j<N ; j++){
				if(bCase_verifier(mat,i,j,autre_joueur)) peut_jouer2 =1;
			}
		}
		if(peut_jouer1==0&&peut_jouer2==0){		//jeu est fini
			return jeu_gagner(mat);
		}
		else if(peut_jouer1==0&&peut_jouer2==1){
			return 3;	
		}
	}
	return 0; 	//jeu n'est pas fini
}//jeu_fini


int pion_capturer(int mat[N][N],int joueur,int x_donne,int y_donne){
	//renvoie 1 si le fonction est fini
	int i,j,x,y;
	//i j le coordonne qui fait capturer
	int autre_joueur;
	int possible=0;	//possible Ã  capturer

		if(joueur==1)autre_joueur=2;
		else autre_joueur=1;
	
		i=x_donne;
		j=y_donne;
		
		
			if(mat[i][j]==joueur&&mat[i+1][j]==autre_joueur){	//condition Ã  bas
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
			if(possible){		//Ã  bas
		//		printf("a");
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
			
			if(mat[i][j]==joueur&&mat[i-1][j]==autre_joueur){	//condition Ã  haut
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
			if(possible){		//Ã  haut
		//	printf("b");
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
			
			
			if(mat[i][j]==joueur&&mat[i][j-1]==autre_joueur){	//condition Ã  gauche
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
			if(possible){		//Ã  gauche
		//	printf("c");
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
			
			if(mat[i][j]==joueur&&mat[i][j+1]==autre_joueur){	//condition Ã  droite
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
			if(possible){		//Ã  droite
		//	printf("d");
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

			
			if(mat[i][j]==joueur&&mat[i-1][j+1]==autre_joueur){	//condition Ã  droite haut
				x=i-1;
				y=j+1;				
				while(x>=0&&y<N){
					if(mat[x][y]==joueur){
						possible=1;
						y=N+1;
					}
					else if(mat[x][y]==0){
						y=N+1;
					}
					x--;
					y++;
				}
			}
			if(possible){		//Ã  droite haut
			//printf("e");
				x=i-1;
				y=j+1;	
				while(x>=0){				
					if(mat[x][y]!=joueur){
						mat[x][y]=joueur;
					}
					else if(mat[x][y]==joueur){
						x=-1;
					}
					x--;
					y++;			
				}	
			}	
			possible=0;
	
			if(mat[i][j]==joueur&&mat[i+1][j+1]==autre_joueur){	//condition Ã  droite bas
				x=i+1;
				y=j+1;				
				while(x<N&&y<N){
					if(mat[x][y]==joueur){
						possible=1;
						x=N+1;
					}
					else if(mat[x][y]==0){
						x=N+1;
					}
					x++;
					y++;
				}
			}
			if(possible){		//Ã  droite bas
			//printf("e");
				x=i+1;
				y=j+1;	
				while(x<N){				
					if(mat[x][y]!=joueur){
						mat[x][y]=joueur;
					}
					else if(mat[x][y]==joueur){
						x=N+1;
					}
					x++;
					y++;			
				}	
			}	
			possible=0;

	
			if(mat[i][j]==joueur&&mat[i-1][j-1]==autre_joueur){	//condition Ã  gauche haut
				x=i-1;
				y=j-1;				
				while(x>=0&&y>=0){
					if(mat[x][y]==joueur){
						possible=1;
						x=-1;
					}
					else if(mat[x][y]==0){
						x=-1;
					}
					x--;
					y--;
				}
			}
			if(possible){		//Ã  gauche haut
			//printf("e");
				x=i-1;
				y=j-1;	
				while(x>=0){				
					if(mat[x][y]!=joueur){
						mat[x][y]=joueur;
					}
					else if(mat[x][y]==joueur){
						x=-1;
					}
					x--;
					y--;			
				}	
			}	
			possible=0;

			if(mat[i][j]==joueur&&mat[i+1][j-1]==autre_joueur){	//condition Ã  gauche bas
				x=i+1;
				y=j-1;				
				while(x<N&&y>=0){
					if(mat[x][y]==joueur){
						possible=1;
						x=N+1;
					}
					else if(mat[x][y]==0){
						x=N+1;
					}
					x++;
					y--;
				}
			}
			if(possible){		//Ã  droite gauche bas
			//printf("e");
				x=i+1;
				y=j-1;	
				while(x<N){				
					if(mat[x][y]!=joueur){
						mat[x][y]=joueur;
					}
					else if(mat[x][y]==joueur){
						x=N+1;
					}
					x++;
					y--;			
				}	
			}	
			possible=0;					
			


	return 1;
}

void coup_possible(int mat[N][N],int joueur){


	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(bCase_verifier(mat,i,j,joueur)){
				mat[i][j]=3;			
			}
		}
	}
	grille_afficher(mat);
	
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			if(mat[i][j]==3)mat[i][j]=0;		
			
		}	
	}	

}	//calcul les differents coups possibles du joueur

/*score_calculer(int mat[N][N], int *score1, int *score2){

	int nbj1, nbj2
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
	
			if(mat[i][j]==1) nbj1++;
			else if(mat[i][j]==2) nbj2++;
		}
	}
	*score1 = *score1 + nbj1;
	*score2 = *score2 + nbj2;

}
*/


int main(){
	int mat[N][N];
	int x,y;
	int fini=0;
	int joueur=1;
	
	grille_initialiser(mat);
	printf("\n\tJoueur %i :\n\n",joueur);
			
	while(fini==0){
		
		coup_possible(mat,joueur);
		case_choisir(&x,&y);
		while(!bCase_verifier(mat,x,y,joueur) && fini==0){		//tant que les joueurs peuvent jouer, ils doivent choisir une case valide
				
				case_choisir(&x,&y);
			}
			
		pion_placer(x,y,mat,joueur);
		pion_capturer(mat,joueur,x,y);
		joueur_changer(&joueur);
		fini=jeu_fini(mat,joueur);
		if(fini==3){
			joueur_changer(&joueur);
			fini=0;
		}
	}
	printf("Le joueur %i gagne !", fini);
}





