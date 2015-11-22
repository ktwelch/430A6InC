typedef struct numV {
  int type; // 0
  int num;
} numV;

typedef struct boolV {
  int type; // 1
  int bool;
} boolV;

typedef struct cloV {
  int type; // 2
  char params[64][64];
  void* body; // ExprC
  // environment
}

test
