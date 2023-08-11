//#include "pef_vector_unif.hpp"
#include "zombit/include/zombit_vector.hpp"
#include "zombit/include/oz_vector.hpp"
#include "pef_vector_opt.hpp"
#include "pef_vector_opt_vigna.hpp"
#include "s18_vector/s18/head/s18_vector.hpp"
#include "randomer.hpp"

#include <vector>
#include <sdsl/vectors.hpp>
#include <sdsl/bit_vectors.hpp>
#include <chrono>
#include <cinttypes>
#include <assert.h> 

using namespace std;


#define BITS 20000
//#define n_queries 1000000
#define n_queries 1000000
#define U 196433254820
#define N 5055078462
//#define U 453314051 
//#define N 20000000
//#define U 106099
//#define N 20000

int main(int argc, char** argv){
  // argv will contain all the test files
  // need to be with the format `universe filepath` 
  for(uint64_t i = 1; i < argc; i += 2){

    double total_time_span_hyb = 0;
    double total_time_span_oz = 0;
    double total_time_span_zombit = 0;
    double total_time_span_sd = 0;
    double total_time_span_s18_8 = 0;
    double total_time_span_s18_16 = 0;
    double total_time_span_s18_32 = 0;
    double total_time_span_s18_64 = 0;
    double total_time_span_s18_128 = 0;
    double total_time_span_s18_256 = 0;
    double total_time_span_rrr_15 = 0;
    double total_time_span_rrr_31 = 0;
    double total_time_span_rrr_63 = 0;
    double total_time_span_rrr_127 = 0;
    double total_time_span_pef_sd_64 = 0;
    double total_time_span_pef_sd_128 = 0;
    double total_time_span_pef_sd_256 = 0;
    double total_time_span_pef_sd_512 = 0;
    double total_time_span_pef_sd_1024 = 0;
    double total_time_span_pef_sd_2048 = 0;
    double total_time_span_pef_vigna_64 = 0;
    double total_time_span_pef_vigna_128 = 0;
    double total_time_span_pef_vigna_256 = 0;
    double total_time_span_pef_vigna_512 = 0;
    double total_time_span_pef_vigna_1024 = 0;
    double total_time_span_pef_vigna_2048 = 0;
     
    double total_time_span_hyb_s = 0;
    double total_time_span_zombit_s = 0;
    double total_time_span_oz_s = 0;
    double total_time_span_sd_s = 0;
    double total_time_span_s18_8_s = 0;
    double total_time_span_s18_16_s = 0;
    double total_time_span_s18_32_s = 0;
    double total_time_span_s18_64_s = 0;
    double total_time_span_s18_128_s = 0;
    double total_time_span_s18_256_s = 0;
    double total_time_span_rrr_15_s = 0;
    double total_time_span_rrr_31_s = 0;
    double total_time_span_rrr_63_s = 0;
    double total_time_span_rrr_127_s = 0;
    double total_time_span_pef_sd_64_s = 0;
    double total_time_span_pef_sd_128_s = 0;
    double total_time_span_pef_sd_256_s = 0;
    double total_time_span_pef_sd_512_s = 0;
    double total_time_span_pef_sd_1024_s = 0;
    double total_time_span_pef_sd_2048_s = 0;
    double total_time_span_pef_vigna_64_s = 0;
    double total_time_span_pef_vigna_128_s = 0;
    double total_time_span_pef_vigna_256_s = 0;
    double total_time_span_pef_vigna_512_s = 0;
    double total_time_span_pef_vigna_1024_s = 0;
    double total_time_span_pef_vigna_2048_s = 0;

    double total_size_hyb = 0;
    double total_size_zombit = 0;
    double total_size_oz = 0;
    double total_size_sd = 0;
    double total_size_s18_8 = 0;
    double total_size_s18_16 = 0;
    double total_size_s18_32 = 0;
    double total_size_s18_64 = 0;
    double total_size_s18_128 = 0;
    double total_size_s18_256 = 0;
    double total_size_rrr_15 = 0;
    double total_size_rrr_31 = 0;
    double total_size_rrr_63 = 0;
    double total_size_rrr_127 = 0;
    double total_size_pef_sd_64 = 0;
    double total_size_pef_sd_128 = 0;
    double total_size_pef_sd_256 = 0;
    double total_size_pef_sd_512 = 0;
    double total_size_pef_sd_1024 = 0;
    double total_size_pef_sd_2048 = 0;
    double total_size_pef_vigna_64 = 0;
    double total_size_pef_vigna_128 = 0;
    double total_size_pef_vigna_256 = 0;
    double total_size_pef_vigna_512 = 0;
    double total_size_pef_vigna_1024 = 0;
    double total_size_pef_vigna_2048 = 0;
    
    double total_size_hyb_1 = 0;
    double total_size_zombit_1 = 0;
    double total_size_oz_1 = 0;
    double total_size_sd_1 = 0;
    double total_size_s18_8_1 = 0;
    double total_size_s18_16_1 = 0;
    double total_size_s18_32_1 = 0;
    double total_size_s18_64_1 = 0;
    double total_size_s18_128_1 = 0;
    double total_size_s18_256_1 = 0;
    double total_size_rrr_15_1 = 0;
    double total_size_rrr_31_1 = 0;
    double total_size_rrr_63_1 = 0;
    double total_size_rrr_127_1 = 0;
    double total_size_pef_sd_64_1 = 0;
    double total_size_pef_sd_128_1 = 0;
    double total_size_pef_sd_256_1 = 0;
    double total_size_pef_sd_512_1 = 0;
    double total_size_pef_sd_1024_1 = 0;
    double total_size_pef_sd_2048_1 = 0;
    double total_size_pef_vigna_64_1 = 0;
    double total_size_pef_vigna_128_1 = 0;
    double total_size_pef_vigna_256_1 = 0;
    double total_size_pef_vigna_512_1 = 0;
    double total_size_pef_vigna_1024_1 = 0;
    double total_size_pef_vigna_2048_1 = 0;
    
    double total_size_hyb_bit = 0;
    double total_size_zombit_bit = 0;
    double total_size_oz_bit = 0;
    double total_size_sd_bit = 0;
    double total_size_s18_8_bit = 0;
    double total_size_s18_16_bit = 0;
    double total_size_s18_32_bit = 0;
    double total_size_s18_64_bit = 0;
    double total_size_s18_128_bit = 0;
    double total_size_s18_256_bit = 0;
    double total_size_rrr_15_bit = 0;
    double total_size_rrr_31_bit = 0;
    double total_size_rrr_63_bit = 0;
    double total_size_rrr_127_bit = 0;
    double total_size_pef_sd_64_bit = 0;
    double total_size_pef_sd_128_bit = 0;
    double total_size_pef_sd_256_bit = 0;
    double total_size_pef_sd_512_bit = 0;
    double total_size_pef_sd_1024_bit = 0;
    double total_size_pef_sd_2048_bit = 0;
    double total_size_pef_vigna_64_bit = 0;
    double total_size_pef_vigna_128_bit = 0;
    double total_size_pef_vigna_256_bit = 0;
    double total_size_pef_vigna_512_bit = 0;
    double total_size_pef_vigna_1024_bit = 0;
    double total_size_pef_vigna_2048_bit = 0;

    uint64_t universe = strtoull(argv[i], NULL, 0);
    char* filepath = argv[i + 1];
    
    ifstream rf(filepath, std::ios::binary);
    if(!rf) {
      std::cout << "Cannot open file! " << filepath << "\n";
      continue;
    }

    uint64_t amount_bv;
    rf.read((char*) &amount_bv, sizeof(uint64_t));
    cout << filepath << " " << amount_bv << "\n";
    rf.read((char*) &universe, sizeof(uint64_t));
    sdsl::bit_vector bv(universe, 0);
    for(uint64_t i_bv = 0; i_bv < amount_bv; i_bv++) {
      vector< uint64_t > pb;
      for(uint64_t auxii = 0; auxii < universe; auxii++) bv[auxii] = 0;
      uint64_t pos_one = 0;
      uint64_t readed = 0;
      
      while(pos_one != universe){
        rf.read((char*) &pos_one, sizeof(uint64_t));
        if(pos_one == universe) {
          break;
        }
        pb.push_back(pos_one);
        if(rf.eof()) break;
        //readed++;
        //if(readed >= BITS) break;
      }

      if(pb.size() == 1) {
        amount_bv--;
        i_bv--;
        continue;
      }
      //universe = pb[pb.size() - 1] + 1;
      //cout << universe << " " << pb.size() << "\n";
      for(uint64_t auxii = 0; auxii < pb.size() ; auxii++) bv[pb[auxii]] = 1;

      Randomer r_randomer{0, universe - 1, 1024};
      Randomer s_randomer{1, pb.size(), 1024};

      vector< uint64_t > vrank;
      vector< uint64_t > vselect;

      for(uint64_t q = 0; q < n_queries; q++){
        vrank.push_back(r_randomer());
        vselect.push_back(s_randomer());
      }
      {
        runs_vectors::oz_vector oz(bv);
        runs_vectors::rank_support_oz<1> rank_oz(&oz);
        runs_vectors::select_support_oz<1> select_oz(&oz);
        //cout << "SIZE HYB VECTOR " 
        //     << (double) (sdsl::size_in_bytes(hyb) + sdsl::size_in_bytes(rank_hyb)) * 8 / pb.size() << " "
        //     << sdsl::size_in_bytes(hyb) << " " << (double) sdsl::size_in_bytes(hyb) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_hyb) << " " << (double) sdsl::size_in_bytes(rank_hyb) / pb.size() << " " 
        //    << "\n";
        total_size_oz_1 += (double) (sdsl::size_in_bytes(oz) + sdsl::size_in_bytes(select_oz) + sdsl::size_in_bytes(rank_oz)) * 8 / pb.size();
        total_size_oz_bit += (double) (sdsl::size_in_bytes(oz) + sdsl::size_in_bytes(select_oz) + sdsl::size_in_bytes(rank_oz)) * 8 / universe;
        total_size_oz += (double) (sdsl::size_in_bytes(oz) + sdsl::size_in_bytes(select_oz) + sdsl::size_in_bytes(rank_oz)) * 8;
        //ofstream file_pef_hyb("/data/PEF_TESTED_ED/HYB.bin", std::ios::out | ios::binary );
        //hyb.serialize(file_pef_hyb);
        //file_pef_hyb.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_oz(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "HYB VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_oz += total_time;
        
        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_oz(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "SD VECTOR SELECT: " << Q_s << " " << total_time_s  << " " << total_time_s << "\n";
        total_time_span_oz_s += total_time_s;
      }
      /*
      {
        runs_vectors::zombit_vector zombit(bv);
        runs_vectors::rank_support_zombit<1> rank_zombit(&zombit);
        //cout << "SIZE HYB VECTOR " 
        //     << (double) (sdsl::size_in_bytes(hyb) + sdsl::size_in_bytes(rank_hyb)) * 8 / pb.size() << " "
        //     << sdsl::size_in_bytes(hyb) << " " << (double) sdsl::size_in_bytes(hyb) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_hyb) << " " << (double) sdsl::size_in_bytes(rank_hyb) / pb.size() << " " 
        //    << "\n";
        total_size_zombit_1 += (double) (sdsl::size_in_bytes(zombit) + sdsl::size_in_bytes(rank_zombit)) * 8 / pb.size();
        total_size_zombit_bit += (double) (sdsl::size_in_bytes(zombit) + sdsl::size_in_bytes(rank_zombit)) * 8 / universe;
        total_size_zombit += (double) (sdsl::size_in_bytes(zombit) + sdsl::size_in_bytes(rank_zombit)) * 8;
        //ofstream file_pef_hyb("/data/PEF_TESTED_ED/HYB.bin", std::ios::out | ios::binary );
        //hyb.serialize(file_pef_hyb);
        //file_pef_hyb.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_zombit(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "HYB VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_zombit += total_time;

      }
      */
      /*
      {
        sdsl::hyb_vector<> hyb(bv);
        sdsl::rank_support_hyb<1> rank_hyb(&hyb);
        //cout << "SIZE HYB VECTOR " 
        //     << (double) (sdsl::size_in_bytes(hyb) + sdsl::size_in_bytes(rank_hyb)) * 8 / pb.size() << " "
        //     << sdsl::size_in_bytes(hyb) << " " << (double) sdsl::size_in_bytes(hyb) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_hyb) << " " << (double) sdsl::size_in_bytes(rank_hyb) / pb.size() << " " 
        //    << "\n";
        total_size_hyb_1 += (double) (sdsl::size_in_bytes(hyb) + sdsl::size_in_bytes(rank_hyb)) * 8 / pb.size();
        total_size_hyb_bit += (double) (sdsl::size_in_bytes(hyb) + sdsl::size_in_bytes(rank_hyb)) * 8 / universe;
        total_size_hyb += (double) (sdsl::size_in_bytes(hyb) + sdsl::size_in_bytes(rank_hyb)) * 8;
        //ofstream file_pef_hyb("/data/PEF_TESTED_ED/HYB.bin", std::ios::out | ios::binary );
        //hyb.serialize(file_pef_hyb);
        //file_pef_hyb.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_hyb(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "HYB VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_hyb += total_time;
      }
      {
        sdsl::sd_vector<> sd(bv);
        sdsl::rank_support_sd<1> rank_sd(&sd);
        sdsl::select_support_sd<1> select_sd(&sd);
        //cout << "SIZE SD VECTOR " 
        //     << (double) (sdsl::size_in_bytes(sd) + sdsl::size_in_bytes(rank_sd) + sdsl::size_in_bytes(select_sd)) * 8 / pb.size() << " "
        //     << sdsl::size_in_bytes(sd) << " " << (double) sdsl::size_in_bytes(sd) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_sd) << " " << (double) sdsl::size_in_bytes(rank_sd) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_sd) << " " << (double) sdsl::size_in_bytes(select_sd) / pb.size() << " " 
        //     << "\n";
        total_size_sd_1 += (double) (sdsl::size_in_bytes(sd) + sdsl::size_in_bytes(rank_sd)) * 8 / pb.size();
        total_size_sd_bit += (double) (sdsl::size_in_bytes(sd) + sdsl::size_in_bytes(rank_sd)) * 8 / universe;
        total_size_sd += (double) (sdsl::size_in_bytes(sd) + sdsl::size_in_bytes(rank_sd)) * 8;
        //ofstream file_pef_sd("/data/PEF_TESTED_ED/SD.bin", std::ios::out | ios::binary );
        //sd.serialize(file_pef_sd);
        //file_pef_sd.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_sd(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "SD VECTOR RANK: " << Q << " " << total_time << " " << total_time << "\n";
        total_time_span_sd += total_time;
      
        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_sd(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "SD VECTOR SELECT: " << Q_s << " " << total_time_s  << " " << total_time_s << "\n";
        total_time_span_sd_s += total_time_s;
      }
      {
        sdsl::s18::vector<8> s18b_8(bv);     
        sdsl::s18::rank_support<1, 8> rank_s18b_8(s18b_8);     
        sdsl::s18::select_support<1, 8> select_s18b_8(s18b_8);
        
        //cout << "SIZE S18 VECTOR " 
        //     << (double) (sdsl::size_in_bytes(s18b_8)) * 8 / pb.size() << "\n";
             //<< sdsl::size_in_bytes(s18b_16) << " " << (double) sdsl::size_in_bytes(s18b_16) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_s18b_16) << " " << (double) sdsl::size_in_bytes(rank_s18b_16) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_s18b_16) << " " << (double) sdsl::size_in_bytes(select_s18b_16) / pb.size() << " " 
        //     << "\n";
        total_size_s18_8_1 += (double) (sdsl::size_in_bytes(s18b_8)) * 8 / pb.size();
        total_size_s18_8_bit += (double) (sdsl::size_in_bytes(s18b_8)) * 8 / universe;
        total_size_s18_8 += (double) (sdsl::size_in_bytes(s18b_8)) * 8;
        //ofstream file_pef_sd("/data/PEF_TESTED_ED/S18B_8.bin", std::ios::out | ios::binary );
        //s18b_8.serialize(file_pef_sd);
        //file_pef_sd.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_s18b_8(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "S18 8 VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_s18_8 += total_time;
      
        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_s18b_8(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "S18 8 VECTOR SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_s18_8_s += total_time_s;
      }
      {
        sdsl::s18::vector<16> s18b_16(bv);     
        sdsl::s18::rank_support<1, 16> rank_s18b_16(s18b_16);     
        sdsl::s18::select_support<1, 16> select_s18b_16(s18b_16);
        
        //cout << "SIZE S18 VECTOR " 
        //     << (double) (sdsl::size_in_bytes(s18b_16)) * 8 / pb.size() << "\n";
             //<< sdsl::size_in_bytes(s18b_16) << " " << (double) sdsl::size_in_bytes(s18b_16) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_s18b_16) << " " << (double) sdsl::size_in_bytes(rank_s18b_16) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_s18b_16) << " " << (double) sdsl::size_in_bytes(select_s18b_16) / pb.size() << " " 
        //     << "\n";
        total_size_s18_16_1 += (double) (sdsl::size_in_bytes(s18b_16)) * 8 / pb.size();
        total_size_s18_16_bit += (double) (sdsl::size_in_bytes(s18b_16)) * 8 / universe;
        total_size_s18_16 += (double) (sdsl::size_in_bytes(s18b_16)) * 8;
        //ofstream file_pef_sd("/data/PEF_TESTED_ED/S18B_16.bin", std::ios::out | ios::binary );
        //s18b_16.serialize(file_pef_sd);
        //file_pef_sd.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_s18b_16(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "S18 16 VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_s18_16 += total_time;
      
        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_s18b_16(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "S18 16 VECTOR SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_s18_16_s += total_time_s;
      }
      {
        sdsl::s18::vector<32> s18b_32(bv);     
        sdsl::s18::rank_support<1, 32> rank_s18b_32(s18b_32);     
        sdsl::s18::select_support<1, 32> select_s18b_32(s18b_32);
        
        //cout << "SIZE S18 32 VECTOR " 
        //     << (double) (sdsl::size_in_bytes(s18b_32)) * 8 / pb.size() << "\n";
        //     << sdsl::size_in_bytes(s18b_32) << " " << (double) sdsl::size_in_bytes(s18b_32) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_s18b_32) << " " << (double) sdsl::size_in_bytes(rank_s18b_32) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_s18b_32) << " " << (double) sdsl::size_in_bytes(select_s18b_32) / pb.size() << " " 
        //     << "\n";
        total_size_s18_32_1 += (double) (sdsl::size_in_bytes(s18b_32)) * 8 / pb.size();
        total_size_s18_32_bit += (double) (sdsl::size_in_bytes(s18b_32)) * 8 / universe;
        total_size_s18_32 += (double) (sdsl::size_in_bytes(s18b_32)) * 8;
        //ofstream file_pef_sd("/data/PEF_TESTED_ED/S18B_32.bin", std::ios::out | ios::binary );
        //s18b_32.serialize(file_pef_sd);
        //file_pef_sd.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_s18b_32(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "S18 32 VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_s18_32 += total_time;
      
      
        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_s18b_32(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "S18 32 VECTOR SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_s18_32_s += total_time_s;
      }
      {
        sdsl::s18::vector<64> s18b_64(bv);     
        sdsl::s18::rank_support<1, 64> rank_s18b_64(s18b_64);     
        sdsl::s18::select_support<1, 64> select_s18b_64(s18b_64);
        
        //cout << "SIZE S18 64 VECTOR " 
        //     << (double) (sdsl::size_in_bytes(s18b_64)) * 8 / pb.size() << "\n";
        //     << sdsl::size_in_bytes(s18b_64) << " " << (double) sdsl::size_in_bytes(s18b_64) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_s18b_64) << " " << (double) sdsl::size_in_bytes(rank_s18b_64) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_s18b_64) << " " << (double) sdsl::size_in_bytes(select_s18b_64) / pb.size() << " " 
        //     << "\n";
        total_size_s18_64_1 += (double) (sdsl::size_in_bytes(s18b_64)) * 8 / pb.size();
        total_size_s18_64_bit += (double) (sdsl::size_in_bytes(s18b_64)) * 8 / universe;
        total_size_s18_64 += (double) (sdsl::size_in_bytes(s18b_64)) * 8;
        //ofstream file_pef_sd("/data/PEF_TESTED_ED/S18B_64.bin", std::ios::out | ios::binary );
        //s18b_64.serialize(file_pef_sd);
        //file_pef_sd.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_s18b_64(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "S18 64 VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_s18_64 += total_time;
      
      
        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_s18b_64(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "S18 64 VECTOR SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_s18_64_s += total_time_s;
      }
      {
        sdsl::s18::vector<128> s18b_128(bv);     
        sdsl::s18::rank_support<1, 128> rank_s18b_128(s18b_128);     
        sdsl::s18::select_support<1, 128> select_s18b_128(s18b_128);
        
        //cout << "SIZE S18 128 VECTOR " 
        //     << (double) (sdsl::size_in_bytes(s18b_128)) * 8 / pb.size() << "\n";
        //     << sdsl::size_in_bytes(s18b_128) << " " << (double) sdsl::size_in_bytes(s18b_128) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_s18b_128) << " " << (double) sdsl::size_in_bytes(rank_s18b_128) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_s18b_128) << " " << (double) sdsl::size_in_bytes(select_s18b_128) / pb.size() << " " 
        //     << "\n";
        total_size_s18_128_1 += (double) (sdsl::size_in_bytes(s18b_128)) * 8 / pb.size();
        total_size_s18_128_bit += (double) (sdsl::size_in_bytes(s18b_128)) * 8 / universe;
        total_size_s18_128 += (double) (sdsl::size_in_bytes(s18b_128)) * 8;
        //ofstream file_pef_sd("/data/PEF_TESTED_ED/S18B_128.bin", std::ios::out | ios::binary );
        //s18b_128.serialize(file_pef_sd);
        //file_pef_sd.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_s18b_128(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "S18 128 VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_s18_128 += total_time;
      
        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_s18b_128(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "S18 128 VECTOR SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_s18_128_s += total_time_s;
      }
      {
        sdsl::s18::vector<256> s18b_256(bv);     
        sdsl::s18::rank_support<1, 256> rank_s18b_256(s18b_256);     
        sdsl::s18::select_support<1, 256> select_s18b_256(s18b_256);
        
        //cout << "SIZE S18 256 VECTOR " 
        //     << (double) (sdsl::size_in_bytes(s18b_256)) * 8 / pb.size() << "\n";
        //     << sdsl::size_in_bytes(s18b_256) << " " << (double) sdsl::size_in_bytes(s18b_256) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_s18b_256) << " " << (double) sdsl::size_in_bytes(rank_s18b_256) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_s18b_256) << " " << (double) sdsl::size_in_bytes(select_s18b_256) / pb.size() << " " 
        //     << "\n";
        total_size_s18_256_1 += (double) (sdsl::size_in_bytes(s18b_256)) * 8 / pb.size();
        total_size_s18_256_bit += (double) (sdsl::size_in_bytes(s18b_256)) * 8 / universe;
        total_size_s18_256 += (double) (sdsl::size_in_bytes(s18b_256)) * 8;
        //ofstream file_pef_sd("/data/PEF_TESTED_ED/S18B_256.bin", std::ios::out | ios::binary );
        //s18b_256.serialize(file_pef_sd);
        //file_pef_sd.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_s18b_256(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "S18 256 VECTOR RANK: " << Q << " " << total_time << "\n";
        total_time_span_s18_256 += total_time;
      
        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_s18b_256(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "S18 256 VECTOR SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_s18_256_s += total_time_s;
      }
      {
        sdsl::rrr_vector<15> rrr_15(bv);
        sdsl::rank_support_rrr<1, 15> rank_rrr_15(&rrr_15);
        sdsl::select_support_rrr<1, 15> select_rrr_15(&rrr_15);
        //cout << "SIZE RRR VECTOR 15 " 
        //     << (double) (sdsl::size_in_bytes(rrr_15) + sdsl::size_in_bytes(select_rrr_15) + sdsl::size_in_bytes(select_rrr_15)) * 8 / pb.size()
        //     << sdsl::size_in_bytes(rrr_15) << " " << (double) sdsl::size_in_bytes(rrr_15) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_rrr_15) << " " << (double) sdsl::size_in_bytes(rank_rrr_15) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_rrr_15) << " " << (double) sdsl::size_in_bytes(select_rrr_15) / pb.size() << " " 
        //     << "\n";
        total_size_rrr_15_1 += (double) (sdsl::size_in_bytes(rrr_15) + sdsl::size_in_bytes(rank_rrr_15)) * 8 / pb.size();
        total_size_rrr_15_bit += (double) (sdsl::size_in_bytes(rrr_15) + sdsl::size_in_bytes(rank_rrr_15)) * 8 / universe;
        total_size_rrr_15 += (double) (sdsl::size_in_bytes(rrr_15) + sdsl::size_in_bytes(rank_rrr_15)) * 8;
        //ofstream file_pef_rrr_15("/data/PEF_TESTED_ED/RRR_15.bin", std::ios::out | ios::binary );
        //rrr_15.serialize(file_pef_rrr_15);
        //file_pef_rrr_15.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_rrr_15(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "RRR VECTOR 15 RANK: " << Q << " " << total_time << "\n";
        total_time_span_rrr_15 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_rrr_15(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "RRR VECTOR 15 SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_rrr_15_s += total_time_s;
      }
      {
        sdsl::rrr_vector<31> rrr_31(bv);
        sdsl::rank_support_rrr<1, 31> rank_rrr_31(&rrr_31);
        sdsl::select_support_rrr<1, 31> select_rrr_31(&rrr_31);
        //cout << "SIZE RRR VECTOR 31 " 
        //     << (double) (sdsl::size_in_bytes(rrr_31) + sdsl::size_in_bytes(select_rrr_31) + sdsl::size_in_bytes(select_rrr_31)) * 8 / pb.size()
        //     << sdsl::size_in_bytes(rrr_31) << " " << (double) sdsl::size_in_bytes(rrr_31) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_rrr_31) << " " << (double) sdsl::size_in_bytes(rank_rrr_31) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_rrr_31) << " " << (double) sdsl::size_in_bytes(select_rrr_31) / pb.size() << " " 
        //     << "\n";
        total_size_rrr_31_1 += (double) (sdsl::size_in_bytes(rrr_31) + sdsl::size_in_bytes(rank_rrr_31)) * 8 / pb.size();
        total_size_rrr_31_bit += (double) (sdsl::size_in_bytes(rrr_31) + sdsl::size_in_bytes(rank_rrr_31)) * 8 / universe;
        total_size_rrr_31 += (double) (sdsl::size_in_bytes(rrr_31) + sdsl::size_in_bytes(rank_rrr_31)) * 8;
        //ofstream file_pef_rrr_31("/data/PEF_TESTED_ED/RRR_31.bin", std::ios::out | ios::binary );
        //rrr_31.serialize(file_pef_rrr_31);
        //file_pef_rrr_31.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_rrr_31(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "RRR VECTOR 31 RANK: " << Q << " " << total_time << "\n";
        total_time_span_rrr_31 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_rrr_31(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "RRR VECTOR 31 SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_rrr_31_s += total_time_s;
      }
      {
        sdsl::rrr_vector<63> rrr_63(bv);
        sdsl::rank_support_rrr<1, 63> rank_rrr_63(&rrr_63);
        sdsl::select_support_rrr<1, 63> select_rrr_63(&rrr_63);
        //cout << "SIZE RRR VECTOR 63 " 
        //     << (double) (sdsl::size_in_bytes(rrr_63) + sdsl::size_in_bytes(select_rrr_63) + sdsl::size_in_bytes(select_rrr_63)) * 8 / pb.size()
        //     << sdsl::size_in_bytes(rrr_63) << " " << (double) sdsl::size_in_bytes(rrr_63) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_rrr_63) << " " << (double) sdsl::size_in_bytes(rank_rrr_63) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_rrr_63) << " " << (double) sdsl::size_in_bytes(select_rrr_63) / pb.size() << " " 
        //     << "\n";
        total_size_rrr_63_1 += (double) (sdsl::size_in_bytes(rrr_63) + sdsl::size_in_bytes(rank_rrr_63)) * 8 / pb.size();
        total_size_rrr_63_bit += (double) (sdsl::size_in_bytes(rrr_63) + sdsl::size_in_bytes(rank_rrr_63)) * 8 / universe;
        total_size_rrr_63 += (double) (sdsl::size_in_bytes(rrr_63) + sdsl::size_in_bytes(rank_rrr_63)) * 8;
        //ofstream file_pef_rrr_63("/data/PEF_TESTED_ED/RRR_63.bin", std::ios::out | ios::binary );
        //rrr_63.serialize(file_pef_rrr_63);
        //file_pef_rrr_63.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_rrr_63(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "RRR VECTOR 63 RANK: " << Q << " " << total_time << "\n";
        total_time_span_rrr_63 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_rrr_63(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "RRR VECTOR 63 SELECT: " << Q_s << " " << total_time_s << "\n"; 
        total_time_span_rrr_63_s += total_time_s;
      }
      {
        sdsl::rrr_vector<127> rrr_127(bv);
        sdsl::rank_support_rrr<1, 127> rank_rrr_127(&rrr_127);
        sdsl::select_support_rrr<1, 127> select_rrr_127(&rrr_127);
        //cout << "SIZE RRR VECTOR 127 " 
        //     << (double) (sdsl::size_in_bytes(rrr_127) + sdsl::size_in_bytes(select_rrr_127) + sdsl::size_in_bytes(select_rrr_127)) * 8 / pb.size()
        //     << sdsl::size_in_bytes(rrr_127) << " " << (double) sdsl::size_in_bytes(rrr_127) / pb.size() << " " 
        //     << sdsl::size_in_bytes(rank_rrr_127) << " " << (double) sdsl::size_in_bytes(rank_rrr_127) / pb.size() << " " 
        //     << sdsl::size_in_bytes(select_rrr_127) << " " << (double) sdsl::size_in_bytes(select_rrr_127) / pb.size() << " " 
        //     << "\n";
        total_size_rrr_127_1 += (double) (sdsl::size_in_bytes(rrr_127) + sdsl::size_in_bytes(rank_rrr_127)) * 8 / pb.size();
        total_size_rrr_127_bit += (double) (sdsl::size_in_bytes(rrr_127) + sdsl::size_in_bytes(rank_rrr_127)) * 8 / universe;
        total_size_rrr_127 += (double) (sdsl::size_in_bytes(rrr_127) + sdsl::size_in_bytes(rank_rrr_127)) * 8;
        //ofstream file_pef_rrr_127("/data/PEF_TESTED_ED/RRR_127.bin", std::ios::out | ios::binary );
        //rrr_127.serialize(file_pef_rrr_127);
        //file_pef_rrr_127.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += rank_rrr_127(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "RRR VECTOR 127 RANK: " << Q << " " << total_time << "\n";
        total_time_span_rrr_127 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += select_rrr_127(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "RRR VECTOR 127 SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_rrr_127_s += total_time_s;
      }
      */
        /*
      {  
        pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 64> pef_opt(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT 64 " << pef_opt.size_in_bits_formula() << " " << ((double)pef_opt.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_sd_64_1 += ((double)pef_opt.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_sd_64_bit += ((double)pef_opt.size_in_bits_formula()) / ((double) universe);
        total_size_pef_sd_64 += ((double)pef_opt.size_in_bits_formula());
        //ofstream file_pef_opt("/data/PEF_TESTED_ED/PEF_OPT.SD.RANK_V5_SELECT_MCL_64.bin", std::ios::out | ios::binary );
        //pef_opt.write(file_pef_opt);
        //file_pef_opt.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt.rank(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT SD RANK V5 " << 64 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_sd_64 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt.select(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT SD RANK V5 " << 64 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_sd_64_s += total_time_s;
      }
      {
        pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 128> pef_opt2(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT 128 " << pef_opt2.size_in_bits_formula() << " " << ((double)pef_opt2.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_sd_128_1 += ((double)pef_opt2.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_sd_128_bit += ((double)pef_opt2.size_in_bits_formula()) / ((double) universe);
        total_size_pef_sd_128 += ((double)pef_opt2.size_in_bits_formula());
        //ofstream file_pef_opt2("/data/PEF_TESTED_ED/PEF_OPT.SD.RANK_V5_SELECT_MCL_128.bin", std::ios::out | ios::binary );
        //pef_opt2.write(file_pef_opt2);
        //file_pef_opt2.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt2.rank(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT SD RANK V5 " << 128 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_sd_128 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt2.select(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT SD RANK V5 " << 128 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_sd_128_s += total_time_s;
      }
      {
        pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 256> pef_opt3(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT 256 " << pef_opt3.size_in_bits_formula() << " " << ((double)pef_opt3.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_sd_256_1 += ((double)pef_opt3.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_sd_256_bit += ((double)pef_opt3.size_in_bits_formula()) / ((double) universe);
        total_size_pef_sd_256 += ((double)pef_opt3.size_in_bits_formula());
        //ofstream file_pef_opt3("/data/PEF_TESTED_ED/PEF_OPT.SD.RANK_V5_SELECT_MCL_256.bin", std::ios::out | ios::binary );
        //pef_opt3.write(file_pef_opt3);
        //file_pef_opt3.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt3.rank(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT SD RANK V5 " << 256 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_sd_256 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt3.select(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT SD RANK V5 " << 256 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_sd_256_s += total_time_s;
      }
      {
        pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 512> pef_opt4(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT 512 " << pef_opt4.size_in_bits_formula() << " " << ((double)pef_opt4.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_sd_512_1 += ((double)pef_opt4.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_sd_512_bit += ((double)pef_opt4.size_in_bits_formula()) / ((double) universe);
        total_size_pef_sd_512 += ((double)pef_opt4.size_in_bits_formula());
        //ofstream file_pef_opt4("/data/PEF_TESTED_ED/PEF_OPT.SD.RANK_V5_SELECT_MCL_512.bin", std::ios::out | ios::binary );
        //pef_opt4.write(file_pef_opt4);
        //file_pef_opt4.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt4.rank(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT SD RANK V5 " << 512 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_sd_512 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt4.select(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT SD RANK V5 " << 512 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_sd_512_s += total_time_s;
      }
      {
        pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 1024> pef_opt5(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT 1024 " << pef_opt5.size_in_bits_formula() << " " << ((double)pef_opt5.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_sd_1024_1 += ((double)pef_opt5.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_sd_1024_bit += ((double)pef_opt5.size_in_bits_formula()) / ((double) universe);
        total_size_pef_sd_1024 += ((double)pef_opt5.size_in_bits_formula());
        //ofstream file_pef_opt5("/data/PEF_TESTED_ED/PEF_OPT.SD.RANK_V5_SELECT_MCL_1024.bin", std::ios::out | ios::binary );
        //pef_opt5.write(file_pef_opt5);
        //file_pef_opt5.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt5.rank(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT SD RANK V5 " << 1024 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_sd_1024 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt5.select(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT SD RANK V5 " << 1024 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_sd_1024_s += total_time_s;
      }
      {
        pef_vector_opt<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 2048> pef_opt6(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT 2048 " << pef_opt6.size_in_bits_formula() << " " << ((double)pef_opt6.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_sd_2048_1 += ((double)pef_opt6.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_sd_2048_bit += ((double)pef_opt6.size_in_bits_formula()) / ((double) universe);
        total_size_pef_sd_2048 += ((double)pef_opt6.size_in_bits_formula());
        //ofstream file_pef_opt6("/data/PEF_TESTED_ED/PEF_OPT.SD.RANK_V5_SELECT_MCL_2048.bin", std::ios::out | ios::binary );
        //pef_opt6.write(file_pef_opt6);
        //file_pef_opt6.close();
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt6.rank(vrank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT SD RANK V5 " << 2048 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_sd_2048 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt6.select(vselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT SD RANK V5 " << 2048 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_sd_2048_s += total_time_s;
      }
      */
        /*
      {
        //pef_vector_opt<sdsl::rank_support_v5<1>, sdsl::select_support_mcl<1>, 64> pef_opt(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT " << pef_opt.size_in_bits_formula() << " " << ((double)pef_opt.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 64> pef_opt_vigna(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT VIGNA 64 " << pef_opt_vigna.size_in_bits_formula() << " " << ((double)pef_opt_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_vigna_64_1 += ((double)pef_opt_vigna.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_vigna_64_bit += ((double)pef_opt_vigna.size_in_bits_formula()) / ((double) universe);
        total_size_pef_vigna_64 += ((double)pef_opt_vigna.size_in_bits_formula());

        sdsl::sd_vector<> sd(bv);
        sdsl::rank_support_sd<1> rank_sd(&sd);
        sdsl::select_support_sd<1> select_sd(&sd);
   
        vector< uint64_t > auxvignarank;
        uint64_t auxvignai = 0;
        
        while(auxvignarank.size() < n_queries) {
          if(rank_sd(vrank[auxvignai]) == pef_opt_vigna.rank(vrank[auxvignai])) {
            auxvignarank.push_back(vrank[auxvignai]);
          }
          if(auxvignai == vrank.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignarank.size() < n_queries) {
          auxvignarank.push_back(auxvignarank[auxvignai++]);
        }

        vector< uint64_t > auxvignaselect;
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          if(select_sd(vselect[auxvignai]) == pef_opt_vigna.select(vselect[auxvignai])) {
            auxvignaselect.push_back(vselect[auxvignai]);
          }
          if(auxvignai == vselect.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          auxvignaselect.push_back(auxvignaselect[auxvignai++]);
        }     

        //ofstream file_pef_opt_vigna1("PEF_OPT.VIGNA.RANK_V5_SELECT_MCL_64.bin", std::ios::out | ios::binary );
        //file_pef_opt_vigna1.write((char*) &pef_opt_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v55<1>, sdsl::select_support_mcl<1>, 64>));
        //file_pef_opt_vigna1.close();
        //sux::bits::EliasFano<> EF(pb, universe); 
        //vector<uint64_t> pb2 = {41,75,111,132,133,134,135,151,152,153,162,173,174,175,177,178,179,180,182,184,188,200,215,216,222,224,228,231,242,243,254,263,282,283,284,290,295,296,298,306,307,310,314,315,316,321,322,323,324,325,326,327,328,330,331,332,333,334,336,337,343,398,399,421,476,477,517,538,546,556,611,620,632,652,684,685,692,693,694,695,725,726,768,784,785,786,796,797,798,803,811,812,814,816,819,1191,1347,1361,1363,1395,1416,1417,1421,1431,1440,1444,1445,1455,1468,1473,1489,1490,1491,1492,1493,1494,1495,1496,1497,1498,1499,1500,1501,1502,1503,1504,1505,1506,1507,1508,1509,1510,1511,1512,1513,1534,1546,1548,1556,1557,1568,1576,1581,1584,1596,1597,1601,1607,1614,1616,1646,1749,1753,1754,1760,1765,1772,1783,1801,1819,1835,1845,1851,1857,1859,1865,1872,1878,1884,1890,1905,1917,1923,1929,1935,1938,1944,1950,1957,2001,2007,2079,2092,2094,2096,2098,2107,2109,2111,2113,2129,2131,2143,2153,2161,2165,2167,2186,2189,2211,2217,2223,2229,2235,2241,2247,2253,2259,2265,2271,2277,2283,2289,2295,2313,2319,2325,2331,2337,2348,2349,2351,2355,2361,2367,2377,2383,2384,2390,2395,2407,2413,2430,2436,2442,2448,2454,2460,2466,2472,2478,2484,2490,2495,2496,2501,2502,2507,2519,2525,2531,2537,2549,2555,2562};
        //sux::bits::EliasFano<> EF2(pb2, 2563);
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt_vigna.rank(auxvignarank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 64 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_vigna_64 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt_vigna.select(auxvignaselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 64 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_vigna_64_s += total_time_s;
      }
      {
        pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 128> pef_opt2_vigna(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT VIGNA 128 " << pef_opt2_vigna.size_in_bits_formula() << " " << ((double)pef_opt2_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_vigna_128_1 += ((double)pef_opt2_vigna.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_vigna_128_bit += ((double)pef_opt2_vigna.size_in_bits_formula()) / ((double) universe);
        total_size_pef_vigna_128 += ((double)pef_opt2_vigna.size_in_bits_formula());
        //ofstream file_pef_opt_vigna2("PEF_OPT.VIGNA.RANK_V5_SELECT_MCL_128.bin", std::ios::out | ios::binary );
        //file_pef_opt_vigna2.write((char*) &pef_opt2_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v55<1>, sdsl::select_support_mcl<1>, 128>));
        //file_pef_opt_vigna2.close();
     
        sdsl::sd_vector<> sd(bv);
        sdsl::rank_support_sd<1> rank_sd(&sd);
        sdsl::select_support_sd<1> select_sd(&sd);
  
        vector< uint64_t > auxvignarank;
        uint64_t auxvignai = 0;
        
        while(auxvignarank.size() < n_queries) {
          if(rank_sd(vrank[auxvignai]) == pef_opt2_vigna.rank(vrank[auxvignai])) {
            auxvignarank.push_back(vrank[auxvignai]);
          }
          if(auxvignai == vrank.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignarank.size() < n_queries) {
          auxvignarank.push_back(auxvignarank[auxvignai++]);
        }

        vector< uint64_t > auxvignaselect;
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          if(select_sd(vselect[auxvignai]) == pef_opt2_vigna.select(vselect[auxvignai])) {
            auxvignaselect.push_back(vselect[auxvignai]);
          }
          if(auxvignai == vselect.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          auxvignaselect.push_back(auxvignaselect[auxvignai++]);
        }     
 
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt2_vigna.rank(auxvignarank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 128 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_vigna_128 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt2_vigna.select(auxvignaselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 128 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_vigna_128_s += total_time_s;
      }
      {
        pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 256> pef_opt3_vigna(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT VIGNA 256 " << pef_opt3_vigna.size_in_bits_formula() << " " << ((double)pef_opt3_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_vigna_256_1 += ((double)pef_opt3_vigna.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_vigna_256_bit += ((double)pef_opt3_vigna.size_in_bits_formula()) / ((double) universe);
        total_size_pef_vigna_256 += ((double)pef_opt3_vigna.size_in_bits_formula());
        //ofstream file_pef_opt_vigna3("PEF_OPT.VIGNA.RANK_V5_SELECT_MCL_256.bin", std::ios::out | ios::binary );
        //file_pef_opt_vigna3.write((char*) &pef_opt3_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v55<1>, sdsl::select_support_mcl<1>, 256>));
        //file_pef_opt_vigna3.close();
     
        sdsl::sd_vector<> sd(bv);
        sdsl::rank_support_sd<1> rank_sd(&sd);
        sdsl::select_support_sd<1> select_sd(&sd);
 
        vector< uint64_t > auxvignarank;
        uint64_t auxvignai = 0;
        
        while(auxvignarank.size() < n_queries) {
          if(rank_sd(vrank[auxvignai]) == pef_opt3_vigna.rank(vrank[auxvignai])) {
            auxvignarank.push_back(vrank[auxvignai]);
          }
          if(auxvignai == vrank.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignarank.size() < n_queries) {
          auxvignarank.push_back(auxvignarank[auxvignai++]);
        }

        vector< uint64_t > auxvignaselect;
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          if(select_sd(vselect[auxvignai]) == pef_opt3_vigna.select(vselect[auxvignai])) {
            auxvignaselect.push_back(vselect[auxvignai]);
          }
          if(auxvignai == vselect.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          auxvignaselect.push_back(auxvignaselect[auxvignai++]);
        }

        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt3_vigna.rank(auxvignarank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 256 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_vigna_256 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt3_vigna.select(auxvignaselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 256 << " SELECT: " << Q_s << " " << total_time_s << "\n";  
        total_time_span_pef_vigna_256_s += total_time_s;
      }
      {
        pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 512> pef_opt4_vigna(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT VIGNA 512 " << pef_opt4_vigna.size_in_bits_formula() << " " << ((double)pef_opt4_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_vigna_512_1 += ((double)pef_opt4_vigna.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_vigna_512_bit += ((double)pef_opt4_vigna.size_in_bits_formula()) / ((double) universe);
        total_size_pef_vigna_512 += ((double)pef_opt4_vigna.size_in_bits_formula());
        //ofstream file_pef_opt_vigna4("PEF_OPT.VIGNA.RANK_V5_SELECT_MCL_512.bin", std::ios::out | ios::binary );
        //file_pef_opt_vigna4.write((char*) &pef_opt4_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v55<1>, sdsl::select_support_mcl<1>, 512>));
        //file_pef_opt_vigna4.close();
     
        sdsl::sd_vector<> sd(bv);
        sdsl::rank_support_sd<1> rank_sd(&sd);
        sdsl::select_support_sd<1> select_sd(&sd);

        vector< uint64_t > auxvignarank;
        uint64_t auxvignai = 0;
        
        while(auxvignarank.size() < n_queries) {
          if(rank_sd(vrank[auxvignai]) == pef_opt4_vigna.rank(vrank[auxvignai])) {
            auxvignarank.push_back(vrank[auxvignai]);
          }
          if(auxvignai == vrank.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignarank.size() < n_queries) {
          auxvignarank.push_back(auxvignarank[auxvignai++]);
        }

        vector< uint64_t > auxvignaselect;
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          if(select_sd(vselect[auxvignai]) == pef_opt4_vigna.select(vselect[auxvignai])) {
            auxvignaselect.push_back(vselect[auxvignai]);
          }
          if(auxvignai == vselect.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          auxvignaselect.push_back(auxvignaselect[auxvignai++]);
        }

        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt4_vigna.rank(auxvignarank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 512 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_vigna_512 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt4_vigna.select(auxvignaselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 512 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_vigna_512_s += total_time_s;
      }
      {
        pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 1024> pef_opt5_vigna(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT VIGNA 1024 " << pef_opt5_vigna.size_in_bits_formula() << " " << ((double)pef_opt5_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_vigna_1024_1 += ((double)pef_opt5_vigna.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_vigna_1024_bit += ((double)pef_opt5_vigna.size_in_bits_formula()) / ((double) universe);
        total_size_pef_vigna_1024 += ((double)pef_opt5_vigna.size_in_bits_formula());
        //ofstream file_pef_opt_vigna5("PEF_OPT.VIGNA.RANK_V5_SELECT_MCL_1024.bin", std::ios::out | ios::binary );
        //file_pef_opt_vigna5.write((char*) &pef_opt5_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v55<1>, sdsl::select_support_mcl<1>, 1024>));
        //file_pef_opt_vigna5.close(); 
     
        sdsl::sd_vector<> sd(bv);
        sdsl::rank_support_sd<1> rank_sd(&sd);
        sdsl::select_support_sd<1> select_sd(&sd);
       
        vector< uint64_t > auxvignarank;
        uint64_t auxvignai = 0;
        
        while(auxvignarank.size() < n_queries) {
          if(rank_sd(vrank[auxvignai]) == pef_opt5_vigna.rank(vrank[auxvignai])) {
            auxvignarank.push_back(vrank[auxvignai]);
          }
          if(auxvignai == vrank.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignarank.size() < n_queries) {
          auxvignarank.push_back(auxvignarank[auxvignai++]);
        }

        vector< uint64_t > auxvignaselect;
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          if(select_sd(vselect[auxvignai]) == pef_opt5_vigna.select(vselect[auxvignai])) {
            auxvignaselect.push_back(vselect[auxvignai]);
          }
          if(auxvignai == vselect.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          auxvignaselect.push_back(auxvignaselect[auxvignai++]);
        }

        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt5_vigna.rank(auxvignarank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 1024 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_vigna_1024 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt5_vigna.select(auxvignaselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 1024 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_vigna_1024_s += total_time_s;
      }
      {
        pef_vector_opt_vigna<sdsl::rank_support_v<1>, sdsl::select_support_mcl<1>, 2048> pef_opt6_vigna(pb, universe, 0.03, 0.3);
        //cout << "SIZE PEF_OPT VIGNA 2048 " << pef_opt6_vigna.size_in_bits_formula() << " " << ((double)pef_opt6_vigna.size_in_bits_formula()) / ((double) pb.size()) << "\n";  
        total_size_pef_vigna_2048_1 += ((double)pef_opt6_vigna.size_in_bits_formula()) / ((double) pb.size());
        total_size_pef_vigna_2048_bit += ((double)pef_opt6_vigna.size_in_bits_formula()) / ((double) universe);
        total_size_pef_vigna_2048 += ((double)pef_opt6_vigna.size_in_bits_formula());
        //ofstream file_pef_opt_vigna6("PEF_OPT.VIGNA.RANK_V5_SELECT_MCL_2048.bin", std::ios::out | ios::binary );
        //file_pef_opt_vigna6.write((char*) &pef_opt6_vigna, sizeof(pef_vector_opt_vigna<sdsl::rank_support_v55<1>, sdsl::select_support_mcl<1>, 2048>));
        //file_pef_opt_vigna6.close();
     
        sdsl::sd_vector<> sd(bv);
        sdsl::rank_support_sd<1> rank_sd(&sd);
        sdsl::select_support_sd<1> select_sd(&sd);
       
        vector< uint64_t > auxvignarank;
        uint64_t auxvignai = 0;
        
        while(auxvignarank.size() < n_queries) {
          if(rank_sd(vrank[auxvignai]) == pef_opt6_vigna.rank(vrank[auxvignai])) {
            auxvignarank.push_back(vrank[auxvignai]);
          }
          if(auxvignai == vrank.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignarank.size() < n_queries) {
          auxvignarank.push_back(auxvignarank[auxvignai++]);
        }

        vector< uint64_t > auxvignaselect;
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          if(select_sd(vselect[auxvignai]) == pef_opt6_vigna.select(vselect[auxvignai])) {
            auxvignaselect.push_back(vselect[auxvignai]);
          }
          if(auxvignai == vselect.size() - 1) break;
          auxvignai = (auxvignai + 1) % n_queries;
        }
        auxvignai = 0;
        while(auxvignaselect.size() < n_queries) {
          auxvignaselect.push_back(auxvignaselect[auxvignai++]);
        }
        
        chrono::high_resolution_clock::time_point start, stop;
        double total_time = 0;
        chrono::duration< double > time_span;
        uint64_t Q = 0;
        start = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q += pef_opt6_vigna.rank(auxvignarank[q]);
        }
        stop = chrono::high_resolution_clock::now();
        time_span = chrono::duration_cast< chrono::microseconds >(stop - start);
        total_time = time_span.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 2048 << " RANK: " << Q << " " << total_time << "\n";
        total_time_span_pef_vigna_2048 += total_time;

        chrono::high_resolution_clock::time_point start_s, stop_s;
        double total_time_s = 0;
        chrono::duration< double > time_span_s;
        uint64_t Q_s = 0;
        start_s = chrono::high_resolution_clock::now();
        for(uint64_t q = 0; q < n_queries; q++){
          Q_s += pef_opt6_vigna.select(auxvignaselect[q]);
        }
        stop_s = chrono::high_resolution_clock::now();
        time_span_s = chrono::duration_cast< chrono::microseconds >(stop_s - start_s);
        total_time_s = time_span_s.count();
        //cout << "PEF OPT VIGNA RANK V5 " << 2048 << " SELECT: " << Q_s << " " << total_time_s << "\n";
        total_time_span_pef_vigna_2048_s += total_time_s;
      }
      */
      pb.clear();
    }
    cout << "\n";
    
    rf.close();
    cout << filepath << " " << amount_bv << "\n";
    cout << "OZ\n";
    cout << total_size_oz << " " << total_size_oz / (double) amount_bv << " " << total_size_oz_1 / (double) amount_bv << " " << total_size_oz_bit / (double) amount_bv << "\n";
    cout << total_time_span_oz << " " << total_time_span_oz / (double) amount_bv << "\n";
    cout << total_time_span_oz_s << " "  << total_time_span_oz_s / (double) amount_bv  << "\n";
 

    /*
    cout << "ZOMBIT\n";
    cout << total_size_zombit << " " << total_size_zombit / (double) amount_bv << " " << total_size_zombit_1 / (double) amount_bv << " " << total_size_zombit_bit / (double) amount_bv << "\n";
    cout << total_time_span_zombit << " " << total_time_span_zombit / (double) amount_bv << "\n";
    cout << total_time_span_zombit_s << " "  << total_time_span_zombit_s / (double) amount_bv  << "\n";
 
    cout << "HYB\n";
    cout << total_size_hyb << " " << total_size_hyb / (double) amount_bv << " " << total_size_hyb_1 / (double) amount_bv << " " << total_size_hyb_bit / (double) amount_bv << "\n";
    cout << total_time_span_hyb << " " << total_time_span_hyb / (double) amount_bv << "\n";
    cout << total_time_span_hyb_s << " "  << total_time_span_hyb_s / (double) amount_bv  << "\n";
    
    cout << "SD\n";
    cout << total_size_sd << " " << total_size_sd / (double) amount_bv << " " << total_size_sd_1 / (double) amount_bv << " " << total_size_sd_bit / (double) amount_bv << "\n";
    cout << total_time_span_sd << " " << total_time_span_sd / (double) amount_bv  << "\n";
    cout << total_time_span_sd_s << " " << total_time_span_sd_s / (double) amount_bv   << "\n";

    cout << "S18 8\n";
    cout << total_size_s18_8 << " " << total_size_s18_8 / (double) amount_bv << " " << total_size_s18_8_1 / (double) amount_bv << " " << total_size_s18_8_bit / (double) amount_bv << "\n";
    cout << total_time_span_s18_8 << " " << total_time_span_s18_8 / (double) amount_bv << "\n";
    cout << total_time_span_s18_8_s << " " << total_time_span_s18_8_s / (double) amount_bv << "\n";

    cout << "S18 16\n";
    cout << total_size_s18_16 << " " << total_size_s18_16 / (double) amount_bv << " " << total_size_s18_16_1 / (double) amount_bv << " " << total_size_s18_16_bit / (double) amount_bv << "\n";
    cout << total_time_span_s18_16 << " " << total_time_span_s18_16 / (double) amount_bv << "\n";
    cout << total_time_span_s18_16_s << " " << total_time_span_s18_16_s / (double) amount_bv << "\n";

    cout << "S18 32\n";
    cout << total_size_s18_32 << " " << total_size_s18_32 / (double) amount_bv << " " << total_size_s18_32_1 / (double) amount_bv << " " << total_size_s18_32_bit / (double) amount_bv << "\n";
    cout << total_time_span_s18_32 << " " << total_time_span_s18_32 / (double) amount_bv << "\n";
    cout << total_time_span_s18_32_s << " " << total_time_span_s18_32_s / (double) amount_bv << "\n";

    cout << "S18 64\n";
    cout << total_size_s18_64 << " " << total_size_s18_64 / (double) amount_bv << " " << total_size_s18_64_1 / (double) amount_bv << " " << total_size_s18_64_bit / (double) amount_bv << "\n";
    cout << total_time_span_s18_64 << " " << total_time_span_s18_64 / (double) amount_bv << "\n";
    cout << total_time_span_s18_64_s << " " << total_time_span_s18_64_s / (double) amount_bv << "\n";

    cout << "S18 128\n";
    cout << total_size_s18_128 << " " << total_size_s18_128 / (double) amount_bv << " " << total_size_s18_128_1 / (double) amount_bv << " " << total_size_s18_128_bit / (double) amount_bv << "\n";
    cout << total_time_span_s18_128 << " " << total_time_span_s18_128 / (double) amount_bv << "\n";
    cout << total_time_span_s18_128_s << " " << total_time_span_s18_128_s / (double) amount_bv << "\n";

    cout << "S18 256\n";
    cout << total_size_s18_256 << " " << total_size_s18_256 / (double) amount_bv << " " << total_size_s18_256_1 / (double) amount_bv << " " << total_size_s18_256_bit / (double) amount_bv << "\n";
    cout << total_time_span_s18_256 << " " << total_time_span_s18_256 / (double) amount_bv << "\n";
    cout << total_time_span_s18_256_s << " " << total_time_span_s18_256_s / (double) amount_bv << "\n";

    cout << "RRR 15\n";
    cout << total_size_rrr_15 << " " << total_size_rrr_15 / (double) amount_bv << " " << total_size_rrr_15_1 / (double) amount_bv << " " << total_size_rrr_15_bit / (double) amount_bv << "\n";
    cout << total_time_span_rrr_15 << " " << total_time_span_rrr_15 / (double) amount_bv << "\n";
    cout << total_time_span_rrr_15_s << " " << total_time_span_rrr_15_s / (double) amount_bv << "\n";
 
    cout << "RRR 31\n";
    cout << total_size_rrr_31 << " " << total_size_rrr_31 / (double) amount_bv << " " << total_size_rrr_31_1 / (double) amount_bv << " " << total_size_rrr_31_bit / (double) amount_bv << "\n";
    cout << total_time_span_rrr_31 << " " << total_time_span_rrr_31 / (double) amount_bv << "\n";
    cout << total_time_span_rrr_31_s << " " << total_time_span_rrr_31_s / (double) amount_bv << "\n";
    
    cout << "RRR 63\n";
    cout << total_size_rrr_63 << " " << total_size_rrr_63 / (double) amount_bv << " " << total_size_rrr_63_1 / (double) amount_bv << " " << total_size_rrr_63_bit / (double) amount_bv << "\n";
    cout << total_time_span_rrr_63 << " " << total_time_span_rrr_63 / (double) amount_bv << "\n";
    cout << total_time_span_rrr_63_s << " " << total_time_span_rrr_63_s / (double) amount_bv << "\n";
    
    cout << "RRR 127\n";
    cout << total_size_rrr_127 << " " << total_size_rrr_127 / (double) amount_bv << " " << total_size_rrr_127_1 / (double) amount_bv << " " << total_size_rrr_127_bit / (double) amount_bv << "\n";
    cout << total_time_span_rrr_127 << " " << total_time_span_rrr_127 / (double) amount_bv << "\n";
    cout << total_time_span_rrr_127_s << " " << total_time_span_rrr_127_s / (double) amount_bv << "\n";
       
    cout << "PEF SD 64\n";
    cout << total_size_pef_sd_64 << " " << total_size_pef_sd_64 / (double) amount_bv << " " << total_size_pef_sd_64_1 / (double) amount_bv << " " << total_size_pef_sd_64_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_64 << " " << total_time_span_pef_sd_64 / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_64_s << " " << total_time_span_pef_sd_64_s / (double) amount_bv << "\n";
    
    cout << "PEF SD 128\n";
    cout << total_size_pef_sd_128 << " " << total_size_pef_sd_128 / (double) amount_bv << " " << total_size_pef_sd_128_1 / (double) amount_bv << " " << total_size_pef_sd_128_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_128 << " " << total_time_span_pef_sd_128 / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_128_s << " " << total_time_span_pef_sd_128_s / (double) amount_bv << "\n";
    
    cout << "PEF SD 256\n";
    cout << total_size_pef_sd_256 << " " << total_size_pef_sd_256 / (double) amount_bv << " " << total_size_pef_sd_256_1 / (double) amount_bv << " " << total_size_pef_sd_256_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_256 << " " << total_time_span_pef_sd_256 / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_256_s << " " << total_time_span_pef_sd_256_s / (double) amount_bv << "\n";
    
    cout << "PEF SD 512\n";
    cout << total_size_pef_sd_512 << " " << total_size_pef_sd_512 / (double) amount_bv << " " << total_size_pef_sd_512_1 / (double) amount_bv << " " << total_size_pef_sd_512_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_512 << " " << total_time_span_pef_sd_512 / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_512_s << " " << total_time_span_pef_sd_512_s / (double) amount_bv << "\n";
    
    cout << "PEF SD 1024\n";
    cout << total_size_pef_sd_1024 << " " << total_size_pef_sd_1024 / (double) amount_bv << " " << total_size_pef_sd_1024_1 / (double) amount_bv << " " << total_size_pef_sd_1024_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_1024 << " " << total_time_span_pef_sd_1024 / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_1024_s << " " << total_time_span_pef_sd_1024_s / (double) amount_bv << "\n";
    
    cout << "PEF SD 2048\n";
    cout << total_size_pef_sd_2048 << " " << total_size_pef_sd_2048 / (double) amount_bv << " " << total_size_pef_sd_2048_1 / (double) amount_bv << " " << total_size_pef_sd_2048_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_2048 << " " << total_time_span_pef_sd_2048 / (double) amount_bv << "\n";
    cout << total_time_span_pef_sd_2048_s << " " << total_time_span_pef_sd_2048_s / (double) amount_bv << "\n";
 
    cout << "PEF VIGNA 64\n";
    cout << total_size_pef_vigna_64 << " " << total_size_pef_vigna_64 / (double) amount_bv << " " << total_size_pef_vigna_64_1 / (double) amount_bv << " " << total_size_pef_vigna_64_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_64 << " " << total_time_span_pef_vigna_64 / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_64_s << " " << total_time_span_pef_vigna_64_s / (double) amount_bv << "\n";
    
    cout << "PEF VIGNA 128\n";
    cout << total_size_pef_vigna_128 << " " << total_size_pef_vigna_128 / (double) amount_bv << " " << total_size_pef_vigna_128_1 / (double) amount_bv << " " << total_size_pef_vigna_128_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_128 << " " << total_time_span_pef_vigna_128 / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_128_s << " " << total_time_span_pef_vigna_128_s / (double) amount_bv << "\n";
    
    cout << "PEF VIGNA 256\n";
    cout << total_size_pef_vigna_256 << " " << total_size_pef_vigna_256 / (double) amount_bv << " " << total_size_pef_vigna_256_1 / (double) amount_bv << " " << total_size_pef_vigna_256_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_256 << " " << total_time_span_pef_vigna_256 / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_256_s << " " << total_time_span_pef_vigna_256_s / (double) amount_bv << "\n";
    
    cout << "PEF VIGNA 512\n";
    cout << total_size_pef_vigna_512 << " " << total_size_pef_vigna_512 / (double) amount_bv << " " << total_size_pef_vigna_512_1 / (double) amount_bv << " " << total_size_pef_vigna_512_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_512 << " " << total_time_span_pef_vigna_512 / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_512_s << " " << total_time_span_pef_vigna_512_s / (double) amount_bv << "\n";
    
    cout << "PEF VIGNA 1024\n";
    cout << total_size_pef_vigna_1024 << " " << total_size_pef_vigna_1024 / (double) amount_bv << " " << total_size_pef_vigna_1024_1 / (double) amount_bv << " " << total_size_pef_vigna_1024_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_1024 << " " << total_time_span_pef_vigna_1024 / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_1024_s << " " << total_time_span_pef_vigna_1024_s / (double) amount_bv << "\n";
    
    cout << "PEF VIGNA 2048\n";
    cout << total_size_pef_vigna_2048 << " " << total_size_pef_vigna_2048 / (double) amount_bv << " " << total_size_pef_vigna_2048_1 / (double) amount_bv << " " << total_size_pef_vigna_2048_bit / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_2048 << " " << total_time_span_pef_vigna_2048 / (double) amount_bv << "\n";
    cout << total_time_span_pef_vigna_2048_s << " " << total_time_span_pef_vigna_2048_s / (double) amount_bv << "\n"; }
  */
}
  return 0;
}
