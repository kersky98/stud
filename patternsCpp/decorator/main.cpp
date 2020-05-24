#include "decorator.h"
#include <vector>
#include <memory>
#include <typeinfo>
#include <string>
using namespace std;

int main()
{
  cout << "Presentation of the DECORATOR pattern!" << std::endl;

  cout << "-----Target channel-----:" << endl;
  IBaseSignal* baseTarget = new Signal();
  baseTarget = new Fdn(baseTarget);
  baseTarget = new Sa(baseTarget);
  baseTarget = new Plo(baseTarget);
  baseTarget = new Tzk(baseTarget);
  cout << baseTarget->GetDescription() << ". data: " << baseTarget->Calculate() << endl;

  cout << "-----Noise channel-----:" << endl;
  IBaseSignal* baseNoise = new Signal();
  baseNoise = new Fdn(baseNoise);
  // без спектральной обработки для пеленгации помех
  baseNoise = new Plo(baseNoise);
  baseNoise = new Tzk(baseNoise);
  cout << baseNoise->GetDescription() << ". data: " << baseNoise->Calculate() << endl;

  cout << endl << "-----Destroy objects-----:" << endl;
  delete baseTarget;
  delete baseNoise;
  return 0;
}
