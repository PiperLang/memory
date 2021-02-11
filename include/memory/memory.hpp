#include <cstddef>
#include <new>

#include <iostream>

#define IN_USE (1 << 0)

namespace piper {
    struct block_header {
        size_t size;
        uint8_t flags;
    };

    size_t next_power_of_two(size_t n) {
        size_t p = 1;

        if (n && !(n & (n - 1))) {
            return n;
        }

        while (p < n) {
            p <<= 1;
        }

        return p;
    }

    template<class T> class Memory {
        public:
            Memory() {
                this->data = NULL;
                this->size = 0;
            }

            Memory(std::size_t size) {
                this->data = malloc(size);
                struct block_header *bh = (struct block_header *)this->data;
                bh->size = size;
                bh->flags = 0;
                this->size = size;
            }

            T *get_new() {
                size_t size = sizeof(T);
                void *addr = this->get_chunk_of_size(size);

                return new (addr) T();
            }

            ~Memory() {
                free(this->data);
            }
        protected:
        private:
            void *get_chunk_of_size(size_t size) {
                // Make sure we have enough memory.
                size += sizeof(struct block_header);
                size = next_power_of_two(size);

                void *ptr = this->data;
                while (ptr < ((char *)this->data + this->size)) {
                    std::cout << "Looking at addr: " << ptr << std::endl;
                    struct block_header *bh = (struct block_header *)ptr;
                    if ((bh->flags & IN_USE) == IN_USE) {
                        if (bh->size == 0) {
                            std::cout << "ERROR!" << std::endl;
                            break;
                        }
                        ptr = ((char *)ptr) + bh->size;
                        continue;
                    } else if (bh->size >= size) {
                        size_t old_size = bh->size;
                        bh->size = size;
                        bh->flags = IN_USE;

                        struct block_header *bh2 = (struct block_header *)((char *)ptr + size);
                        bh2->size = old_size - size;
                        bh2->flags = 0;

                        return ((char *)bh) + sizeof(struct block_header);
                    } else {
                        if (bh->size == 0) {
                            std::cout << "ERROR!" << std::endl;
                            break;
                        }
                        ptr = (char *)ptr + bh->size;
                        continue;
                    }
                }

                std::cout << "ERROR" << std::endl;
                return NULL;
            }

            void *data;
            size_t size;
    };
}

#undef IN_USE
