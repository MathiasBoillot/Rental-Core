#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "chaine.h"


/*
*This library was created by Matthieu Prezut 
*it can replace string.h and add some new features
*/

char *trim (char *str) {

    char * result ;
    int deb = 0;
    int j = 0 ;
    result = (char *)malloc(sizeof(char)*(longChaine(str)+1)) ;


    for (int i =0; i<longChaine(str);i++)
    {
        if ((deb == 0) & (str[i] != ' '))
        {
            deb = 1 ;
        }

        if ((deb == 1) & (str[i] != ' '))
        {
            result[j] = str[i] ;
            j++ ;
        }
    }
    result[j] = '\0' ;
    return result ;

}


char *suppr (char *str) {

    char * result ;
    int deb = 0;
    int j = 0 ;
    result = (char *)malloc(sizeof(char)*(longChaine(str)+1)) ;


    for (int i =0; i<longChaine(str);i++)
    {
        if ((deb == 0) & (str[i] != '\n'))
        {
            deb = 1 ;
        }

        if ((deb == 1) & (str[i] != '\n'))
        {
            result[j] = str[i] ;
            j++ ;
        }
    }
    result[j] = '\0' ;
    return result ;

}


char *trim2(char *str)
{
    char *ibuf, *obuf;

    if (str)
    {
        for (ibuf = obuf = str; *ibuf; )
        {
            while (*ibuf && (isspace(*ibuf)))
                ibuf++;
            if (*ibuf && (obuf != str))
                *(obuf++) = ' ';
            while (*ibuf && (!isspace(*ibuf)))
                *(obuf++) = *(ibuf++) ;
        }
        *obuf = '\0' ;
    }
    return (str);
}

int longChaine(char *chaine)
{
    int i = 0;

    while(chaine[i] != '\0')
    {
        i++;
    }

    return i;
}


void nbSeparation(char *chaine, int *nbSep, int position[50],char sep)
{
    int i = 0, j = 0;

    while(chaine[i] != '\0')
    {
        if(chaine[i] == sep)
        {
            (*nbSep)++;
            position[j] = i+1;
            j++;
        }

        i++;
    }

    if(*nbSep == 0)
    {
        position[j] = longChaine(chaine)+1;
        (*nbSep)++;
    }
}


int compChaine(char *chaine1, char *chaine2)
{
    int verif = 0;

    if(longChaine(chaine1) == longChaine(chaine2))
    {
        for(int i = 0;i < longChaine(chaine1); i++)
        {
            if(chaine1[i] == chaine2[i])
            {
                verif++;
            }
            else
            {
                return -1;
            }
        }
    }
    else
    {
        return -1;
    }

    if( verif == longChaine(chaine1) && verif == longChaine(chaine2))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}


void copieChaine(char *dest, char *src)
{
    int i;

    for(i = 0;src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }

    dest[i] = '\0';
}


void chaine(char *chaine, int *lgChaine, int *nbSep, int position[50], char sep)
{
    if(*nbSep != 0)
    {
        *nbSep = 0;
    }

    *lgChaine = longChaine(chaine);

    nbSeparation(chaine,nbSep,position,sep);
}


void initResult(int *lgChaine, char ***resultat, int *position, int *nbSep)
{
    char **temp = (char **)calloc((*nbSep + 1), sizeof(char *));

    for(int j = 0;j <= *nbSep; j++)
    {
        if(j == 0)
        {
            //printf("$$%d\n",position[j]+1);
            temp[j] = (char *)calloc(((position[j]+1)), sizeof(char));
        }
        else if(j < *nbSep && j != 0)
        {
            int positionJ = position[j];
            int positionJm1 = position[j-1];
            char *t = (char *)malloc(sizeof(char)*(positionJ-positionJm1+1));
            temp[j] = t;
        }
        else
        {
            temp[j] = (char *)malloc(sizeof(char)*(*lgChaine-position[j-1]+2));
        }
    }
    *resultat = temp;
}


void sousChaine(char *chaine, int *lgChaine, char **resultat, int position[20], int *nbSep)
{
    int i,j,k;

    for(j = 0;j <= *nbSep; j++)
    {
        if(j == 0 && position[j] != 1)
        {
            for(i = 0,k = 0;i < position[j]-1; i++,k++)
            {
                resultat[j][k] = chaine[i];
            }

            resultat[j][k] = '\0';
        }
        else if(j < *nbSep && j != 0)
        {
            for(i = position[j-1],k = 0;i < position[j]-1; i++, k++)
            {
                resultat[j][k] = chaine[i];
            }

            resultat[j][k] = '\0';
        }
        else if(j == *nbSep)
        {
            for(i = position[j-1],k = 0;i < *lgChaine; i++,k++)
            {
                resultat[j][k] = chaine[i];
            }

            resultat[j][k] = '\0';
        }
    }
}


int Fill(char *chaine, char sep)
{
    int i,empty = 0;

    for(i = 0;i < longChaine(chaine); i++)
    {
        if(chaine[i] == sep)
        {
            empty ++;
        }
        else
        {
            break;
        }
    }

    if(empty == longChaine(chaine) && empty != 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


void fonct(char *info, char ***R, int *nb, char sep)
{
    int lg = 0,nbSep = 0;
    int *posit = (int*)malloc(sizeof(int)*longChaine(info));

    char **result = NULL;

    if(info == NULL)
    {
        printf("Chaine nulle\n");
    }
    else if(Fill(info,sep) != 0)
    {
        printf("Chaine remplie de séparateurs\n");
    }
    else if(info[0] != '\0' && info != NULL)
    {
        // SEPARATION SOUS CHAINE
        chaine(info,&lg,&nbSep,posit,sep);

        initResult(&lg,&result,posit,&nbSep);

        sousChaine(info,&lg,result,posit,&nbSep);

        // AFFICHAGE SOUS CHAINE
        /*for(int i = 0;i <= nbSep; i++)
        {
            if((posit[nbSep] != longChaine(result[i])) && compChaine(result[i],"") != 0)
            {
                printf("Sous chaine %d = %s\n",i,result[i]);
            }
        }*/

        *R = result;
        *nb = nbSep;
    }
    else
    {
        printf("Chaine vide\n");
    }
    free(posit);
}