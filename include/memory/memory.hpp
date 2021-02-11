#include <cstddef>
#include <new>

namespace piper {
    #ifndef PIPER_MEMORY_H
    #define PIPER_MEMORY_H

    class Memory {
        public:
            Memory();
            Memory(std::size_t size);

            void *get_chunk_of_size(size_t size);

            ~Memory();
        protected:
        private:
            void *data;
            size_t size;
    };

    #endif

    template<class T> T* allocate(Memory *memory) {
        size_t size = sizeof(T);
        void *addr = memory->get_chunk_of_size(size);

        return new (addr) T();
    }
}