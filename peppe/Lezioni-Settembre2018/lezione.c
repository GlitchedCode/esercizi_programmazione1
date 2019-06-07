#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lezione.h"

// Ciclo vitale
void init_lista_lezioni(ListaLezioni *head)
{
    *head = NULL;
}

void destroy_lista_lezioni(ListaLezioni head)
{
    ListaLezioni temp;
    while(head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Funzioni di persistenza
int load_from_file(ListaLezioni *head, const char *filename)
{
    FILE* fp;
    char code[CODE_MAX_LEN + 1];
    unsigned short day, mon, year;
    unsigned presenze;
    ListaLezioni *start = head;
    fp = fopen(filename, "r");
    
    if(!fp) return 0;
    
    while(fscanf(fp, "%s %2hd/%2hd/%4hd %hd\n", code, &day, &mon, &year, &presenze) != EOF)
    {   
        if(!*head)
        {

            if(!insert_head(head, code, day, mon, year, presenze))
            {
                destroy_lista_lezioni(*start);
                *start = NULL;
                fclose(fp);
                return 0;
            }
        }
        else
        {
            if(!insert_tail(*head, code, day, mon, year, presenze))
            {
                destroy_lista_lezioni(*start);
                *start = NULL;
                fclose(fp);
                return 0;
            }
            else
                head = &(*head)->next;
        }     
    }

    fclose(fp);
    return 1;
}

int save_to_file(ListaLezioni head, const char *filename)
{
    FILE *fp;

    fp = fopen(filename, "w");
    if(!fp) return 0;

    while(head)
    {
                    //  11 + 2*3 + 2 + 1 + [>= 1] >= 21
        if(fprintf(fp, "%s %2hd/%2hd/%4hd %hd\n", head->code, head->day, 
            head->mon, head->year, head->presenze) < 21)
            return 0;   // Errore durante la scrittura;
        head = head->next;
    }

    fclose(fp);
    return 1;
}

// Funzioni di accesso
int insert_head(ListaLezioni *head, const char *code, unsigned short day, unsigned short mon, 
    unsigned short year, unsigned presenze)
{
    ListaLezioni temp;
    if(!*head) 
    {
        *head = (ListaLezioni)malloc(sizeof(Lezione));
        if(!*head)
        {
            fprintf(stderr, "Errore durante l'allocazione.\n");
            return 0;
        }
        (*head)->next = NULL;
    }    
    else
    {
        temp = (ListaLezioni)malloc(sizeof(Lezione));
        if(!temp)
        {
            fprintf(stderr, "Errore durante l'allocazione.\n");
            return 0;
        }
        temp->next = *head;
        *head = temp;
    }

    strncpy((*head)->code, code, CODE_MAX_LEN);
    (*head)->day = day;
    (*head)->mon = mon;
    (*head)->year = year;
    (*head)->presenze = presenze;
    return 1;
}
int insert_tail(ListaLezioni tail, const char *code, unsigned short day, unsigned short mon, 
    unsigned short year, unsigned presenze)
{
    ListaLezioni temp;
    if(tail) 
    {
        temp = (ListaLezioni)malloc(sizeof(Lezione));
        if(!temp)
        {
            fprintf(stderr, "Errore durante l'allocazione.\n");
            return 0;
        }
        tail->next = temp;
        tail = temp;
    }
    else
    {
        fprintf(stderr, "Puntatore nullo passato a insert_tail.\n");
        return 0;
    }
    

    strncpy(tail->code, code, CODE_MAX_LEN);
    tail->day = day;
    tail->mon = mon;
    tail->year = year;
    tail->presenze = presenze;
    return 1;
}

// Manipolazione dei dati
float media_presenze(ListaLezioni head, const char *code)
{
    float sum = 0.f;
    unsigned count = 0;

    while(head)
    {
        if(!strncmp(code, head->code, CODE_MAX_LEN))
        {
            count++;
            sum = sum + (float)head->presenze;
        }
        head = head->next;
    }
    if(count)
        return sum / count;
    else
        return 0;
}

// Lista di supporto per immagazzinare gli indirizzi di alcune stringhe.
typedef struct string_list
{
    char* str;
    struct string_list *next;    
} string_list;

int string_insert(string_list **head, char* str, unsigned len)
{
    string_list* temp;
    if(!*head)
    {
        *head = (string_list*)malloc(sizeof(string_list));
        if(!*head) return 0;
        (*head)->str = str;
        (*head)->next = NULL;
    }
    else
    {
        while((*head))
        {
            if(!strncmp(str, (*head)->str, len))
            {
                return 1;
            }
            temp = *head;
            head = &(*head)->next;
        }
        temp->next = (string_list*) malloc(sizeof(string_list));
        if(!temp->next) return 0;
        temp->next->str = str;
        temp->next->next = NULL;
    }    

    return 1;
}

void destroy_strings(string_list* head)
{
    string_list* temp;
    while(head)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void print_most_unpopular(ListaLezioni head)
{
    string_list *strings = NULL, *currentString;
    string_list* chosen;
    float avg = -1.f, temp;
    ListaLezioni current = head;
    while(current)
    {
        if(!string_insert(&strings, current->code, CODE_MAX_LEN))
        {
            destroy_strings(strings);
            fprintf(stderr, "Errore durante l'allocazione.\n");            
        }
        current = current->next;
    }
    currentString = strings;
    while(currentString)
    {
        temp = media_presenze(head, currentString->str);
        if(temp < avg || avg == -1.f)
        {
            avg = temp;
            chosen = currentString;
        }
        currentString = currentString->next;
    }
    if(avg == -1.f)
        printf("Nessuna lezione inserita.\n");
    else
        printf("Corso: %s\nMedia presenze: %f\n", chosen->str, avg);
    destroy_strings(strings);
}

void print_most_popular(ListaLezioni head)
{
    string_list *strings = NULL, *currentString;
    string_list* chosen;
    float avg = -1.f, temp;
    ListaLezioni current = head;
    while(current)
    {
        if(!string_insert(&strings, current->code, CODE_MAX_LEN))
        {
            destroy_strings(strings);
            fprintf(stderr, "Errore durante l'allocazione.\n");            
        }
        current = current->next;
    }
    currentString = strings;
    while(currentString)
    {
        temp = media_presenze(head, currentString->str);
        if(temp > avg)
        {
            avg = temp;
            chosen = currentString;
        }
        currentString = currentString->next;
    }
    if(avg == -1.f)
        printf("Nessuna lezione inserita.\n");
    else
        printf("Corso: %s\nMedia presenze: %f\n", chosen->str, avg);
    destroy_strings(strings);
}

void print_courses_data(ListaLezioni head)
{
    string_list *strings = NULL, *currentString;
    float temp;
    ListaLezioni current = head;
    while(current)
    {
        if(!string_insert(&strings, current->code, CODE_MAX_LEN))
        {
            destroy_strings(strings);
            fprintf(stderr, "Errore durante l'allocazione.\n");            
        }
        current = current->next;
    }
    currentString = strings;
    while(currentString)
    {
        printf("Corso: %s\nMedia presenze: %f\n", currentString->str, 
            media_presenze(head, currentString->str));
        currentString = currentString->next;
    }
    destroy_strings(strings);
}