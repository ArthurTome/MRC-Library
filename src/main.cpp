#include <iostream>
#include "MRC.hpp"

int main(int argc, char *argv[])
{
  SoC <double, 10>  channel;
  channel.Calc_EMEDS(97, 1);
  channel.Calc_SoC();
  //channel.Get();

  return 0;
}