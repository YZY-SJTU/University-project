#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// include SSE intrinsics
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <x86intrin.h>
#endif


#define CLOCK_RATE_GHZ 2.26e9

static __inline__ uint64_t RDTSC()
{
    uint32_t hi, lo;
    __asm__ volatile
	(
		"rdtsc"
		: "=a"(lo), "=d"(hi)
	);
	return (((uint64_t)hi) << 32) | ((uint64_t)lo);
}

static int sum_naive(int n, int *a)
{
    int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}
	return sum;
}

static int sum_unrolled(int n, int *a)
{
    int sum = 0;

    // unrolled loop
	for (int i = 0; i < n / 4 * 4; i += 4)
    {
        sum += a[i+0];
        sum += a[i+1];
        sum += a[i+2];
        sum += a[i+3];

    }

    // tail case
	for (int i = n / 4 * 4; i < n; i++)
	{
		sum += a[i];
	}

    return sum;
}

/*static int sum_vectorized(int n, int *a)//only a 32-bit integer in a __128i
{
    // WRITE YOUR VECTORIZED CODE HERE
	int A[4] = {0, 0, 0, 0};
	__m128i sum = _mm_setzero_si128();
	//__m128i sum = _mm_loadu_si128(A);
	//loop	part
	for (int i = 0; i < n; i += 1)
	{
		__m128i tmp = _mm_loadu_si128(a + i);
		sum = _mm_add_epi32(sum, tmp);	
	}
	_mm_storeu_si128(A, sum);
	int res = A[0];
    return res;
}*/

static int sum_vectorized(int n, int *a)
{
    // WRITE YOUR VECTORIZED CODE HERE
	int A[4] = {0, 0, 0, 0};
	__m128i sum = _mm_setzero_si128();
	//__m128i sum = _mm_loadu_si128(A);
	//loop	part
	for (int i = 0; i < n / 4 * 4; i += 4)
	{
		__m128i tmp = _mm_loadu_si128(a + i);
		sum = _mm_add_epi32(sum, tmp);	
	}
	_mm_storeu_si128(A, sum);
	int res = A[0] + A[1] + A[2] + A[3];

	//tail	part
	for (int i = n / 4 * 4; i < n; i++)
		res += a[i];
    return res;
}

static int sum_vectorized_unrolled(int n, int *a)
{
    // UNROLL YOUR VECTORIZED CODE HERE
	int A[4] = {0, 0, 0, 0};
	__m128i sum1 = _mm_setzero_si128();
	__m128i sum2 = _mm_setzero_si128();
	__m128i sum3 = _mm_setzero_si128();
	__m128i sum4 = _mm_setzero_si128();
	//__m128i sum = _mm_loadu_si128(A);
	//loop	part
	for (int i = 0; i < n / 16 * 16; i += 16)
	{
		__m128i tmp1 = _mm_loadu_si128(a + i);
		__m128i tmp2 = _mm_loadu_si128(a + i + 4);
		__m128i tmp3= _mm_loadu_si128(a + i + 8);
		__m128i tmp4 = _mm_loadu_si128(a + i + 12);
		sum1 = _mm_add_epi32(sum1, tmp1);
		sum2 = _mm_add_epi32(sum2, tmp2);	
		sum3 = _mm_add_epi32(sum3, tmp3);	
		sum4 = _mm_add_epi32(sum4, tmp4);		
	}
	sum1 = _mm_add_epi32(sum1, sum2);
	sum1 = _mm_add_epi32(sum1, sum3);
	sum1 = _mm_add_epi32(sum1, sum4);
	_mm_storeu_si128(A, sum1);
	int res = A[0] + A[1] + A[2] + A[3];

	//tail	part
	for (int i = n / 16 * 16; i < n; i++)
		res += a[i];
    return res;
}

void benchmark(int n, int *a, int(*computeSum)(int, int*), char *name)
{
    // warm up cache
    int sum = computeSum(n, a);

    // measure
    uint64_t beginCycle = RDTSC();
    sum += computeSum(n, a);
	uint64_t cycles = RDTSC() - beginCycle;

    double microseconds = cycles/CLOCK_RATE_GHZ*1e6;

    // print results
	printf("%20s: ", name);
	if (sum == 2 * sum_naive(n, a))
	{
		printf("%.2f microseconds\n", microseconds);
	}
	else
	{
		printf("ERROR!\n");
	}
}

int main(int argc, char **argv)
{
    const int n = 9999;

    // initialize the array with random values
	srand48(time(NULL));
	int a[n] __attribute__((aligned(16)));
	for (int i = 0; i < n; i++)
	{
		a[i] = lrand48();
	}

    // benchmark series of codes
	benchmark(n, a, sum_naive, "naive");
	benchmark(n, a, sum_unrolled, "unrolled");
	benchmark(n, a, sum_vectorized, "vectorized");
	benchmark(n, a, sum_vectorized_unrolled, "vectorized unrolled");

    return 0;
}
