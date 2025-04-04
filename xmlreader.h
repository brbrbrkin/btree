#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define buffer 10

// entrega
typedef struct
{
    int cod;
    char descricao[20];
    double custo;
} entrega;

// doc
typedef struct
{
    double version;
    char encoding[20];
    entrega entregas[buffer];
} xml_doc;

/*
    set cod in <cod> section
*/
int set_cod(char *line)
{
    bool in = false;
    int e, k = 0;
    char bfr[3];
    for (int i = 0; line[i] != '\0'; i++)
    {

        if (in)
        {
            bfr[k] = line[i];
            k++;
            if (line[i + 1] == '<')
                break;
        }
        if (line[i] == '>')
            in = true;
    }
    sscanf(bfr, "%d", &e);
    return e;
}
/*
    set cod in <cod> section
*/
void set_sts(char *line, xml_doc *xml)
{
    bool in = false;
    int k = 0, j=0;
    double e;
    char bfr[20];
    int i;
    for (i = 0; line[i] != '\0'; i++)
    {

        if (in)
        {
            bfr[k] = line[i];
            k++;
            if (line[i + 1] == '\"')
                j = i+2; 
                in = false;
                break;
        }
        if (line[i] == '\"')
            in = true;
    }
    // char * -> double 
    sscanf(bfr, "%lf", &e);
    xml->version = e;

    k=0;
    // cleaning buffer
    for (int h = 0; h < 20; h++)
        bfr[h] = '\0';

    for (j=i+4;line[j] != '\0'; j++)
    {

        if (in)
        {
            bfr[k] = line[j];
            k++;
            if (line[j + 1] == '\"') 
                break;
        }
        if (line[j] == '\"')
            in = true;
    }
    strcpy(xml->encoding,bfr);
}
/*
    set custo in <custo> section
*/
double set_price(char *line)
{
    bool in = false;
    int k = 0;
    double e;
    char bfr[10];
    for (int i = 0; line[i] != '\0'; i++)
    {

        if (in)
        {
            bfr[k] = line[i];
            k++;
            if (line[i + 1] == '<')
                break;
        }
        if (line[i] == '>')
            in = true;
    }
    for (int j = 0; bfr[j] != '\0'; j++)
    {
        if (bfr[j] == ',')
            bfr[j] = '.';
    }
    sscanf(bfr, "%lf", &e);
    return e;
}

/*
    set descr in <descr> section
*/
char *set_des(char *line, char *dest)
{
    bool in = false;
    int k = 0;
    char bfr[20];
    for (int j = 0; j < 20; j++)
        bfr[j] = '\0';

    for (int i = 0; line[i] != '\0'; i++)
    {

        if (in)
        {
            bfr[k] = line[i];
            k++;
            if (line[i + 1] == '<')
                break;
        }
        if (line[i] == '>')
            in = true;
    }
    //printf("%s", bfr);
    strcpy(dest, bfr);
    return bfr;
}

/*
    returns xml
*/
xml_doc* xml_read(char *filepath)
{
    FILE *xml = fopen(filepath, "r+");
    if (xml == NULL)
        system("echo \" ERROR Could not found the arquive\" ");
    xml_doc * xmlarq = (xml_doc*)malloc(sizeof(xml_doc));

    char linha[1024];
    int entrega = 0;
    while (fgets(linha, sizeof(linha), xml) != NULL)
    {
        if(linha[1]=='?')
        {
            set_sts(linha, xmlarq);
        }
        if (strcmp(linha, "        <Entrega>\n") == 0)
        {
            int id = 0;
            do
            {
                fgets(linha, sizeof(linha), xml);
                switch (id)
                {
                case 0:
                    xmlarq->entregas[entrega].cod = set_cod(linha);
                    break;
                case 1:
                    set_des(linha, xmlarq->entregas[entrega].descricao);
                    break;
                case 2:
                    xmlarq->entregas[entrega].custo = set_price(linha);
                    break;
                default:
                    break;
                }
                id++;
                //printf("%s", linha);
            } while (strcmp(linha, "        </Entrega>\n") != 0);
            entrega++;
        }
    }

    return xmlarq;
}

// int main(void)
// {    
//     xml_doc kp = xml_read("AV3_AEDII\\entregas.txt");
//     system("pause");
// }