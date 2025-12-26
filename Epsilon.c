#include <stdio.h>

#define MAX_STATES 20
#define MAX_SYMBOLS 10

int nStates, nSymbols;
char symbols[MAX_SYMBOLS];
int startState;

int isFinal[MAX_STATES];
int newFinal[MAX_STATES];

int eps[MAX_STATES][MAX_STATES];   // epsilon transitions
int trans[MAX_STATES][MAX_SYMBOLS][MAX_STATES]; // normal transitions

int eclosure[MAX_STATES][MAX_STATES];
int newTrans[MAX_STATES][MAX_SYMBOLS][MAX_STATES];



void readNFA() {
    int i, j, k;

    printf("Number of states: ");
    scanf("%d", &nStates);

    printf("Number of symbols: ");
    scanf("%d", &nSymbols);

    printf("Symbols:\n");
    for (i = 0; i < nSymbols; i++)
        scanf(" %c", &symbols[i]);

    printf("Start state: ");
    scanf("%d", &startState);

    printf("Final states (0/1):\n");
    for (i = 0; i < nStates; i++)
        scanf("%d", &isFinal[i]);

    printf("Epsilon transition matrix:\n");
    for (i = 0; i < nStates; i++)
        for (j = 0; j < nStates; j++)
            scanf("%d", &eps[i][j]);

    printf("Symbol transitions:\n");
    for (i = 0; i < nStates; i++)
        for (j = 0; j < nSymbols; j++)
            for (k = 0; k < nStates; k++)
                scanf("%d", &trans[i][j][k]);
}



void dfsEpsilon(int s, int visited[]) {
    visited[s] = 1;
    for (int i = 0; i < nStates; i++) {
        if (eps[s][i] && !visited[i])
            dfsEpsilon(i, visited);
    }
}

void computeEclosures() {
    for (int s = 0; s < nStates; s++) {
        int visited[MAX_STATES] = {0};
        dfsEpsilon(s, visited);
        for (int i = 0; i < nStates; i++)
            eclosure[s][i] = visited[i];
    }
}



void computeNewTransitions() {
    for (int p = 0; p < nStates; p++) {
        for (int a = 0; a < nSymbols; a++) {
            for (int q = 0; q < nStates; q++) {
                if (eclosure[p][q]) {
                    for (int r = 0; r < nStates; r++) {
                        if (trans[q][a][r]) {
                            for (int t = 0; t < nStates; t++) {
                                if (eclosure[r][t])
                                    newTrans[p][a][t] = 1;
                            }
                        }
                    }
                }
            }
        }
    }
}



void computeNewFinalStates() {
    for (int s = 0; s < nStates; s++) {
        for (int i = 0; i < nStates; i++) {
            if (eclosure[s][i] && isFinal[i]) {
                newFinal[s] = 1;
                break;
            }
        }
    }
}



void displayNewNFA() {
    printf("\nNew final states:\n");
    for (int i = 0; i < nStates; i++)
        if (newFinal[i])
            printf("q%d ", i);

    printf("\n\nNew transitions (without ε):\n");
    for (int i = 0; i < nStates; i++) {
        for (int a = 0; a < nSymbols; a++) {
            for (int j = 0; j < nStates; j++) {
                if (newTrans[i][a][j])
                    printf("q%d --%c--> q%d\n", i, symbols[a], j);
            }
        }
    }
}


int main() {
    readNFA();
    computeEclosures();
    computeNewTransitions();
    computeNewFinalStates();
    displayNewNFA();
    return 0;
}
