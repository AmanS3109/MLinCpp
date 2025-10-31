#ifndef NN_H_
#define NN_H_ 

//idea to cummulate
// float d[] = {0, 1, 0, 1};
// Mat m = { .rows = 1, .cols = 4, .es = d};

//float d[] = {
//  0, 0, 1,
//  0, 1, 1,
//  1, 0, 1,
//  1, 1, 1,
//};
//Mat input = { .rows = 4, .cols = 2, stride = 3, .es = &d[0]};
//Mat ouput = { .rows = 4, .cols = 1, stride = 3, .es = &d[3]};

typedef struct {
	size_t rows;
	size_t cols;
	float *es;
} Mat;   

Mat mat_alloc(size_t rows, size_t cols);
void mat_dot(Mat c, Mat a, Mat b);
void Mat mat_sum();

#endif //NN_H
      

#ifdef NN_IMPLEMENTATION



#endif   // NN_IMPLEMENTATION
