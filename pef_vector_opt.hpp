#ifndef PEF_OPT
#define PEF_OPT

#include <vector>
#include <utility>
#include <sdsl/vectors.hpp>
#include <sdsl/bit_vectors.hpp>
#include <cinttypes>
#include <assert.h> 


using namespace std;
using namespace sdsl;

class cost_window {
  
  public:
    std::vector<uint64_t>::iterator _start_it;
    std::vector<uint64_t>::iterator _end_it;
    uint64_t _start = 0;
    uint64_t _end = 0; // end-th position is not in the current window
    uint64_t _min_p = 0; // element that preceed the first element of the window
    uint64_t _max_p = 0;

    uint64_t _cost_upper_bound; // The maximum cost for this window

    cost_window(std::vector<uint64_t>::iterator begin, uint64_t __cost_upper_bound) {
      _start_it = begin;
      _end_it = begin;
      _min_p = *begin;
      _max_p = 0;
      _cost_upper_bound = __cost_upper_bound;
    }

    uint64_t universe() const {
      return _max_p - _min_p + 1;
    }

    uint64_t size() const {
      return _end - _start;
    }

    void advance_start() {
      _min_p = *_start_it + 1;
      ++_start;
      ++_start_it;
    }

    void advance_end() {
      _max_p = *_end_it;
      ++_end;
      ++_end_it;
    }

    uint64_t start() {
      return _start;
    }

    uint64_t end() {
      return _end;
    }

    uint64_t cost_upper_bound() {
      return _cost_upper_bound;
    }

    void print(uint64_t i) {
      cout << "window " << i << ": " 
           << _start << " " 
           << _end << " " 
           << _min_p << " " 
           << _max_p << " "  
           << _cost_upper_bound << "\n";
    }
};

static const uint64_t type_bits = 1; // all_ones is implicit

// from succint repository
static const uint8_t debruijn64_mapping[64] = {
  63,  0, 58,  1, 59, 47, 53,  2,
  60, 39, 48, 27, 54, 33, 42,  3,
  61, 51, 37, 40, 49, 18, 28, 20,
  55, 30, 34, 11, 43, 14, 22,  4,
  62, 57, 46, 52, 38, 26, 32, 41,
  50, 36, 17, 19, 29, 10, 13, 21,
  56, 45, 25, 31, 35, 16,  9, 12,
  44, 24, 15,  8, 23,  7,  6,  5
};

static const uint64_t debruijn64 = 0x07EDD5E59A4E28C2ULL;

// return the position of the single bit set in the word x
inline uint8_t bit_position(uint64_t x){
    assert(popcount(x) == 1);
    return debruijn64_mapping[(x * debruijn64) >> 58];
}

inline uint8_t msb(uint64_t x, unsigned long& ret){
  if (!x) {
    return false;
  }

  // right-saturate the word
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  x |= x >> 32;

  // isolate the MSB
  x ^= x >> 1;
  ret = bit_position(x);

  return true;
}
 
inline uint8_t msb(uint64_t x){
  unsigned long ret = -1U;
  msb(x, ret);
  return (uint8_t)ret;
}



inline uint64_t ceil_log2(uint64_t x) {

  return (x > 1) ? msb(x - 1) + 1 : 0;
}

// bitsize calculator for plain bit vector in https://github.com/ot/partitioned_elias_fano
uint64_t bitsize_plain_bitvector(uint64_t universe, uint64_t n){
  // global parameters
  //uint64_t rb_log_rank1_sampling = 9; // cuidado con esto
  //uint64_t rb_log_sampling1 = 8; // cuidado con esto

  //uint64_t log_rank1_sampling = rb_log_rank1_sampling; // cuidado con esto
  //uint64_t log_sampling1 = rb_log_sampling1; // cuidado con esto

  //uint64_t rank1_sample_size = ceil_log2(n + 1);
  //uint64_t pointer_size = ceil_log2(universe);
  //uint64_t rank1_samples = universe >> log_rank1_sampling;
  //uint64_t pointers1 = n >> log_sampling1;
  //uint64_t rank1_samples_offset = 0;
  //uint64_t pointers1_offset = rank1_samples_offset + rank1_samples * rank1_sample_size;
  //uint64_t bits_offset = pointers1_offset + pointers1 * pointer_size;

  //return bits_offset + universe;
  return 64 * (1 + ((universe - 1) / 64) + 1) + 0.2 * universe + 0.0625 * universe;
}

// bitsize calculator for elias fano in https://github.com/ot/partitioned_elias_fano
uint64_t bitsize_elias_fano(uint64_t universe, uint64_t n){
  //global parameters
  //uint64_t ef_log_sampling0 = 9; // cuidado con esto
  //uint64_t ef_log_sampling1 = 8; // cuidado con esto
  //uint64_t log_sampling0 = ef_log_sampling0;
  //uint64_t log_sampling1 = ef_log_sampling1;
  //uint64_t lower_bits = universe > n ? msb(universe / n) : 0;
  //uint64_t mask = (((uint64_t) 1) << lower_bits) - 1;
  //uint64_t higher_bits_length = n + (universe >> lower_bits) + 2;
  //uint64_t pointer_size = ceil_log2(higher_bits_length);
  //uint64_t pointers0 = (higher_bits_length - n) >> log_sampling0;
  //uint64_t pointers1 = (n >> log_sampling1);
  //uint64_t pointers0_offset = 0;
  //uint64_t pointers1_offset = (pointers0_offset + pointers0 * pointer_size);
  //uint64_t higher_bits_offset = pointers1_offset + pointers1 * pointer_size;
  //uint64_t lower_bits_offset = higher_bits_offset + higher_bits_length;

  //return lower_bits_offset + n * lower_bits;
  return n * (2 + ceil_log2((universe / n))) + 128;
}

// best bitsize function in https://github.com/ot/partitioned_elias_fano
uint64_t bitsize(uint64_t universe, uint64_t n){
  uint64_t best_cost;

  // the sequence has all 1s? --> 0 bits; otherwise, +infty
  best_cost  = (universe == n) ? 0 : uint64_t(-1);
  //cout << "universe: " << universe << " n: " << n << " ";

  uint64_t ef_cost = bitsize_elias_fano(universe, n) + type_bits;
  if (ef_cost < best_cost) {
    best_cost = ef_cost;
  }

  uint64_t rb_cost = bitsize_plain_bitvector(universe, n) + type_bits;
  if (rb_cost < best_cost) {
    best_cost = rb_cost;
  }
  //cout << ef_cost << " " << rb_cost << "\n";
  return best_cost;
}

uint64_t type_encoding(uint64_t universe, uint64_t n){
  uint64_t best_cost;
  uint64_t type;

  // the sequence has all 1s? --> 0 bits; otherwise, +infty
  //cout << "universe: " << universe << " n: " << n << " "; 
  best_cost  = (universe == n) ? 0 : uint64_t(-1);
  type = 0;

  uint64_t ef_cost = bitsize_elias_fano(universe, n) + type_bits;
  if (ef_cost < best_cost) {
    best_cost = ef_cost;
    type = 1;
  }

  uint64_t rb_cost = bitsize_plain_bitvector(universe, n) + type_bits;
  if (rb_cost < best_cost) {
    best_cost = rb_cost;
    type = 2;
  }

  return type;
}

// cost fun in github https://github.com/ot/partitioned_elias_fano
uint64_t cost_fun(uint64_t universe, uint64_t n) {
  // estimated best cost + fix cost
  return bitsize(universe, n) + 196; // config.fix_cost;  // esto último es 64? Ver, me parece que en general no.
};

void print(vector< uint64_t > &v){
  uint64_t i;
  for(i = 0; i < ((uint64_t) v.size()) - 1; i++){
    cout << v[i] << " ";
  }
  cout << v[i] << "\n";
}

template<class rank_support=rank_support_scan<1>, class select_support=select_support_scan<1>>
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
      uint64_t size = sdsl::size_in_bytes(L) + sdsl::size_in_bytes(select_L)
                    + sdsl::size_in_bytes(rank_L)
                    + sdsl::size_in_bytes(E) + sdsl::size_in_bytes(select_E)
                    + sdsl::size_in_bytes(rank_E)
                    + sdsl::size_in_bytes(B) + 3 * sizeof(uint64_t) 
                    + nBlocks * sizeof(void *);
      
      for (uint64_t i=0; i < nBlocks; ++i) {
        if (B[i]) {
          size += sdsl::size_in_bytes(*(sd_vector<> *)P[i]) ;
                //+ sdsl::size_in_bytes(*(select_support_sd<1> *)block_select[i])
                //+ sdsl::size_in_bytes(*(rank_support_sd<1> *)block_rank[i]);
        } else {
          if (P[i]) {
            size += sdsl::size_in_bytes(*(bit_vector *)P[i]); 
                  //+ sdsl::size_in_bytes(*(select_support *)block_select[i])
                  //+ sdsl::size_in_bytes(*(rank_support *)block_rank[i]);
          }
        }
      }

      return size;
    }

    std::pair<std::vector<uint64_t>, uint64_t> optimal_partition(std::vector<uint64_t> &ones_bv, double eps1, double eps2){
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
          while (window._end < last_end) {
            window.advance_end();
          }

          uint64_t window_cost;
          while (true) {
            //window.print(i);
            window_cost = cost_fun(window.universe(), window.size());
            //cout << window_cost << "\n";
            if (min_cost[i] + window_cost < min_cost[window.end()]) {
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
        P[i] = new sd_vector<>(block_bv);
        block_select[i] = new select_support_sd<1>((sd_vector<> *)P[i]);
        block_rank[i] = new rank_support_sd<1>((sd_vector<> *)P[i]);
      //rb
      } else if(type_encoding_block == 2) { 
        B[i] = 0;
        P[i] = new bit_vector(block_bv);
        block_select[i] = new select_support((bit_vector *)P[i]); 
        block_rank[i] = new rank_support((bit_vector *)P[i]); 
      }
    }

    pef_vector_opt(sdsl::bit_vector &bv, double eps1, double eps2) {
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
      cout << n << " "; 
      cout << "size sd: " << bitsize_elias_fano(u, n) <<  " " << bitsize_plain_bitvector(u, n) << "\n";
      //----- Optimal partition -----
      pair<std::vector<uint64_t>, uint64_t> ret = optimal_partition(ones_bv, eps1, eps2);
      std::vector<uint64_t> partition = ret.first;
      uint64_t cost_opt = ret.second;
      //-----------------------------

      nBlocks = partition.size(); // OJO, ver esto, el tamaño de ese vector debería ser el número de bloques

      P.resize(nBlocks, NULL);
      block_select.resize(nBlocks, NULL);
      block_rank.resize(nBlocks, NULL);

      B = bit_vector(nBlocks, 0);

      uint64_t start = 0;
      uint64_t first_elem = 1;

      uint64_t last_elem, end, size_block, i;
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

        uint64_t type_encoding_block = type_encoding(elem - first_elem + 1, amount_ones);
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
      uint64_t type_encoding_block = type_encoding(elem - first_elem + 1, amount_ones);
      add_block(block_bv, type_encoding_block, i);

      L = sd_vector<>(elements_of_L.begin(), elements_of_L.end());
      util::init_support(select_L, &L);
      util::init_support(rank_L, &L);

      E = sd_vector<>(elements_of_E.begin(), elements_of_E.end());
      util::init_support(select_E, &E);
      util::init_support(rank_E, &E);
    } 

    pef_vector_opt(std::vector<uint64_t> &pb, uint64_t universe, double eps1, double eps2) {
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
      cout << nBlocks << " " << cost_opt << "\n";

      P.resize(nBlocks, NULL);
      block_select.resize(nBlocks, NULL);
      block_rank.resize(nBlocks, NULL);

      B = bit_vector(nBlocks, 0);

      uint64_t start = 0;
      uint64_t first_elem = 1;

      uint64_t last_elem, end, size_block, i;
      for(i = 0; i < nBlocks - 1; i++){
        last_elem = partition[i];
        end = pb[last_elem - 1 - 1];
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

        uint64_t type_encoding_block = type_encoding(elem - first_elem + 1, amount_ones);
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
      uint64_t type_encoding_block = type_encoding(elem - first_elem + 1, amount_ones);
      add_block(block_bv, type_encoding_block, i);

      L = sd_vector<>(elements_of_L.begin(), elements_of_L.end());
      util::init_support(select_L, &L);
      util::init_support(rank_L, &L);

      E = sd_vector<>(elements_of_E.begin(), elements_of_E.end());
      util::init_support(select_E, &E);
      util::init_support(rank_E, &E);
    } 

    uint64_t select(uint64_t i){
      assert(i <= n);

      uint64_t blk = rank_E(i);
      if (B[blk]) {
        if (blk == 0) {
          return (*(select_support_sd<1> *)block_select[blk])(i);
        } else {
          uint64_t i_block = i - select_E(blk);
          return select_L(blk) + 1 + (*(select_support_sd<1> *)block_select[blk])(i_block); 
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
          rank_val += (*(rank_support_sd<1> *)block_rank[blk])(i);
        } else {
          //obtain position in the block
          uint64_t i_block = i - 1 - select_L(blk);
          rank_val += (*(rank_support_sd<1> *)block_rank[blk])(i_block);
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
