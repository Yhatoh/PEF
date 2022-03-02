#include "pef_vector_unif.hpp"
#include "pef_vector_opt.hpp"

#define N 1000000


int main() {
  bit_vector b(N);// = {0,0,0,1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1};
  //bit_vector b = {0,0,0,1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,1,1,1};
  //bit_vector b = {0,0,1,1,0,1,0,1,0,1,0,1,0,0};

  //bit_vector test = {0,0,1,1,0,1,0,1,0,1,0,1,0,0};
  sdsl::util::set_random_bits(b);
  //sdsl::util::set_to_value(b, 1);
  sd_vector<> sd(b);
  //sd_vector<> sd_t(test);
  rank_support_sd<1> rank_sd(&sd);    
  //rank_support_sd<1> rank_test(&sd_t);  
  //cout << rank_test(2) << "\n";  
  select_support_sd<1> select_sd(&sd); 

  uint64_t n = rank_sd(N);


  cout << "---------------- PEF UNIF TESTS ----------------\n";
  pef_vector_unif<264, rank_support_scan<1>, select_support_scan<1>> pef(b);

  cout << "# Select\n";
  bool pass_tests = 1;
  for (uint64_t i = 1; i <= n; i++) {
    if (pef.select(i) != select_sd(i)){
      pass_tests = 0;
      cout << pef.select(i) << " " << select_sd(i) << "\n";
    }
  }
  if(pass_tests) cout << "No difference!\n";

  cout << "# Rank\n";
  for (uint64_t i = 0; i <= N; i++) {
    if (pef.rank(i) != rank_sd(i)){
      pass_tests = 0;
      cout << pef.rank(i) << " " << rank_sd(i) << "\n";
    }
  }
  if(pass_tests) cout << "No difference!\n";

  cout << "---------------- PEF OPTI TESTS ----------------\n";

  pef_vector_opt<rank_support_v5<1>, select_support_mcl<1>> pef_opt(b, 0.03, 0.3);
  cout << "# Select\n";
  pass_tests = 1;
  for (uint64_t i = 1; i <= n; i++) {
    if (pef_opt.select(i) != select_sd(i)){
      pass_tests = 0;
      cout << pef_opt.select(i) << " " << select_sd(i) << "\n";
    }
  }
  if(pass_tests) cout << "No difference!\n";
  pass_tests = 1;
  cout << "# Rank\n";
  for (uint64_t i = 0; i <= N; i++) {
    if (pef.rank(i) != rank_sd(i)){
      pass_tests = 0;
      cout << pef.rank(i) << " " << rank_sd(i) << "\n";
    }
  }
  if(pass_tests) cout << "No difference!\n";
  cout << "------------------------------------------------\n";


  cout << "Size EF " << size_in_bytes(sd) << "\n";
  cout << "Size PEF UNIF " << pef.size_in_bytes() << "\n";
  cout << "Size PEF OPT " << pef_opt.size_in_bytes() << "\n";

  return 0;
}

