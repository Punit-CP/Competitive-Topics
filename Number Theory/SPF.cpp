// M-1
// spf using Euler's Sieve (Linear Sieve):
// TC. O(N)

const int N = 15 * 1e6 + 1;
vector<bool> isPrime(N, true);
vector<int> spf(N);
vector<int> primes;
void initSieve()
{
    for (int i = 2; i <= N; ++i) {
    if (spf[i] == 0) {
        spf[i] = i;
        primes.push_back(i);
    }
    for (int p : primes) {
        if (p > spf[i] || i * p > N) break;
        spf[i * p] = p;
    }
}

initSieve(); // call this in main function




// M-2 
// TC. O(NlogN)
const int N = 1e6 + 1;
vector<bool> isPrime(N, true);
vector<int> spf(N);

void initSieve()
{
    isPrime[0] = false, isPrime[1] = false;
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i <= N; i++)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= N; j += i)
            {
                isPrime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

initSieve(); // call this in main function


// or
vector<int> spf;
void sieve(int n)
{
    spf.assign(n + 1, 0);
    for (int i = 2; i <= n; ++i)
    {
        if (spf[i] == 0)
        {
            for (int j = i; j <= n; j += i)
            {
                if (spf[j] == 0)
                    spf[j] = i;
            }
        }
    }
}
sieve(1e5 + 1);
