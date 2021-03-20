#include "lib.h"

extern int docSimilar(document_t *a, document_t *b, uint8_t *bitmap);
int docSimilarC(document_t *a, document_t *b, uint8_t *bitmap);

int main(void)
{
  // Documento A
  int dataI1 = 1000;
  float dataF1 = (float)0.69;
  char *dataS1 = "hola";
  document_t *docuA =
      docNew(3, TypeInt, &(dataI1), TypeString, dataS1, TypeFloat, &(dataF1));

  // Documento B
  int dataI2 = 1000;
  float dataF2 = (float)0.69;
  char *dataS2 = "hola";
  document_t *docuB =
      docNew(3, TypeInt, &(dataI2), TypeString, dataS2, TypeFloat, &(dataF2));

  for (uint8_t i = 0; i < 8; i++)
  {
    // bitmap
    uint8_t bitmap = i;

    // Ejecutar funcion
    int result = docSimilar(docuA, docuB, &bitmap);
    int resultC = docSimilarC(docuA, docuB, &bitmap);

    if (result != resultC)
    {
      printf("no haces una bien eh\n");
      printf("bitmap: %x\n", bitmap);
      printf("resultASM: %i\n", result);
      printf("resultC: %i\n", resultC);
    }
  }

  // Borrar documentos creados
  docDelete(docuA);
  docDelete(docuB);

  return 0;
}
int docSimilarC(document_t *a, document_t *b, uint8_t *bitmap)
{

  uint8_t localbitMap = *bitmap;
  // Sort by size
  if (a->count < b->count)
    return 1;
  if (a->count > b->count)
    return -1;
  // Sort by type
  for (int i = 0; i < a->count; i++)
  {
    if (a->values[i].type < b->values[i].type)
      return 1;
    if (a->values[i].type > b->values[i].type)
      return -1;
  }
  // Sort by data
  for (int i = 0; i < a->count; i++)
  {
    if (localbitMap % 2 == 1)
    {
      funcCmp_t *fc = getCompareFunction(a->values[i].type);
      int cmp = fc(a->values[i].data, b->values[i].data);
      if (cmp != 0)
        return cmp;
    }
    localbitMap = localbitMap >> 1;
  }
  // Are equal
  return 0;
}