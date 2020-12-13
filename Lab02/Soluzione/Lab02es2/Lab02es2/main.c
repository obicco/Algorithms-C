//
//  main.c
//  Lab02es2
//
//  Created by Oskar Bich on 04/11/2020.
//

#include <stdio.h>
#include <string.h>
#define MAXN 1000
#define MAXS 31
#define CMD 6

typedef struct {
    int y;
    int m;
    int d;
} date;

typedef struct {
    int h;
    int m;
    int s;
} time;

typedef struct{
    char cod[MAXS];
    char dep[MAXS];
    char arr[MAXS];
    date date;
    time dep_t;
    time arr_t;
    int delay;
} line;

typedef enum {r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine} comando_e;

int readLog(line lines[]);
void printLine(line line);
void printInstructions(char instructions[][MAXS]);
void selectData(line lines[], comando_e cmd, int n);
int compareDate(date d1, date d2);

comando_e readInstruction(char instructions[][MAXS]);

int main(int argc, const char * argv[]) {
    char instructions[][MAXS] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    int go = 1;
    comando_e cmd;
    line lines[MAXN];
    int n;
    
    n = readLog(lines);
    printf("Line list:\n");
    for(int i = 0; i < n; i++) {
    printLine(lines[i]);
    }
    
    printInstructions(instructions);
    do {
        cmd = readInstruction(instructions);
        switch(cmd) {
            case r_date:
        selectData(lines, r_date, n);
                break;
            case r_partenza:
        selectData(lines, r_partenza, n);
                break;
            case r_capolinea:
        selectData(lines, r_capolinea, n);
                break;
            case r_ritardo:
        selectData(lines, r_ritardo, n);
                break;
            case r_ritardo_tot:
        selectData(lines, r_ritardo_tot, n);
                break;
            case r_fine:
                go = 0;
                break;
      default:
        printInstructions(instructions);
        }
    } while(go);
    return 0;
}

int readLog(line lines[]) {
    int n;
    char tmp_date[11], tmp_t1[9], tmp_t2[9];
    FILE *fIN = fopen("log.txt", "r");
    
    fscanf(fIN, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fIN, "%s %s %s %s %s %s %d", lines[i].cod, lines[i].dep, lines[i].arr, tmp_date, tmp_t1, tmp_t2, &lines[i].delay);
        sscanf(tmp_date, "%d/%d/%d", &lines[i].date.y, &lines[i].date.m, &lines[i].date.d);
        sscanf(tmp_t1, "%d:%d:%d", &lines[i].dep_t.h, &lines[i].dep_t.m, &lines[i].dep_t.s);
        sscanf(tmp_t2, "%d:%d:%d", &lines[i].arr_t.h, &lines[i].arr_t.m, &lines[i].arr_t.s);
    }
    fclose(fIN);
    return n;
}

void printLine(line line) {
        printf("%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", line.cod, line.dep, line.arr, line.date.y, line.date.m, line.date.d, line.dep_t.h, line.dep_t.m, line.dep_t.s, line.arr_t.h, line.arr_t.m, line.arr_t.s, line.delay);
}

comando_e readInstruction(char instructions[][MAXS]) {
  char cmd[MAXS];
  printf("Comando > ");
  scanf("%s", cmd);
  for (int i = 0; i < CMD; i++) {
    if (strcmp(cmd, instructions[i]) == 0)
      return (comando_e) i;
  }
  return -1;
}

void printInstructions(char instructions[][MAXS]) {
    printf("Comandi disponibili:\n");
    for (int i = 0; i < CMD; i++) {
        printf("%s - ", instructions[i]);
    }
    printf("\n");
}

void selectData(line lines[], comando_e cmd, int n) {
  date d1, d2;
    int tot = 0;
  char target[MAXS];
  if (cmd == r_date) {
    printf("Inserire prima data [aaaa/mm/gg]: ");
    scanf("%d/%d/%d", &d1.y,&d1.m,&d1.d);
    printf("Inserire seconda data [aaaa/mm/gg]: ");
    scanf("%d/%d/%d", &d2.y,&d2.m,&d2.d);
      for(int i = 0; i < n; i++) {
          if(compareDate(d1, lines[i].date) <= 0 && compareDate(lines[i].date, d2) <= 0)
              printLine(lines[i]);
      }
  } else if (cmd == r_partenza) {
    printf("Inserire luogo di partenza: ");
    scanf("%s", target);
      for(int i = 0; i < n; i++) {
          if(strcmp(lines[i].dep,target) == 0)
              printLine(lines[i]);
      }
  } else if (cmd == r_capolinea) {
    printf("Inserire luogo di destinazione: ");
    scanf("%s", target);
      for(int i = 0; i < n; i++) {
          if(strcmp(lines[i].arr,target) == 0)
              printLine(lines[i]);
      }
  } else if(cmd == r_ritardo) {
    printf("Inserire prima data [aaaa/mm/gg]: ");
    scanf("%d/%d/%d", &d1.y,&d1.m,&d1.d);
    printf("Inserire seconda data [aaaa/mm/gg]: ");
    scanf("%d/%d/%d", &d2.y,&d2.m,&d2.d);
      for(int i = 0; i < n; i++) {
          if(compareDate(d1, lines[i].date) <= 0 && compareDate(lines[i].date, d2) <= 0 && lines[i].delay > 0)
              printLine(lines[i]);
      }
  } else if(cmd == r_ritardo_tot) {
    printf("Inserire codice della tratta: ");
    scanf("%s", target);
      for(int i = 0; i < n; i++) {
          if(strcmp(lines[i].cod, target) == 0 && lines[i].delay > 0)
              tot += lines[i].delay;
      }
      printf("Il ritardo totale della tratta %s è di %d minuti\n", target, tot);
  }
}
             
 int compareDate(date d1, date d2) {
     if (d1.y != d2.y)
       return (d1.y-d2.y);
     else if (d1.m != d2.m)
       return (d1.m-d2.m);
     else if (d1.d != d2.d)
       return (d1.d-d2.d);
     else return 0;
}
