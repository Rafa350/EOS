#ifndef __eosIntrusiveList__
#define __eosInterusiveList__


namespace eos {
       
    template <typename TItem>
    class IntrusiveListItem {
        
        TItem* next;
        TItem* prev;
        
        TItem* getNext() const {
            
            return next;
        }

        TItem* getPrev() const {
            
            return prev;
        }
    }
    
    templace <typename TItem>
    class IntrusiveList {
        
        TItem* head;
        TItem* tail;
        
        TItem* getHead() cosnt {
            
            return head;
        }
        
        TItem* getTail() const {
            
            return tail;
        }
        
        void addHead(TItem* item) {
            
        }

        void addTail(TItem* item) {
            
        }
        
        void add(TItem* item, TItem* prev, TItem* next) {
            
        }
    }
}


#endif
