
#include <bits/stdc++.h>
#include <sys/mman.h>
#include <sys/stat.h>

// ---------------------------------------------------------------
// Fast mmap‑based reader / buffered writer (from the __yzlf code)
// ---------------------------------------------------------------
namespace fastio {
using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;

constexpr std::size_t BUF_DEF_SIZE       = 262144;
constexpr std::size_t BUF_FLUSH_THRESHOLD = 32;
constexpr u64 E16 = 10000000000000000ULL;
constexpr u64 E12 = 1000000000000ULL;
constexpr u64 E8  = 100000000ULL;
constexpr u64 E4  = 10000ULL;

struct _io_t {
    u8  t_i[1 << 15];          // two‑digit decode table
    u32 t_o[10000];            // four ASCII digits packed in u32
    constexpr _io_t() : t_i{}, t_o{} {
        std::fill(t_i, t_i + (1 << 15), u8(-1));
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                t_i[0x3030 + 256 * j + i] = j + 10 * i;
        int idx = 0;
        for (int e0 = (48 << 0); e0 < (58 << 0); e0 += (1 << 0))
            for (int e1 = (48 << 8); e1 < (58 << 8); e1 += (1 << 8))
                for (int e2 = (48 << 16); e2 < (58 << 16); e2 += (1 << 16))
                    for (int e3 = (48 << 24); e3 < (58 << 24); e3 += (1 << 24))
                        t_o[idx++] = e0 ^ e1 ^ e2 ^ e3;
    }
    constexpr void get(char* s, u32 p) const { *reinterpret_cast<u32*>(s) = t_o[p]; }
};
constexpr _io_t _iot{};

struct Reader {
    char* bg;
    char* p;
    char* ed;
    explicit Reader(FILE* f = stdin) {
        int fd = fileno(f);
        struct stat st; fstat(fd, &st);
        bg = static_cast<char*>(mmap(nullptr, st.st_size + 4, PROT_READ, MAP_PRIVATE, fd, 0));
        madvise(bg, st.st_size + 4, MADV_SEQUENTIAL);
        p  = bg;
        ed = bg + st.st_size;
    }
    ~Reader() = default; // OS will clean the mapping

    inline void skip_space() { while (*p <= ' ') ++p; }

    template <typename T>
    Reader& operator>>(T& x) {
        skip_space(); bool neg = false;
        if constexpr (std::is_signed_v<T>) { neg = (*p == '-'); p += neg; }
        x = *p++ - '0';
        while (true) {
            u32 y = _iot.t_i[*reinterpret_cast<u16*>(p)];
            if (y > 99) break;
            x = x * 100 + y; p += 2;
        }
        if (*p > ' ') x = x * 10 + (*p++ & 15);
        if (neg) x = -x; return *this;
    }
};

struct Writer {
    char* bg; char* p; char* ed; FILE* f;
    explicit Writer(FILE* fi = stdout, std::size_t sz = BUF_DEF_SIZE) : f(fi) {
        bg = new char[sz]; p = bg; ed = bg + sz - BUF_FLUSH_THRESHOLD;
    }
    ~Writer() { flush(); delete[] bg; }
    inline void flush() { fwrite(bg, 1, p - bg, f); p = bg; }
    inline void chk() { if (p > ed) flush(); }

    inline void put_block(u32 x) { _iot.get(p, x); p += 4; }

    inline void put2(u32 x) {
        if (x > 9) { _iot.get(p, x * 100); p += 2; }
        else *p++ = char('0' + x);
    }
    inline void put4(u32 x) {
        if (x > 99) { if (x > 999) put_block(x); else { _iot.get(p, x * 10); p += 3; } }
        else put2(x);
    }
    inline void write_u32(u32 x) {
        if (x >= E8) { put2(x / E8); x %= E8; put_block(x / E4); put_block(x % E4); }
        else if (x >= E4) { put4(x / E4); put_block(x % E4); }
        else put4(x);
        chk();
    }
    inline void write_u64(u64 x) {
        if (x >= E8) {
            u64 q0 = x / E8, r0 = x % E8;
            if (x >= E16) { u64 q1 = q0 / E8, r1 = q0 % E8; put4(q1); put_block(r1 / E4); put_block(r1 % E4); }
            else if (x >= E12) { put4(q0 / E4); put_block(q0 % E4); }
            else put4(q0);
            put_block(r0 / E4); put_block(r0 % E4);
        } else if (x >= E4) { put4(x / E4); put_block(x % E4); }
        else put4(static_cast<u32>(x));
        chk();
    }

    Writer& operator<<(u32 x) { write_u32(x); return *this; }
    Writer& operator<<(u64 x) { write_u64(x); return *this; }
    Writer& operator<<(int x) { if (x < 0) { *p++ = '-'; write_u32(-static_cast<u32>(x)); } else write_u32(static_cast<u32>(x)); return *this; }
    Writer& operator<<(long long x) { if (x < 0) { *p++ = '-'; write_u64(-static_cast<u64>(x)); } else write_u64(static_cast<u64>(x)); return *this; }
    Writer& operator<<(char c) { *p++ = c; chk(); return *this; }
};

inline Reader in;
inline Writer out;
} // namespace fastio