#ifndef SIPHASHER_H
#define SIPHASHER_H 1

#include <cstdint>

class SipHasher {
    public:
        /**
         * Size of the key that seeds the hasher
         */
        static const int KEY_SIZE = 2;

    private:
        static const int STATE_SIZE = 4;
        static const uint64_t DEFAULT_KEY[SipHasher::KEY_SIZE];
        static const uint64_t INIT_STATE[SipHasher::STATE_SIZE];

        uint64_t key[SipHasher::KEY_SIZE];
        uint64_t state[SipHasher::STATE_SIZE];
        uint64_t length;
        uint64_t tail;
        uint64_t tail_count;

        static void round(uint64_t state[SipHasher::STATE_SIZE]);
        static void c_rounds(uint64_t state[SipHasher::STATE_SIZE]);
        static void d_rounds(uint64_t state[SipHasher::STATE_SIZE]);

    public:
        /**
         * Initialize the hasher with the default key.
         */
        SipHasher();

        /**
         * Initialize the hasher seeded by the given key.
         */
        SipHasher(const uint64_t key[SipHasher::KEY_SIZE]);

        /**
         * Resets the hasher internal state. Useful to compute another hash
         * using the same hasher.
         */
        void reset();

        /**
         * Resets the hasher internal state, and also sets a new key. Useful to
         * compute another hash using the same hasher.
         */
        void reset(const uint64_t key[SipHasher::KEY_SIZE]);

        /**
         * Copies the key into output.
         */
        void get_key(uint64_t output[SipHasher::KEY_SIZE]) const;

        /**
         * Feeds the hasher with the given input byte.
         */
        SipHasher &operator << (unsigned char data);

        /**
         * Returns the final hash based on the internal state, given the fed
         * input data.
         */
        uint64_t finish() const;
};

#endif
