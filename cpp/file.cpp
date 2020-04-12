#include <stdio.h>

#include <iostream>

int main(void) {
  FILE* pFile;
  pFile = fopen("myfile.txt", "w");
  if (pFile != NULL) {
    fputs("1", pFile);
    fclose(pFile);
  }

  pFile = fopen("myfile.txt", "r");
  if (pFile != NULL) {
    bool a = static_cast<bool>(fgetc(pFile) - '0');
    std::cout << a << std::endl;
    fclose(pFile);
  }

  // static_cast<>();
  // reinterpret_cast<>();
  // const_cast<>();
  // dynamic_cast<>();

  return 0;
}
