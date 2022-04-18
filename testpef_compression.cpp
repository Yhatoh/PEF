#include "pef_vector_unif.hpp"
#include "pef_vector_opt.hpp"
#include "pef_vector_opt_vigna.hpp"

#define BITS 80000000
#define N 196433254820

int main(int argc, char** argv){
  vector< uint64_t > pb;
  // argv will contain all the test files
  // need to be with the format `universe filepath` 
  for(uint64_t i = 1; i < argc; i += 2){
    uint64_t universe = strtoull(argv[i], NULL, 0);
    char* filepath = argv[i + 1];
    cout << universe << " " << filepath << "\n";
    
    ifstream rf(filepath, std::ios::binary);
    if(!rf) {
      std::cout << "Cannot open file! " << filepath << "\n";
      continue;
    }

    uint64_t pos_one;
    uint64_t readed = 0;
    while(!rf.eof()){
      rf.read((char*) &pos_one, sizeof(uint64_t));
      pb.push_back(pos_one);
      readed++;
      if(readed >= BITS) break;
    }
    rf.close();
    /*
    sdsl::sd_vector<> sd(pb.begin(), pb.end());
    cout << "SIZE SD_VECTOR " << ((double)sdsl::size_in_bytes(sd) * 8) / ((double) pb.size()) << "\n";
 
    pef_vector_unif<4096, sdsl::rank_support_v5<1>, sdsl::select_support_mcl<1>> pef_unif(pb, pb[pb.size() - 1] + 1);
    cout << "SIZE PEF_UNIF " << ((double)pef_unif.size_in_bytes() * 8) / ((double) pb.size()) << "\n"; 
    
    pef_vector_opt<sdsl::rank_support_v5<1>, sdsl::select_support_mcl<1>, 1, 1, 4096> pef_opt(pb, pb[pb.size() - 1] + 1, 0.03, 0.3);
    cout << "SIZE PEF_OPT " << ((double)pef_opt.size_in_bytes() * 8) / ((double) pb.size()) << "\n";  
    */
    pef_vector_opt_vigna<sdsl::rank_support_v5<1>, sdsl::select_support_mcl<1>, 1, 1024> pef_opt_vigna(pb, pb[pb.size() - 1] + 1, 0.03, 0.3);
    cout << "SIZE PEF_OPT_VIGNA " << ((double)pef_opt_vigna.size_in_bytes() * 8) / ((double) pb.size()) << "\n";  


  }
  return 0;
}
