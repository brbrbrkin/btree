#include "xmlreader.h"
#include "ArvB.h"

void Show_all(TipoApontador root)
{
    int i=0;
    if(root == NULL)
        return;
    for(i=0; i< root->n ;i++)
    {
        printf("Codigo : %d\n",root->r[i].Chave);
        printf("Descricao : %s\n",root->r[i].descricao);
        printf("Custo : %.2lf\n",root->r[i].custo);
    }
    printf("\n");
    for (i = 0; i <= root->n; i++)
		Show_all(root->p[i]);
}//78,500 
double get_custo(TipoApontador root)
{
    int i=0;
    double res=0;
    if(root == NULL)
        return 0;
    for(i=0; i< root->n ;i++)
    {
        res += root->r[i].custo;
    }
    for (i = 0; i <= root->n; i++)
		res += get_custo(root->p[i]);
    return res;
}
int main(void)
{
    char c;
    int chv;
    TipoApontador arv_b;
    Inicializa(&arv_b);
    xml_doc *document;
    TipoRegistro rg,*registro;
    registro = (TipoRegistro*)malloc(sizeof(TipoRegistro));
    while(1)
    {
        system("cls");
        fflush(stdin);
        printf(">> B:/entregas :\n1 = Leitura do xml (*filepath)\n2 = Pesquisar a etapa da obra (*Cod)\n3 = Exibe todas as etapas da obra.\n4 = Custo total da obra.\n5 = Sair.\n");
        scanf("%c",&c);
        system("cls");
        
        switch(c)
        {
            case '1':
                {
                    printf("XML Path : \n");
                    char *path = (char*)malloc(sizeof(char));
                    fflush(stdin);
                    gets(path);
                    // Inserindo as entregas na árvore B
                    document = xml_read(path);                
                    int x=10;
                    while (x--)
                    {
                        
                        rg.Chave = (long int)document->entregas[x].cod;
                        rg.custo  = document->entregas[x].custo;
                        strcpy(rg.descricao,document->entregas[x].descricao );
                        Insere(rg, &arv_b);
                    }
                    printf("Read!\n");
                }
                break;
            case '2':
                {
                    printf("Insira o cod :\n");
                    scanf("%d",&chv);
                    registro->Chave = (long int)chv;
                    registro = Pesquisa(registro,arv_b);
                    printf("Etapa : %s\n", registro->descricao);
                    printf("Custo : %.2lf\n", registro->custo);
                }
                break;
            case '3':
                Show_all(arv_b);
               //Imprime(arv_b);
                break;
            case '4':
                {
                    double custo = 0;
                    custo = get_custo(arv_b);
                    printf("Custo total: %.2lf",custo);
                }
                break;
            case '5':
                printf("Shuting off...\n");
                system("pause");
                exit(0);
                break;
            default:
                break;
        }
        system("pause");
    }
    system("pause");
}