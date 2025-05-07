#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 332  // Frame height for QCIF format
#define M 498  // Frame width for QCIF format
#define INPUT_FILE "cat_498x332_444.yuv"
#define OUTPUT_FILE "cat_yuv_output.yuv"

int current_y[N][M];
int current_u[N][M];
int current_v[N][M];
double current_r[N][M];
double current_g[N][M];
double current_b[N][M];
double current_gray[N][M];

void read_yuv_frame() {
    FILE *frame = fopen(INPUT_FILE, "rb");
    if (frame == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            current_y[i][j] = fgetc(frame);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            current_u[i][j] = fgetc(frame);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            current_v[i][j] = fgetc(frame);

    fclose(frame);
}

void write_grayscale_frame() {
    FILE *frame = fopen(OUTPUT_FILE, "wb");
    if (frame == NULL) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            fputc((int)current_gray[i][j], frame);

    fclose(frame);
}

void convert_to_rgb() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            current_r[i][j] = current_y[i][j] + 1.140 * current_v[i][j];
            current_g[i][j] = current_y[i][j] - 0.395 * current_u[i][j] - 0.581 * current_v[i][j];
            current_b[i][j] = current_y[i][j] + 2.032 * current_u[i][j];
        }
}

void convert_to_grayscale() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            current_gray[i][j] = (current_r[i][j] + current_g[i][j] + current_b[i][j]) / 3;
}

int main() {
    read_yuv_frame();
    convert_to_rgb();
    convert_to_grayscale();

    // Optional: Print grayscale values
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            printf("%.2f ", current_gray[i][j]);
        printf("\n");
    }

    write_grayscale_frame();
    return 0;
}
