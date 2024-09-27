#ifndef TOOLS_H
#define TOOLS_H

void normalize(float* v);
void cross_product(float* a, float* b, float* result);
void normal_vectors(float* a, float* b, float* c, float* result);
void subdivide(float v1[3], float v2[3], float v3[3], int depth);


#endif