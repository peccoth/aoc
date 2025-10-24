#include <iostream>
#define RESET progress = 0; l = 0; r = 0;

int main() {
  char c;
  const std::string templ = "mul(";
  const std::string g_templ1 = "don't()";
  const std::string g_templ2 = "do()";
  unsigned long l = 0, r = 0, silver = 0, gold = 0; 
  short dis_progress = 0, en_progress = 0, progress = 0;
  bool status = 1;
  while (std::cin.get(c)) {
    if (dis_progress == g_templ1.length())
      status = 0;
    if (en_progress == g_templ2.length())
      status = 1;

    switch (progress) {
      case 5:
        if (std::isdigit(c) && r < 1000) {
          r = r * 10 + (c - '0'); 
        } else if (c == ')') {
          silver += l * r;
          gold += l * r * status;
          RESET
        } else {
          RESET
        }
      break;

      case 4:
        if (progress == 4) {
          if (std::isdigit(c) && l < 1000) {
            l = l * 10 + (c - '0'); 
          } else if (c == ',') {
            progress ++;
          } else {
            RESET
          }
        }
        break;

      default:
        if (c == templ[progress]) {
          progress++;
        } else {
          RESET
        }
    }

    if (c == g_templ1[dis_progress]) {
      dis_progress++;
    } else {
      dis_progress = 0;
    }

    if (c == g_templ2[en_progress]) {
      en_progress++;
    } else {
      en_progress = 0;
    }
  }
  std::cout<<"Silver: "<<silver<<std::endl<<"Gold: "<<gold<<std::endl;
}
