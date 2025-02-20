#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SIZE 16  // 가상 그리드 개념 제거로 크기 변경

// Function Prototypes
void printing(int** grid);
void update_grid(int** grid);
int count_neighbors(int** grid, int row, int col);

int main() {
    int** grid = (int**)malloc(SIZE * sizeof(int*));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation failed for grid!\n");
        return 1;
    }

    for (int i = 0; i < SIZE; i++) {
        grid[i] = (int*)malloc(sizeof(int) * SIZE);
        if (grid[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for grid[%d]!\n", i);
            // 이전에 할당된 메모리 해제
            for (int j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return 1;
        }
    }

    // 초기 상태 설정
    for (int i = 0; i < SIZE; i++) {
        memset(grid[i], 0, SIZE * sizeof(int));
    }

    // 초기 데이터
    int initial_data[SIZE][SIZE] = {
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1}
    };

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = initial_data[i][j];
        }
    }

    int check;
    while (1) {
        printf("계속하려면 1, 종료하려면 2를 입력하세요:\n");
        printing(grid);

        update_grid(grid);

        scanf_s("%d", &check);
        if (check == 2)
            break;
    }

    // 메모리 해제
    for (int i = 0; i < SIZE; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}

// Grid 출력 함수
void printing(int** grid) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

// 다음 세대 계산 및 Grid 업데이트 함수
void update_grid(int** grid) {
    int** next_grid = (int**)malloc(SIZE * sizeof(int*));
    if (next_grid == NULL) {
        fprintf(stderr, "Memory allocation failed for next_grid!\n");
        exit(1);
    }
    for (int i = 0; i < SIZE; i++) {
        next_grid[i] = (int*)malloc(sizeof(int) * SIZE);
        if (next_grid[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for next_grid[%d]!\n", i);
            // 이전에 할당된 메모리 해제
            for (int j = 0; j < i; j++) {
                free(next_grid[j]);
            }
            free(next_grid);
            exit(1);
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            next_grid[i][j] = grid[i][j];  // 복사
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int neighbors = count_neighbors(grid, i, j);

            // Conway's Game of Life 규칙 적용
            if (grid[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    next_grid[i][j] = 0; // 죽음
                }
            }
            else {
                if (neighbors == 3) {
                    next_grid[i][j] = 1; // 탄생
                }
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = next_grid[i][j];  // 복사
        }
    }

    // 메모리 해제
    for (int i = 0; i < SIZE; i++) {
        free(next_grid[i]);
    }
    free(next_grid);
}

// 주변 이웃 수 계산 함수
int count_neighbors(int** grid, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // 자기 자신은 제외

            int neighbor_row = row + i;
            int neighbor_col = col + j;

            // 경계 검사: 이웃 셀이 그리드 내에 있는지 확인
            if (neighbor_row >= 0 && neighbor_row < SIZE && neighbor_col >= 0 && neighbor_col < SIZE) {
                count += grid[neighbor_row][neighbor_col];
            }
        }
    }
    return count;
}
