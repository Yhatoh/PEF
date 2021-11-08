#ifndef PEF_OPT
#define PEF_OPT

#include <vector>
#include <sdsl/vectors.hpp>
#include <sdsl/bit_vectors.hpp>
#include <cinttypes>
#include <assert.h> 

using namespace std;
using namespace sdsl;

class cost_window 
{
    std::vector<uint64_t>::iterator start_it;
    std::vector<uint64_t>::iterator end_it;
    uint64_t start;
    uint64_t end; // end-th position is not in the current window
    uint64_t min_p; // element that preceed the first element of the window
    uint64_t max_p;

    uint64_t cost_upper_bound; // The maximum cost for this window

    cost_window(std::vector<uint64_t>::iterator begin, uint64_t _cost_upper_bound) 
    {
        start_it = begin;
        end_it = begin;
        min_p = *begin;
        max_p = 0;
        cost_upper_bound = _cost_upper_bound;
    }

    uint64_t universe() const
    {
        return max_p - min_p + 1;
    }

    uint64_t size() const
    {
        return end - start;
    }

    void advance_start()
    {
        min_p = *start_it + 1;
        ++start;
        ++start_it;
    }

    void advance_end()
    {
        max_p = *end_it;
        ++end;
        ++end_it;
    }

    uint64_t start()
    {
        return start;
    }

    uint64_t end() 
    {
        return end;
    }

    uint64_t cost_upper_bound()
    {
        return cost_upper_bound;
    }

};



static const uint64_t type_bits = 1; // all_ones is implicit

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

// return the position of the single bit set in the word x
inline uint8_t bit_position(uint64_t x)
{
    assert(popcount(x) == 1);
    return detail::debruijn64_mapping[(x * detail::debruijn64) >> 58];
}


inline uint8_t msb(uint64_t x, unsigned long& ret)
{
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


inline uint8_t msb(uint64_t x)
{
    unsigned long ret = -1U;
    msb(x, ret);
    return (uint8_t)ret;
}


inline uint64_t ceil_log2(const uint64_t x) 
{
    return (x > 1) ? msb(x - 1) + 1 : 0;
}


uint64_t bitsize_elias_fano(uint64_t universe, uint64_t n)
{
    uint64_t log_sampling0 = 9; // cuidado con esto
    uint64_t log_sampling1 = 8; // cuidado con esto
    uint64_t lower_bits = universe > n ? msb(universe / n) : 0;

    //uint64_t mask = (uint64_t(1) << lower_bits) - 1;
    // pad with a zero on both sides as sentinels
    uint64_t higher_bits_length = n + (universe >> lower_bits) + 2;
    uint64_t pointer_size = ceil_log2(higher_bits_length);
    uint64_t pointers0 = (higher_bits_length - n) >> log_sampling0;                
    uint64_t pointers1 = n >> log_sampling1;
    uint64_t pointers0_offset = 0; //(base_offset)
    uint64_t pointers1_offset = pointers0_offset + pointers0 * pointer_size;
    uint64_t higher_bits_offset = pointers1_offset + pointers1 * pointer_size;
    uint64_t lower_bits_offset = higher_bits_offset + higher_bits_length;
    return lower_bits_offset + n * lower_bits;
}


uint64_t bitsize_plain_bitvector(uint64_t universe, uint64_t n)
{
    log_rank1_sampling = 9; // cuidado con esto
    log_sampling1 = 8;      // cuidado con esto
    rank1_sample_size = ceil_log2(n + 1);
    pointer_size = ceil_log2(universe);
    rank1_samples = universe >> log_rank1_sampling;
    pointers1 = n >> log_sampling1;
    rank1_samples_offset


            , rb_log_rank1_sampling(9)
            , rb_log_sampling1(8)
            , log_partition_size(7)


                , rank1_sample_size(ceil_log2(n + 1))
                , pointer_size(ceil_log2(universe))
                , rank1_samples(universe >> params.rb_log_rank1_sampling)
                , pointers1(n >> params.rb_log_sampling1)

                , rank1_samples_offset(base_offset)
                , pointers1_offset(rank1_samples_offset + rank1_samples * rank1_sample_size)
                , bits_offset(pointers1_offset + pointers1 * pointer_size)
                , end(bits_offset + universe)

}



uint64_t bitsize(uint64_t universe, uint64_t n)
{
    uint64_t best_cost;

    // the sequence has all 1s? --> 0 bits; otherwise, +infty
    best_cost  = (universe == n) ? 0 : uint64_t(-1);


    uint64_t ef_cost = bitsize_elias_fano(universe, n) + type_bits;
    if (ef_cost < best_cost) {
        best_cost = ef_cost;
    }

    uint64_t rb_cost = bitsize_plain_bitvector(params, universe, n) + type_bits;
    if (rb_cost < best_cost) {
        best_cost = rb_cost;
    }

    return best_cost;
}



uint64_t cost_fun(uint64_t universe, uint64_t n) 
{
    return indexed_sequence::bitsize(params, universe, n) + conf.fix_cost;  // esto último es 64? Ver, me parece que en general no.
};




//template<uint64_t b=256>
class pef_vector_opt
{
    sdsl::sd_vector<> L;
    sdsl::select_support_sd<1> select_L;

    std::vector<void *> P;  // pointer to the block encoding
    sdsl::bit_vector B; // bit vector indicating the encoding of each block.
    // B[i] == 0 && P[i] == NULL -> All ones in block
    // B[i] == 0 && P[i] != NULL -> Plain bit vector encoding of the block
    // B[i] == 1                 -> Elias-Fano encoding ob the block
    std::vector<void *> block_select;

    uint64_t u; // universe size  (bitvector length)
    uint64_t n; // set size (number of 1s in the bitvector)
    uint64_t nBlocks; 
    
public:

    pef_vector_opt() {;}

    ~pef_vector_opt() {;}

    uint64_t size()
    {
        return u;
    }

    uint64_t n_ones()
    {
        return n;
    }

    uint64_t size_in_bytes()
    {
        uint64_t size = sdsl::size_in_bytes(L) + sdsl::size_in_bytes(select_L) 
                      + sdsl::size_in_bytes(B) + 3*sizeof(uint64_t) 
                      + nBlocks*sizeof(void *);
        
	for (uint64_t i=0; i<nBlocks; ++i) {
	    if (B[i]) {
	        size += sdsl::size_in_bytes(*(sd_vector<> *)P[i]) + sdsl::size_in_bytes(*(select_support_sd<1> *)block_select[i]);
	    }
	    else {
	        if (P[i]) {
		    size += sdsl::size_in_bytes(*(bit_vector *)P[i]) + sdsl::size_in_bytes(*(select_support_scan<1> *)block_select[i]);
		}
	    }
	}

        return size;
    }



    pef_vector_opt(sdsl::bit_vector &bv, float eps1, float eps2) {
        sdsl::select_support_mcl<1> select_1(&bv);
        sdsl::rank_support_v<1> rank_1(&bv);
        sdsl::bit_vector block_bv;
        std::vector<uint64_t> elements_of_L;

        u = bv.size();
        n = rank_1(bv.size());

        std::vector<uint64_t> ones_bv;

        for (uint64_t i = 0; i < n; i++)
            ones_bv.push_back(select_1(i+1));

        

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
                    window_cost = cost_fun(window.universe(), window.size());
                    if ((min_cost[i] + window_cost < min_cost[window.end()])) {
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
        cost_opt = min_cost[n];

        nBlocks = partition.size(); // OJO, ver esto, el tamaño de ese vector debería ser el número de bloques

        P.resize(nBlocks, NULL);
        block_select.resize(nBlocks, NULL);

        B = bit_vector(nBlocks, 0);        



    } 


};

#endif
