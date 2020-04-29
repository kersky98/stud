#include <iostream>
#include "strategy.h"

int main()
{
  std::cout << "Presentation of the STRATEGY pattern!" << std::endl;

  Ya400 ya400;
  ya400.Display();
  ya400.PerformWrite();
  ya400.PerformRead();
  ya400.CommonFunction();

  Write2Ethernet write2Ethernet;
  ReadFromEthernet readFromEthernet;
  ya400.SetWriteBehavior(&write2Ethernet);
  ya400.SetReadBehavior(&readFromEthernet);
  ya400.PerformWrite();
  ya400.PerformRead();

  B420 b420;
  b420.Display();
  b420.PerformWrite();
  b420.PerformRead();
  b420.CommonFunction();

  return 0;
}