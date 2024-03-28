Years ago I created ![VSDB, a vectorspace database](https://github.com/bigattichouse/vectorspace) for document similarity search and clustering. I'm slowly working on reorganizing it into a RAG tool for LLMs, which includes rethinking some things about it operates, and
deciding if I want to continue to work on it in C, or switch to a newer language.  The beast was built organinically as I learned about term vectorspaces, so it's a bit of a hot mess for anyone.  I mostly use it for research.

VSBD allows vectors in the queries to have any number of dimensions, which are represented by a hash id. This allows the hashes to be meaningful (ex: MD5("House")=1 ) or even represent object properties ( ex: MD5("BOOK_METADATA_PAGES")=235 ).  I use indicies to speed up comparisons, and it's generally very fast.

Recently I read about LLMs using 1.58bit quantization (-1,0,1), and a small mention of 0.68bit quantization (which, using the log ruil I believe represents 0,1), so I decided to pull out the relevant parts of VSDB into two programs, write something up and see if it works.

It does work, but has some caveats.

Here's the basis of where I landed. Just take the signs for given dimensions and convert to 1s and zeros. You'll notice that this is pretty much XNOR operations.

```
- * - = +   00 > 1
+ * - = -   10 > 0
- * + = -   01 > 0
+ * + = +   11 > 1
```

Here's a fairly simple representation of how we build similarity:
```
01011111
01101100
++--++-- = 50% similarity

+ = match, - = opposite
```

so XNOR, count the 1's, divide by number of places. WAY faster than the cosine.

Let's call it '"bit similarity"



I tried various algos

Population count.
[https://en.wikipedia.org/wiki/Hamming_weight]

granted, a simple 4 bit lookup makes the problem smaller. O(1)
then just write it out for 64k or something for 8 bits. fast fast
0000 = 0
0001 = 1
0010 = 1
0011 = 2

Then just look it up. 8 bits would cover quite a bit, can break a problem into pieces easily in C
some 64bit integer > 8X8bit words in C, lookup from 64k map... four operations per int.

 int BitCount(unsigned int u)
    {
         unsigned int uCount;

         uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
         return ((uCount + (uCount >> 3)) & 030707070707) % 63;
    }

From: [https://web.archive.org/web/20151229003112/http://blogs.msdn.com/b/jeuge/archive/2005/06/08/hakmem-bit-count.aspx]
[Explained: https://tekpool.wordpress.com/category/bit-count/]
