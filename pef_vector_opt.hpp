#ifndef PEF_OPT
#define PEF_OPT

#include <vector>
#include <utility>
//#include "sdsl-lite/include/sdsl/vectors.hpp"
//#include "sdsl-lite/include/sdsl/bit_vectors.hpp"
#include <sdsl/vectors.hpp>
#include <sdsl/bit_vectors.hpp>
#include <cinttypes>
#include <assert.h> 
#include "util.hpp"

using namespace std;
//using namespace sdsl;

template<class rank_support=sdsl::rank_support_scan<1>, class select_support=sdsl::select_support_scan<1>, uint64_t _fixed_cost=64>
class pef_vector_opt {
  // last element of each block
  sdsl::sd_vector<> L;
  sdsl::select_support_sd<1> select_L;
  sdsl::rank_support_sd<1> rank_L;

  // the accumulatives lengths of blocks
  sdsl::sd_vector<> E;
  sdsl::select_support_sd<1> select_E;
  sdsl::rank_support_sd<1> rank_E;

  std::vector<void *> P;  // pointer to the block encoding
  sdsl::bit_vector B; // bit vector indicating the encoding of each block.
  // B[i] == 0 && P[i] == NULL -> All ones in block
  // B[i] == 0 && P[i] != NULL -> Plain bit vector encoding of the block
  // B[i] == 1                 -> Elias-Fano encoding ob the block
  std::vector<void *> block_select;
  std::vector<void *> block_rank;

  uint64_t u; // universe size  (bitvector length)
  uint64_t n; // set size (number of 1s in the bitvector)
  uint64_t nBlocks; 
    
  public:

    pef_vector_opt() {;}

    ~pef_vector_opt() {;}

    uint64_t size(){
      return u;
    }

    uint64_t n_ones(){
      return n;
    }

    uint64_t size_in_bytes(){
      uint64_t only_encoding = sdsl::size_in_bytes(L)
                             + sdsl::size_in_bytes(E)
                             + sdsl::size_in_bytes(B) + 3 * sizeof(uint64_t) 
                             + nBlocks * sizeof(void *);
 
      uint64_t size = sdsl::size_in_bytes(L) + sdsl::size_in_bytes(select_L)
                    + sdsl::size_in_bytes(rank_L)
                    + sdsl::size_in_bytes(E) + sdsl::size_in_bytes(select_E)
                    + sdsl::size_in_bytes(rank_E)
                    + sdsl::size_in_bytes(B) + 3 * sizeof(uint64_t) 
                    + nBlocks * sizeof(void *);
      uint64_t ef_times = 0;
      uint64_t bit_times = 0;
      uint64_t all_ones_times = 0;
      for (uint64_t i=0; i < nBlocks; ++i) {
        if (B[i]) {
          only_encoding += sdsl::size_in_bytes(*(sdsl::sd_vector<> *)P[i]); 
          size += sdsl::size_in_bytes(*(sdsl::sd_vector<> *)P[i])
                + sdsl::size_in_bytes(*(sdsl::select_support_sd<1> *)block_select[i])
                + sdsl::size_in_bytes(*(sdsl::rank_support_sd<1> *)block_rank[i]);
	        ef_times++;
        } else {
          if (P[i]) {
            only_encoding += sdsl::size_in_bytes(*(sdsl::bit_vector *)P[i]); 
            size += sdsl::size_in_bytes(*(sdsl::bit_vector *)P[i])             
                  + sdsl::size_in_bytes(*(rank_support *)block_rank[i])
                  + sdsl::size_in_bytes(*(select_support *)block_select[i]);
            bit_times++;
	        } else { 
            all_ones_times++;
          }
        }
      }
      cout << "EF " << ef_times << " BIT " << bit_times << " ALL_ONES " << all_ones_times << " " << (double) only_encoding / (double) n << " ";
      return size;
    }
    
    uint64_t size_in_bits_formula(){
      rank_support rank_B(&B);

      uint64_t u_L = L.size();
      uint64_t n_L = rank_L(u_L);
      
      uint64_t u_E = E.size();
      uint64_t n_E = rank_E(u_E);

      uint64_t n_B = rank_B(nBlocks);
      uint64_t u_B = nBlocks;

      uint64_t size = bits_built_sd_vector(u_L, n_L, L) 
                    + bits_built_sd_vector(u_E, n_E, E)
                    + ((u_B / 64 + 1) * 64);
                    + 3 * sizeof(uint64_t) * 8
                    + nBlocks * sizeof(void *) * 8;
      uint64_t size_L = bits_built_sd_vector(u_L, n_L, L);
      uint64_t size_E = bits_built_sd_vector(u_E, n_E, E);
      uint64_t size_B = ((u_B / 64 + 1) * 64);
                   /*
      size = bitsize_elias_fano(u_L, n_L) 
                    + bitsize_elias_fano(u_E, n_E)
                    + bitsize_plain_bitvector(u_B, n_B);
                    + 3 * sizeof(uint64_t) * 8
                    + nBlocks * sizeof(void *) * 8;
*/
      cout << u << " " << n << " " 
           << size << " " << (double) size / n << " "
           << size_L << " " << (double) size_L / n << " "
           << size_E << " " << (double) size_E / n << " "
           << size_B << " " << (double) size_B / n << " ";
      
      uint64_t ef_times = 0;
      uint64_t ef_size = 0;
      
      uint64_t bit_times = 0;
      uint64_t bit_size = 0;
      
      uint64_t only_blocks = 0;

      uint64_t all_ones_times = 0;
      
      for (uint64_t i=0; i < nBlocks; ++i) {
        if (B[i]) {
          uint64_t u_p = (*(sdsl::sd_vector<> *)P[i]).size();
          uint64_t n_p = (*(sdsl::rank_support_sd<1> *)block_rank[i])(u_p);
          //if(i > 84780) cout << "SD " << i << " " << u_p << " " << n_p << " " << bits_built_sd_vector(u_p, n_p, *(sdsl::sd_vector<> *)P[i]) << "\n";
          size += bits_built_sd_vector(u_p, n_p, *(sdsl::sd_vector<> *)P[i]);
          ef_size += bits_built_sd_vector(u_p, n_p, *(sdsl::sd_vector<> *)P[i]);
          //only_blocks += bits_built_sd_vector(u_p, n_p, *(sdsl::sd_vector<> *)P[i]);
          only_blocks += bits_built_sd_vector_no_select(u_p, n_p);

          //if(i > 9784) cout << "SD " << i << " " << u_p << " " << n_p << " " << bits_sd_vector(u_p, n_p) << "\n";
          //size += bits_sd_vector(u_p, n_p);
          //ef_size += bits_sd_vector(u_p, n_p);
          //only_blocks += bits_sd_vector(u_p, n_p);

          //if(i > 84790) cout << "SD " << i << " " << u_p << " " << n_p << " " << bitsize_elias_fano(u_p, n_p) << "\n";
          //size += bitsize_elias_fano(u_p, n_p);
          //ef_size += bitsize_elias_fano(u_p, n_p);

	        ef_times++;
        } else {
          if (P[i]) {
	          uint64_t u_p = (*(sdsl::bit_vector *)P[i]).size();
            uint64_t n_p = (*(rank_support *)block_rank[i])(u_p);
            //if(i > 84780) cout << "BIT " << i << " " << u_p << " " << n_p << " " << bits_built_bit_vector(u_p, n_p, *(select_support *)block_select[i]) << "\n";
            size += bits_built_bit_vector(u_p, n_p, *(select_support *)block_select[i]);
            bit_size += bits_built_bit_vector(u_p, n_p, *(select_support *)block_select[i]);
            //only_blocks += bits_built_bit_vector(u_p, n_p, *(select_support *)block_select[i]);
            only_blocks += bits_built_bit_vector_no_select(u_p, n_p);
 
            //if(i > 9784) cout << "BIT " << i << " " << u_p << " " << n_p << " " << bits_bit_vector(u_p, n_p) << "\n";
            //size += bits_bit_vector(u_p, n_p);
            //bit_size += bits_bit_vector(u_p, n_p);
            //only_blocks += bits_bit_vector(u_p, n_p);
                       
            //if(i > 84790) cout << "BIT " << i << " " << u_p << " " << n_p << " " << bitsize_plain_bitvector(u_p, n_p) << "\n";
            //size += bitsize_plain_bitvector(u_p, n_p);
            //bit_size += bitsize_plain_bitvector(u_p, n_p);
            bit_times++;
	        } else { 
            all_ones_times++;
          }
        }
      }
      cout << "EF " << ef_times << " BIT " << bit_times << " ALL_ONES " << all_ones_times 
           << " " << ef_size << " " << bit_size << " "
           << (double) ef_size / n << " " << (double) bit_size / n << " "
           << only_blocks << " "
           << (double) only_blocks / n << "\n";
      return size;
    }
    
    uint64_t size_in_bits_formula_no_select(){
      rank_support rank_B(&B);

      uint64_t u_L = L.size();
      uint64_t n_L = rank_L(u_L);
      
      uint64_t u_E = E.size();
      uint64_t n_E = rank_E(u_E);

      uint64_t n_B = rank_B(nBlocks);
      uint64_t u_B = nBlocks;

      uint64_t size = bits_built_sd_vector(u_L, n_L, L) 
                    + bits_built_sd_vector(u_E, n_E, E)
                    + ((u_B / 64 + 1) * 64);
                    + 3 * sizeof(uint64_t) * 8
                    + nBlocks * sizeof(void *) * 8;
      uint64_t size_L = bits_built_sd_vector(u_L, n_L, L);
      uint64_t size_E = bits_built_sd_vector(u_E, n_E, E);
      uint64_t size_B = ((u_B / 64 + 1) * 64);
                   /*
      size = bitsize_elias_fano(u_L, n_L) 
                    + bitsize_elias_fano(u_E, n_E)
                    + bitsize_plain_bitvector(u_B, n_B);
                    + 3 * sizeof(uint64_t) * 8
                    + nBlocks * sizeof(void *) * 8;
*/
      cout << u << " " << n << " " 
           << size << " " << (double) size / n << " "
           << size_L << " " << (double) size_L / n << " "
           << size_E << " " << (double) size_E / n << " "
           << size_B << " " << (double) size_B / n << " ";
      
      uint64_t ef_times = 0;
      uint64_t ef_size = 0;
      
      uint64_t bit_times = 0;
      uint64_t bit_size = 0;
      
      uint64_t only_blocks = 0;

      uint64_t all_ones_times = 0;
      
      for (uint64_t i=0; i < nBlocks; ++i) {
        if (B[i]) {
          uint64_t u_p = (*(sdsl::sd_vector<> *)P[i]).size();
          uint64_t n_p = (*(sdsl::rank_support_sd<1> *)block_rank[i])(u_p);
          //if(i > 84780) cout << "SD " << i << " " << u_p << " " << n_p << " " << bits_built_sd_vector(u_p, n_p, *(sdsl::sd_vector<> *)P[i]) << "\n";
          size += bits_built_sd_vector(u_p, n_p, *(sdsl::sd_vector<> *)P[i]);
          ef_size += bits_built_sd_vector(u_p, n_p, *(sdsl::sd_vector<> *)P[i]);
          //only_blocks += bits_built_sd_vector(u_p, n_p, *(sdsl::sd_vector<> *)P[i]);
          only_blocks += bits_built_sd_vector_no_select(u_p, n_p);

          //if(i > 9784) cout << "SD " << i << " " << u_p << " " << n_p << " " << bits_sd_vector(u_p, n_p) << "\n";
          //size += bits_sd_vector(u_p, n_p);
          //ef_size += bits_sd_vector(u_p, n_p);
          //only_blocks += bits_sd_vector(u_p, n_p);

          //if(i > 84790) cout << "SD " << i << " " << u_p << " " << n_p << " " << bitsize_elias_fano(u_p, n_p) << "\n";
          //size += bitsize_elias_fano(u_p, n_p);
          //ef_size += bitsize_elias_fano(u_p, n_p);

	        ef_times++;
        } else {
          if (P[i]) {
	          uint64_t u_p = (*(sdsl::bit_vector *)P[i]).size();
            uint64_t n_p = (*(rank_support *)block_rank[i])(u_p);
            //if(i > 84780) cout << "BIT " << i << " " << u_p << " " << n_p << " " << bits_built_bit_vector(u_p, n_p, *(select_support *)block_select[i]) << "\n";
            size += bits_built_bit_vector(u_p, n_p, *(select_support *)block_select[i]);
            bit_size += bits_built_bit_vector(u_p, n_p, *(select_support *)block_select[i]);
            //only_blocks += bits_built_bit_vector(u_p, n_p, *(select_support *)block_select[i]);
            only_blocks += bits_built_bit_vector_no_select(u_p, n_p);
 
            //if(i > 9784) cout << "BIT " << i << " " << u_p << " " << n_p << " " << bits_bit_vector(u_p, n_p) << "\n";
            //size += bits_bit_vector(u_p, n_p);
            //bit_size += bits_bit_vector(u_p, n_p);
            //only_blocks += bits_bit_vector(u_p, n_p);
                       
            //if(i > 84790) cout << "BIT " << i << " " << u_p << " " << n_p << " " << bitsize_plain_bitvector(u_p, n_p) << "\n";
            //size += bitsize_plain_bitvector(u_p, n_p);
            //bit_size += bitsize_plain_bitvector(u_p, n_p);
            bit_times++;
	        } else { 
            all_ones_times++;
          }
        }
      }
      cout << "EF " << ef_times << " BIT " << bit_times << " ALL_ONES " << all_ones_times 
           << " " << ef_size << " " << bit_size << " "
           << (double) ef_size / n << " " << (double) bit_size / n << " "
           << only_blocks << " "
           << (double) only_blocks / n << "\n";
      return size;
    }
    std::pair<std::vector<uint64_t>, uint64_t> optimal_partition(std::vector<uint64_t> &ones_bv, double eps1, double eps2){
      //fixed_cost = 2 * ceil_log2(u) + ceil_log2(n);
      uint64_t single_block_cost = cost_fun(u, n);
      std::vector<uint64_t> min_cost(n+1, single_block_cost);
      min_cost[0] = 0;

      // create the required window: one for each power of approx_factor
      std::vector<cost_window> windows;
      uint64_t cost_lb = cost_fun(1, 1); // minimum cost

      uint64_t cost_bound = cost_lb;

      while (eps1 == 0 || cost_bound < cost_lb / eps1) {
        windows.emplace_back(ones_bv.begin(), cost_bound);
        if (cost_bound >= single_block_cost) break;
        cost_bound = cost_bound * (1 + eps2);
      }

      std::vector<uint64_t> path(n + 1, 0);
        
      for (uint64_t i = 0; i < n; i++) {
        size_t last_end = i + 1;
        for (auto& window: windows) {

          assert(window.start() == i);
          while (window.end() < last_end) {
            window.advance_end();
          }

          uint64_t window_cost;
          while (true) {
            //window.print(i);
            window_cost = cost_fun(window.universe(), window.size());
            //cout << window_cost << "\n";
            if (min_cost[i] + window_cost < min_cost[window.end()]) {
              //window.print(i);
              //cout << window_cost << "\n";
              min_cost[window.end()] = min_cost[i] + window_cost;
              path[window.end()] = i;
            }
            last_end = window.end();
            if (window.end() == n) break;
            if (window_cost >= window.cost_upper_bound()) break;
            window.advance_end();
          }
          window.advance_start();
        }
      }

      uint64_t curr_pos = n;
      std::vector<uint64_t> partition;
      while (curr_pos != 0) {
        partition.push_back(curr_pos);
        curr_pos = path[curr_pos];
      }

      std::reverse(partition.begin(), partition.end());
      uint64_t cost_opt = min_cost[n];

      //print(partition);
      return {partition, cost_opt};
    }

    void add_block(sdsl::bit_vector &block_bv, int64_t type_encoding_block, uint64_t i){
      //all ones
      if(type_encoding_block == 0) {
        B[i] = 0;
        P[i] = NULL; 
        block_select[i] = NULL;
        block_rank[i] = NULL;
      //elias-fano
      } else if(type_encoding_block == 1) {
        B[i] = 1;
        P[i] = new sdsl::sd_vector<>(block_bv);
        block_select[i] = new sdsl::select_support_sd<1>((sdsl::sd_vector<> *)P[i]);
        block_rank[i] = new sdsl::rank_support_sd<1>((sdsl::sd_vector<> *)P[i]);
      //rb
      } else if(type_encoding_block == 2) { 
        B[i] = 0;
        P[i] = new sdsl::bit_vector(block_bv);
        block_select[i] = new select_support((sdsl::bit_vector *)P[i]); 
        block_rank[i] = new rank_support((sdsl::bit_vector *)P[i]); 
      }
    }

    pef_vector_opt(sdsl::bit_vector &bv, double eps1, double eps2) {
      // setup fixed_cost 
      fixed_cost = _fixed_cost;

      select_support select_1(&bv);
      rank_support rank_1(&bv);
      sdsl::bit_vector block_bv;
      std::vector<uint64_t> elements_of_L;
      std::vector<uint64_t> elements_of_E;

      u = bv.size();
      n = rank_1(bv.size());
      std::vector<uint64_t> ones_bv;

      for (uint64_t i = 0; i < n; i++)
        ones_bv.push_back(select_1(i+1));
      //cout << n << " "; 
      //cout << "size sd: " << bitsize_elias_fano(u, n) <<  " " << bitsize_plain_bitvector(u, n) << "\n";
      //----- Optimal partition -----
      pair<std::vector<uint64_t>, uint64_t> ret = optimal_partition(ones_bv, eps1, eps2);
      std::vector<uint64_t> partition = ret.first;
      uint64_t cost_opt = ret.second;
      //-----------------------------

      nBlocks = partition.size(); // OJO, ver esto, el tamaño de ese vector debería ser el número de bloques

      P.resize(nBlocks, NULL);
      block_select.resize(nBlocks, NULL);
      block_rank.resize(nBlocks, NULL);

      B = sdsl::bit_vector(nBlocks, 0);

      uint64_t start = 0;
      uint64_t first_elem = 1;

      uint64_t last_elem, end, size_block, i = 0;
      for(i = 0; i < nBlocks - 1; i++){
        last_elem = partition[i];
        end = select_1(last_elem - 1);
        size_block = end - start + 1;

        block_bv.resize(size_block);
        sdsl::util::set_to_value(block_bv, 0);

        //last element is not include
        uint64_t amount_ones, elem, temp;
        for(elem = first_elem, amount_ones = 0; elem < last_elem; elem++, amount_ones++) {
          temp = select_1(elem);
          block_bv[temp - start] = 1;
        }
        elements_of_L.push_back(temp);
        elements_of_E.push_back(amount_ones + (i == 0 ? 0 : elements_of_E[i - 1]));

        uint64_t type_encoding_block = new_type_encoding(size_block, amount_ones);
        add_block(block_bv, type_encoding_block, i);
        start = end + 1;
        first_elem = partition[i];
      }
      // last block
      last_elem = partition[i];
      end = u;
      size_block = end - start;

      block_bv.resize(size_block);
      sdsl::util::set_to_value(block_bv, 0);

      uint64_t amount_ones, elem, temp;
      for(elem = first_elem, amount_ones = 0; elem <= last_elem; elem++, amount_ones++) {
        temp = select_1(elem);
        block_bv[temp - start] = 1;
      }
      elements_of_L.push_back(temp);
      elements_of_E.push_back(amount_ones + (nBlocks == 1 ? 0 : elements_of_E[i - 1]));
      uint64_t type_encoding_block = new_type_encoding(size_block, amount_ones);
      add_block(block_bv, type_encoding_block, i);

      L = sdsl::sd_vector<>(elements_of_L.begin(), elements_of_L.end());
      sdsl::util::init_support(select_L, &L);
      sdsl::util::init_support(rank_L, &L);

      E = sdsl::sd_vector<>(elements_of_E.begin(), elements_of_E.end());
      sdsl::util::init_support(select_E, &E);
      sdsl::util::init_support(rank_E, &E);
    } 

    pef_vector_opt(std::vector<uint64_t> &pb, uint64_t universe, double eps1, double eps2) {
      // setup fixed_cost 
      fixed_cost = _fixed_cost;

      sdsl::bit_vector block_bv;
      std::vector<uint64_t> elements_of_L;
      std::vector<uint64_t> elements_of_E;

      u = universe;
      n = pb.size();

      //----- Optimal partition -----
      pair<std::vector<uint64_t>, uint64_t> ret = optimal_partition(pb, eps1, eps2);
      std::vector<uint64_t> partition = ret.first;
      uint64_t cost_opt = ret.second;
      //-----------------------------

      nBlocks = partition.size(); // OJO, ver esto, el tamaño de ese vector debería ser el número de bloques
      cout << nBlocks << " " << cost_opt << " " << (double) cost_opt / n << "\n";

      P.resize(nBlocks, NULL);
      block_select.resize(nBlocks, NULL);
      block_rank.resize(nBlocks, NULL);

      B = sdsl::bit_vector(nBlocks, 0);

      uint64_t start = 0;
      uint64_t first_elem = 1;

      uint64_t last_elem, end, size_block, i = 0;
      
      uint64_t nani = 0;
      for(i = 0; i < nBlocks - 1; i++){
        last_elem = partition[i];
        end = pb[last_elem - 1 - 1];
        //cout << last_elem << " "
        size_block = end - start + 1;

        block_bv.resize(size_block);
        sdsl::util::set_to_value(block_bv, 0);

        //last element is not include
        uint64_t amount_ones, elem, temp;
        for(elem = first_elem, amount_ones = 0; elem < last_elem; elem++, amount_ones++) {
          temp = pb[elem - 1];
          block_bv[temp - start] = 1;
        }
        elements_of_L.push_back(temp);
        elements_of_E.push_back(amount_ones + (i == 0 ? 0 : elements_of_E[i - 1]));

        uint64_t type_encoding_block = new_type_encoding(end - pb[first_elem - 1] + 1, amount_ones);
        nani += cost_fun(end - pb[first_elem - 1] + 1, amount_ones);
        //uint64_t type_encoding_block = new_type_encoding(end - start + 1, amount_ones);
        //nani += cost_fun(end - start + 1, amount_ones);

        add_block(block_bv, type_encoding_block, i);
        start = end + 1;
        first_elem = partition[i];
      }
      // last block
      last_elem = partition[i];
      end = u;
      size_block = end - start;

      block_bv.resize(size_block);
      sdsl::util::set_to_value(block_bv, 0);

      uint64_t amount_ones, elem, temp;
      for(elem = first_elem, amount_ones = 0; elem <= last_elem; elem++, amount_ones++) {
        temp = pb[elem - 1];
        block_bv[temp - start] = 1;
      }
      elements_of_L.push_back(temp);
      elements_of_E.push_back(amount_ones + (nBlocks == 1 ? 0 : elements_of_E[i - 1]));
      
      uint64_t type_encoding_block = new_type_encoding(end - pb[first_elem - 1], amount_ones);
      nani += cost_fun(end - pb[first_elem - 1], amount_ones);
      //uint64_t type_encoding_block = new_type_encoding(end - start, amount_ones);
      //nani += cost_fun(end - start, amount_ones);
     
      add_block(block_bv, type_encoding_block, i);
      cout << nBlocks << " " << nani << " " << (double) nani/n << "\n";
      L = sdsl::sd_vector<>(elements_of_L.begin(), elements_of_L.end());
      sdsl::util::init_support(select_L, &L);
      sdsl::util::init_support(rank_L, &L);
    
      E = sdsl::sd_vector<>(elements_of_E.begin(), elements_of_E.end());
      sdsl::util::init_support(select_E, &E);
      sdsl::util::init_support(rank_E, &E);
    } 

    uint64_t select(uint64_t i){
      assert(i <= n);

      uint64_t blk = rank_E(i);
      if (B[blk]) {
        if (blk == 0) {
          return (*(sdsl::select_support_sd<1> *)block_select[blk])(i);
        } else {
          uint64_t i_block = i - select_E(blk);
          return select_L(blk) + 1 + (*(sdsl::select_support_sd<1> *)block_select[blk])(i_block); 
        }
      } else {
        if (P[blk]) {
          if (blk == 0) {
            return (*(select_support *)block_select[blk])(i);
          } else {
            uint64_t i_block = i - select_E(blk);
            return select_L(blk) + 1 + (*(select_support *)block_select[blk])(i_block);
          }
        } else {
          // block is a run of 1s
          if (blk == 0) {
            return (i - 1);
          } else {            
            uint64_t i_block = i - select_E(blk);
            return select_L(blk) + i_block;
          }
        }
      }

      return 0;
    }

    uint64_t rank(uint64_t i){
      if(i >= u) return n_ones();

      uint64_t blk = rank_L(i);
      if(blk == nBlocks) return n_ones();

      uint64_t rank_val = 0;

      if(blk > 0)
        rank_val += select_E(blk);

      if (B[blk]) {
        if(blk == 0){
          rank_val += (*(sdsl::rank_support_sd<1> *)block_rank[blk])(i);
        } else {
          //obtain position in the block
          uint64_t i_block = i - 1 - select_L(blk);
          rank_val += (*(sdsl::rank_support_sd<1> *)block_rank[blk])(i_block);
        }
      } else {
        if (P[blk]) {
          if(blk == 0){
            rank_val += (*(rank_support *)block_rank[blk])(i);
          } else{
            //obtain position in the block
            uint64_t i_block = i - 1 - select_L(blk);
            rank_val += (*(rank_support *)block_rank[blk])(i_block);
          }
        } else {
          // block is a run of 1s
          if(blk == 0){
            rank_val += i;
          } else{
            rank_val += i - 1 - select_L(blk);
          }
        }
      }
      return rank_val;
    }

    uint64_t operator[](uint64_t i){
      //if i >= u doesn't make sense

      uint64_t amount_ones = rank(i + 1);
      if(amount_ones == 0) return 0;

      uint64_t pos_last_one = select(amount_ones);

      if(pos_last_one < i) return 0;
      else return 1; 
    }
  
};

#endif
