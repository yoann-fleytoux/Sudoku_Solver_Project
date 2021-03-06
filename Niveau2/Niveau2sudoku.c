
#include <stdio.h>
#include <stdbool.h>

typedef struct
{
  	int val;
  	int n_candidats;
	int candidats[9];
}T_case;



typedef struct
{	
	T_case grille[81];
}T_sudoku;

void saisie2 (T_sudoku p)
{
  
	int cpt;
	int d;
	cpt=0;
	FILE* grille;
	while (cpt!=81)
	{
		grille=fopen(”C :\\grille.txt”, ”a”);
		printf("Veuillez entrez le %d ieme case de la grille",cpt);
		scanf("%d",&d);
		fprintf(grille,”|”,d);/*met d a la suite du fichier grille.txt*/
		cpt=cpt+1;
	}
}

void affichecand2 (T_sudoku d)
{
  
	FILE* grille;
	int i;
	grille=fopen(”C :\\grille.txt”, ”a”);
	for (i=0;i<82;i++)
	{
		fscanf(grille,"|",d.grille[i].val);/*affiche la valeur de cas qui est la ieme valeur du fichier grille.txt*/
	}
}

void afficheligne2 (T_sudoku p, int cas)
{
	int i,j;
	affichecand2(p);
	for (i=0;i<10;i++)
	{
		for (j=0;j<3;j++)
		{
			printf("|");
			printf("%d",p.grille[cas+i].candidats[j]);
		}
	}
	printf("|\n");
	for (i=0;i<10;i++)
	{
		for (j=3;j<6;j++)
		{
			printf("|");
			printf("%d",p.grille[cas+i].candidats[j]);
		}
	}
	printf("|\n");
	for (i=0;i<10;i++)
	{
		for (j=6;j<9;j++)
		{
			printf("|");
			printf("%d",p.grille[cas+i].candidats[j]);
		}
	}
	printf("|\n");
}

void affiche2 (T_sudoku p)
{
	int i;
	for (i=0;i<10;i++)
	{
    
		afficheligne2(p, i*9);
		if (i==2)
		{
			printf("-----------------------------------------------------------------\n");
		}
	}
}

void R1 (T_sudoku p, int o)
{
	int i;
	if (p.grille[o].n_candidats==1)
	{
    
		for (i=0;i<10;i++)
		{
      
			if (p.grille[o].candidats[i]!=' ')
			{
	
				p.grille[o].val=p.grille[o].candidats[i];
      
			}
    
		}
  
	}

}

void castrans (int d,int col, int lig)
{
  
	col=d%9;
  
	lig=(d-col)/9;

}

int R2hori (T_sudoku p, int d)
{
  
	int can[9]={1,2,3,4,5,6,7,8,9};
  
	int cas,i,col,lig;
  
	castrans(d,col,lig);
  
	for (i=0;i<10;i++)
	{
    
		cas=9*lig+i;
    
		if (cas!=d)
		{
      
			if (p.grille[cas].val!=0)
			{
	
				can[(p.grille[cas].val)-1]=' ';
      
			}
    
		}
  
	}
  	
	return(can[9]);

}

int R2verti (T_sudoku p, int d)
{
  
	int can2[9]={1,2,3,4,5,6,7,8,9};
  
	int cas,i,col,lig;
  
	castrans(d,col,lig);
  
	for (i=0;i<10;i++)
	{
    
		cas=i*9+col;
    
		if (cas!=d)
		{
      
			if (p.grille[cas].val!=0)
			{
	
				can2[(p.grille[cas].val)-1]=' ';
      
			}
    
		}
  
	}
  
	return(can2[9]);

}

int lboite (int a)
{
  
	if (a<3)
	{
    
		a=1;
  
	}
	else if (a<6)
	{
    
		a=4;
  
	}
	else
	{

    		a=7;
  
	}
  
	return(a);

}

int cboite (int a)
{
  
	if (a%3==1)
	{
    
		a=1;
  
	}
	else if (a%3==2)
	{
    
		a=4;
  
	}
	else
	{
    
		a=7;
  
	}
  
	return(a);

}

int R2boite (T_sudoku p, int d)
{
  
	int can3[9]={1,2,3,4,5,6,7,8,9};
  
	int cas,col,lig,i,j;
  
	castrans(d,col,lig);
  
	lig=lboite(lig);
  
	col=cboite(col);
  
	for (i=0;i<4;i++)
	{
		for (j=0;j<4;j++)
		{
      
			cas=(lig+j)*9+(col+i);
      
			if (cas!=d)
			{
	
				if (p.grille[cas].val!=0)
				{
	  
					can3[(p.grille[cas].val)-1]=' ';
	
				}
      
			}
    
		}
  
	}

	return(can3[9]);
}

int R2 (T_sudoku p, int d)
{
  
	int i;
  
	int can[9], can2[9], can3[9]; 
	can[9]=R2verti(p,d);
	can2[9]=R2hori(p,d);
	can3[9]=R2boite(p,d);
	for (i=0;i<10;i++)
	{
    
		if (can[i]==can2[i] && can2[i]==can3[i])
		{
      
			p.grille[d].candidats[i]=can[i];
    
		}
		else
		{
      
			p.grille[d].candidats[i]=' ';
    
		}
  
	}
  
	return(p.grille[d].candidats[9]);

}

int valacas (T_sudoku p, int i, int cas)
{
	if (p.grille[cas].val==i)
	{
		return (cas);
	}
	return (81);
}

int cherch (T_sudoku p, int i, int loca)
{
	int j,n;
	for (j=1;j<loca+1;j++)
	{
		n=valacas(p,i,j);
		if (n!=81)
		{
			return(n);
		}
	}
	return(81);
}

void gestioncandidats (T_sudoku p)
{
	int n;
	int i;
	for (i=0;i<82;i++)
	{
		if (p.grille[i].val==0)
		{
			if (p.grille[i].n_candidats==1)
			{
				if ( p.grille[i].candidats[5]==' ')
				{
					n=cherch(p,p.grille[i].val,p.grille[i].candidats[9]);
					p.grille[i].candidats[5]=p.grille[i].candidats[n];
					p.grille[i].candidats[n]=' ';
				}
			}
		}
	}
}	

void initialise (T_sudoku p)
{
  
	int i,j;
  
	for (i=0;i<81;i++)
	{
      
		p.grille[i].val=0;
      
		p.grille[i].n_candidats=0;
      
		for (j=1;j<10;j++)
		{
	
			p.grille[j].candidats[j-1]=' ';
      
		}
  
	}

}

int supp(int cand,T_case a)
{
	
	int i;
	for (i=0;i<10;i++)
	{
		if (a.candidats[i]==cand)
		{
			a.candidats[i]=' ';
		}
	}
	return(a.candidats[9]);
}

bool verif (T_sudoku p)
{
	int i;
	for (i=0;i<82;i++)
	{
		if (p.grille[i].val==0)
		{
			return (false);
		}
	}
	return (true);
}

int dif (int can[9], int can2[9])
{
  
	int j[9];
  
	int i;
	for (i=0;i<10;i++)
	{
    
		if (can[i]==can2[i])
		{
      
			j[i]=0;
    
		}
		else if (can[i]!=can2[i] && can[i]!=' ')
		{
      
			j[i]=can[i];

		}
		else if (can[i]!=can2[i] && can2[i]!=' ')
		{
      
			j[i]=can2[i];
    
		}
  
	}
  
	return(j[9]);

}

int nbval (int j[9])
{
	int i,k;
	int val[9];
  	k=0;
	for (i=0;i<10;i++)
	{
    
		if (j[i]!=0)
		{
      
			k=k+1;
      
			val[1]=j[i];
    
		}
  
	}
  
	val[0]=k;
  
	return(val[9]);

}


void R3 (T_sudoku p, int group,int pos)
{
	int j[9],val[9], can[9];
	if (group==1)
	{
		can[9]=R2hori(p,pos);
		j[9]=dif(can[9], p.grille[pos].candidats[9]);
		val[9]=nbval(j[9]);
		if (val[0]==1)
		{
			p.grille[pos].val=val[1]; 
		}
	}
	else if (group==2)
	{
		can[9]=R2verti(p,pos);
		j[9]=dif(can[9], p.grille[pos].candidats[9]);
		val[9]=nbval(j[9]);
		if (val[0]==1)
		{
			p.grille[pos].val=val[1]; 
		}
	}
	else if (group==3)
	{
		can[9]=R2boite(p,pos);
		j[9]=dif(can[9], p.grille[pos].candidats[9]);
		val[9]=nbval(j[9]);
		if (val[0]==1)
		{ 
			p.grille[pos].val=val[1]; 
		}
	}
}

int add (int can[9],int can2[9])
{
	int i;
	for (i=0;i<10;i++)
	{
		if (can[i]!=can2[i] && can[i]==' ')
		{ 
			can[i]=can2[i];
		}
		else
		{    
			can[i]=can[i];   
		} 
	}
	return(can[9]);
}

int dif1 (int can[9], int can2[9])
{
	int j[9];
	int i; 
	for (i=0;i<10;i++)
	{
		if (can[i]!=can2[i] && can[i]!=' ')
		{
			j[i]=can[i];
		}	
		else
		{
			j[i]=0;
		}
	}
	return(j[9]);
}

int ligtrans (int col, int lig)
{
	lig=lig-1;
	col=col-1;
	return((lig*9)+col);
}

int candligb (int lig, int col, T_sudoku p)
{
	int cas, cas2, cas3;
	int can[9];
	cas=ligtrans(col,lig);
	cas2=ligtrans(col+1,lig);
	cas3=ligtrans(col+2,lig);
	can[9]=add(p.grille[cas].candidats[9],p.grille[cas2].candidats[9]);
	can[9]=add(can[9],p.grille[cas3].candidats[9]);
  	return (can[9]);
}   
   


int cand_lig (T_sudoku p, int boit)
{
	int ligb, colb;
	int can[9], can2[9], can3[9];
	bool contin;
	ligb=lboite(boit);
	colb=cboite(boit);
	can[9]=canligb(ligb,colb);
	can2[9]=canligb(ligb+1,colb);
	can3[9]=canligb(ligb+2,colb);
	can2[9]=add(can2[9],can3[9]);
	can[9]=diff1(can[9],can2[9]);
	if (can[i]!=0)
	{
		contin=true;
	}
	else
	{
		contin=false;
	}
	if (contin=true)  
	{
		return(can[9]);
	}
	return (0);
}

int cancolb (int lig, int col, T_sudoku p)
{
	int cas, cas2, cas3;
	int can[9];
	cas=ligtrans(col,lig);
	cas2=ligtrans(col,lig+1);
	cas3=ligtrans(col,lig+2);
	can[9]=add(p.grille[cas].candidats[],p.grille[cas2].candidats[9]);
	can[9]=add(can[],p.grille[cas3].candidats[9]);
  	return (can[9]);
}   
   


int cand_col (T_sudoku p, int boit)
{
	int ligb, colb;
	int can2[9], can3[9];
	bool contin;
	ligb=lboite(boit);
	colb=cboite(boit);
	can[9]=cancolb(ligb,colb,p);
	can2[9]=cancolb(ligb,colb+1,p);
	can3[9]=cancolb(ligb,colb+2,p);
	can2[9]=add(can2[9],can3[9]);
	can[9]=diff1(can[9],can2[9]);
	if (can[i]!=0)
	{
		contin=true;
	}
	else
	{
		contin=false;
	}
	if (contin=true)  
	{
		return(can[9]);
	}
	return(0);
}  

int ordre (int j[9])
{
	int i, g;
	for (i=0;i<9;i++)
	{
		if (j[i]==0)
		{
			j[i]=j[i+1];
		}
		else
		{
			if (j[i]>j[i+1])
			{
				g=j[i];
				j[i]=j[i+1];
				j[i+1]=j[i];
			}
		}
	}
	return(j[9]);
}

int R4col (T_sudoku p, int pos)
{
	int candcol[9], candcol2[9], candcol3[9];
	int j1[9], j2[9], j[9];
	int i, k;
	candcol[9]=cand_col(p,pos);
	candcol2[9]=cand_col(p,pos+1);
	candcol3[9]=cand_col(p,pos+2);
	j1[9]=dif1(candcol[9],candcol2[9]);
	j2[9]=dif1(candcol[9],candcol3[9]);
	j1[9]=ordre(j1[9]);
	j2[9]=ordre(j2[9]);
	for(i=0;i<10;i++)
	{
		for (k=0;k<10;k++)
		{
			if (j1[i]==j2[k])
			{
				j[i]=j1[i];
				k=10;
			}
			else if (j1[i]>j2[k])
			{
				k=10;
			}
		}
	}
	return(j[9]);
}

int R4lig (T_sudoku p, int pos)
{
	int candlig[9], candlig2[9], candlig3[9];
	int j1[9], j2[9], j[9];
	int i, k;
	candlig[9]=cand_lig(p,pos);
	candlig2[9]=cand_lig(p,pos+1);
	candlig3[9]=cand_lig(p,pos+2);
	j1[9]=dif1(candlig[9],candlig2[9]);
	j2[9]=dif1(candlig[9],candlig3[9]);
	j1[9]=ordre(j1[9]);
	j2[9]=ordre(j2[9]);
	for(i=0;i<10;i++)
	{
		for (k=0;k<10;k++)
		{
			if (j1[i]==j2[k])
			{
				j[i]=j1[i];
				k=10;
			}
			else if (j1[i]>j2[k])
			{
				k=10;
			}
		}
	}
	return(j[9]);
}

void R4 (T_sudoku p, int pos)
{
	int lig[9], col[9];
	lig[9]=R4lig(p,pos);
	col[9]=R4col(p,pos);
	supplig(p,col[9],pos);
	suppcol(p,lig[9],pos);
}