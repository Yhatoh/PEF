#include "pef_vector_unif.hpp"
#include "pef_vector_opt.hpp"

#define N 196433254820

int main() {
  std::vector<uint64_t> pb;
  uint64_t pos;
  while(cin >> pos){
    pb.push_back(pos);
  }

  pef_vector_unif<1024, rank_support_v5<1>, select_support_mcl<1>> pef_unif(pb, N);
  cout << "Size PEF UNIF BIT VECTOR " << pef_unif.size_in_bytes() << "\n";
  
  return 0;
}