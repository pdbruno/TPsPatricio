#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bgra_t
{
  uint8_t b, g, r, a;
} __attribute__((packed)) bgra_t;

extern void hide(uint32_t *imagen, uint8_t *t, int m, int n);
void hideC(uint32_t *imagen, uint8_t *t, int m, int n);

int main(void)
{
  for (int i = 0; i < 20; i++)
  {

    // Construir dos imagenes al azar
    srand((unsigned int)i);
    int n = 8 * i;
    int m = 20 * 8 - n;
    uint8_t *img = malloc(sizeof(uint8_t) * (long unsigned int)(4 * n * m));
    uint8_t *img2 = malloc(sizeof(uint8_t) * (long unsigned int)(4 * n * m));
    uint8_t *t = malloc(sizeof(uint8_t) * (long unsigned int)(n * m));
    for (int j = 0; j < m * n * 4; j++)
    {
      img[j] = (uint8_t)(rand() % 255);
      img2[j] = img[j];
    }
    for (int j = 0; j < m * n; j++)
    {
      t[j] = (uint8_t)(rand() % 255);
    }

    // Ejecutar funcion
    hide((uint32_t *)img, t, m, n);
    hideC((uint32_t *)img2, t, m, n);

    if (memcmp(img, img2, sizeof(uint8_t) * (long unsigned int)(4 * n * m)) != 0)
    {
      printf("Salame!\n");
    }
    // Borrar imagenes
    free(img);
    free(img2);
    free(t);
  }

  return 0;
}

void hideC(uint32_t *imagen, uint8_t *t, int m, int n)
{
  bgra_t(*src) = (bgra_t(*))imagen;

  for (int i = 0; i < m * n; i++)
  {
    src[i].b = (uint8_t)((src[i].b & 0xF8) | (t[i] >> 5));
    src[i].g = (uint8_t)((src[i].g & 0xFC) | ((t[i] & 0x18) >> 3));
    src[i].r = (uint8_t)((src[i].r & 0xF8) | (t[i] & 0x7));
  }
}