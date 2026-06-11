#ifndef __eosPoolAllocator__
#define	__eosPoolAllocator__


#include "eos.h"
#include "eosAssert.h"
#include "RTOS/rtosPool.h"


namespace eos {

    /// \brief Pool de memoria per un tipus concret d'objecte
    /// \param Type_: Tipus d'objecte.
	/// \param numBlocks_: Nombre de blocs disponibles en el pool.
	///
    template <typename Type_, uint32_t maxBlocks_>
    class PoolAllocator final {
    	private:
    		rtos::Pool _pool;

    	public:
    		PoolAllocator(): _pool(sizeof(Type_), maxBlocks_) { }

    		inline Type_* allocate() { return static_cast<Type_*>(_pool.allocate()); }
    		inline void deallocate(Type_* ptr) { _pool.deallocate(ptr); }
    };

    /// \brief Base pels objectes amb pool de memoria
    /// \param Type_: Tipus d'objecte.
	/// \param numBlocks_: Nombre de blocs disponibles en el pool.
    ///
    template <typename Type_, uint32_t maxBlocks_>
    class PoolAllocatable {
    	private:
    		static PoolAllocator<Type_, maxBlocks_> _allocator;

    	public:
    		virtual ~PoolAllocatable() = default;

        	inline static void* operator new(size_t size) { return _allocator.allocate(); }
        	inline static void operator delete(void *ptr) { _allocator.deallocate(static_cast<Type_*>(ptr)); }
    };

    template <typename Type_, uint32_t maxBlocks_>
    PoolAllocator<Type_, maxBlocks_> PoolAllocatable<Type_, maxBlocks_>::_allocator;
}


#endif // __eosPoolAllocator__


