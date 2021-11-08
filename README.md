# PEF

## PEF Uniform

### rank operation

Description: Given an position `i`, do `rank(i)`

The rank operation first at all have to do a rank in the vector `L` to know in which block the bit `i` is.

Then, if the block is not the first block, have to sum $b$ ones times the numbers of block before the actual block, this is because before of this block there is $b$ ones for each block.

Thenk, depending of the value of `B[blk]` and `P[blk]` will use differente rank operation:

* if `B[blk] = 1` the block use Elias-Fano Encoding, so we will use rank operation to that encoding, then:
  * if the block is the first block can do the operation rank with the value of `i`
  * if the block is not the first block, then have to know the position of the `i` bit in that block, to do that have to do the difference between `i - 1` and the result of a select in `L` with the value of the block, to know what was the position of the last `1` from the previous block, and finally we can do rank with that value
* if `B[blk] = 0 && P[blk] != NULL` the block use a plan bit vector encoding, so we will use rank operation to that encoding, then:
  * if the block is the first block can do the operation rank with the value of `i`
  * if the block is not the first block, then have to know the position of the `i` bit in that block, to do that have to do the difference between `i - 1` and the result of a select in `L` with the value of the block, to know what was the position of the last `1` from the previous block, and finally we can do rank with that value
* if `B[blk] = 0 && P[blk] == NULL` the block is full of ones, then:
  * if the block is the first block the result of the rank is just `i`
  * if the block is not the first block, have to now the position of the `i` bit in that block, to do that have to do the difference between `i - 1` and the result of a select in `L` with the value of the block, to know what was the position of the last `1` from the previous block, and the rank of in that block will be that value.
