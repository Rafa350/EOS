module;

#include "FreeRTOS.h"


export module Eos.System.Core.PoolAllocator;

import Eos.Types;
import Eos.System.Core.CriticalSection;
import Eos.System.Core.HeapAllocator;


namespace eos::internal {

	class Pool final: private NonCopyableClass {
        private:
            UInt8 *_blocks;
            UInt8 *_nextBlock;
            UInt32 _blockSize;
            UInt32 _maxBlocks;
            UInt32 _freeBlocks;
            UInt32 _initializedBlocks;

        public:
            Pool(UInt32 blockSize, UInt32 maxBlocks);
            ~Pool();

            [[nodiscard]] void* allocate();
            void deallocate(void* ptr);

            void* getStoragePtr() const { return _blocks; }
            UInt32 getStorageSize() const { return _blockSize * _maxBlocks; }
            UInt32 getAllocatedSize() const { return (_maxBlocks - _freeBlocks) * _blockSize; }
            UInt32 getAvailableSize() const { return _freeBlocks * _blockSize; }

        private:
            UInt8* addrFromIndex(UInt32 idx) const;
            UInt32 indexFromAddr(const UInt8* ptr) const;
    };

}


export namespace eos {

    /// \brief Pool de memoria per un tipus concret d'objecte
    /// \param T_: Tipus d'objecte.
	/// \param numBlocks_: Nombre de blocs disponibles en el pool.
	///
    template <typename T_, UInt32 maxBlocks_>
    class PoolAllocator final {
    	private:
    		internal::Pool _pool;

    	public:
    		PoolAllocator():
                _pool(sizeof(T_), maxBlocks_) {
            }

            PoolAllocator(const PoolAllocator&) = delete;

    		[[nodiscard]] T_* allocate() {
                return static_cast<T_*>(_pool.allocate());
            }

            void deallocate(T_* ptr) {
                _pool.deallocate(ptr);
            }

			UInt32 getAllocatedSize() const {
                return _pool.getAllocatedSize();
            }

            UInt32 getAvailableSize() const {
                return _pool.getAvailableSize();
            }
    };

    /// \brief Base pels objectes amb pool de memoria
    /// \param T_: Tipus d'objecte.
	/// \param numBlocks_: Nombre de blocs disponibles en el pool.
    ///
    template <typename T_, UInt32 maxBlocks_>
    class PoolAllocatable {
    	private:
    		static PoolAllocator<T_, maxBlocks_> _allocator;

    	public:
    		virtual ~PoolAllocatable() = default;

        	inline static void* operator new(size_t size) {
                return _allocator.allocate();
            }

            inline static void operator delete(void *ptr) {
                _allocator.deallocate(static_cast<T_*>(ptr));
            }
    };

    template <typename T_, UInt32 maxBlocks_>
    PoolAllocator<T_, maxBlocks_> PoolAllocatable<T_, maxBlocks_>::_allocator;
}


using namespace eos;
using namespace eos::internal;


/// ---------------------------------------------------------------------------
/// \brief    Constructor.
/// \param    blockSize: Tamany de cada element en bytes.
/// \param    maxBlocks: Numero maxim d'elements.
///
Pool::Pool(
    UInt32 blockSize,
    UInt32 maxBlocks):

    _blockSize {blockSize},
    _maxBlocks {maxBlocks},
    _freeBlocks {maxBlocks},
    _initializedBlocks {0} {

    // Ajusta el tamany minim del block per poder guardar un 'UInt32'
    //
    if (_blockSize < sizeof(UInt32))
        _blockSize = sizeof(UInt32);

    // Ajusta el tamany del bloc per que quedi aliniat
    //
#if portBYTE_ALIGNMENT != 1
	if (blockSize & portBYTE_ALIGNMENT_MASK)
		blockSize += portBYTE_ALIGNMENT - (blockSize & portBYTE_ALIGNMENT_MASK);
#endif

    _blocks = static_cast<UInt8*>(HeapAllocator::allocate(_blockSize * _maxBlocks));
    _nextBlock = _blocks;
}


/// ---------------------------------------------------------------------------
/// \brief    Destructor.
///
Pool::~Pool() {

    HeapAllocator::deallocate(_blocks);
}


/// ---------------------------------------------------------------------------
/// \brief    Reserva un bloc de memoria.
/// \return   El punter al block.
///
void *Pool::allocate() {

    void *ptr = nullptr;

    CriticalSection::enter();

    if (_initializedBlocks < _maxBlocks) {
        UInt32 *p = reinterpret_cast<UInt32*>(addrFromIndex(_initializedBlocks));
        _initializedBlocks += 1;
        *p = _initializedBlocks;
    }

    if (_freeBlocks > 0) {
        ptr = static_cast<void*>(_nextBlock);
        _freeBlocks -= 1;
        if (_freeBlocks > 0)
            _nextBlock = addrFromIndex(*(reinterpret_cast<UInt32*>(_nextBlock)));
        else
            _nextBlock = nullptr;
    }

    CriticalSection::exit();

    return ptr;
}


/// ---------------------------------------------------------------------------
/// \brief    Allivera el bloc de memoria.
/// \param    ptr: El puntern al bloc de memoria.
///
void Pool::deallocate(
    void *ptr) {

    CriticalSection::enter();

    if (_nextBlock != nullptr)
        *(static_cast<UInt32*>(ptr)) = indexFromAddr(_nextBlock);
    else
        *(static_cast<UInt32*>(ptr)) = _maxBlocks;

    _nextBlock = static_cast<UInt8*>(ptr);
    _freeBlocks += 1;

    CriticalSection::exit();
}


/// ---------------------------------------------------------------------------
/// \brief    Obte l'adressa d'un bloc a partir del seu index.
/// \param    i: El index del bloc.
/// \return   L'adressa del bloc.
///
UInt8 *Pool::addrFromIndex(
    UInt32 idx) const {

    return _blocks + (_blockSize * idx);
}


/// ---------------------------------------------------------------------------
/// \brief    Obte el index d'un bloc a partir de la seva adressa.
/// \param    p: L'adressa del bloc.
/// \return   El index del bloc.
///
UInt32 Pool::indexFromAddr(
    const UInt8 *ptr) const {

    return (ptr - _blocks) / _blockSize;
}
