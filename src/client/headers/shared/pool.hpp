#pragma once

#include <queue>
#if 0 //Disabled as not needed
namespace intercept {
    template<typename T, std::size_t Size = 1024>
    class game_data_pool {
    public:
        game_data_pool() {
            //for (std::size_t i = 0; i < Size; ++i)
            //    _buy_entry();
        }
        /*
        inline T * acquire() {
            if (_pool_queue.size() == 0)
                _buy_entry();
            T * ret = _pool_queue.front();
            _pool_queue.pop();
            return ret;
        }

        inline void release(T *_ptr) {
            //rv_allocator<T>::deallocate(_ptr);
            //memset((void *)_ptr, 0xcdf3cdde, sizeof(T));
            //_pool_queue.push(_ptr);
        }
        */
        ~game_data_pool() {
            //for (auto entry : _pool)
            //    free(entry);
        }

        game_data_pool(const game_data_pool &) = delete;
        game_data_pool(game_data_pool &&) = delete;
        game_data_pool & operator=(const game_data_pool &) = delete;
        game_data_pool & operator=(game_data_pool &&) = delete;
    protected:
        inline void _buy_entry() {
            void *entry = malloc(sizeof(T));
            _pool_queue.push(reinterpret_cast<T *>(entry));
            _pool.push_back(reinterpret_cast<T *>(entry));
        }

        std::queue<T *> _pool_queue;
        std::vector<T *> _pool;

    };

    template<typename T, std::size_t Size = 1024, std::size_t Alloc_Count = 128>
    class game_data_array_pool {
    public:
        game_data_array_pool() {
            //for (std::size_t i = 0; i < Size; ++i)
            //    _buy_entry(Alloc_Count);
        }
          /*
        inline T * acquire(std::size_t alloc_count_) {
            if (_pool_queue.size() == 0 || alloc_count_ > Alloc_Count)
                _buy_entry(alloc_count_);
            T * ret = _pool_queue.front();
            std::size_t *count = (std::size_t *)((char *)ret - sizeof(std::size_t));
            *count = alloc_count_;
            _pool_queue.pop();
            return ret;
        }

        inline void release(T *_ptr) {
            std::size_t *count = (std::size_t *)((char *)_ptr - sizeof(std::size_t));
            for (std::size_t i = 0; i < *count; ++i)
                _ptr[i].~T();
            *count = 0;
            _pool_queue.push(_ptr);
 
        }
        */
        ~game_data_array_pool() {
            /*
            for (auto entry : _pool) {
                release((T *)(entry + sizeof(std::size_t)));
                free((void *)entry);
            }
            */
        }

        game_data_array_pool(const game_data_array_pool &) = delete;
        game_data_array_pool(game_data_array_pool &&) = delete;
        game_data_array_pool & operator=(const game_data_array_pool &) = delete;
        game_data_array_pool & operator=(game_data_array_pool &&) = delete;
    protected:
        std::queue<T *> _pool_queue;
        std::vector<char *> _pool;

        inline void _buy_entry(std::size_t alloc_count_) {
            //char *entry_data = (char *)malloc((sizeof(T)*alloc_count_) + sizeof(std::size_t));
            //*(std::size_t *)entry_data = alloc_count_;
            //T *entry_addr = (T *)(entry_data + sizeof(std::size_t));
            //for (std::size_t i = 0; i < alloc_count_; ++i)
            //    T *entry = new (entry_addr+i) T();
            //_pool_queue.push(entry_addr);
            //_pool.push_back(entry_data);
        }

    };


}
#endif