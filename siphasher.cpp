#include "siphasher.h"

const uint64_t SipHasher::DEFAULT_KEY[SipHasher::KEY_SIZE] = {0, 0};
const uint64_t SipHasher::INIT_STATE[SipHasher::STATE_SIZE] = {
    0x736f6d6570736575,
    0x646f72616e646f6d,
    0x6c7967656e657261,
    0x7465646279746573
};

SipHasher::SipHasher(): SipHasher(SipHasher::DEFAULT_KEY)
{
}

SipHasher::SipHasher(const uint64_t key[SipHasher::KEY_SIZE])
{
    for (int i = 0; i < SipHasher::KEY_SIZE; i++) {
        this->key[i] = key[i];
    }
    this->reset();
}

SipHasher &SipHasher::operator << (unsigned char data)
{
    int needed = 0;
    this->length += 1;

    if (this->tail_count < 7) {
        this->tail |= data << (8 * this->tail_count);
        this->tail_count += 1;
    } else {
        if (this->tail_count == 1) {
            this->tail |= data << (8 * this->tail_count);
            this->state[3] ^= this->tail;
            SipHasher::c_rounds(this->state);
            this->state[0] ^= this->tail;
        }

        this->tail_count -= 7;
        this->tail = data;
    }

    return *this;
}

void SipHasher::reset()
{
    this->length = 0;
    for (int i = 0; i < SipHasher::STATE_SIZE; i++) {
        int index = i % SipHasher::KEY_SIZE;
        this->state[i] = this->key[index] ^ SipHasher::INIT_STATE[i];
    }
    this->tail = 0;
    this->tail_count = 0;
}

uint64_t SipHasher::finish()
{
    uint64_t state[SipHasher::STATE_SIZE];
    for (int i = 0; i < SipHasher::STATE_SIZE; i++) {
        state[i] = this->state[i];
    }

    uint64_t new_tail = this->length << 56 | this->tail;
    state[3] ^= new_tail;
    SipHasher::c_rounds(state);
    state[0] ^= new_tail;
    state[2] ^= 0xFF;
    SipHasher::d_rounds(state);

    uint64_t hash = 0;
    for (int i = 0; i < SipHasher::STATE_SIZE; i++) {
        hash ^= state[i];
    }
    return hash;
}


void SipHasher::round(uint64_t state[SipHasher::STATE_SIZE])
{
    state[0] += state[1];
    state[1] = state[1] << 13 | state[1] >> (64 - 13);
    state[0] ^= state[1];
    state[0] = state[0] << 32 | state[0] >> (64 - 32);
    state[2] += state[3];
    state[3] = state[3] << 16 | state[3] >> (64 - 16);
    state[3] ^= state[2];
    state[0] += state[3];
    state[3] = state[3] << 21 | state[3] >> (64 - 21);
    state[3] ^= state[0];
    state[2] += state[1];
    state[1] = state[1] << 17 | state[1] >> (64 - 17);
    state[1] ^= state[2];
    state[2] = state[2] << 32 | state[2] >> (64 - 32);
}

void SipHasher::c_rounds(uint64_t state[SipHasher::STATE_SIZE])
{
    SipHasher::round(state);
    SipHasher::round(state);
}

void SipHasher::d_rounds(uint64_t state[SipHasher::STATE_SIZE])
{
    SipHasher::round(state);
    SipHasher::round(state);
    SipHasher::round(state);
    SipHasher::round(state);
}