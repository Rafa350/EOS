module;


#include "FreeRTOS.h"


export module Eos.System.Core.PoolAllocator;


import Eos.Types;
import Eos.System.Core.CriticalSection;
import Eos.System.Core.HeapAllocator;


namespace eos {

	class Pool final: private NonCopyableClass {
        private:
            uint8_t *_blocks;
            uint8_t *_nextBlock;
            uint32_t _blockSize;
            uint32_t _maxBlocks;
            uint32_t _freeBlocks;
            uint32_t _initializedBlocks;

        public:
            Pool(uint32_t blockSize, uint32_t maxBlocks);
            ~Pool();

            [[nodiscard]] void* allocate();
            void deallocate(void* ptr);

            void* getStoragePtr() const { return _blocks; }
            uint32_t getStorageSize() const { return _blockSize * _maxBlocks; }
            uint32_t getAllocatedSize() const { return (_maxBlocks - _freeBlocks) * _blockSize; }
            uint32_t getAvailableSize() const { return _freeBlocks * _blockSize; }

        private:
            uint8_t* addrFromIndex(uint32_t idx) const;
            uint32_t indexFromAddr(const uint8_t* ptr) const;
    };

}


export namespace eos {

    /// \brief Pool de memoria per un tipus concret d'objecte
    /// \param T_: Tipus d'objecte.
	/// \param numBlocks_: Nombre de blocs disponibles en el pool.
	///
    template <typename T_, uint32_t maxBlocks_>
    class PoolAllocator final {
    	private:
    		Pool _pool;

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

			uint32_t getAllocatedSize() const {
                return _pool.getAllocatedSize();
            }

            uint32_t getAvailableSize() const {
                return _pool.getAvailableSize();
            }
    };

    /// \brief Base pels objectes amb pool de memoria
    /// \param T_: Tipus d'objecte.
	/// \param numBlocks_: Nombre de blocs disponibles en el pool.
    ///
    template <typename T_, uint32_t maxBlocks_>
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

    template <typename T_, uint32_t maxBlocks_>
    PoolAllocator<T_, maxBlocks_> PoolAllocatable<T_, maxBlocks_>::_allocator;
}


/// ---------------------------------------------------------------------------
/// \brief    Constructor.
/// \param    blockSize: Tamany de cada element en bytes.
/// \param    maxBlocks: Numero maxim d'elements.
///
eos::Pool::Pool(
    uint32_t blockSize,
    uint32_t maxBlocks):

    _blockSize {blockSize},
    _maxBlocks {maxBlocks},
    _freeBlocks {maxBlocks},
    _initializedBlocks {0} {

    // Ajusta el tamany minim del block per poder guardar un 'uint32_t'
    //
    if (_blockSize < sizeof(uint32_t))
        _blockSize = sizeof(uint32_t);

    // Ajusta el tamany del bloc per que quedi aliniat
    //
#if portBYTE_ALIGNMENT != 1
	if (blockSize & portBYTE_ALIGNMENT_MASK)
		blockSize += portBYTE_ALIGNMENT - (blockSize & portBYTE_ALIGNMENT_MASK);
#endif

    _blocks = static_cast<uint8_t*>(HeapAllocator::allocate(_blockSize * _maxBlocks));
    _nextBlock = _blocks;
}


/// ---------------------------------------------------------------------------
/// \brief    Destructor.
///
eos::Pool::~Pool() {

    HeapAllocator::deallocate(_blocks);
}


/// ---------------------------------------------------------------------------
/// \brief    Reserva un bloc de memoria.
/// \return   El punter al block.
///
void *eos::Pool::allocate() {

    void *ptr = nullptr;

    CriticalSection::enter();

    if (_initializedBlocks < _maxBlocks) {
        uint32_t *p = reinterpret_cast<uint32_t*>(addrFromIndex(_initializedBlocks));
        _initializedBlocks += 1;
        *p = _initializedBlocks;
    }

    if (_freeBlocks > 0) {
        ptr = static_cast<void*>(_nextBlock);
        _freeBlocks -= 1;
        if (_freeBlocks > 0)
            _nextBlock = addrFromIndex(*(reinterpret_cast<uint32_t*>(_nextBlock)));
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
void eos::Pool::deallocate(
    void *ptr) {

    CriticalSection::enter();

    if (_nextBlock != nullptr)
        *(static_cast<uint32_t*>(ptr)) = indexFromAddr(_nextBlock);
    else
        *(static_cast<uint32_t*>(ptr)) = _maxBlocks;

    _nextBlock = static_cast<uint8_t*>(ptr);
    _freeBlocks += 1;

    CriticalSection::exit();
}


/// ---------------------------------------------------------------------------
/// \brief    Obte l'adressa d'un bloc a partir del seu index.
/// \param    i: El index del bloc.
/// \return   L'adressa del bloc.
///
uint8_t *eos::Pool::addrFromIndex(
    uint32_t idx) const {

    return _blocks + (_blockSize * idx);
}


/// ---------------------------------------------------------------------------
/// \brief    Obte el index d'un bloc a partir de la seva adressa.
/// \param    p: L'adressa del bloc.
/// \return   El index del bloc.
///
uint32_t eos::Pool::indexFromAddr(
    const uint8_t *ptr) const {

    return (ptr - _blocks) / _blockSize;
}
