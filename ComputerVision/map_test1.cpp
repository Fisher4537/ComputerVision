#include <string>
#include <map>
#include <iostream>

std::string decomp(int n) {
  if (n < 2) return "1";

  std::string out;
  std::map<int,int> factors = {{2,0}};
  for (int i = 2; i <= n; i++) {
    int j = i;
    std::cout << "i = " << i << std::endl;
    
    //get primes scomposition of current factor
    for (std::map<int,int>::iterator it = factors.begin(); it != factors.end();) {
      std::cout << "j = " << j << " it = " << it->first << " -> " << it->second << std::endl;
      if (j%it->first == 0) {
        j = j/(it->first);
        (it->second)++;
      } else {
        ++it;
      }
    }
    if (j != 1) {
      factors[j] = 1;
    }
    std::cout << "j = " << j << std::endl;
  }
  
  for (std::map<int,int>::iterator it = factors.begin(); it != factors.end(); ++it) {
    out += std::to_string(it->first) + ((it->second) > 1 ? "^" + std::to_string(it->second) : "") + " * ";
    std::cout << "it = " << it->first << " => " << it->second << std::endl;
  }
  if (out.size() > 2) {
    out.resize(out.size() - 3);
  } 
  return out;
}

int main(int argc, char* argv[]) {
  std::cout << "start " << atoi(argv[1]) << std::endl;
  std::string out = decomp(atoi(argv[1]));
  std::cout << "end " << out << std::endl;
  return 0;
}