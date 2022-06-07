#include "pef_vector_unif.hpp"
#include "pef_vector_opt.hpp"
#include "pef_vector_opt_vigna.hpp"

//#define BITS 20000000
//#define N 196433254820

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
      //readed++;
      //if(readed >= BITS) break;
    }
    rf.close();
    
    sdsl::sd_vector<> sd(pb.begin(), pb.end());
    sdsl::rank_support_sd<1> rank_sd(&sd);
    sdsl::select_support_sd<1> select_sd(&sd);
    cout << "SIZE SD VECTOR " 
         << (double) (sdsl::size_in_bytes(sd) + sdsl::size_in_bytes(rank_sd) + sdsl::size_in_bytes(select_sd)) * 8 / pb.size()
         << "\n";
    ofstream file_pef_opt("SD.bin", std::ios::out | ios::binary );
    file_pef_opt.write((char*) &sd, sizeof(sdsl::sd_vector<>));
    file_pef_opt.write((char*) &rank_sd, sizeof(sdsl::rank_support_v<1>));
    file_pef_opt.write((char*) &select_sd, sizeof(sdsl::select_support_sd<1>));
    file_pef_opt.close();

    pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 64> pef_opt(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT " << pef_opt.size_in_bits_formula() << " " << ((double)pef_opt.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt("PEF_OPT.SD.RANK_V_SELECT_MCL_64.bin", std::ios::out | ios::binary );
    file_pef_opt.write((char*) &pef_opt, sizeof(pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt.close();
    
    pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 128> pef_opt2(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT " << pef_opt2.size_in_bits_formula() << " " << ((double)pef_opt2.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt2("PEF_OPT.SD.RANK_V_SELECT_MCL_128.bin", std::ios::out | ios::binary );
    file_pef_opt2.write((char*) &pef_opt2, sizeof(pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt2.close();
    
    pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 256> pef_opt3(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT " << pef_opt3.size_in_bits_formula() << " " << ((double)pef_opt3.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt3("PEF_OPT.SD.RANK_V_SELECT_MCL_256.bin", std::ios::out | ios::binary );
    file_pef_opt3.write((char*) &pef_opt3, sizeof(pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt3.close();
    
    pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 512> pef_opt4(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT " << pef_opt4.size_in_bits_formula() << " " << ((double)pef_opt4.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt4("PEF_OPT.SD.RANK_V_SELECT_MCL_512.bin", std::ios::out | ios::binary );
    file_pef_opt4.write((char*) &pef_opt4, sizeof(pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt4.close();
    

    pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 1024> pef_opt5(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT " << pef_opt5.size_in_bits_formula() << " " << ((double)pef_opt5.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt5("PEF_OPT.SD.RANK_V_SELECT_MCL_1024.bin", std::ios::out | ios::binary );
    file_pef_opt5.write((char*) &pef_opt5, sizeof(pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt5.close();
    
    pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 2048> pef_opt6(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT " << pef_opt6.size_in_bits_formula() << " " << ((double)pef_opt6.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt6("PEF_OPT.SD.RANK_V_SELECT_MCL_2048.bin", std::ios::out | ios::binary );
    file_pef_opt6.write((char*) &pef_opt6, sizeof(pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt6.close();
    
    pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 64> pef_opt_vigna(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT VIGNA " << pef_opt_vigna.size_in_bits_formula() << " " << ((double)pef_opt_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt_vigna1("PEF_OPT.VIGNA.RANK_V_SELECT_MCL_64.bin", std::ios::out | ios::binary );
    file_pef_opt_vigna1.write((char*) &pef_opt_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt_vigna1.close();

    pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 128> pef_opt2_vigna(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT VIGNA " << pef_opt2_vigna.size_in_bits_formula() << " " << ((double)pef_opt2_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt_vigna2("PEF_OPT.VIGNA.RANK_V_SELECT_MCL_128.bin", std::ios::out | ios::binary );
    file_pef_opt_vigna2.write((char*) &pef_opt2_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt_vigna2.close();
    
    pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 256> pef_opt3_vigna(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT VIGNA " << pef_opt3_vigna.size_in_bits_formula() << " " << ((double)pef_opt3_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt_vigna3("PEF_OPT.VIGNA.RANK_V_SELECT_MCL_256.bin", std::ios::out | ios::binary );
    file_pef_opt_vigna3.write((char*) &pef_opt3_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt_vigna3.close();   

    pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 512> pef_opt4_vigna(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT VIGNA " << pef_opt4_vigna.size_in_bits_formula() << " " << ((double)pef_opt4_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt_vigna4("PEF_OPT.VIGNA.RANK_V_SELECT_MCL_512.bin", std::ios::out | ios::binary );
    file_pef_opt_vigna4.write((char*) &pef_opt4_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt_vigna4.close();   

    pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 1024> pef_opt5_vigna(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT VIGNA " << pef_opt5_vigna.size_in_bits_formula() << " " << ((double)pef_opt5_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt_vigna5("PEF_OPT.VIGNA.RANK_V_SELECT_MCL_1024.bin", std::ios::out | ios::binary );
    file_pef_opt_vigna5.write((char*) &pef_opt5_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt_vigna5.close();   

    pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 2048> pef_opt6_vigna(pb, universe, 0.03, 0.3);
    cout << "SIZE PEF_OPT VIGNA " << pef_opt6_vigna.size_in_bits_formula() << " " << ((double)pef_opt6_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
    ofstream file_pef_opt_vigna6("PEF_OPT.VIGNA.RANK_V_SELECT_MCL_2048.bin", std::ios::out | ios::binary );
    file_pef_opt_vigna6.write((char*) &pef_opt6_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>));
    file_pef_opt_vigna6.close();

  }
  return 0;
}
