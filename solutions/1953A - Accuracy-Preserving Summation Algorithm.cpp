#include <bits/stdc++.h>
using namespace std;

struct FastScanner {
    static const int BUFSZ = 1 << 20;
    int idx = 0, size = 0;
    char buf[BUFSZ];

    inline char readChar() {
        if (idx >= size) {
            size = (int)fread(buf, 1, BUFSZ, stdin);
            idx = 0;
            if (size == 0) return 0;
        }
        return buf[idx++];
    }

    bool readInt(int &out) {
        char c;
        do {
            c = readChar();
            if (!c) return false;
        } while (c <= ' ');
        int sgn = 1;
        if (c == '-') { sgn = -1; c = readChar(); }
        long long x = 0;
        while (c > ' ') {
            x = x * 10 + (c - '0');
            c = readChar();
        }
        out = (int)(x * sgn);
        return true;
    }

    bool readToken(char *s, int maxlen) {
        char c;
        do {
            c = readChar();
            if (!c) return false;
        } while (c <= ' ');
        int n = 0;
        while (c > ' ') {
            if (n + 1 < maxlen) s[n++] = c;
            c = readChar();
        }
        s[n] = 0;
        return true;
    }
};

struct FastOutput {
    static const int BUFSZ = 1 << 22;
    int idx = 0;
    char buf[BUFSZ];

    ~FastOutput() { flush(); }

    inline void flush() {
        if (idx) {
            fwrite(buf, 1, idx, stdout);
            idx = 0;
        }
    }

    inline void putChar(char c) {
        if (idx >= BUFSZ) flush();
        buf[idx++] = c;
    }

    inline void putStr(const char *s) {
        while (*s) putChar(*s++);
    }

    inline void putInt(int x) {
        char tmp[16];
        int n = 0;
        while (x > 0) {
            tmp[n++] = char('0' + (x % 10));
            x /= 10;
        }
        for (int i = n - 1; i >= 0; --i) putChar(tmp[i]);
    }
};

// IEEE-754 half helpers (round-to-nearest-even)
static inline uint16_t float_to_half(float f) {
    uint32_t x;
    memcpy(&x, &f, sizeof(x));

    uint32_t sign = (x >> 31) & 1;
    int32_t exp = (int32_t)((x >> 23) & 0xFF) - 127;
    uint32_t mant = x & 0x7FFFFF;

    uint16_t hs = (uint16_t)(sign << 15);

    if (((x >> 23) & 0xFF) == 0xFF) {
        // inf/nan
        if (mant == 0) return (uint16_t)(hs | 0x7C00);
        return (uint16_t)(hs | 0x7E00);
    }

    if (exp > 15) {
        // overflow -> inf
        return (uint16_t)(hs | 0x7C00);
    }

    if (exp < -14) {
        // subnormal or underflow
        int shift = (-14 - exp);
        if (shift > 24) return hs; // too small -> 0
        uint32_t m = mant | 0x800000; // implicit 1
        // round to nearest-even at bit (shift + 13)
        uint32_t round_bit = 1u << (shift + 12);
        uint32_t sticky_mask = round_bit - 1;
        uint32_t add = round_bit;
        uint32_t v = m + add;
        uint32_t frac = (v >> (shift + 13));
        // tie-to-even adjustment
        bool tie = ((m & (round_bit - 1)) == 0) && ((m & round_bit) != 0);
        if (tie && (frac & 1u)) frac -= 1;
        return (uint16_t)(hs | (uint16_t)frac);
    }

    // normal
    uint16_t he = (uint16_t)(exp + 15);
    uint32_t m = mant;
    // rounding from 23-bit mantissa to 10-bit
    uint32_t round = 0x00001000; // 1<<(13)
    uint32_t v = m + round;
    uint32_t frac = v >> 13;
    // tie-to-even:
    bool tie = ((m & 0x00001FFF) == 0x00001000);
    if (tie && (frac & 1u)) frac -= 1;

    if (frac == 0x400) { // mantissa overflow
        frac = 0;
        he += 1;
        if (he >= 31) return (uint16_t)(hs | 0x7C00);
    }
    return (uint16_t)(hs | (he << 10) | (uint16_t)frac);
}

static inline float half_to_float(uint16_t h) {
    uint32_t sign = (h >> 15) & 1;
    uint32_t exp  = (h >> 10) & 0x1F;
    uint32_t mant = h & 0x3FF;

    uint32_t out;
    if (exp == 0) {
        if (mant == 0) {
            out = sign << 31;
        } else {
            // subnormal
            int e = -14;
            uint32_t m = mant;
            while ((m & 0x400) == 0) { m <<= 1; e--; }
            m &= 0x3FF;
            uint32_t fe = (uint32_t)(e + 127);
            out = (sign << 31) | (fe << 23) | (m << 13);
        }
    } else if (exp == 31) {
        // inf/nan
        out = (sign << 31) | (0xFF << 23) | (mant ? 0x400000 : 0);
    } else {
        uint32_t fe = (exp - 15 + 127);
        out = (sign << 31) | (fe << 23) | (mant << 13);
    }
    float f;
    memcpy(&f, &out, sizeof(f));
    return f;
}

static inline bool finitef(float x) {
    return isfinite((double)x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    FastScanner fs;
    FastOutput fo;

    int N;
    if (!fs.readInt(N)) return 0;

    const int B = 16;
    vector<double> block;
    block.reserve(B);

    fo.putStr("{d:");
    bool firstBlock = true;

    char tok[128];
    int i = 1;
    while (i <= N) {
        block.clear();
        int start = i;
        int end = min(N, start + B - 1);

        for (int j = start; j <= end; j++) {
            fs.readToken(tok, (int)sizeof(tok));
            double x = strtod(tok, nullptr);
            block.push_back(x);
        }

        // reference sum in long double
        long double sum64 = 0;
        for (double x : block) sum64 += (long double)x;

        // simulate fp32 sum
        float acc32 = (float)block[0];
        bool ok32 = finitef(acc32);
        for (int k = 1; k < (int)block.size() && ok32; k++) {
            float v = (float)block[k];
            acc32 = acc32 + v;
            ok32 = finitef(acc32);
        }
        long double sum32 = (long double)acc32;

        // simulate fp16 sum (cast each input to half, add, round to half each step)
        uint16_t hacc = float_to_half((float)block[0]);
        float facc = half_to_float(hacc);
        bool ok16 = isfinite((double)facc);
        for (int k = 1; k < (int)block.size() && ok16; k++) {
            uint16_t hv = float_to_half((float)block[k]);
            float fv = half_to_float(hv);
            float s = facc + fv;
            uint16_t hs = float_to_half(s);
            facc = half_to_float(hs);
            ok16 = isfinite((double)facc);
        }
        long double sum16 = (long double)facc;

        long double scale = fabsl(sum64);
        if (scale < 1e-30L) scale = 1e-30L;

        long double err16 = ok16 ? fabsl(sum16 - sum64) : 1e300L;
        long double err32 = ok32 ? fabsl(sum32 - sum64) : 1e300L;

        // choose type conservatively
        char t;
        if (ok16 && err16 <= 1e-4L * scale) t = 'h';
        else if (ok32 && err32 <= 1e-7L * scale) t = 's';
        else t = 'd';

        if (!firstBlock) fo.putChar(',');
        firstBlock = false;

        fo.putChar('{');
        fo.putChar(t);
        fo.putChar(':');
        for (int j = start; j <= end; j++) {
            if (j != start) fo.putChar(',');
            fo.putInt(j);
        }
        fo.putChar('}');

        i = end + 1;
    }

    fo.putChar('}');
    fo.putChar('\n');
    return 0;
}
