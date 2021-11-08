#include "pef_vector_unif.hpp"

#define N 100000000


int main() {
  bit_vector b(N);// = {0,0,0,1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1};
  //bit_vector b = {0,0,0,1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,1,1,1};
  //bit_vector b = {0,0,1,1,0,1,0,1,0,1,0,1,0,0,0,1,1,0,1,1,1,1};
  sdsl::util::set_random_bits(b);

  pef_vector_unif<1024> pef(b);
  sd_vector<> sd(b);

  rank_support_sd<1> rank_sd(&sd);    
  select_support_sd<1> select_sd(&sd);

  uint64_t n = rank_sd(N);

  for (uint64_t i = 1; i <= n; i++) {
    if (pef.rank(i) != rank_sd(i))
      cout << pef.select(i) << " " << select_sd(i) << endl;
  }

  for (uint64_t i = 1; i <= N; i++) {
    if (pef.rank(i) != rank_sd(i))
      cout << pef.rank(i) << " " << rank_sd(i) << endl;
  }

  cout << "Size EF " << size_in_bytes(sd) << endl;
  cout << "Size PEF " << pef.size_in_bytes() << endl;
  return 0;
}

